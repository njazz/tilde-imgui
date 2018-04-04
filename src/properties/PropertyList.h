// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef CM_PROPERTYLIST_H
#define CM_PROPERTYLIST_H

#include "Property.h"

#include <map>

class UIObject;

typedef std::map<std::string, Property*> UIPropertyData;
typedef std::map<std::string, UIPropertyData*> UIPropertyGroups;

//#define PROPERTY_LISTENER(x, y) connect(objectData()->properties()->get(x), &Property::changed, this, y)
//#define PROPERTY_DISCONNECT_LISTENER(x, y) disconnect(objectData()->properties()->get(x), &Property::changed, this, y)
//#define PROPERTY_SET(x, y) objectData()->properties()->set(x, y)
//#define PROPERTY_GET(x) objectData()->properties()->get(x)

////
/// \brief Property handling class for ui object - property list
class PropertyList {

private:
    UIPropertyData _data;
    UIPropertyGroups _groups;

public:
    PropertyList(){};

    UIPropertyData* group(std::string grpName);
    UIPropertyData* fromGroup(std::string grpName);

    template <typename T>
    void create(std::string pName, std::string pGroup, std::string pVersion, T defaultData)
    {
        Property* newP = new Property;

        newP->version = (pVersion);
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
    void set(std::string pName, U value)
    {
        if (_data[pName]) {
            _data[pName]->set(value);
        }
    };

    Property* get(std::string pName);

    // ------------

    ////
    /// \brief returns string for saving in file
    std::string asPdFileString();

    ////
    /// \brief list of all property names
    /// \return
    ///
    std::vector<std::string> names();

    ////
    /// \brief list of all property names for specific propertyData
    /// \detais todo normal classes
    std::vector<std::string> names(UIPropertyData* data1);

    ////
    /// \brief list of all group names
    std::vector<std::string> groupNames();

    ////
    /// \brief extract properties from string in pd file
    /// \details returns first part of the string before the first property
    /// \return
    ///
    std::string extractFromPdFileString(std::string input);
};


#endif // CM_PROPERTYLIST_H
