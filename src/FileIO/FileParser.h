// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef CM_FILEPARSER_H
#define CM_FILEPARSER_H

#include <string>
#include <vector>
#include <vector>
#include <string>

class PatchWindow;
class CanvasData;
class CanvasView;

class UiObjectBase;

class AppController;
class PdPatchViewController;

class PdPatchViewControllerStack {
    std::vector<PdPatchViewController*> _stack;

public:
    void push(PdPatchViewController* c);
    PdPatchViewController* pop();

    PdPatchViewController* last();

    void clear();

    size_t size();
};

////
/// \brief Parses pd files on 'client' (GUI) side
/// \details ?? 'FileParser' and 'FileSaver' should probably be moved to separate library
class FileParser {
private:
    FileParser(){};

    static PdPatchViewControllerStack _stack;

    static PdPatchViewController* _pdParserWindowController;
    static PdPatchViewController* _pdParserFirstWindowController;

    static AppController* _appController;

    //

    static void parseString(std::string line); ///< [2] checks first atoms ("#N", "#X" etc) and sends contents as string vectors to canvas
    static void parseStringListAtoms(PdPatchViewController* controller, std::vector<std::string> list); ///< [3] parses vec<str> of atoms to canvas - creates objects etc, converts list, passes data to 'sendStringToCanvas'

//    static bool legacyProcess(PdPatchViewController* controller, std::vector<std::string> list); ///< [3.2] process legacy pd files

public:
    static std::string pdParserFileName;
    static std::string legacyCanvasCoords; ///< used for #X coords

    static void setAppController(AppController* appController);
    static void setParserWindowController(PdPatchViewController* wnd);
    static void setParserWindowControllers(PdPatchViewController* wnd, PdPatchViewController*, PdPatchViewController* first);

    ////
    /// \brief returns first created window
    /// \details mostly used by OOP loader
    static PdPatchViewController* parserFirstWindowController();
    static PdPatchViewController* parserWindowController();

    static void open(std::string fname); ///> [1] opens file, converts to strings, calls 'parseString'

    static UiObjectBase* sendStringToCanvas(PdPatchViewController* controller, std::vector<std::string> list); ///< [3.1] subroutine - formats list and send it to canvas as a string


};


#endif // CM_FILEPARSER_H
