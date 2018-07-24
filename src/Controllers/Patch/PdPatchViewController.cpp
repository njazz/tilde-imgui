
//
//  PdPatchViewController.cpp
//  imguiController
//
//  Created by Alex on 22/03/2018.
//

#include "PdPatchViewController.hpp"
#include "AppController.hpp"
#include "ArrangeObjects.h"
#include "imgui_internal.h"

#include "nfd.h"

#include "math.h"

PdPatchViewController::PdPatchViewController(PdCommonMenus* m)
    : _patchMenu(m)
    , _preferencesWindow(AppController::preferences(), &displayPreferences)
    , _audioSettingsWindow(AppController::audioMIDISettings(), &displayAudioSettings)

{
    //
    _grid.editModeFlag = &editMode;
    _grid.gridStep = &data.gridStep;
    _grid.showGrid = &data.showGrid;
    addSubview(&_grid);

    menu = &_patchMenu;

    _emptyObject.addAction(UIObject::oObjectChanged, &objectCreated);
    _emptyObject.addAction(UIObject::oAutocomplete, &autocomplete);
    _emptyObject.hidden = true;
    addSubview(&_emptyObject);

    //
    _attachPatchMenu();
    _attachArrangeMenu();
    _attachPutMenu();

    mouseEnabled = true;

    //    addComponent(&_preferencesWindow);
}

void PdPatchViewController::setPdProcess(xpd::ProcessPtr p, xpd::CanvasPtr cnv)
{
    data.pdProcess = p;

    if (data.pdProcess && !cnv)
        data.canvas = data.pdProcess->createCanvas();
    else
        data.canvas = cnv;
    /*
    // test
    createObject("print", 300, 300);

    createObject("pack 0 0 0", 300, 200);
    createObject("unpack 0 0 0 0 0", 300, 250);

    createObject("+", 300, 150);

    auto o1 = createObject("osc~ 440", 50, 150);
    auto o2 = createObject("dac~ 1 2", 50, 300);
    connectObjects(o1, 0, o2, 0);
    connectObjects(o1, 0, o2, 1);

    createObject("ui.toggle", 100, 100);
    createObject("ui.bang", 100, 150);
    createObject("ui.msg", 100, 200);
    createObject("ui.float", 100, 250);
    */
}

void PdPatchViewController::drawMenu()
{
    _patchMenu.setWindowController(windowController());
    _patchMenu.common->setWindowController(windowController());
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4, 4));
    IUViewController::drawMenu();
    ImGui::PopStyleVar();
}

void PdPatchViewController::_drawGrid()
{
    // grid
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 scrolling;

    ImGui::SetCursorPos(ImVec2(0, 0));
    ImGui::SetNextWindowBgAlpha(0);
    ImGui::BeginChild(ImGui::GetID("grid"));
    if (editMode && data.showGrid) {
        ImU32 GRID_COLOR = IM_COL32(200, 200, 200, 40);
        float GRID_SZ = data.gridStep; //30.0f;

        offset = ImGui::GetCursorScreenPos();
        ImVec2 win_pos = offset; // - ImVec2(0, 0);
        ImVec2 canvas_sz = ImVec2(contentSize.x, contentSize.y - 20); //ImGui::GetWindowSize();

        for (float x = fmodf(scrolling.x, GRID_SZ); x < contentSize.x; x += GRID_SZ)
            draw_list->AddLine(ImVec2(x, 0.0f) + win_pos, ImVec2(x, contentSize.y - 20) + win_pos, GRID_COLOR);
        for (float y = fmodf(scrolling.y, GRID_SZ); y < contentSize.y - 20; y += GRID_SZ)
            draw_list->AddLine(ImVec2(0.0f, y) + win_pos, ImVec2(contentSize.x, y) + win_pos, GRID_COLOR);
    }
    ImGui::EndChild();
    ImGui::SetCursorPos(ImVec2(0, 0));
}

