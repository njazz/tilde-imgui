// (c) 2017 Alex Nadzharov
// License: GPL3

#include "FileParser.h"

//#include "PatchWindow.h"

//#include "ApplicationController.h"
//#include "CanvasView.h"
//#include "PdPatchViewController.h"

//#include <QFile>
//#include <QTextStream>

#include "PdStringConverter.h"

#include "PdPatchViewController.hpp"

#include "AppController.hpp"

#include <fstream>
#include <iostream>

#include <regex>

PdPatchViewControllerStack FileParser::_stack;
PdPatchViewController* FileParser::_pdParserWindowController = 0;
PdPatchViewController* FileParser::_pdParserFirstWindowController = 0;

AppController* FileParser::_appController = 0;

std::string FileParser::pdParserFileName = "";

std::string FileParser::legacyCanvasCoords = "";

// ----------------
void PdPatchViewControllerStack::push(PdPatchViewController* c) { _stack.push_back(c); };

PdPatchViewController* PdPatchViewControllerStack::pop()
{
    PdPatchViewController* ret = last();
    _stack.pop_back();
    return ret;
};

PdPatchViewController* PdPatchViewControllerStack::last()
{
    if (_stack.size() == 0)
        return 0;
    return _stack.at(_stack.size() - 1);
}

void PdPatchViewControllerStack::clear() { _stack.clear(); }

size_t PdPatchViewControllerStack::size(){return _stack.size();}
// ----------------

inline void legacyProcessMsg(PdPatchViewController* controller, std::vector<std::string> list)
{
    list[0] = "obj";
    list.insert(list.begin() + 3, "ui.msg");
    FileParser::sendStringToCanvas(controller, list);

    // no special properties
}

inline void legacyProcessText(PdPatchViewController* controller, std::vector<std::string> list)
{
    list[0] = "obj";
    list.insert(list.begin() + 3, "ui.text");
    list.insert(list.begin() + 4, "@Text");

    //UIObject* obj =
    FileParser::sendStringToCanvas(controller, list);

    //        list.removeAt(0);
    //        list.removeAt(0);
    //        list.removeAt(0);
    //        list.removeAt(0);
    //        std::string text = list.join(" ");
    //        obj->properties()->set("Text", text);
}

inline void legacyProcessAtom(PdPatchViewController* controller, std::vector<std::string> list)
{
    list[0] = "obj";
    list.insert(list.begin() + 3, "ui.float");
    //UIObject* obj =
    FileParser::sendStringToCanvas(controller, list);

    //temporary - to have readable list at some point
    //box_width lower upper 1 label send receive

    //check bounds
    //int lBoxWidth = ((std::string)list.at(4)).toInt();
    //float lMinimum = ((std::string)list.at(5)).toFloat();
    //float lMaximum = ((std::string)list.at(6)).toFloat();
    //int lInit = ((std::string)list.at(7)).toInt();

    std::string lLabel = "";
    std::string lSend = "";
    std::string lReceive = "";

    if (list.size() > 10) {
        lLabel = ((std::string)list.at(8));
        lSend = ((std::string)list.at(9));
        lReceive = ((std::string)list.at(10));
    }

    //todo set / create
}

inline void legacyProcessSymbolAtom(PdPatchViewController* controller, std::vector<std::string> list)
{

    std::vector<std::string> list2 = {"obj","0","0","ui.msg","<symbol>"};

    list2[1] = list[1];
    list2[2] = list[2];

    FileParser::sendStringToCanvas(controller, list2);

    //temporary - to have readable list at some point
    //box_width lower upper 1 label send receive

    //check bounds
    //        int lBoxWidth = ((std::string)list.at(4)).toInt();
    //        float lMinimum = ((std::string)list.at(5)).toFloat();
    //        float lMaximum = ((std::string)list.at(6)).toFloat();
    //        int lInit = ((std::string)list.at(7)).toInt();
    //        std::string lLabel = ((std::string)list.at(8));
    //        std::string lSend = ((std::string)list.at(9));
    //        std::string lReceive = ((std::string)list.at(10));

    //todo set / create
}

