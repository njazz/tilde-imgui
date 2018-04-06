// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef CM_PROPERTYLIST_H
#define CM_PROPERTYLIST_H

#include "Property.h"

#include <map>

class UIObject;

typedef std::map<std::string, Property*> UIPropertyData;
typedef std::map<std::string, UIPropertyData*> UIPropertyGroups;

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
    Property* create(std::string pName, std::string pGroup, std::string pVersion, T defaultData)
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

        return newP;
    }

    // ----------

    template <typename T>
    void set(std::string pName, T value)
    {
        if (_data[pName]) {
            _data[pName]->set(value);
        }
    };


    // ----------

    Property& operator[](std::string key)
    {
        return *_data[key];
    }

    // ----------


    Property* get(std::string key)
    {
        return _data[key];
    };

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