void PdPatchViewController::_drawSelectionFrame()
{
    // selection frame

    if (ImGui::IsMouseClicked(0) && editMode) {

        _clickedObject = data.objectAtPos(ImGui::GetMousePos()); //&& !_selectionFrame;

        if (_clickedObject && !_multipleObjectsSelected && !_draggingObjects) {
            data.selectSingleObject(ImGui::GetMousePos());
            _multipleObjectsSelected = false;
            _draggingObjects = true;
        }
        _draggingObjects = _clickedObject;

        if (!data.objectAtPos(ImGui::GetMousePos()) && !_draggingObjects && (ImGui::GetMousePos().y > 20)) {
            printf("pos %f\n", ImGui::GetMousePos().y);

            data.deselectAll();
            _multipleObjectsSelected = false;
            _draggingObjects = false;
        }

        if (!data.objectAtPos(ImGui::GetMousePos()) && !_draggingObjects) {

            _selectionStart = _selectionEnd = ImGui::GetMousePos();
            _selectionFrame = true;
        }
    }

    if (_selectionFrame && !ImGui::IsMouseReleased(0)) {
        bool b = data.selectObjectsInFrame(_selectionStart, _selectionEnd);
        _multipleObjectsSelected = b;
    }
}

void PdPatchViewController::_drawObjectMaker()
{
    // new empty object
    if (ImGui::IsMouseDoubleClicked(0) && editMode) {
        if (!data.objectAtPos(ImGui::GetIO().MousePos)) {
            //addObject("", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
            _emptyObject.x = (ImGui::GetIO().MousePos.x);
            _emptyObject.y = (ImGui::GetIO().MousePos.y);
            _emptyObject.data.emptyBox = true;
            _emptyObject.data.errorBox = true;
            _emptyObject.data.pdObject = 0;
            _emptyObject.data.pdObjectID = 0;
            _emptyObject.objectText = "";
            _emptyObject.hidden = false;
            _emptyObject.clearEditText();
        }
    }
}

void PdPatchViewController::draw()
{
    //ImGui::SetNextWindowSize(ImVec2(width, height - 20));

    // todo
    //    ImGui::GetIO().FontAllowUserScaling = true;

    // temporary!
    resizeContentsToObjects();

    x = 0;
    y = 22;

    width = windowController()->width / 2;
    height = windowController()->height / 2; // - 22;

    bool w = true;

    title = "patch";
    flags = flags | ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus;

    manualLayout = true;

    padding = 0;
    //contentSize = ImVec2(1024,1024);

    _grid.width = width;
    _grid.height = height;
    _grid.contentSize = ImVec2(width, height);

    IUViewController::draw();

    _preferencesWindow._drawContents();
    _audioSettingsWindow._drawContents();
};

void PdPatchViewController::_drawContents()
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    /// \todo use IULayer
    ImGui::SetCursorPos(ImVec2(0, -22));

    //_drawGrid();

    //ImGui::SetTooltip("content size %f %f",contentSize.x,contentSize.y);

    //    ImGui::SetCursorPos(ImVec2(0, -22));
    //for (auto s: _subviews)
    //    s->updateOffset();

    //    _drawSelectionFrame();

    //    if (ImGui::IsMouseDragging()) {
    //        if (_draggingObjects) {
    //            dragSelectedObjects(ImGui::GetIO().MouseDelta);
    //        } else {
    //            _selectionFrame &= true;
    //            _selectionEnd = ImGui::GetMousePos();
    //        }
    //    }

    //
    //ImGui::SetCursorPos(ImVec2(0,0));
    //IULayer::draw();

    if (_selectionFrame) {
        draw_list->AddRectFilled(_selectionStart, _selectionEnd, IM_COL32(0, 168, 192, 128));
    }

    //    if (ImGui::IsMouseReleased(0)) {
    //        //        printf("up\n");
    //        _selectionFrame = false;
    //        _draggingObjects = false;
    //    }

    //
    ImVec2 pos = ImGui::GetMousePos();

    _newPatchcord.inputX = pos.x;
    _newPatchcord.inputY = pos.y;
    //ImGui::SetTooltip("pos %f %f",pos.x,pos.y);

    _newPatchcord.draw();

    //ImGui::End();

    //    _drawObjectMaker();

    //    // deselect patchcord
    //    if (ImGui::IsMouseClicked(0)) {
    //        if (!hitObject(ImGui::GetIO().MousePos)) {
    //            _newPatchcord.outputObj = 0;
    //        }
    //    }
}

