
//
//  PdPatchViewController.cpp
//  imguiController
//
//  Created by Alex on 22/03/2018.
//

#include "PdPatchViewController.hpp"

void PdPatchViewController::_drawMenu()
{
    _menu.draw();
//    return ;
//    //
//    ImGui::BeginMainMenuBar();
//    if (ImGui::BeginMenu("File")) {

//        if (ImGui::MenuItem("New patch window", "Cmd + N")) {
//           //updated(oMenuNew);
//            //windowController()->restoreContext();
//        }

//        ImGui::MenuItem("Open in new window...", "Cmd + O");
//        ImGui::MenuItem("Save patch", "Cmd + S");
//        ImGui::MenuItem("Save patch as ...", "Cmd + Shift + S");

//        ImGui::Separator();
//        if (ImGui::MenuItem("Exit", "Cmd + Q")) {
//            //updated(oMenuExit);
//            //windowController()->restoreContext();
//        }
//        ImGui::EndMenu();
//    }

//    if (ImGui::BeginMenu("Edit")) {
//        ImGui::MenuItem("Undo","Cmd + Z");
//        ImGui::MenuItem("Redo","Cmd + Shift + Z");
//        ImGui::Separator();
//        ImGui::MenuItem("Cut","Cmd + X");
//        ImGui::MenuItem("Copy","Cmd + C");
//        ImGui::MenuItem("Paste","Cmd + V");
//        ImGui::Separator();
//        ImGui::MenuItem("Select all","Cmd + A");
//        ImGui::Separator();
//        ImGui::MenuItem("Delete selected","Del");

//        ImGui::EndMenu();

//    }

//    if (ImGui::BeginMenu("Put")) {
//        ImGui::MenuItem("Object","Cmd + 1");
//        ImGui::MenuItem("Message","Cmd + 2");
//        ImGui::MenuItem("Comment","Cmd + 5");
//        ImGui::Separator();
//        ImGui::MenuItem("Bang","Cmd + Shift + B");
//        ImGui::MenuItem("Toggle","Cmd + Shift + T");
//        ImGui::MenuItem("Number","Cmd + 3");
//        ImGui::EndMenu();

//    }

//    if (ImGui::BeginMenu("Arrange")) {
//        ImGui::MenuItem("Show grid");
//        ImGui::MenuItem("Snap to grid");
//        ImGui::Separator();
//        ImGui::MenuItem("Align to grid");
//        ImGui::MenuItem("Tidy up");
//        ImGui::Separator();
//        ImGui::MenuItem("Zoom in");
//        ImGui::MenuItem("Zoom out");
//        ImGui::MenuItem("Zoom 100%");
//        ImGui::EndMenu();
//    }

//    if (ImGui::BeginMenu("Media")) {
//        ImGui::MenuItem("DSP On");
//        ImGui::MenuItem("DSP Off");
//        ImGui::EndMenu();
//    }

//    ImGui::EndMainMenuBar();
}

void PdPatchViewController::setPdProcess(xpd::ProcessPtr p)
{
    _pdProcess = p;

    if (_pdProcess)
        _canvas = _pdProcess->createCanvas();

    // test
    addObject("print", 300, 300);

    addObject("pack 0 0 0", 300, 200);
    addObject("unpack 0 0 0 0 0", 300, 250);

    addObject("+", 300, 150);

    auto o1 = addObject("osc~ 440", 50, 150);
    auto o2 = addObject("dac~ 1 2", 50, 300);
    connectObjects(o1, 0, o2, 0);
    connectObjects(o1, 0, o2, 1);
}

