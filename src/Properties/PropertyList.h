// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef CM_PROPERTYLIST_H
#define CM_PROPERTYLIST_H

//#include "Property.h"

#include "Property.h"

#include "PropertyTypes.h"

#include <map>

class UIObject;

typedef std::map<std::string, PropertyBase*> UIPropertyData;
typedef std::map<std::string, UIPropertyData*> UIPropertyGroups;

//typedef std::map<std::string, PropertyBase*> UIPropertyData__;

////
/// \brief Property handling class for ui object - property list
class PropertyList {

private:
    UIPropertyData _data;
    UIPropertyGroups _groups;

public:
    PropertyList(){};

    template <typename T>
    PropertyBase* create(std::string pName, std::string pGroup, std::string pVersion, T defaultData);

    template <typename T>
    void set(std::string pName, T value);

    void setFromString(std::string pName, std::string str);

    PropertyBase* get(std::string key);
    PropertyBase* operator[](std::string key);

    // -------------

    ////
    /// \brief list of all property names
    /// \return
    std::vector<std::string> allNames();

    UIPropertyData* fromGroup(std::string grpName);

    ////
    /// \brief list of all property names for specific propertyData
    /// \detais todo: normal classes?
    std::vector<std::string> namesInGroup(UIPropertyData* d);

    ////
    /// \brief list of all group names
    std::vector<std::string> groupNames();

    // --------------

    ////
    /// \brief extract properties from object string in pd file
    /// \details returns first part of the string before the first property
    /// \return
    std::string extractFromPdFileString(std::string input);

    ////
    /// \brief returns string for saving in file
    std::string asPdFileString();

    // -----

    json toJSON();
    void fromJSON(json j);  // loads from JSON into existing properties
    std::string toJSONString();
    void fromJSONString(std::string s);
};

// ----------

template <typename T>
PropertyBase* PropertyList::create(std::string pName, std::string pGroup, std::string pVersion, T defaultData)
{

    auto newP = new PropertyT<T>();

    newP->version = (pVersion);
    newP->setDefaultValue(defaultData);
    newP->set(defaultData);

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
void PropertyList::set(std::string pName, T value)
{
    if (_data[pName]) {
        auto p_ = _data[pName]->typed<T>();
        if (p_)
            p_->template set(value);
    }
};



#endif // CM_PROPERTYLIST_H