inline void legacyProcessArray(PdPatchViewController* controller, std::vector<std::string> list)
{
    // lol
    std::vector<std::string> l2 = { "obj ", "20 ", "20 ", "ui.array ", list.at(1) }; //list.at(2).split(" ")

    //std::string(std::string("obj ") + std::string("20 ") + std::string("20 ") + std::string("ui.array ") + list.at(1) + " " + list.at(2)).split(" ");

    //std::vector<std::string> l2 = std::string("obj 20 20 ui.array temp 100").split(" ");

    std::cout << "array parse"; // TODO: << l2;
    FileParser::sendStringToCanvas(controller, l2);
}

// ----------

inline void legacyProcessUIBang(PdPatchViewController* controller, std::vector<std::string> list)
{
    //box_width time1 time2 init send_ receive_ label label_offset_x label_offset_y (font) font_size bgcolor frontcolor labelcolor ?

    std::vector<std::string> list2 = {"obj","0","0","ui.bang"};

    list2[1] = list[1];
    list2[2] = list[2];

    list2.push_back("@Size " + list[4] + list[4]);

    // TODO

    FileParser::sendStringToCanvas(controller, list2);
}

inline void legacyProcessUIToggle(PdPatchViewController* controller, std::vector<std::string> list)
{

    //box_width init send_ receive_ label label_offset_x label_offset_y (font) font_size bgcolor frontcolor labelcolor low_value high_value

    std::vector<std::string> list2; //TODO: !! = std::string("obj 0 0 ui.toggle").split(" ");

    list2[1] = list[1];
    list2[2] = list[2];

    list2.push_back("@Size " + list[4] + list[4]);

    // TODO

    FileParser::sendStringToCanvas(controller, list2);
}

inline void legacyProcessUISlider(PdPatchViewController* controller, std::vector<std::string> list)
{

    std::vector<std::string> list2 = {"obj","0","0","ui.slider"};

    list2[1] = list[1];
    list2[2] = list[2];

    if (list.size() > 5) {
        list2.push_back("@Size " + list[4] + " " + list[5]);
        list2.push_back("@Offset " + list[6]);
        list2.push_back("@Range " + list[7]);
    }

    FileParser::sendStringToCanvas(controller, list2);
}

inline void legacyProcessUIHRadio(PdPatchViewController* controller, std::vector<std::string> list)
{

    std::vector<std::string> list2 = {"obj","0","0","ui.matrix"};

    list2[1] = list[1];
    list2[2] = list[2];

    // temporary
    list2.push_back("@Columns 5 @Rows 1");

    if (list.size() > 4)
        list2.push_back("@Size " + std::to_string(std::stof(list[4]) * 5) + " " + list[4]); //replace 5 with size

    //list2.append("@Offset " + list2[6] );
    //list2.append("@Range" +  list2[7]);

    FileParser::sendStringToCanvas(controller, list2);
}

inline void legacyProcessUIVRadio(PdPatchViewController* controller, std::vector<std::string> list)
{

    std::vector<std::string> list2 = {"obj","0","0","ui.matrix"};

    list2[1] = list[1];
    list2[2] = list[2];

    // temporary
    list2.push_back("@Columns 1 @Rows 5");

    if (list.size() > 4)
        list2.push_back("@Size " + list[4] + " " + std::to_string(std::stof(list[4]) * 5));

    //list2.append("@Offset " + list2[6] );
    //list2.append("@Range" +  list2[7]);

    FileParser::sendStringToCanvas(controller, list2);
}

inline void legacyProcessUINumber2(PdPatchViewController* controller, std::vector<std::string> list)
{
    // TODO
}

