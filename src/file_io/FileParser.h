// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef CM_FILEPARSER_H
#define CM_FILEPARSER_H

#include <string>
#include <vector>

// todo: non-static class ?

#include <vector>
#include <string>

class PatchWindow;
class CanvasData;
class CanvasView;

class ObjectBase;

class AppController;
class PdPatchViewController;

class PdPatchViewControllerStack {
    std::vector<PdPatchViewController*> _stack;

public:
    void push(PdPatchViewController* c) { _stack.push_back(c); };
    PdPatchViewController* pop()
    {
        PdPatchViewController* ret = last();
        _stack.pop_back();
        return ret;
    };
    PdPatchViewController* last()
    {
        if (_stack.size() == 0)
            return 0;
        return _stack.at(_stack.size() - 1);
    }
    void clear() { _stack.clear(); }
};

////
/// \brief Parses pd files on 'client' (GUI) side
/// \details 'FileParser' and 'FileSaver' should probably be moved to separate library
class FileParser {
private:
    FileParser(){};

    static PdPatchViewControllerStack _stack;
    static PdPatchViewController* _pdParserWindowController;
    static PdPatchViewController* _pdParserFirstWindowController;

    static AppController* _appController;

public:
    static std::string pdParserFileName;
    static std::string legacyCanvasCoords; ///> used for #X coords

    static void setAppController(AppController* appController);
    static void setParserWindowController(PatchWindowController* wnd);
    static void setParserWindowControllers(PatchWindowController* wnd, PatchWindowController*, PatchWindowController* first);

    ////
    /// \brief returns first created window
    /// \details mostly used by OOP loader
    static PdPatchViewController* parserFirstWindowController();
    static PdPatchViewController* parserWindowController();

    static void open(std::string fname); ///> [1] opens file, converts to QStrings, calls 'parseString'
    static void parseString(std::string line); ///> [2] checks first atoms ("#N", "#X" etc) and sends QStringList of contents to canvas
    static void parseStringListAtoms(PatchWindowController* controller, std::vector<std::string> list); ///> [3] parses QStringLists of atoms to canvas - creates objects etc, converts list, passes data to 'sendStringToCanvas'

    static ObjectBase* sendStringToCanvas(PdPatchViewController* controller, std::vector<std::string> list); ///> [3.1] subroutine - formats list and send it to canvas as a string
    static bool legacyProcess(PdPatchViewController* controller, std::vector<std::string> list); ///> [3.2] process legacy pd files
};


#endif // CM_FILEPARSER_H
