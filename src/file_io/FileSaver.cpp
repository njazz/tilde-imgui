// (c) 2017 Alex Nadzharov
// License: GPL3


#include "FileSaver.h"
#include "data_models/CanvasData.h"
#include "PdPatchViewController.hpp"

#include <vector>

#include "PdStringConverter.h"

void FileSaver::saveCanvas(CanvasData* canvasData, std::ofstream& file)
{
    // this calls top 'canvas' and gets all data as QStringList
    // canvas saves contents recursively



    std::vector<std::string> fileData = canvasData->asPdFileStrings();

//    printf("*** File: \n%s\n",joinStringWithToken(fileData,"\n").c_str());

    //todo check
    //for (int i = 0; i < fileData.size(); i++) {
    //    std::string str1 = fileData.at(i);

    for (auto str1 : fileData)
    {
        file << str1 << "\r\n";
//        printf("* %s \n", str1.c_str());
    }

    //}
};

void FileSaver::save(std::string fname, CanvasData* canvasData)
{

    std::ofstream f(fname,std::ios_base::binary);

    if (!f.is_open())
        printf("file %s not open\n",fname.c_str());

    FileSaver::saveCanvas(canvasData, f);
    f.close();

}