UiObjectBase* PdPatchViewController::createObject(std::string text, int x, int y)
{
    if (!data.pdProcess)
        return 0;

    UiObjectBase* n = UIObjectFactory::createUiObject(text); //new NodeObject;
    if (!n)
        return 0;

    n->objectText = text;
    n->x = (x);
    n->y = (y);

    if (text.size())
        n->data.pdObjectID = data.canvas->createObject(text, x, y);

    n->data.pdObject = (xpd::PdObject*)const_cast<xpd::Object*>(data.canvas->objects().findObject(n->data.pdObjectID));
    n->width = 90;

    //    if (!n->pdObject)
    //        return 0;

    //    if (n->pdObject) {
    //        n->inletCount = n->pdObject->inletCount();
    //        n->outletCount = n->pdObject->outletCount();
    //
    //
    n->updateFromPdObject();

    //std::string info = text + " ins: " + std::to_string(n->data.inletCount) + " outs:" + std::to_string(n->data.outletCount);
    //data.pdProcess->post(info + "\n");

    addSubview(n);
    n->editModePtr = &editMode;

    //    data.objects.push_back(n);

    data.addObject(n);

    n->addAction(UIObject::oAutocomplete, &autocomplete);
    n->addAction(UIObject::oObjectChanged, &objectUpdated);
    n->addAction(UiObjectBase::oInletClicked, &inletClicked);
    n->addAction(UiObjectBase::oInletHovered, &inletHovered);
    n->addAction(UiObjectBase::oOutletClicked, &outletClicked);
    n->addAction(UiObjectBase::oOpenCanvas, &openCanvas);
    n->addAction(UiObjectBase::oOpenHelp, &showHelpPatch);

//    if (n->data.pdObject) {
//        n->data.pdObject->registerObserver(xpd::ObserverPtr(&n->observer));
//        n->data.isAbstraction = n->data.pdObject->PdObject::isAbstraction();
//        n->data.isCanvas = n->data.pdObject->PdObject::isCanvas();

//        printf("new obj abs %i cnv %i\n", n->data.pdObject->PdObject::isAbstraction(), n->data.pdObject->PdObject::isCanvas());
//    }
    return n;
}

void PdPatchViewController::connectObjects(UiObjectBase* outObj, int outIdx, UiObjectBase* inObj, int inIdx)
{
    UIPatchcord* c = new UIPatchcord;
    c->outputObj = outObj;
    c->outputIdx = outIdx;
    c->inputObj = inObj;
    c->inputIdx = inIdx;

    data.canvas->connect(outObj->data.pdObjectID, outIdx, inObj->data.pdObjectID, inIdx);

    addSubview(c);
    data.addPatchcord(c);
}

void PdPatchViewController::connectObjectsByIndices(int outObjIdx, int outletIdx, int inObjIdx, int inletIdx)
{
    UiObjectBase* obj1 = data.getObjectByIndex(outObjIdx);
    UiObjectBase* obj2 = data.getObjectByIndex(inObjIdx);

    if (!obj1 || !obj2) {
        printf("object not found - could not connect");
        return;
    }

    /// \todo correct error object connections handling
    if (outletIdx >= obj1->data.outletCount)
        return;
    if (inletIdx >= obj2->data.inletCount)
        return;

    if (!obj1->data.errorBox && !obj2->data.errorBox) {
        printf("patchcord\n");
        connectObjects(obj1, outletIdx, obj2, inletIdx);
    }
}

void PdPatchViewController::dragSelectedObjects(ImVec2 delta)
{
    if (_selectionFrame)
        return;
    for (auto o : data.objects) {
        UIObject* obj = (UIObject*)o;
        if (obj->data.selected) {
            o->x = (o->x + delta.x);
            o->y = (o->y + delta.y);
        }
    }
}

