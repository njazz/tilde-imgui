// (c) 2017 Alex Nadzharov
// License: GPL3

/*
#ifndef UIOBJECTDATA_H
#define UIOBJECTDATA_H

#include "CommonTypes.h"
#include <QObject>

namespace tilde {

class PropertyList;
class Port;

typedef std::vector<Port*> portItemVec;

////
/// \brief Data model for UIObject
///
class UIObjectData : public QObject {
    Q_OBJECT

    QString _dataString;
    PropertyList* _properties;

    QString _fullHelpName;
    bool _errorBox;

    t_objectSize _objectSizeMode;
    int _minimumBoxWidth;
    int _minimumBoxHeight;

public:
    explicit UIObjectData(QObject* parent = 0);
    ~UIObjectData();

    QString toQString();
    PropertyList* properties();

    QString fullHelpName();
    bool errorBox();
    void setFullHelpName(QString fullHelpName);
    void setErrorBox(bool errorBox);

    void setData(QString inputData); ///> set both properties and Pd object string
    QString data();

    void setObjectSize(t_objectSize sizeMode, int minW, int minH); ///> sets all size constraints

    void setMminimumBoxWidth(int w);
    void setMminimumBoxHeight(int h);

    int minimumBoxWidth();
    int minimumBoxHeight();
    t_objectSize objectSizeMode();



signals:

public slots:
};
}

#endif // UIOBJECTDATA_H
*/
