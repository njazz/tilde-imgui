// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef CM_FILESAVER_H
#define CM_FILESAVER_H

#include <fstream>
#include <iostream>
#include <string>

class PdPatchViewController;

class CanvasData;

////
/// \brief saves pd files on 'client' (GUI) side
class FileSaver {
private:
    FileSaver(){};

    ////
    /// \brief new API saveCanvas
    /// \param canvas
    /// \param file
    static void saveCanvas(CanvasData* CanvasData, std::ofstream &file);
public:
    ////
    /// \brief save file to disk; runs 'savecanvas' recursively
    /// \param fname
    /// \param canvas
    static void save(std::string fname, CanvasData* canvasData);


};

#endif // CM_FILESAVER_H
