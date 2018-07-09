
//
//  PdPatchViewController.cpp
//  imguiController
//
//  Created by Alex on 22/03/2018.
//

#include "PdPatchViewController.hpp"

#include "ArrangeObjects.h"

#include "imgui_internal.h"

PdPatchViewController::PdPatchViewController(PdCommonMenus* m)
    : _patchMenu(m)

{
    menu = &_patchMenu;

    _emptyObject.addAction(UIObject::oObjectChanged, &objectCreated);
    _emptyObject.addAction(UIObject::oAutocomplete, &autocomplete);
    _emptyObject.hidden = true;
    addSubview(&_emptyObject);

    _patchMenu.common->menuFile.setAction(PdCommonFileMenu::aFileSave, &menuSaveAction);
    _patchMenu.common->menuFile.setAction(PdCommonFileMenu::aFileSaveAs, &menuSaveAsAction);

    _patchMenu.menuEdit.setAction(PdPatchEditMenu::aEditMode, &editModeAction);
    _patchMenu.menuEdit.editModeFlag = &editMode;

    _patchMenu.menuEdit.setAction(PdPatchEditMenu::aCut, &menuCutAction);
    _patchMenu.menuEdit.setAction(PdPatchEditMenu::aCopy, &menuCopyAction);
    _patchMenu.menuEdit.setAction(PdPatchEditMenu::aPaste, &menuPasteAction);

    _patchMenu.menuEdit.setAction(PdPatchEditMenu::aSelectAll, &menuSelectAllAction);

    _patchMenu.menuEdit.setAction(PdPatchEditMenu::aDelete, &menuDeleteObjectAction);

    //

    arrangeLeftAction = IUAction([this]() {
        ArrangeObjects::alignLeft(&data.objects);
    });
    arrangeCenterAction = IUAction([this]() {
        ArrangeObjects::alignCenter(&data.objects);
    });
    arrangeRightAction = IUAction([this]() {
        ArrangeObjects::alignRight(&data.objects);
    });
    arrangeTopAction = IUAction([this]() {
        ArrangeObjects::alignTop(&data.objects);
    });
    arrangeBottomAction = IUAction([this]() {
        ArrangeObjects::alignBottom(&data.objects);
    });

    //

    _patchMenu.menuArrange.showGrid = &data.showGrid;
    _patchMenu.menuArrange.snapToGrid = &data.snapToGrid;

    _patchMenu.menuArrange.setAction(PdPatchArrangeMenu::aAlignLeft, &arrangeLeftAction);
    _patchMenu.menuArrange.setAction(PdPatchArrangeMenu::aAlignCenter, &arrangeCenterAction);
    _patchMenu.menuArrange.setAction(PdPatchArrangeMenu::aAlignRight, &arrangeRightAction);
    _patchMenu.menuArrange.setAction(PdPatchArrangeMenu::aAlignTop, &arrangeTopAction);
    _patchMenu.menuArrange.setAction(PdPatchArrangeMenu::aAlignBottom, &arrangeBottomAction);


    _patchMenu.menuArrange.setAction(PdPatchArrangeMenu::aZoomIn, &zoomIn);
    _patchMenu.menuArrange.setAction(PdPatchArrangeMenu::aZoomOut, &zoomOut);
    _patchMenu.menuArrange.setAction(PdPatchArrangeMenu::aZoomOne, &zoomOne);

    //
    // contentSize = ImVec2(width, height);
}

void PdPatchViewController::setPdProcess(xpd::ProcessPtr p)
{
    data.pdProcess = p;

    if (data.pdProcess)
        data.canvas = data.pdProcess->createCanvas();

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

    ImGui::SetCursorPos(ImVec2(0,0));
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
    ImGui::SetCursorPos(ImVec2(0,0));
}