inline void legacyProcessUICnv(PdPatchViewController* controller, std::vector<std::string> list)
{

    // ----- canvas

    //temporary
    //check bounds
    //int lBoxWidth = ((std::string)list.at(4)).toInt(); //?
    std::string lSend = (list.at(7));
    std::string lReceive = (list.at(8));
    std::string lLabel = (list.at(9));

    std::string fontSize = (list.size() > 13) ? (list.at(13)) : "11";
    if (lLabel == "empty")
        lLabel = "";

    //    union color {
    //        int32_t c_i;
    //        int8_t c_char[4];
    //    };

    long color2;
    color2 = (list.size() > 14) ? std::stol(list.at(14)) : 0;
    long color1;
    color1 = (list.size() > 15) ? std::stol(list.at(15)) : 0;

    //    color1.c_i &= 0xFFFFFFFF;
    //    color2.c_i &= 0xFFFFFFFF;

    //    QByteArray arr1 = QByteArray::fromRawData((char*)color1.c_i, 1);
    //    QByteArray arr2 = QByteArray::fromRawData((char*)color2.c_i, 1);

    std::cout << "*** colors" << color1 << color2;
    //std::cout << "*** colors" << (std::string)list.at(17) << (std::string)list.at(16);
    //std::cout << "*** colors" << ((std::string)list.at(17)).toLong() << ((std::string)list.at(16)).toLongLong();

    union color {
        int32_t c_int;
        struct {
            uint8_t b[8];
        } c_byte;
    };

    color c1;
    c1.c_int = color1;
    color c2;
    c2.c_int = color2;

    std::cout << "*** colors" << c1.c_int << c2.c_int;

    c1.c_int = -1 - c1.c_int;
    c1.c_int = ((c1.c_int & 0x3f000) << 6) | ((c1.c_int & 0xfc0) << 4) | ((c1.c_int & 0x3f) << 2);

    c2.c_int = -1 - c2.c_int;
    c2.c_int = ((c2.c_int & 0x3f000) << 6) | ((c2.c_int & 0xfc0) << 4) | ((c2.c_int & 0x3f) << 2);

    std::cout << (c1.c_int & 0xFF) << ((c1.c_int >> 8) & 0xFF) << ((c1.c_int >> 16) & 0xFF) << ((c1.c_int >> 24) & 0xFF);

    std::string lcolor1 = std::to_string(c1.c_byte.b[2]) + " " + std::to_string(c1.c_byte.b[1]) + " " + std::to_string(c1.c_byte.b[0]) + " 255";
    std::string lcolor2 = std::to_string(c2.c_byte.b[2]) + " " + std::to_string(c2.c_byte.b[1]) + " " + std::to_string(c2.c_byte.b[0]) + " 255";

    //std::string lcolor2 = "128 128 255 255"; //std::to_string((uint8_t)arr2.at(0)) + " " + std::to_string((uint8_t)arr2.at(1)) + " " + std::to_string((uint8_t)arr2.at(2)) + " "+ std::to_string((uint8_t)arr2.at(2));

    std::cout << lcolor1 << lcolor2 << " ***";

    //std::string lcolor1 = std::to_string(((int)color1.c_char[0])) + " " + std::to_string(((int)color1.c_char[1])) + " " + std::to_string(((int)color1.c_char[2])) + " 255";
    //std::string lcolor2 = "0 0 0 255"; // = std::to_string(((int)color2.c_char[0])) + " " + std::to_string(((int)color2.c_char[1])) + " " + std::to_string(((int)color2.c_char[2])) + " 255";

    //...
    //int lFontSize = ((std::string)list.at(4)).toInt() * 8 + 3;

    std::vector<std::string> list2;
    list2.push_back("obj");
    list2.push_back(list.at(1));
    list2.push_back(list.at(2));
    list2.push_back("ui.text");
    list2.push_back("@Text");
    list2.push_back(lLabel);
    list2.push_back("@FontSize");
    list2.push_back(fontSize);
    list2.push_back("@TextColor");
    list2.push_back(lcolor1);
    list2.push_back("@BackgroundColor");
    list2.push_back(lcolor2);
    list2.push_back("@AutoResizeToText");
    list2.push_back(0);
    list2.push_back("@Size");
    list2.push_back(list.at(5));
    list2.push_back(list.at(6));

    //UIObject* obj =
    FileParser::sendStringToCanvas(controller, list2);
}

// ----------

