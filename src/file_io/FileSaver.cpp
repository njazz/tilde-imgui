// (c) 2017 Alex Nadzharov
// License: GPL3

#include "FileSaver.h"
#include "CanvasData.h"
#include "PatchWindow.h"

namespace tilde {

void FileSaver::saveCanvas(CanvasData* canvasData, QFile* file)
{
    // this calls top 'canvas' and gets all data as QStringList
    // canvas saves contents recursively

    QStringList fileData = canvasData->asPdFileStrings();

    //todo check
    for (int i = 0; i < fileData.count(); i++) {
        QString str1 = fileData.at(i);
        file->write(str1.toStdString().c_str(), str1.size());
    }
};

void FileSaver::save(QString fname, CanvasData* canvasData)
{
    QFile f(fname);
    f.open(QIODevice::WriteOnly);

    FileSaver::saveCanvas(canvasData, &f);

    f.close();
}
}
