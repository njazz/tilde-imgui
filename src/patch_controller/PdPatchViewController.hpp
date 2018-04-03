
//
//  AppController.hpp
//  imguiController
//
//  Created by Alex on 22/03/2018.
//

#ifndef PdPatchViewController_hpp
#define PdPatchViewController_hpp

#include "IUViewController.hpp"
#include "imgui.h"

#include "pd_localprocess.h"
#include "pd_localserver.h"

#include "UiObjects/UIObject.hpp"
#include "UiObjects/UIPatchcord.hpp"

#include "views/NewConnection.hpp"

#include "math.h"

#include "UiObjects/UIObjectFactory.h"
#include "menus/PdPatchMenu.hpp"

#include "undo/UndoStack.hpp"

#include "nfd.h"

#include "data_models/CanvasData.h"

#include "file_io/FileSaver.h"

class PdPatchViewController : public IUViewController {

    xpd::CanvasPtr _canvas;
    xpd::ProcessPtr _pdProcess = 0;

    //    std::vector<ObjectBase*> _objects;
    //    std::vector<UIPatchcord*> _patchcords;

    NewConnection _newPatchcord;

    ImVec2 _selectionStart;
    ImVec2 _selectionEnd;
    bool _selectionFrame = false;
    bool _draggingObjects = false;
    bool _clickedObject = false;
    bool _multipleObjectsSelected = false;

    void _drawMenu();
    PdPatchMenu _menu;

    UIObject _emptyObject;

    //
    inline void _drawGrid();
    inline void _drawSelectionFrame();
    inline void _drawObjectMaker();

    //
    UndoStack _undoStack;

public:
    CanvasData data;

    PdPatchViewController(PdCommonMenus* m);

    xpd::PdLocalServer* pdServer = 0;
    void setPdProcess(xpd::ProcessPtr p);

    bool editMode = true;

    virtual void draw() override;

    ObjectBase* createObject(std::string text, int x, int y);
    void connectObjects(ObjectBase* outObj, int outIdx, ObjectBase* inObj, int inIdx);
    void connectObjectsByIndices(int outObjIdx, int outletIdx, int inObjIdx, int inletIdx);

    // ===============

    IUObserver autocomplete = IUObserver([this] {

        ImGui::SetCursorPos(ImVec2(this->autocomplete.sender->x, this->autocomplete.sender->y + 10));

        ImGui::BeginChildFrame(ImGui::GetID("##autocomplete"), ImVec2(150, 100));

        UIObject* b = (UIObject*)autocomplete.sender;

        for (auto s : _canvas->availableObjects()) {
            if (strncmp(b->enteredText.c_str(), s.c_str(), b->enteredText.size()) == 0)
                if (ImGui::MenuItem(s.c_str())) {
                    //printf(">>>\n");
                    b->objectText = s;
                    b->finishedEditingText();
                    ImGui::EndChildFrame();
                    return;
                }
        }
        ImGui::EndChildFrame();

    });

    IUObserver objectUpdated = IUObserver([this] {

        UIObject* o = (UIObject*)objectUpdated.sender;

        // test
        //        if (o)
        //            addObject(o->objectText, o->x,o->y);

        if (!o->pdObject) {
            o->pdObjectID = _canvas->createObject(o->objectText.c_str(), o->x, o->y);
            o->pdObject = (xpd::PdObject*)const_cast<xpd::Object*>(_canvas->objects().findObject(o->pdObjectID));

            o->errorBox = (o->pdObject == 0);

            o->updateFromPdObject();

            //            if (o->pdObject) {
            //                o->inletCount = o->pdObject->inletCount();
            //                o->outletCount = o->pdObject->outletCount();
            //                std::string info = o->objectText + " ins: " + std::to_string(o->inletCount) + " outs:" + std::to_string(o->outletCount);
            //                }
            _pdProcess->post(o->objectText + " ins: " + std::to_string(o->inletCount) + " outs:" + std::to_string(o->outletCount));
        }

        // todo replace

        //        if (text.size())
        //            n->pdObjectID = _canvas->createObject(text, x, y);
        //        else
        //            n->emptyBox = true;

    });

    IUObserver objectCreated = IUObserver([this] {

        UIObject* o = (UIObject*)objectCreated.sender;

        _pdProcess->post(("created: " + o->objectText).c_str());

        // test
        if (o)
            createObject(o->objectText, o->x, o->y);

        _emptyObject.hidden = true;

    });

    //

    IUObserver outletClicked = IUObserver([this] {
        ObjectBase* b = (ObjectBase*)outletClicked.sender;
        _newPatchcord.outputObj = b;
        _newPatchcord.outputIdx = b->outletClicked;
        _newPatchcord.inputObj = 0;

    });

    IUObserver inletHovered = IUObserver([this] {
        // hovered
        ObjectBase* b = (ObjectBase*)inletClicked.sender;
        if (b == _newPatchcord.outputObj)
            return;
        _newPatchcord.inputObj = b;
        _newPatchcord.inputIdx = b->inletClicked;
    });

    IUObserver inletClicked = IUObserver([this] {

        // hovered
        ObjectBase* b = (ObjectBase*)inletClicked.sender;
        if (b == _newPatchcord.outputObj)
            return;
        connectObjects(_newPatchcord.outputObj, _newPatchcord.outputIdx, b, b->inletClicked);

        _newPatchcord.outputObj = 0;
    });

    IUObserver editModeAction = IUObserver([this]() {
        editMode = !editMode;
    });

    IUObserver deleteObjectAction = IUObserver([this]() {

    });

    // ----------

    IUObserver menuSaveAction = IUObserver([this]() {
        nfdchar_t* f = new nfdchar_t[1024];

        if (NFD_SaveDialog("pd", "~/", &f) == NFD_OKAY) {
            FileSaver::save(f, &data);
        }

    });

    IUObserver menuSaveAsAction = IUObserver([this]() {
        nfdchar_t* f = new nfdchar_t[1024];

        if (NFD_SaveDialog("pd", "~/", &f) == NFD_OKAY) {
            FileSaver::save(f, &data);
        }
    });

    // ----------

    IUObserver menuCutAction = IUObserver([this]() {
        data.cut();
    });

    IUObserver menuCopyAction = IUObserver([this]() {
        data.copy();
    });

    IUObserver menuPasteAction = IUObserver([this]() {
        data.paste();
    });

    // ----------

    IUObserver arrangeLeftAction;
    IUObserver arrangeCenterAction;
    IUObserver arrangeRightAction;
    IUObserver arrangeTopAction;
    IUObserver arrangeBottomAction;
    IUObserver arrangeDHAction;
    IUObserver arrangeDVAction;

    bool hitObject(ImVec2 pos);

    void selectSingleObject(ImVec2 pos);
    bool selectObjects();
    void deselectAll();

    void dragSelectedObjects(ImVec2 delta);

    void resizeToObjects(){};

    void loadbang()
    {
        _canvas->loadbang();
    }
};

#endif /* AppController_hpp */
