// (c) 2017 Alex Nadzharov
// License: GPL3

#include "FileParser.h"

#include "PatchWindow.h"

#include "ApplicationController.h"
#include "CanvasView.h"
#include "PatchWindowController.h"

#include <QFile>
#include <QTextStream>

#include "fileparserconverter.h"

using namespace std;

namespace tilde {

//PatchWindowController* FileParser::_pdParserPrevWindowController = 0;

PatchWindowControllerStack FileParser::_stack;
PatchWindowController* FileParser::_pdParserWindowController = 0;
PatchWindowController* FileParser::_pdParserFirstWindowController = 0;

ApplicationController* FileParser::_appController = 0;

string FileParser::pdParserFileName = "";

string FileParser::legacyCanvasCoords;

// ----------------

inline void legacyProcessMsg(PatchWindowController* controller, QStringList list)
{
    list[0] = "obj";
    list.insert(3, "ui.msg");
    FileParser::sendStringToCanvas(controller, list);

    // no special properties
}

inline void legacyProcessText(PatchWindowController* controller, QStringList list)
{
    list[0] = "obj";
    list.insert(3, "ui.text");
    list.insert(4, "@Text");

    //UIObject* obj =
    FileParser::sendStringToCanvas(controller, list);

    //        list.removeAt(0);
    //        list.removeAt(0);
    //        list.removeAt(0);
    //        list.removeAt(0);
    //        QString text = list.join(" ");
    //        obj->properties()->set("Text", text);
}

inline void legacyProcessAtom(PatchWindowController* controller, QStringList list)
{
    list[0] = "obj";
    list.insert(3, "ui.float");
    //UIObject* obj =
    FileParser::sendStringToCanvas(controller, list);

    //temporary - to have readable list at some point
    //box_width lower upper 1 label send receive

    //check bounds
    //int lBoxWidth = ((QString)list.at(4)).toInt();
    //float lMinimum = ((QString)list.at(5)).toFloat();
    //float lMaximum = ((QString)list.at(6)).toFloat();
    //int lInit = ((QString)list.at(7)).toInt();

    QString lLabel = "";
    QString lSend = "";
    QString lReceive = "";

    if (list.size() > 10) {
        lLabel = ((QString)list.at(8));
        lSend = ((QString)list.at(9));
        lReceive = ((QString)list.at(10));
    }

    //todo set / create
}

inline void legacyProcessSymbolAtom(PatchWindowController* controller, QStringList list)
{

    QStringList list2 = QString("obj 0 0 ui.msg <symbol>").split(" ");

    list2[1] = list[1];
    list2[2] = list[2];

    FileParser::sendStringToCanvas(controller, list2);

    //temporary - to have readable list at some point
    //box_width lower upper 1 label send receive

    //check bounds
    //        int lBoxWidth = ((QString)list.at(4)).toInt();
    //        float lMinimum = ((QString)list.at(5)).toFloat();
    //        float lMaximum = ((QString)list.at(6)).toFloat();
    //        int lInit = ((QString)list.at(7)).toInt();
    //        QString lLabel = ((QString)list.at(8));
    //        QString lSend = ((QString)list.at(9));
    //        QString lReceive = ((QString)list.at(10));

    //todo set / create
}

inline void legacyProcessArray(PatchWindowController* controller, QStringList list)
{
    // lol
    QStringList l2 = QString(QString("obj ") + QString("20 ") + QString("20 ") + QString("ui.array ") + list.at(1) + " " + list.at(2)).split(" ");

    //QStringList l2 = QString("obj 20 20 ui.array temp 100").split(" ");
    qDebug() << "array parse" << l2;
    FileParser::sendStringToCanvas(controller, l2);
}

// ----------

inline void legacyProcessUIBang(PatchWindowController* controller, QStringList list)
{
    //box_width time1 time2 init send_ receive_ label label_offset_x label_offset_y (font) font_size bgcolor frontcolor labelcolor ?

    QStringList list2 = QString("obj 0 0 ui.bang").split(" ");

    list2[1] = list[1];
    list2[2] = list[2];

    list2.append("@Size " + list[4] + list[4]);

    // TODO

    FileParser::sendStringToCanvas(controller, list2);
}

inline void legacyProcessUIToggle(PatchWindowController* controller, QStringList list)
{

    //box_width init send_ receive_ label label_offset_x label_offset_y (font) font_size bgcolor frontcolor labelcolor low_value high_value

    QStringList list2 = QString("obj 0 0 ui.toggle").split(" ");

    list2[1] = list[1];
    list2[2] = list[2];

    list2.append("@Size " + list[4] + list[4]);

    // TODO

    FileParser::sendStringToCanvas(controller, list2);
}

inline void legacyProcessUISlider(PatchWindowController* controller, QStringList list)
{

    QStringList list2 = QString("obj 0 0 ui.slider").split(" ");

    list2[1] = list[1];
    list2[2] = list[2];

    if (list.size() > 5) {
        list2.append("@Size " + list[4] + " " + list[5]);
        list2.append("@Offset " + list[6]);
        list2.append("@Range " + list[7]);
    }

    FileParser::sendStringToCanvas(controller, list2);
}

inline void legacyProcessUIHRadio(PatchWindowController* controller, QStringList list)
{

    QStringList list2 = QString("obj 0 0 ui.matrix").split(" ");

    list2[1] = list[1];
    list2[2] = list[2];

    // temporary
    list2.append("@Columns 5 @Rows 1");

    if (list.size() > 4)
        list2.append("@Size " + QString::number(list[4].toFloat() * 5) + " " + list[4]); //replace 5 with size

    //list2.append("@Offset " + list2[6] );
    //list2.append("@Range" +  list2[7]);

    FileParser::sendStringToCanvas(controller, list2);
}

inline void legacyProcessUIVRadio(PatchWindowController* controller, QStringList list)
{

    QStringList list2 = QString("obj 0 0 ui.matrix").split(" ");

    list2[1] = list[1];
    list2[2] = list[2];

    // temporary
    list2.append("@Columns 1 @Rows 5");

    if (list.size() > 4)
        list2.append("@Size " + list[4] + " " + QString::number(list[4].toFloat() * 5));

    //list2.append("@Offset " + list2[6] );
    //list2.append("@Range" +  list2[7]);

    FileParser::sendStringToCanvas(controller, list2);
}

inline void legacyProcessUINumber2(PatchWindowController* controller, QStringList list)
{
    // TODO
}

inline void legacyProcessUICnv(PatchWindowController* controller, QStringList list)
{

    // ----- canvas

    //temporary
    //check bounds
    //int lBoxWidth = ((QString)list.at(4)).toInt(); //?
    QString lSend = ((QString)list.at(7));
    QString lReceive = ((QString)list.at(8));
    QString lLabel = ((QString)list.at(9));

    QString fontSize = (list.size() > 13) ? ((QString)list.at(13)) : "11";
    if (lLabel == "empty")
        lLabel = "";

    //    union color {
    //        int32_t c_i;
    //        int8_t c_char[4];
    //    };

    long color2;
    color2 = (list.size() > 14) ? ((QString)list.at(14)).toLong() : 0;
    long color1;
    color1 = (list.size() > 15) ? ((QString)list.at(15)).toLong() : 0;

    //    color1.c_i &= 0xFFFFFFFF;
    //    color2.c_i &= 0xFFFFFFFF;

    //    QByteArray arr1 = QByteArray::fromRawData((char*)color1.c_i, 1);
    //    QByteArray arr2 = QByteArray::fromRawData((char*)color2.c_i, 1);

    qDebug() << "*** colors" << color1 << color2;
    //qDebug() << "*** colors" << (QString)list.at(17) << (QString)list.at(16);
    //qDebug() << "*** colors" << ((QString)list.at(17)).toLong() << ((QString)list.at(16)).toLongLong();

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

    qDebug() << "*** colors" << c1.c_int << c2.c_int;

    c1.c_int = -1 - c1.c_int;
    c1.c_int = ((c1.c_int & 0x3f000) << 6) | ((c1.c_int & 0xfc0) << 4) | ((c1.c_int & 0x3f) << 2);

    c2.c_int = -1 - c2.c_int;
    c2.c_int = ((c2.c_int & 0x3f000) << 6) | ((c2.c_int & 0xfc0) << 4) | ((c2.c_int & 0x3f) << 2);

    qDebug() << (c1.c_int & 0xFF) << ((c1.c_int >> 8) & 0xFF) << ((c1.c_int >> 16) & 0xFF) << ((c1.c_int >> 24) & 0xFF);

    QString lcolor1 = QString::number(c1.c_byte.b[2]) + " " + QString::number(c1.c_byte.b[1]) + " " + QString::number(c1.c_byte.b[0]) + " 255";
    QString lcolor2 = QString::number(c2.c_byte.b[2]) + " " + QString::number(c2.c_byte.b[1]) + " " + QString::number(c2.c_byte.b[0]) + " 255";

    //QString lcolor2 = "128 128 255 255"; //QString::number((uint8_t)arr2.at(0)) + " " + QString::number((uint8_t)arr2.at(1)) + " " + QString::number((uint8_t)arr2.at(2)) + " "+ QString::number((uint8_t)arr2.at(2));

    qDebug() << lcolor1 << lcolor2 << " ***";

    //QString lcolor1 = QString::number(((int)color1.c_char[0])) + " " + QString::number(((int)color1.c_char[1])) + " " + QString::number(((int)color1.c_char[2])) + " 255";
    //QString lcolor2 = "0 0 0 255"; // = QString::number(((int)color2.c_char[0])) + " " + QString::number(((int)color2.c_char[1])) + " " + QString::number(((int)color2.c_char[2])) + " 255";

    //...
    //int lFontSize = ((QString)list.at(4)).toInt() * 8 + 3;

    QStringList list2;
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

bool FileParser::legacyProcess(PatchWindowController* controller, QStringList list)
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

UIObject* FileParser::sendStringToCanvas(PatchWindowController* controller, QStringList list)
{
    qDebug("new obj");

    if (list.size() > 3) {
        QString objname;
        QString msgname;
        QPoint pos;

        pos.setX(((QString)list.value(1)).toFloat());
        pos.setY(((QString)list.value(2)).toFloat());

        //lol
        QStringList objList = list;
        objList.removeAt(0);
        objList.removeAt(0);
        objList.removeAt(0);

        objname = objList.join(" ");

        objList.removeAt(0);
        msgname = objList.join(" ");

        //qDebug() << "objname" << objname;

        // check property handling
        // probably should be moved here?

        return controller->createObject(QString(list.at(3) + " " + msgname).toStdString(), pos);

    } else {
        qDebug("list error");
        //create error object here to keep connections
        return 0;
    }
}

void FileParser::parseStringListAtoms(PatchWindowController* controller, QStringList list) //rename
{
    //legacy parser first
    if (FileParser::legacyProcess(controller, list))
        return;

    //qDebug() << "list at 0" << list.at(0);

    if (list.at(0) == "obj") {
        FileParser::sendStringToCanvas(controller, list);
    } else

        if (list.at(0) == "connect") {
        //qDebug("new connect");

        if (list.size() > 4) {
            if (controller) {
                // TODO

                UIObject* obj1 = controller->canvasData()->getObjectByIndex(((QString)list.value(1)).toInt());
                UIObject* obj2 = controller->canvasData()->getObjectByIndex(((QString)list.value(3)).toInt());

                if (!obj1 || !obj2) {
                    qDebug("object not found - could not connect");
                    return;
                }

                int idx1 = ((QString)list.value(2)).toInt();
                int idx2 = ((QString)list.value(4)).toInt();

                //cmcanvasView()->patchcord();
                if (!obj1->errorBox() && !obj2->errorBox()) {
                    qDebug("patchcord");
                    controller->createPatchcord(obj1, idx1, obj2, idx2);
                }
            }
        }

        else {
            qDebug("list error");
        }
    } else if (list.at(0) == "coords") {
    } else if (list.at(0) == "restore") {

        qDebug("restore canvas: %lu | previous %lu", _pdParserWindowController, _stack.last());

        //parserwindow - subpatch
        //prev window - parent patch

        //restore pd box
        if (list.size() > 2) {
            QString objname;
            QPoint pos;

            pos.setX(((QString)list.value(1)).toFloat());
            pos.setY(((QString)list.value(2)).toFloat());

            //lol
            QStringList objList = list;
            objList.removeAt(0);
            objList.removeAt(0);
            objList.removeAt(0);
            objname = objList.join(" ");

            qDebug() << "objname" << objname;
            //temporary

            QString objectData = objList.join(" ");

            //if (objList.at(0) == "pd")
            {
                if (_stack.last()) {
                    //if (_pdParserPrevWindowController->firstWindow()->canvasView())
                    //{

                    //                                                UIBox *b1 = 0;

                    //                                                b1 = pdParserPrevWindow->canvasView()->restoreSubcanvas(objname.toStdString(), pos, pdParserWindow->canvasView()->pdCanvas);
                    //                                                b1->cmSubcanvas = pdParserWindow;

                    //                        UIBox* b1 = _pdParserWindowController->subpatchBox();

                    //                        b1->setPos(pos.x(),pos.y());

                    _stack.last()->restoreUIBoxForSubpatch(_pdParserWindowController, objectData, pos);

                    qDebug("restore");
                    qDebug() << "data" << objectData;

                    // TODO
                    // UIObject* b = _pdParserPrevWindow->canvasView()->createBoxForPatchWindow(_pdParserWindow, objData, pos);

                    //UIObject* b = _pdParserPrevWindow->canvasView()->createObject(QString(objData.c_str()), pos);

                    //IObject *b = createBoxForCanvas(newCanvas, objectData, pos);
                    //((UIBox*)b)->setSubpatchWindow((QMainWindow*)_pdParserPrevWindow);
                    //((Canvas*)b)->setSubcanvas(_pdParserPrevWindow->canvas);
                }
            }
            //            }
            //            else {
            //                qDebug("pd subpatch error");
            //            }

            //draw subpatch
            _pdParserWindowController = _stack.last();
            //            _pdParserPrevWindowController = 0;
            _stack.pop();

        } else {
            qDebug("list error");
        }
    } else {
        // add dummy object to keep connections

        if (list.size() > 2) {
            QString objname;
            QString msgname;
            QPoint pos;

            pos.setX(((QString)list.value(1)).toFloat());
            pos.setY(((QString)list.value(2)).toFloat());

            //lol
            QStringList objList = list;
            objList.removeAt(1);
            objList.removeAt(1);

            objname = objList.join(" ");

            qDebug() << "objname" << objname;

            //temporary
            //cmcanvasView()->createBox(objname.toStdString(), pos);

            // TODO cmcanvas->createObject(objname, pos);
        }
    }
}

void FileParser::parseQString(QString line)
{
    line = FileParserConverter::unescapeString(line);

    QStringList atoms = line.split(QRegExp("\\ (?!\\\\\\ )")); //

    atoms.last() = atoms.last().remove(";");

    if (atoms.at(0) == "#N") {

        QStringList msg = atoms;
        msg.removeFirst();

        _stack.push(_pdParserWindowController);

        PatchWindowController* newWnd = new PatchWindowController(FileParser::_appController);
        newWnd->setAppController(FileParser::_appController);
        _pdParserWindowController = newWnd;

        //save pointer to first canvas. needed to set file name
        if (!_stack.last())
            _pdParserFirstWindowController = _pdParserWindowController;

        msg.removeFirst();
        if (_pdParserWindowController)
            newWnd->mainWindow()->setWindowTitle(msg.at(4));

        // todo different canvas argumentlists
        QPoint pos = QPoint(((QString)msg.at(0)).toInt(), ((QString)msg.at(1)).toInt());
        QSize size = QSize(((QString)msg.at(2)).toInt(), ((QString)msg.at(3)).toInt());

        if (pos.x() > 1000)
            pos.setX(1000);
        if (pos.y() > 500)
            pos.setY(500);
        if (size.width() > 1000)
            size.setWidth(1000);
        if (size.height() > 700)
            size.setHeight(700);

        if (size.width() < 40)
            size.setWidth(1000);
        if (size.height() < 40)
            size.setHeight(100);

        //qDebug() << "*** canvas dim" << pos << size;

        newWnd->mainWindow()->canvasView()->setWindowSize(size);
        newWnd->mainWindow()->setBaseSize(size);
        newWnd->mainWindow()->move(pos);

        // TODO

        if (msg.size() > 5) {

            if (msg.at(5).toInt())
                newWnd->mainWindow()->show();
            else
                newWnd->mainWindow()->hide();
        } else
            newWnd->mainWindow()->show();
    }

    if (atoms.at(0) == "#X") {
        QStringList msg = atoms;
        msg.removeFirst();

        if (_pdParserWindowController) {
            //qDebug("X");
            FileParser::parseStringListAtoms(_pdParserWindowController, msg);
        } else {
            qDebug("parser error - no canvas");
        }
    }

    if (atoms.at(0) == "#A") {
        //create array
    }
    //TODO
}

void FileParser::open(QString fname)
{
    QFile f(fname);

    if (f.open(QIODevice::ReadOnly)) {
        QStringList stringList;

        setParserWindowController(0);

        pdParserFileName = fname.toStdString();

        QTextStream textStream(&f);
        while (true) {
            QString line = textStream.readLine();
            if (line.isNull())
                break;
            else {
                stringList.append(line);
                qDebug("* %s", line.toStdString().c_str());
                //

                FileParser::parseQString(line);
            }
        }

        if (_pdParserWindowController) {
            _pdParserWindowController->mainWindow()->setFileName(fname);
            _pdParserWindowController->mainWindow()->canvasView()->setEditMode(em_Locked);

            _pdParserWindowController->mainWindow()->canvasView()->resizeToObjects();
            _pdParserWindowController->mainWindow()->show();

            _pdParserWindowController->serverCanvas()->loadbang();
        }

        f.close();
    } else {
        //_pdParserWindowController->mainServerInstance()->
        ApplicationController::post("error: cannot open file: " + fname);
    }
}

// --------------------------------------------------

void FileParser::setAppController(AppController *appController)
{
    _appController = appController;
}

void FileParser::setParserWindowController(PatchWindowController* wnd)
{
    //_pdParserPrevWindowController = wnd;
    _stack.clear();
    _pdParserWindowController = wnd;
}

void FileParser::setParserWindowControllers(PatchWindowController* wnd, PatchWindowController*, PatchWindowController* first)
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
PatchWindowController* FileParser::parserFirstWindowController()
{
    return _pdParserFirstWindowController;
}

PatchWindowController* FileParser::parserWindowController()
{
    return _pdParserWindowController;
}
}
