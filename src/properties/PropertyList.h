// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef CM_PROPERTYLIST_H
#define CM_PROPERTYLIST_H

#include "Property.h"

#include <map>

//#include <QDebug>
//#include <QObject>

using namespace std;

namespace tilde {

class UIObject;

typedef map<string, Property*> UIPropertyData;
typedef map<string, UIPropertyData*> UIPropertyGroups;

typedef map<string, Property*>::iterator UIPropertyDataIterator;
typedef map<string, UIPropertyData*>::iterator UIPropertyGroupIterator;

#define PROPERTY_LISTENER(x, y) connect(objectData()->properties()->get(x), &Property::changed, this, y)
#define PROPERTY_DISCONNECT_LISTENER(x, y) disconnect(objectData()->properties()->get(x), &Property::changed, this, y)
#define PROPERTY_SET(x, y) objectData()->properties()->set(x, y)
#define PROPERTY_GET(x) objectData()->properties()->get(x)

////
/// \brief Property handling class for ui object - property list
///
class PropertyList : public QObject {
    Q_OBJECT

private:
    UIPropertyData _data;
    UIPropertyGroups _groups;

public:
    PropertyList(){};

    UIPropertyData* group(QString grpName);
    UIPropertyData* fromGroup(QString grpName);

    template <typename T>
    void create(string pName, string pGroup, QString pVersion, T defaultData)
    {
        Property* newP = new Property;

        //newP->setGroup(pGroup);
        newP->setVersion(pVersion);
        newP->set(defaultData);
        newP->copyDataToDefault();

        _data[pName] = newP;
        //fix

        UIPropertyData* grp = _groups[pGroup];
        if (!grp)
            grp = new UIPropertyData();
        (*grp)[pName] = newP;
        _groups[pGroup] = grp;
    }

    // ----------

    template <typename U>
    void set(string pName, U value)
    {
        if (_data[pName]) {
            _data[pName]->set(value);
            //            emit propertyChangedSignal(QString(pName.c_str()));

            emit get(pName.c_str())->changed();
        }
    };

    Property* get(QString pName);

    //todo

    //    Property* operator[](QString pName)
    //    {
    //        return get(pName);
    //    }

    //    Property* operator[](QString pName) const
    //    {
    //        return get(pName);
    //    }

    // ------------

    ////
    /// \brief returns string for saving in file
    /// \return
    ///
    string asPdFileString();

    ////
    /// \brief list of all property names
    /// \return
    ///
    QStringList names();

    ////
    /// \brief list of all property names for specific propertyData
    /// \detais todo normal classes
    /// \return
    ///
    QStringList names(UIPropertyData* data1);

    ////
    /// \brief list of all group names
    /// \return
    ///
    QStringList groupNames();

    ////
    /// \brief extract properties from string in pd file
    /// \details returns first part of the string before the first property
    /// \return
    ///
    QString extractFromPdFileString(QString input);

    //    void addListener(QString name, QObject *obj, t_PropertyListener func)
    //    {
    //        Property *prop = get(name);

    //        if (prop)
    //        {
    //            connect(prop, &Property::changed, (UIObject*)obj, func);

    //        }

    //    }

signals:
    void propertyChangedSignal();
};
}

#endif // CM_PROPERTYLIST_H
