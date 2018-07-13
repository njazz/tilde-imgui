// (c) 2017 Alex Nadzharov
// License: GPL3

#include "PropertyList.h"

#include "json.hpp"

PropertyBase* PropertyList::operator[](std::string key)
{
    return _data[key];
}

// ----------

PropertyBase* PropertyList::get(std::string key)
{
    if (_data.find(key) == _data.end())
        return 0;
    return _data[key];
};

std::vector<std::string> PropertyList::namesInGroup(UIPropertyData* d)
{
    std::vector<std::string> ret;

    for (auto it : *d) {
        ret.push_back(it.first);
    }

    return ret;
}

UIPropertyData* PropertyList::fromGroup(std::string grpName)
{
    UIPropertyData* ret;
    ret = this->_groups[grpName];
    return ret;
}

std::vector<std::string> PropertyList::groupNames()
{
    std::vector<std::string> ret;

    for (auto it = this->_groups.begin(); it != this->_groups.end(); ++it) {
        ret.push_back(it->first.c_str());
    }

    return ret;
}

std::string PropertyList::asPdFileString()
{
    std::string ret;

    //UIPropertyDataIterator it;
    for (auto it = this->_data.begin(); it != this->_data.end(); ++it) {
        //save only modified values
        if (it->second) //?
            if (it->second->isDefault()) {
                ret += " @" + it->first + " ";
                ret += it->second->asPdString() + " ";
            }
    }

    return ret;
}

// ----------

json PropertyList::toJSON()
{
    json j;

    json dataObject = json::object();

    for (auto k : _data)
        dataObject[k.first] = _data[k.first]->toJSON();

    j["data"] = dataObject;

    // todo:
//    json groupsObject = json::object();

//    for (auto k : _groups)
//        groupsObject[k.first] = _groups[k.first]->toJSON();
//    j["groups"] = groupsObject;

    return j;
};
void PropertyList::fromJSON(json j)
{
    try {
        json dataObject = j["data"];

        for (auto k:_data)
        {
            if (_data.find(k.first) != _data.end())
                _data[k.first]->fromJSON(dataObject[k.first]);

            // todo in another method:
            //_data[k.first] = PropertyBase::createFromJSON(dataObject[k.first]);
        }
        //        _data = j["data"];
        //        _groups = j["groups"];
    } catch (std::exception& e) {
        printf("ERROR: bad JSON data (%s)\n", e.what());
    }
};
std::string PropertyList::toJSONString()
{
    return toJSON().dump();
};
void PropertyList::fromJSONString(std::string s)
{
    try {
        json j = json::parse(s);
        fromJSON(j);
    } catch (std::exception& e) {
        printf("ERROR: bad JSON string (%s)\n", e.what());
    }
};

/*
namespace tilde {

UIPropertyData* PropertyList::group(QString grpName)
{
    UIPropertyData* ret;
    ret = this->_groups[grpName.toStdString()];
    return ret;
}

UIPropertyData* PropertyList::fromGroup(QString grpName)
{
    UIPropertyData* ret;
    ret = this->_groups[grpName.toStdString()];
    return ret;
}

Property* PropertyList::get(QString pName)
{
    Property* ret = 0;
    std::map<std::string, Property*>::iterator it = _data.find(pName.toStdString());
    if (it != _data.end())
        ret = this->_data[pName.toStdString()];
    return ret;
};

template <>
void PropertyList::set(std::string pName, Property* value)
{
    if (_data[pName]) {

        _data[pName] = value;
        emit get(pName.c_str())->changed();
    }
};

// -----------------

std::string PropertyList::asPdFileString()
{
    std::string ret;

    UIPropertyDataIterator it;
    for (it = this->_data.begin(); it != this->_data.end(); ++it) {
        //save only modified values
        if (it->second) //?
            if (it->second->data() != it->second->defaultData()) {
                ret += " @" + it->first + " ";
                ret += it->second->asPdSaveString().toStdString() + " ";
            }
    }

    return ret;
}




QString PropertyList::extractFromPdFileString(QString input)
{
    QStringList propertyList = input.split(" @");

    if (!propertyList.size())
        return "";

    QString ret = propertyList.at(0);
    if (ret.size())
        if (ret.at(ret.size() - 1) == " ")
            ret = ret.left(ret.size() - 1);

    if (propertyList.size() == 1)
        return ret;

    propertyList.removeAt(0);

    for (QStringList::iterator it = propertyList.begin(); it != propertyList.end(); ++it) {
        QString s = *it;
        s = Property::unescapeString(s);

        QStringList list = s.split(" ");

        //TODO
        for (int i = list.size() - 1; i > 0; i--) {
            if (list.at(i) == "") {
                list.removeAt(i);
            }
        }

        QString pname = list.at(0);

        qDebug() << list;

        if (_data[pname.toStdString()]) {
            list.removeAt(0);

            if (list.size() == 0) {
                set(pname.toStdString(), "");
            } else if (list.size() == 1)
                set(pname.toStdString(), list.at(0));
            else
                set(pname.toStdString(), list);
        } else
            ret.append(" @" + s);
    }

    return ret;
}
}

*/