bool FileParser::legacyProcess(PdPatchViewController* controller, std::vector<std::string> list)
{

    if (list.at(0) == "msg") {

        legacyProcessMsg(controller, list);
        return true;
    }

    if (list.at(0) == "text") {

        legacyProcessText(controller, list);
        return true;
    }

    if (list.at(0) == "floatatom") {

        legacyProcessAtom(controller, list);
        return true;
    }

    if (list.at(0) == "symbolatom") {

        legacyProcessSymbolAtom(controller, list);
        return true;
    }

    if (list.at(0) == "array") {

        legacyProcessArray(controller, list);

        return true;
    }

    // IEMGUI

    if (list.at(0) == "obj") {
        if (list.at(3) == "bng") {
            legacyProcessUIBang(controller, list);
            return true;
        }

        if (list.at(3) == "tgl") {

            legacyProcessUIToggle(controller, list);
            return true;
        }

        if ((list.at(3) == "hsl") || (list.at(3) == "vsl")) {

            legacyProcessUISlider(controller, list);
            return true;
        }

        if (list.at(3) == "number2") {

            legacyProcessUINumber2(controller, list);
            return true;
        }

        if (list.at(3) == "hradio") {

            legacyProcessUIHRadio(controller, list);
            return true;
        }
        if (list.at(3) == "vradio") {

            legacyProcessUIVRadio(controller, list);
            return true;
        }
        if (list.at(3) == "cnv") {

            legacyProcessUICnv(controller, list);
            return true;
        }
    }

    return false; // if it is not a special legacy object
}

UiObjectBase* FileParser::sendStringToCanvas(PdPatchViewController* controller, std::vector<std::string> list)
{
    printf("new obj");

    if (list.size() > 3) {
        std::string objname;
        std::string msgname;
        ImVec2 pos;

        pos.x = std::stof(list.at(1)); //(((std::string)list.value(1)).toFloat());
        pos.y = std::stof(list.at(2)); //(((std::string)list.value(2)).toFloat());

        //lol
        std::vector<std::string> objList = list;
        objList.erase(objList.begin());
        objList.erase(objList.begin());
        objList.erase(objList.begin());

        objname = joinStringWithToken(objList," ");//"objname"; // TODO: !!! objList.join(" ");

        objList.erase(objList.begin());
        msgname =  joinStringWithToken(objList," ");//"msgname"; // TODO: !!! objList.join(" ");

        //std::cout << "objname" << objname;

        // check property handling
        // probably should be moved here?

        _appController->post("create object: "+ list.at(3)+" "+msgname);
        return controller->createObject(std::string(list.at(3) + " " + msgname), pos.x, pos.y);

    } else {
        printf("list error");
        _appController->post("list error");
        //create error object here to keep connections
        return 0;
    }
}