void PdPatchViewController::_drawSelectionFrame()
{
    // selection frame

    if (ImGui::IsMouseClicked(0) && editMode) {

        _clickedObject = hitObject(ImGui::GetMousePos()); //&& !_selectionFrame;

        if (_clickedObject && !_multipleObjectsSelected && !_draggingObjects) {
            selectSingleObject(ImGui::GetMousePos());
            _draggingObjects = true;
        }
        _draggingObjects = _clickedObject;

        if (!hitObject(ImGui::GetMousePos()) && !_draggingObjects && (ImGui::GetMousePos().y > 20)) {
            printf("pos %f\n", ImGui::GetMousePos().y);

            deselectAll();
            _multipleObjectsSelected = false;
            _draggingObjects = false;
        }

        if (!hitObject(ImGui::GetMousePos()) && !_draggingObjects) {

            _selectionStart = _selectionEnd = ImGui::GetMousePos();
            _selectionFrame = true;
        }
    }

    if (_selectionFrame && !ImGui::IsMouseReleased(0)) {
        bool b = selectObjects();
        _multipleObjectsSelected = b;
    }
}

void PdPatchViewController::_drawObjectMaker()
{
    // new empty object
    if (ImGui::IsMouseDoubleClicked(0) && editMode) {
        if (!hitObject(ImGui::GetIO().MousePos)) {
            //addObject("", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
            _emptyObject.x = (ImGui::GetIO().MousePos.x);
            _emptyObject.y = (ImGui::GetIO().MousePos.y);
            _emptyObject.data.emptyBox = true;
            _emptyObject.data.errorBox = true;
            _emptyObject.pdObject = 0;
            _emptyObject.pdObjectID = 0;
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
    resizeToObjects();

    x = 0;
    y = 22;

    height = windowController()->height/2-22;

    bool w = true;

    title = "patch";
    flags = ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoTitleBar;

    manualLayout = true;

    padding = 0;
    //contentSize = ImVec2(1024,1024);

    IUViewController::draw();


};

void PdPatchViewController::drawLayerContents()
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    // todo: IULayer
     ImGui::SetCursorPos(ImVec2(0, -22));

    _drawGrid();

    //ImGui::SetTooltip("content size %f %f",contentSize.x,contentSize.y);

    ImGui::SetCursorPos(ImVec2(0, -22));
    //for (auto s: _subviews)
    //    s->updateOffset();

    _drawSelectionFrame();

    if (ImGui::IsMouseDragging()) {
        if (_draggingObjects) {
            dragSelectedObjects(ImGui::GetIO().MouseDelta);
        } else {
            _selectionFrame &= true;
            _selectionEnd = ImGui::GetMousePos();
        }
    }

    //
    //ImGui::SetCursorPos(ImVec2(0,0));
    //IULayer::draw();

    if (_selectionFrame) {
        draw_list->AddRectFilled(_selectionStart, _selectionEnd, IM_COL32(0, 168, 192, 128));
    }

    if (ImGui::IsMouseReleased(0)) {
        //        printf("up\n");
        _selectionFrame = false;
        _draggingObjects = false;
    }

    //
    ImVec2 pos = ImGui::GetMousePos();
    _newPatchcord.inputX = pos.x;
    _newPatchcord.inputY = pos.y;
    //ImGui::SetTooltip("pos %f %f",pos.x,pos.y);

    _newPatchcord.draw();

    //ImGui::End();

    _drawObjectMaker();

    // deselect patchcord
    if (ImGui::IsMouseClicked(0)) {
        if (!hitObject(ImGui::GetIO().MousePos)) {
            _newPatchcord.outputObj = 0;
        }
    }
}

UiObjectBase* PdPatchViewController::createObject(std::string text, int x, int y)
{
    if (!data.pdProcess)
        return 0;

    UiObjectBase* n = UIObjectFactory::createUiObject(text); //new NodeObject;
    if (!n) return 0;
    n->objectText = text;
    n->x = (x);
    n->y = (y);

    if (text.size())
        n->pdObjectID = data.canvas->createObject(text, x, y);

    //    else
    //        n->emptyBox = true;

    n->pdObject = (xpd::PdObject*)const_cast<xpd::Object*>(data.canvas->objects().findObject(n->pdObjectID));

    n->width = 90;

    //    if (!n->pdObject)
    //        return 0;

    //    if (n->pdObject) {
    //        n->inletCount = n->pdObject->inletCount();
    //        n->outletCount = n->pdObject->outletCount();
    //
    //
    n->updateFromPdObject();

    std::string info = text + " ins: " + std::to_string(n->inletCount) + " outs:" + std::to_string(n->outletCount);
    data.pdProcess->post(info + "\n");

    addSubview(n);

    n->editModePtr = &editMode;

    //    data.objects.push_back(n);

    data.addObject(n);

    n->addAction(UIObject::oAutocomplete, &autocomplete);
    n->addAction(UIObject::oObjectChanged, &objectUpdated);
    n->addAction(UiObjectBase::oInletClicked, &inletClicked);
    n->addAction(UiObjectBase::oInletHovered, &inletHovered);
    n->addAction(UiObjectBase::oOutletClicked, &outletClicked);

    if (n->pdObject)
        n->pdObject->registerObserver(xpd::ObserverPtr(&n->observer));

    return n;
}

void PdPatchViewController::connectObjects(UiObjectBase* outObj, int outIdx, UiObjectBase* inObj, int inIdx)
{
    UIPatchcord* c = new UIPatchcord;
    c->outputObj = outObj;
    c->outputIdx = outIdx;
    c->inputObj = inObj;
    c->inputIdx = inIdx;

    data.canvas->connect(outObj->pdObjectID, outIdx, inObj->pdObjectID, inIdx);

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

    // todo: correct error object connections handling
    if (outletIdx >= obj1->outletCount)
        return;
    if (inletIdx >= obj2->inletCount)
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

void PdPatchViewController::deselectAll()
{
    data.deselectObjects();
    data.deselectPatchcords();

    _multipleObjectsSelected = false;
    _draggingObjects = false;
}

void PdPatchViewController::selectSingleObject(ImVec2 pos)
{
    bool ret = false;
    for (auto o : data.objects) {
        UIObject* obj = (UIObject*)o;

        obj->data.selected = (obj->x <= pos.x);
        obj->data.selected &= (obj->y <= pos.y);
        obj->data.selected &= (obj->x + obj->width >= pos.x);
        obj->data.selected &= (obj->y + obj->height >= pos.y);

        ret |= obj->data.selected;
        _multipleObjectsSelected = false;
    }
    //        return ret;
}

bool PdPatchViewController::hitObject(ImVec2 pos)
{
    bool ret = false;
    for (auto o : data.objects) {
        UIObject* obj = (UIObject*)o;

        bool hit;
        hit = (obj->x <= pos.x);
        hit &= (obj->y <= pos.y);
        hit &= (obj->x + obj->width >= pos.x);
        hit &= (obj->y + obj->height >= pos.y);

        ret |= hit;
    }
    return ret;
}

bool PdPatchViewController::selectObjects()
{
    return data.selectObjectsInFrame(_selectionStart, _selectionEnd);
}

// ==========

inline void PdPatchViewController::_autocomplete()
{

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
}

inline void PdPatchViewController::_objectUpdated()
{
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
}

inline void PdPatchViewController::_objectCreated()
{
    UIObject* o = (UIObject*)objectCreated.sender;

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
    if (!_newPatchcord.outputObj) return;
    if (b == _newPatchcord.outputObj)
        return;
    connectObjects(_newPatchcord.outputObj, _newPatchcord.outputIdx, b, b->data.inletClicked);

    _newPatchcord.outputObj = 0;
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

void PdPatchViewController::resizeToObjects()
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

void PdPatchViewController::loadbang()
{
    data.canvas->loadbang();
}

// -----

void PdPatchViewController::_zoomIn()
{
    printf("zoom in\n");
    ImGui::SetWindowFontScale(1.5);

//    for (auto c:_components)
//        c->zoomable = true;

//    zoomable = true;
}

void PdPatchViewController::_zoomOut()
{
    printf("zoom out\n");
    ImGui::SetWindowFontScale(0.5);

//    for (auto c:_components)
//        c->zoomable = true;

//    zoomable = true;
}

void PdPatchViewController::_zoomOne()
{
    printf("zoom one\n");
    ImGui::GetCurrentWindow()->FontWindowScale = 1.;
}