void PdPatchViewController::draw()
{
    ImGui::SetNextWindowSize(ImVec2(width, height-20));
    //ImGui::SetNextWindowContentSize(ImVec2(width, height-22));
    ImGui::SetNextWindowPos(ImVec2(0, 20));

    ImGui::Begin("patch");

    _drawMenu();

    // grid
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 scrolling;
    ImGui::BeginChild(ImGui::GetID("grid"));
    if (1) {
        ImU32 GRID_COLOR = IM_COL32(200, 200, 200, 40);
        float GRID_SZ = 30.0f;

        ImVec2 win_pos = ImGui::GetCursorScreenPos() - ImVec2(4, 4);
        ImVec2 canvas_sz = ImVec2(width, height-20); //ImGui::GetWindowSize();

        for (float x = fmodf(scrolling.x, GRID_SZ); x < this->width; x += GRID_SZ)
            draw_list->AddLine(ImVec2(x, 0.0f) + win_pos, ImVec2(x, this->height-20) + win_pos, GRID_COLOR);
        for (float y = fmodf(scrolling.y, GRID_SZ); y < this->height-20; y += GRID_SZ)
            draw_list->AddLine(ImVec2(0.0f, y) + win_pos, ImVec2(this->width, y) + win_pos, GRID_COLOR);

    }
    ImGui::EndChild();

    // selection frame

    //ImGui::SetTooltip("mult %i drag  %i clicked %i", _multipleObjectsSelected, _draggingObjects, _clickedObject);

    if (ImGui::IsMouseClicked(0)) {
//        printf("down\n");

        _clickedObject = hitObject(ImGui::GetMousePos()); //&& !_selectionFrame;

        if (_clickedObject && !_multipleObjectsSelected && !_draggingObjects) {
            selectSingleObject(ImGui::GetMousePos());
            _draggingObjects = true;
        }
        _draggingObjects = _clickedObject;

        if (!hitObject(ImGui::GetMousePos()) && !_draggingObjects) {
            deselectAll();
            _multipleObjectsSelected = false;
            _draggingObjects = false;
        }

        if (!hitObject(ImGui::GetMousePos()) && !_draggingObjects) {

            _selectionStart = _selectionEnd = ImGui::GetMousePos();
            _selectionFrame = true;
        }
    }

    if (ImGui::IsMouseDragging()) {
        if (_draggingObjects) {
            dragSelectedObjects(ImGui::GetIO().MouseDelta);
        } else {
            _selectionFrame &= true;
            _selectionEnd = ImGui::GetMousePos();
        }
    }

    if (_selectionFrame && !ImGui::IsMouseReleased(0)) {
        bool b = selectObjects();
        _multipleObjectsSelected = b;
    }

    //
    IUViewController::draw();

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

    ImGui::End();

    // new empty object
    if (ImGui::IsMouseDoubleClicked(0)) {
        if (!hitObject(ImGui::GetIO().MousePos)) {
            addObject("", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
        }
    }

    // deselect patchcord
    if (ImGui::IsMouseClicked(0)) {
        if (!hitObject(ImGui::GetIO().MousePos)) {
            _newPatchcord.outputObj = 0;
        }
        }
};

ObjectBase* PdPatchViewController::addObject(std::string text, int x, int y)
{
    if (!_pdProcess)
        return 0;

    ObjectBase* n = UIObjectFactory::createUiObject("*");//new NodeObject;
    n->objectText = text;
    n->x = x;
    n->y = y;

    if (text.size())
        n->pdObjectID = _canvas->createObject(text, x, y);
    else
        n->emptyBox = true;

    n->pdObject = (xpd::PdObject*)const_cast<xpd::Object*>(_canvas->objects().findObject(n->pdObjectID));
    n->errorBox = (n->pdObject == 0);

    if (n->pdObject) {
        n->inletCount = n->pdObject->inletCount();
        n->outletCount = n->pdObject->outletCount();
        std::string info = text + " ins: " + std::to_string(n->inletCount) + " outs:" + std::to_string(n->outletCount);
        _pdProcess->post(info);
    }

    n->width = 90;

    addSubview(n);
    _objects.push_back(n);

    n->addObserverFor(NodeObject::oAutocomplete, &autocomplete);
    n->addObserverFor(NodeObject::oObjectChanged, &objectUpdated);
    n->addObserverFor(ObjectBase::oInletClicked, &inletClicked);
    n->addObserverFor(ObjectBase::oInletHovered, &inletHovered);
    n->addObserverFor(ObjectBase::oOutletClicked, &outletClicked);
    return n;
}

void PdPatchViewController::connectObjects(ObjectBase* outObj, int outIdx, ObjectBase* inObj, int inIdx)
{
    NodeConnection* c = new NodeConnection;
    c->outputObj = outObj;
    c->outputIdx = outIdx;
    c->inputObj = inObj;
    c->inputIdx = inIdx;

    _canvas->connect(outObj->pdObjectID, outIdx, inObj->pdObjectID, inIdx);

    addSubview(c);
    _patchcords.push_back(c);
}

void PdPatchViewController::dragSelectedObjects(ImVec2 delta)
{
    if (_selectionFrame)
        return;
    for (auto o : _objects) {
        NodeObject* obj = (NodeObject*)o;
        if (obj->selected) {
            o->x += delta.x;
            o->y += delta.y;
        }
    }
}

void PdPatchViewController::deselectAll()
{
    for (auto o : _objects) {
        NodeObject* obj = (NodeObject*)o;

        obj->selected = false;
    }

    _multipleObjectsSelected = false;
    _draggingObjects = false;
}

void PdPatchViewController::selectSingleObject(ImVec2 pos)
{
    bool ret = false;
    for (auto o : _objects) {
        NodeObject* obj = (NodeObject*)o;

        obj->selected = (obj->x <= pos.x);
        obj->selected &= (obj->y <= pos.y);
        obj->selected &= (obj->x + obj->width >= pos.x);
        obj->selected &= (obj->y + obj->height >= pos.y);

        ret |= obj->selected;
        _multipleObjectsSelected = false;
    }
    //        return ret;
}

bool PdPatchViewController::hitObject(ImVec2 pos)
{
    bool ret = false;
    for (auto o : _objects) {
        NodeObject* obj = (NodeObject*)o;

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
    bool ret = false;
    for (auto o : _objects) {
        NodeObject* obj = (NodeObject*)o;

        obj->selected = (obj->x >= _selectionStart.x);
        obj->selected &= (obj->y >= _selectionStart.y);
        obj->selected &= (obj->x <= _selectionEnd.x);
        obj->selected &= (obj->y <= _selectionEnd.y);

        ret |= obj->selected;
    }
    return ret;
}