//void PdPatchViewController::deselectAll()
//{
//    data.deselectObjects();
//    data.deselectPatchcords();

//    _multipleObjectsSelected = false;
//    _draggingObjects = false;
//}

//bool PdPatchViewController::data.objectAtPos(ImVec2 pos)
//{
//    bool ret = false;
//    for (auto o : data.objects) {
//        UIObject* obj = (UIObject*)o;

//        bool hit;
//        hit = (obj->x <= pos.x);
//        hit &= (obj->y <= pos.y);
//        hit &= (obj->x + obj->width >= pos.x);
//        hit &= (obj->y + obj->height >= pos.y);

//        ret |= hit;
//    }
//    return ret;
//}

//bool PdPatchViewController::selectObjects()
//{
//    return data.selectObjectsInFrame(_selectionStart, _selectionEnd);
//}

// ==========

inline void PdPatchViewController::_autocomplete()
{
    ImGui::SetCursorPos(ImVec2(this->autocomplete.sender->x, this->autocomplete.sender->y + 10));

    //ImGui::BeginPopup()
    if //(ImGui::BeginPopupEx(ImGui::GetCurrentContext()->CurrentWindow->GetID("_autocomplete"), ImGuiWindowFlags_NoCollapse & ImGuiWindowFlags_NoFocusOnAppearing)){
        (ImGui::BeginChildFrame(ImGui::GetID("##autocomplete"), ImVec2(150, 100))) {
        UIObject* b = (UIObject*)autocomplete.sender;

        for (auto s : data.canvas->availableObjects()) {
            if (strncmp(b->enteredText.c_str(), s.c_str(), b->enteredText.size()) == 0)
                if (ImGui::MenuItem(s.c_str())) {
                    printf(">>> %s\n", s.c_str());
                    b->objectText = s;
                    auto t = b->_editText;
                    b->_editText = const_cast<char*>(s.c_str());
                    b->finishedEditingText();
                    b->_editText = t;
                    b->_editText[0] = '\0';
                    ImGui::EndChildFrame();
                    //ImGui::EndMenu();
                    return;
                }
        }

        //ImGui::EndPopup();
        ImGui::EndChildFrame();
    }
}

inline void PdPatchViewController::_objectUpdated()
{
    UIObject* o = (UIObject*)objectUpdated.sender;

    // test
    //        if (o)
    //            addObject(o->objectText, o->x,o->y);

    if (!o->data.pdObject) {
        o->data.pdObjectID = data.canvas->createObject(o->objectText.c_str(), o->x, o->y);
        o->data.pdObject = (xpd::PdObject*)const_cast<xpd::Object*>(data.canvas->objects().findObject(o->data.pdObjectID));

        o->data.errorBox = (o->data.pdObject == 0);

        o->updateFromPdObject();

        //            if (o->pdObject) {
        //                o->inletCount = o->pdObject->inletCount();
        //                o->outletCount = o->pdObject->outletCount();
        //                std::string info = o->objectText + " ins: " + std::to_string(o->inletCount) + " outs:" + std::to_string(o->outletCount);
        //                }
        data.pdProcess->post(o->objectText + " ins: " + std::to_string(o->data.inletCount) + " outs:" + std::to_string(o->data.outletCount));
    }

    // todo replace

    //        if (text.size())
    //            n->pdObjectID = data.canvas->createObject(text, x, y);
    //        else
    //            n->emptyBox = true;
}

inline void PdPatchViewController::_objectCreated()
{
    UIObject* o = (UIObject*)objectCreated.sender;

    if (o)
        data.pdProcess->post(("created: " + o->objectText + "\n").c_str());

    // test
    if (o)
        createObject(o->objectText, o->x, o->y);

    _emptyObject.hidden = true;
}

// ---------------

inline void PdPatchViewController::_outletClicked()
{
    UiObjectBase* b = (UiObjectBase*)outletClicked.sender;
    _newPatchcord.outputObj = b;
    _newPatchcord.outputIdx = b->data.outletClicked;
    _newPatchcord.inputObj = 0;
}