void FileParser::parseStringListAtoms(PdPatchViewController* controller, std::vector<std::string> list) //rename
{
    //legacy parser first
    if (FileParser::legacyProcess(controller, list))
        return;

    //std::cout << "list at 0" << list.at(0);

    if (list.at(0) == "obj") {
        FileParser::sendStringToCanvas(controller, list);
    } else

        if (list.at(0) == "connect") {
        //printf("new connect");

        if (list.size() > 4) {
            if (controller) {
                // TODO

                //                UIObject* obj1 = controller->canvasData()->getObjectByIndex(((std::string)list.value(1)).toInt());
                //                UIObject* obj2 = controller->canvasData()->getObjectByIndex(((std::string)list.value(3)).toInt());

                //                if (!obj1 || !obj2) {
                //                    printf("object not found - could not connect");
                //                    return;
                //                }

                //                int idx1 = ((std::string)list.value(2)).toInt();
                //                int idx2 = ((std::string)list.value(4)).toInt();

                //                //cmcanvasView()->patchcord();
                //                if (!obj1->errorBox() && !obj2->errorBox()) {
                //                    printf("patchcord");
                //                    controller->connectObjects(obj1, idx1, obj2, idx2);
                //                }


                //---
                controller->connectObjectsByIndices(std::stoi(list.at(1)), std::stoi(list.at(2)), std::stoi(list.at(3)), std::stoi(list.at(4)));
            }
        }

        else {
            printf("list error");
        }
    } else if (list.at(0) == "coords") {
    } else if (list.at(0) == "restore") {

        printf("restore canvas: %lu | previous %lu", (long)_pdParserWindowController, (long)_stack.last());

        //parserwindow - subpatch
        //prev window - parent patch

        //restore pd box
        if (list.size() > 2) {
            std::string objname;
            ImVec2 pos;

            pos.x = std::stof(list.at(1)); //(((std::string)list.value(1)).toFloat());
            pos.y = std::stof(list.at(2)); //(((std::string)list.value(2)).toFloat());

            //lol
            std::vector<std::string> objList = list;
            objList.erase(objList.begin());
            objList.erase(objList.begin());
            objList.erase(objList.begin());

            objname =  joinStringWithToken(objList," ");//"objlist";  objList.join(" ");

            std::cout << "objname" << objname;
            //temporary

            std::string objectData =  joinStringWithToken(objList," ");//"objdata";  objList.join(" ");

            //if (objList.at(0) == "pd")
            {
                if (_stack.last()) {
                    // TODO: !!!
                    //_stack.last()->restoreUIBoxForSubpatch(_pdParserWindowController, objectData, pos);
                    printf("restore");
                    std::cout << "data" << objectData;

                    // ----------

                    //if (_pdParserPrevWindowController->firstWindow()->canvasView())
                    //{

                    //                                                UIBox *b1 = 0;

                    //                                                b1 = pdParserPrevWindow->canvasView()->restoreSubcanvas(objname, pos, pdParserWindow->canvasView()->pdCanvas);
                    //                                                b1->cmSubcanvas = pdParserWindow;

                    //                        UIBox* b1 = _pdParserWindowController->subpatchBox();

                    //                        b1->setPos(pos.x(),pos.y());

                    // TODO
                    // UIObject* b = _pdParserPrevWindow->canvasView()->createBoxForPatchWindow(_pdParserWindow, objData, pos);

                    //UIObject* b = _pdParserPrevWindow->canvasView()->createObject(std::string(objData.c_str()), pos);

                    //IObject *b = createBoxForCanvas(newCanvas, objectData, pos);
                    //((UIBox*)b)->setSubpatchWindow((QMainWindow*)_pdParserPrevWindow);
                    //((Canvas*)b)->setSubcanvas(_pdParserPrevWindow->canvas);
                }
            }
            //            }
            //            else {
            //                printf("pd subpatch error");
            //            }

            //draw subpatch
            _pdParserWindowController = _stack.last();
            //            _pdParserPrevWindowController = 0;
            _stack.pop();

        } else {
            printf("list error");
        }
    } else {
        // add dummy object to keep connections

        if (list.size() > 2) {
            std::string objname;
            std::string msgname;
            ImVec2 pos;

            pos.x = std::stof(list.at(1)); //(((std::string)list.value(1)).toFloat());
            pos.y = std::stof(list.at(2)); //(((std::string)list.value(2)).toFloat());

            //lol
            std::vector<std::string> objList = list;
            objList.erase(objList.begin() + 1);
            objList.erase(objList.begin() + 1);

            objname =  joinStringWithToken(objList," ");//"objlist";  !!! objList.join(" ");

            std::cout << "objname" << objname;

            //temporary
            //cmcanvasView()->createBox(objname, pos);

            // TODO cmcanvas->createObject(objname, pos);
        }
    }
}

