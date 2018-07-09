
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

#include "UIObject.hpp"
#include "UIPatchcord.hpp"

#include "NewConnection.hpp"

#include "math.h"

#include "PdPatchMenu.hpp"
#include "UIObjectFactory.h"

#include "UndoStack.hpp"

#include "nfd.h"

#include "CanvasData.h"

#include "FileSaver.h"

#include "IUAction.hpp"

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

    virtual void drawMenu() override;
    PdPatchMenu _patchMenu;

    UIObject _emptyObject;
    UIObject* _movingObject = 0;

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
    virtual void drawLayerContents() override;

    UiObjectBase* createObject(std::string text, int x, int y);
    void connectObjects(UiObjectBase* outObj, int outIdx, UiObjectBase* inObj, int inIdx);
    void connectObjectsByIndices(int outObjIdx, int outletIdx, int inObjIdx, int inletIdx);

    // ===============

    IU_ACTION(autocomplete)
    IU_ACTION(objectUpdated)
    IU_ACTION(objectCreated)
    IU_ACTION(outletClicked)
    IU_ACTION(inletHovered)
    IU_ACTION(inletClicked)

public:
    IUAction editModeAction = IUAction([this]() {
        editMode = !editMode;
    });

    // --------------------

    IU_ACTION(menuSaveAction)
    IU_ACTION(menuSaveAsAction)

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

    // -----

    IU_ACTION(zoomIn);
    IU_ACTION(zoomOut);
    IU_ACTION(zoomOne);

    // ----------

    bool hitObject(ImVec2 pos);

    void selectSingleObject(ImVec2 pos);
    bool selectObjects();
    void deselectAll();

    void dragSelectedObjects(ImVec2 delta);

    void resizeToObjects();
    void loadbang();
};

#endif /* AppController_hpp */