inline void PdPatchViewController::_inletHovered()
{
    UiObjectBase* b = (UiObjectBase*)inletClicked.sender;
    if (b == _newPatchcord.outputObj)
        return;
    _newPatchcord.inputObj = b;
    _newPatchcord.inputIdx = b->data.inletClicked;
}

inline void PdPatchViewController::_inletClicked()
{
    UiObjectBase* b = (UiObjectBase*)inletClicked.sender;
    if (!_newPatchcord.outputObj)
        return;
    if (b == _newPatchcord.outputObj)
        return;
    connectObjects(_newPatchcord.outputObj, _newPatchcord.outputIdx, b, b->data.inletClicked);

    _newPatchcord.outputObj = 0;
}

inline void PdPatchViewController::_openCanvas()
{
    UiObjectBase* b = (UiObjectBase*)inletClicked.sender;

    auto cnv = b->data.pdObject->asPdCanvas();

    setUserObjectForAction(oNewCanvasWindow, (void*)cnv);

    printf("open abstraction: %lu\n", (long)cnv);

    updated(oNewCanvasWindow);

    windowController()->restoreContext();
}

void PdPatchViewController::_showHelpPatch()
{
    UiObjectBase* b = (UiObjectBase*)inletClicked.sender;

    auto d = b->data.pdObject->helpDir();
    auto f = b->data.pdObject->helpFilename();

    printf("help file: %s/%s", d.c_str(), f.c_str());

    updated(oOpenHelpPatch);
}

// --------------

void PdPatchViewController::_menuSaveAction()
{
    nfdchar_t* f = new nfdchar_t[1024];

    if (NFD_SaveDialog("pd", "~/", &f) == NFD_OKAY) {
        FileSaver::save(f, &data);
    }
}

void PdPatchViewController::_menuSaveAsAction()
{
    nfdchar_t* f = new nfdchar_t[1024];

    if (NFD_SaveDialog("pd", "~/", &f) == NFD_OKAY) {
        FileSaver::save(f, &data);
    }
}

// --------------

void PdPatchViewController::resizeContentsToObjects()
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

    _grid.contentSize = contentSize;
};

void PdPatchViewController::loadbang()
{
    data.canvas->loadbang();
}

// -----

void PdPatchViewController::_zoomIn()
{
    printf("zoom in\n");
    //ImGui::SetWindowFontScale(1.5);

    //    zoomable = true;
    scale = 1.5;

    //    for (auto c:_components)
    //        c->zoomable = true;

    //    zoomable = true;
}

void PdPatchViewController::_zoomOut()
{
    printf("zoom out\n");
    //    ImGui::SetWindowFontScale(0.5);

    //    zoomable = true;
    //    _grid.setScale(0.5);

    //    for (auto c:_components)
    //        c->zoomable = true;

    //    zoomable = true;
}

void PdPatchViewController::_zoomOne()
{
    printf("zoom one\n");
    //ImGui::GetCurrentWindow()->FontWindowScale = 1.;

    //zoomable = false;
    //    _grid.setScale(1.);
}

// ---

void PdPatchViewController::_attachPatchMenu()
{


    _patchMenu.menuEdit.setAction(PdPatchEditMenu::aEditMode, &editModeAction);
    _patchMenu.menuEdit.editModeFlag = &editMode;

    _patchMenu.menuEdit.setAction(PdPatchEditMenu::aCut, &menuCutAction);
    _patchMenu.menuEdit.setAction(PdPatchEditMenu::aCopy, &menuCopyAction);
    _patchMenu.menuEdit.setAction(PdPatchEditMenu::aPaste, &menuPasteAction);

    _patchMenu.menuEdit.setAction(PdPatchEditMenu::aSelectAll, &menuSelectAllAction);

    _patchMenu.menuEdit.setAction(PdPatchEditMenu::aDelete, &menuDeleteObjectAction);

    // test only
    if (!_patchMenu.common) return;

    _patchMenu.common->menuFile.setAction(PdCommonFileMenu::aFileSave, &menuSaveAction);
    _patchMenu.common->menuFile.setAction(PdCommonFileMenu::aFileSaveAs, &menuSaveAsAction);
    //
    _patchMenu.common->menuWindow.setAction(PdCommonWindowMenu::aSettings, &menuPreferences);
    _patchMenu.common->menuWindow.setAction(PdCommonWindowMenu::aAudioMIDI, &menuAudioSettings);
}