void FileParser::parseString(std::string line)
{
    line = line.substr(0,line.size()-1);

    line = PdStringConverter::unescapeString(line);

    std::vector<std::string> atoms = splitStringByToken(line, " "); //  !!! = line.split(QRegExp("\\ (?!\\\\\\ )")); //

    std::cout << "src" << line << ", atoms";
    for (auto a : atoms)
        std::cout << "," << a;
    std::cout << "\n";

    //return;

    if (atoms.size() == 0) {

        printf("==0\n");
        return;
    }

    //    atoms.erase(atoms.end());

    //    if (atoms.size()==0)
    //    {
    //        return;
    //    }

    if (atoms.size() < 4) {
        printf("<4\n");
        return;
    }

    if (atoms.at(0) == "#N") {

        _appController->post("new canvas");
        //return;

        std::vector<std::string> msg = atoms;
        msg.erase(msg.begin());

        _stack.push(_pdParserWindowController);

        PdPatchViewController* newWnd = _appController->createNewPatchWindow(); //new PdPatchViewController();    //FileParser::_appController
        _pdParserWindowController = newWnd;

        //save pointer to first canvas. needed to set file name
        if (!_stack.last())
            _pdParserFirstWindowController = _pdParserWindowController;

        msg.erase(msg.begin());

        // todo: title
        //        if (_pdParserWindowController)
        //            newWnd->windowController()->setTitle(msg.at(4));

        //newWnd->mainWindow()->setWindowTitle(msg.at(4));

        // todo different canvas argumentlists
        ImVec2 pos = ImVec2(std::stoi(msg.at(0)), std::stoi(msg.at(1))); //((std::string)msg.at(0)).toInt(), ((std::string)msg.at(1)).toInt());
        ImVec2 size = ImVec2(std::stoi(msg.at(2)), std::stoi(msg.at(3))); // (((std::string)msg.at(2)).toInt(), ((std::string)msg.at(3)).toInt());

        if (pos.x > 1000)
            pos.x = (1000);
        if (pos.y > 500)
            pos.y = (500);
        if (size.x > 1000)
            size.x = (1000);
        if (size.y > 700)
            size.y = (700);

        if (size.x < 40)
            size.x = (1000);
        if (size.y < 40)
            size.y = (100);

        //std::cout << "*** canvas dim" << pos << size;

        newWnd->windowController()->width = size.x;
        newWnd->windowController()->height = size.y;
        newWnd->windowController()->x = pos.x;
        newWnd->windowController()->y = pos.y;
        // TODO: set base size

        //newWnd->mainWindow()->canvasView()->setWindowSize(size);
        //        newWnd->mainWindow()->setBaseSize(size);
        //        newWnd->mainWindow()->move(pos);

        // TODO: !!! hide

        /*
        if (msg.size() > 5) {

            if (msg.at(5).toInt())
                newWnd->mainWindow()->show();
            else
                newWnd->mainWindow()->hide();
        } else
            newWnd->mainWindow()->show();
            */
    }

    if (atoms.at(0) == "#X") {
        _appController->post("new object");
        //return;

        std::vector<std::string> msg = atoms;
        msg.erase(msg.begin());

        if (_pdParserWindowController) {
            //printf("X");
            FileParser::parseStringListAtoms(_pdParserWindowController, msg);
        } else {
            printf("parser error - no canvas");
        }
    }

    if (atoms.at(0) == "#A") {
        //create array
    }
    //TODO
}

void FileParser::open(std::string fname)
{
    //    QFile f(fname);

    std::ifstream f(fname);

    //f.open(fname);
    {
        std::vector<std::string> stringList;

        setParserWindowController(0);

        pdParserFileName = fname;

        std::string line;
        while (std::getline(f, line)) {
            // = //textStream.readLine();

            if (line == "\0")
                break;
            else {
                stringList.push_back(line);
                printf("* %s\n", line.c_str());
                //

                FileParser::parseString(line);
            }
        }

        if (_pdParserWindowController) {
            _pdParserWindowController->data.fileName = fname;
            _pdParserWindowController->editMode = true;
            //            _pdParserWindowController->mainWindow()->setFileName(fname);
            //            _pdParserWindowController->mainWindow()->canvasView()->setEditMode(em_Locked);

            _pdParserWindowController->resizeContentsToObjects(); //mainWindow()->canvasView()->resizeToObjects();
            //_pdParserWindowController->mainWindow()->show();

            _pdParserWindowController->loadbang();
        }

        f.close();
        //    } else {
        //_pdParserWindowController->mainServerInstance()->
        //        ApplicationController::post("error: cannot open file: " + fname);

        //        _appController->post("error: cannot open file: " + fname);
    }
}

// --------------------------------------------------

void FileParser::setAppController(AppController* appController)
{
    _appController = appController;
}

void FileParser::setParserWindowController(PdPatchViewController* wnd)
{
    //_pdParserPrevWindowController = wnd;
    _stack.clear();
    _pdParserWindowController = wnd;
}

void FileParser::setParserWindowControllers(PdPatchViewController* wnd, PdPatchViewController*, PdPatchViewController* first)
{
    _pdParserWindowController = wnd;
    _stack.clear();
    _pdParserFirstWindowController = first;
}

////
/// \brief returns first created window
/// \details mostly used by OOP loader
/// \return
///
PdPatchViewController* FileParser::parserFirstWindowController()
{
    return _pdParserFirstWindowController;
}

PdPatchViewController* FileParser::parserWindowController()
{
    return _pdParserWindowController;
}
