
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

    ImVec2 contentSize;

    PdPatchViewController(PdCommonMenus* m);

    xpd::PdLocalServer* pdServer = 0;
    void setPdProcess(xpd::ProcessPtr p);

    bool editMode = true;

    virtual void draw() override;

    ObjectBase* createObject(std::string text, int x, int y);
    void connectObjects(ObjectBase* outObj, int outIdx, ObjectBase* inObj, int inIdx);
    void connectObjectsByIndices(int outObjIdx, int outletIdx, int inObjIdx, int inletIdx);

    // ===============

    IUAction autocomplete = IUAction([this] {

        ImGui::SetCursorPos(ImVec2(this->autocomplete.sender->x, this->autocomplete.sender->y + 10));

        ImGui::BeginChildFrame(ImGui::GetID("##autocomplete"), ImVec2(150, 100));

        UIObject* b = (UIObject*)autocomplete.sender;

        for (auto s : data.canvas->availableObjects()) {
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

    IUAction objectUpdated = IUAction([this] {

        UIObject* o = (UIObject*)objectUpdated.sender;

        // test
        //        if (o)
        //            addObject(o->objectText, o->x,o->y);

        if (!o->pdObject) {
            o->pdObjectID = data.canvas->createObject(o->objectText.c_str(), o->x, o->y);
            o->pdObject = (xpd::PdObject*)const_cast<xpd::Object*>(data.canvas->objects().findObject(o->pdObjectID));

            o->data.errorBox = (o->pdObject == 0);

            o->updateFromPdObject();

            //            if (o->pdObject) {
            //                o->inletCount = o->pdObject->inletCount();
            //                o->outletCount = o->pdObject->outletCount();
            //                std::string info = o->objectText + " ins: " + std::to_string(o->inletCount) + " outs:" + std::to_string(o->outletCount);
            //                }
            data.pdProcess->post(o->objectText + " ins: " + std::to_string(o->inletCount) + " outs:" + std::to_string(o->outletCount));
        }

        // todo replace

        //        if (text.size())
        //            n->pdObjectID = data.canvas->createObject(text, x, y);
        //        else
        //            n->emptyBox = true;

    });

    IUAction objectCreated = IUAction([this] {

        UIObject* o = (UIObject*)objectCreated.sender;

        data.pdProcess->post(("created: " + o->objectText).c_str());

        // test
        if (o)
            createObject(o->objectText, o->x, o->y);

        _emptyObject.hidden = true;

    });

    //

    IUAction outletClicked = IUAction([this] {
        ObjectBase* b = (ObjectBase*)outletClicked.sender;
        _newPatchcord.outputObj = b;
        _newPatchcord.outputIdx = b->data.outletClicked;
        _newPatchcord.inputObj = 0;

    });

    IUAction inletHovered = IUAction([this] {
        // hovered
        ObjectBase* b = (ObjectBase*)inletClicked.sender;
        if (b == _newPatchcord.outputObj)
            return;
        _newPatchcord.inputObj = b;
        _newPatchcord.inputIdx = b->data.inletClicked;
    });

    IUAction inletClicked = IUAction([this] {

        // hovered
        ObjectBase* b = (ObjectBase*)inletClicked.sender;
        if (b == _newPatchcord.outputObj)
            return;
        connectObjects(_newPatchcord.outputObj, _newPatchcord.outputIdx, b, b->data.inletClicked);

        _newPatchcord.outputObj = 0;
    });

    IUAction editModeAction = IUAction([this]() {
        editMode = !editMode;
    });

    IUAction deleteObjectAction = IUAction([this]() {

    });

    // ----------

    IUAction menuSaveAction = IUAction([this]() {
        nfdchar_t* f = new nfdchar_t[1024];

        if (NFD_SaveDialog("pd", "~/", &f) == NFD_OKAY) {
            FileSaver::save(f, &data);
        }

    });

    IUAction menuSaveAsAction = IUAction([this]() {
        nfdchar_t* f = new nfdchar_t[1024];

        if (NFD_SaveDialog("pd", "~/", &f) == NFD_OKAY) {
            FileSaver::save(f, &data);
        }
    });

    // ----------

    IUAction menuCutAction = IUAction([this]() {
        data.cut();
    });

    IUAction menuCopyAction = IUAction([this]() {
        data.copy();
    });

    IUAction menuPasteAction = IUAction([this]() {
        data.paste();
    });

    IUAction menuSelectAllAction = IUAction([this]() {
        data.selectAllObjects();
    });

    IUAction menuDeleteObjectAction = IUAction([this]() {
        data.deleteSelectedObjects();
    });

    // ----------

    IUAction arrangeLeftAction;
    IUAction arrangeCenterAction;
    IUAction arrangeRightAction;
    IUAction arrangeTopAction;
    IUAction arrangeBottomAction;
    IUAction arrangeDHAction;
    IUAction arrangeDVAction;

    // ----------

    bool hitObject(ImVec2 pos);

    void selectSingleObject(ImVec2 pos);
    bool selectObjects();
    void deselectAll();

    void dragSelectedObjects(ImVec2 delta);

    void resizeToObjects()
    {
        int w = 0;
        int h = 0;

        for (auto o : data.objects) {
            if (w < (o->x + o->width))
                w = o->x + o->width;
            if (h < (o->y + o->height))
                h = o->y + o->height;
        }

        contentSize.x = (width > w) ? width : w;
        contentSize.y = (height > h) ? height : h;
    };

    void loadbang()
    {
        data.canvas->loadbang();
    }
};

#endif /* AppController_hpp */
