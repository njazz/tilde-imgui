// (c) 2017 Alex Nadzharov
// License: GPL3


#include "FileSaver.h"
#include "CanvasData.h"
#include "PdPatchViewController.hpp"

#include <vector>

#include "PdStringConverter.h"

void FileSaver::saveCanvas(CanvasData* canvasData, std::ofstream& file)
{
    // this calls top 'canvas' and gets all data as vec<str>
    // canvas saves contents recursively

    if (!canvasData)
    {
        printf("FileSaver: empty canvas data");
        return;
    }

    std::vector<std::string> fileData = canvasData->asPdFileStrings();

    for (auto str1 : fileData)
    {
        file << str1 << "\r\n";
    }

};

void FileSaver::save(std::string fname, CanvasData* canvasData)
{

    if (!canvasData)
    {
        printf("FileSaver: empty canvas data");
        return;
    }

    std::ofstream f(fname,std::ios_base::binary);

    if (!f.is_open())
    {
        printf("file %s not open\n",fname.c_str());
        return;
    }

    FileSaver::saveCanvas(canvasData, f);
    f.close();

}