void PdPatchViewController::_attachPutMenu()
{
    _patchMenu.menuPut.setAction(PdPatchPutMenu::aObject, &create.putObject);
    _patchMenu.menuPut.setAction(PdPatchPutMenu::aMessage, &create.putMessage);
    _patchMenu.menuPut.setAction(PdPatchPutMenu::aComment, &create.putComment);

    _patchMenu.menuPut.setAction(PdPatchPutMenu::aBang, &create.putBang);
    _patchMenu.menuPut.setAction(PdPatchPutMenu::aToggle, &create.putToggle);
    _patchMenu.menuPut.setAction(PdPatchPutMenu::aNumber, &create.putNumber);
}

void PdPatchViewController::_attachArrangeMenu()
{
    _patchMenu.menuArrange.showGrid = &data.showGrid;
    _patchMenu.menuArrange.snapToGrid = &data.snapToGrid;

    _patchMenu.menuArrange.setAction(PdPatchArrangeMenu::aAlignLeft, &arrangeMenuActions.arrangeLeftAction);
    _patchMenu.menuArrange.setAction(PdPatchArrangeMenu::aAlignCenter, &arrangeMenuActions.arrangeCenterAction);
    _patchMenu.menuArrange.setAction(PdPatchArrangeMenu::aAlignRight, &arrangeMenuActions.arrangeRightAction);
    _patchMenu.menuArrange.setAction(PdPatchArrangeMenu::aAlignTop, &arrangeMenuActions.arrangeTopAction);
    _patchMenu.menuArrange.setAction(PdPatchArrangeMenu::aAlignBottom, &arrangeMenuActions.arrangeBottomAction);

    _patchMenu.menuArrange.setAction(PdPatchArrangeMenu::aZoomIn, &zoomIn);
    _patchMenu.menuArrange.setAction(PdPatchArrangeMenu::aZoomOut, &zoomOut);
    _patchMenu.menuArrange.setAction(PdPatchArrangeMenu::aZoomOne, &zoomOne);
}

// ---
void PdPatchViewController::_editModeAction()
{
    editMode = !editMode;
}

// ---
void PdPatchViewController::_menuCutAction()
{
    data.cut();
}

void PdPatchViewController::_menuCopyAction()
{
    data.copy();
}

void PdPatchViewController::_menuPasteAction()
{
    data.paste();
}

void PdPatchViewController::_menuSelectAllAction()
{
    data.selectAllObjects();
}

void PdPatchViewController::_menuDeleteObjectAction()
{
    data.deleteSelectedObjects();
}
// ---

//void PdPatchViewController::_arrangeLeftAction()
//{
//    ArrangeObjects::alignLeft(&data.objects);
//}

//void PdPatchViewController::_arrangeCenterAction()
//{
//    ArrangeObjects::alignCenter(&data.objects);
//};

//void PdPatchViewController::_arrangeRightAction()
//{
//    ArrangeObjects::alignRight(&data.objects);
//};

//void PdPatchViewController::_arrangeTopAction()
//{
//    ArrangeObjects::alignTop(&data.objects);
//};

//void PdPatchViewController::_arrangeBottomAction()
//{
//    ArrangeObjects::alignBottom(&data.objects);
//};

//void PdPatchViewController::_arrangeDHAction()
//{
//}

//void PdPatchViewController::_arrangeDVAction()
//{
//}

// ---

//void PdPatchViewController::_putObject()
//{
//    _movingObject = createObject("", 150, 150);
//}

//void PdPatchViewController::_putMessage()
//{
//    _movingObject = createObject("ui.msg", 150, 150);
//}

//void PdPatchViewController::_putComment()
//{
//    // todo
//}

