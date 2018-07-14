
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

#include "Grid.hpp"

#include "Preferences.h"

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
    UiObjectBase* _movingObject = 0;

    //
    inline void _drawGrid();
    inline void _drawSelectionFrame();
    inline void _drawObjectMaker();

    //
    UndoStack _undoStack;

    //
    void _attachArrangeMenu();
    void _attachPutMenu();

    Grid _grid;

    UIPropertiesWindow _preferencesWindow;
    UIPropertiesWindow _audioSettingsWindow;
    bool displayPreferences = false;
    bool displayAudioSettings = false;

public:
    CanvasData data;

    PdPatchViewController(PdCommonMenus* m);

    xpd::PdLocalServer* pdServer = 0;
    void setPdProcess(xpd::ProcessPtr p, xpd::CanvasPtr cnv = 0);

    bool editMode = true;

    virtual void draw() override;
    virtual void _drawContents() override;

    UiObjectBase* createObject(std::string text, int x, int y);
    void connectObjects(UiObjectBase* outObj, int outIdx, UiObjectBase* inObj, int inIdx);
    void connectObjectsByIndices(int outObjIdx, int outletIdx, int inObjIdx, int inletIdx);

    // ===============
    // object actions

    IU_ACTION(autocomplete)
    IU_ACTION(objectUpdated)
    IU_ACTION(objectCreated)
    IU_ACTION(outletClicked)
    IU_ACTION(inletHovered)
    IU_ACTION(inletClicked)

    IU_ACTION(openCanvas)
    IU_ACTION(showHelpPatch);

public:
    // --------------------

    IU_ACTION(menuSaveAction)
    IU_ACTION(menuSaveAsAction)

    // ----------

    IU_ACTION(menuCutAction);
    IU_ACTION(menuCopyAction);
    IU_ACTION(menuPasteAction);
    IU_ACTION(menuSelectAllAction);
    IU_ACTION(menuDeleteObjectAction);

    IU_ACTION(editModeAction);

    // ---

    IU_ACTION(menuPreferences);
    IU_ACTION(menuAudioSettings);

    // ----------

    IUAction arrangeDHAction;
    IUAction arrangeDVAction;

    IU_ACTION(arrangeLeftAction);
    IU_ACTION(arrangeCenterAction);
    IU_ACTION(arrangeRightAction);
    IU_ACTION(arrangeTopAction);
    IU_ACTION(arrangeBottomAction);

    // -----

    IU_ACTION(zoomIn);
    IU_ACTION(zoomOut);
    IU_ACTION(zoomOne);

    // ----------

    IU_ACTION(putObject);
    IU_ACTION(putMessage);
    IU_ACTION(putComment);

    IU_ACTION(putBang);
    IU_ACTION(putToggle);
    IU_ACTION(putNumber);

    // ----------

    bool hitObject(ImVec2 pos);

    void selectSingleObject(ImVec2 pos);
    bool selectObjects();
    void deselectAll();

    void dragSelectedObjects(ImVec2 delta);

    void resizeToObjects();
    void loadbang();

    //

    virtual void onMouseDown(ImVec2 pos) override;
    virtual void onMouseDoubleClick(ImVec2 pos) override;
    virtual void onMouseDrag(ImVec2 pos) override;
    virtual void onMouseUp(ImVec2 pos) override;
    virtual void onMouseHover(ImVec2 pos) override;

    //
    static const int oNewCanvasWindow = 100;
    static const int oOpenHelpPatch = 200;
};

#endif /* AppController_hpp */