//void PdPatchViewController::_putBang()
//{
//    _movingObject = createObject("ui.bang", 150, 150);
//}

//void PdPatchViewController::_putToggle()
//{
//    _movingObject = createObject("ui.toggle", 150, 150);
//}

//void PdPatchViewController::_putNumber()
//{
//    _movingObject = createObject("ui.float", 150, 150);
//}

// ---

void PdPatchViewController::onMouseDown(ImVec2 pos)
{
    // deselect new object
    _movingObject = 0;

    //        printf("onMouseDown()\n");

    // deselect patchcord
    if (ImGui::IsMouseClicked(0)) {
        if (!data.objectAtPos(ImGui::GetIO().MousePos)) {
            _newPatchcord.outputObj = 0;
        }
    }

    //if (ImGui::IsMouseClicked(0) && editMode)
    if (editMode) {

        _clickedObject = data.objectAtPos(ImGui::GetMousePos()); //&& !_selectionFrame;

        if (_clickedObject && !_multipleObjectsSelected && !_draggingObjects) {
            data.selectSingleObject(ImGui::GetMousePos());
            _multipleObjectsSelected = false;
            _draggingObjects = true;
        }
        _draggingObjects = _clickedObject;

        if (!data.objectAtPos(ImGui::GetMousePos()) && !_draggingObjects && (ImGui::GetMousePos().y > 20)) {
            //                printf("pos %f\n", ImGui::GetMousePos().y);

            data.deselectAll();
            _multipleObjectsSelected = false;
            _draggingObjects = false;
        }

        if (!data.objectAtPos(ImGui::GetMousePos()) && !_draggingObjects) {

            _selectionStart = _selectionEnd = ImGui::GetMousePos();
            _selectionFrame = true;
        }
    }

    if (_selectionFrame && !ImGui::IsMouseReleased(0)) {
        bool b = data.selectObjectsInFrame(_selectionStart, _selectionEnd);
        _multipleObjectsSelected = b;
    }
};

void PdPatchViewController::onMouseDoubleClick(ImVec2 pos)
{
    //        if (ImGui::IsMouseDoubleClicked(0) && editMode) {
    if (editMode) {
        if (!data.objectAtPos(ImGui::GetIO().MousePos)) {
            //addObject("", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
            _emptyObject.x = (ImGui::GetIO().MousePos.x);
            _emptyObject.y = (ImGui::GetIO().MousePos.y);
            _emptyObject.data.emptyBox = true;
            _emptyObject.data.errorBox = true;
            _emptyObject.data.pdObject = 0;
            _emptyObject.data.pdObjectID = 0;
            _emptyObject.objectText = "";
            _emptyObject.hidden = false;
            _emptyObject.clearEditText();
        }
    }
};

void PdPatchViewController::onMouseDrag(ImVec2 pos)
{
    if (!editMode)
        return;

    if (_draggingObjects) {
        dragSelectedObjects(ImGui::GetIO().MouseDelta);
    } else {
        _selectionFrame &= true;
        _selectionEnd = ImGui::GetMousePos();

        //
        //            if (_clickedObject && !_multipleObjectsSelected && !_draggingObjects)

        //if (_selectionFrame && !ImGui::IsMouseReleased(0))
        //            {
        bool b = data.selectObjectsInFrame(_selectionStart, _selectionEnd);
        _multipleObjectsSelected = b;
        //            }
    }
};

void PdPatchViewController::onMouseUp(ImVec2 pos)
{
    _selectionFrame = false;
    _draggingObjects = false;
};

void PdPatchViewController::onMouseHover(ImVec2 pos)
{

    if (!editMode)
        return;
    _newPatchcord.inputX = pos.x;
    _newPatchcord.inputY = pos.y;

    if (_movingObject) {
        _movingObject->x = pos.x;
        _movingObject->y = pos.y;
//        ImGui::SetTooltip("pos %f %f", pos.x, pos.y);
    }
};

// ---

void PdPatchViewController::_menuPreferences()
{
    displayPreferences = true;
}

void PdPatchViewController::_menuAudioSettings()
{
    displayAudioSettings = true;
}
