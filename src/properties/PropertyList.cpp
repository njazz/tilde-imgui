// (c) 2017 Alex Nadzharov
// License: GPL3

#include "PropertyList.h"

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

QStringList PropertyList::names()
{
    QStringList ret;

    UIPropertyDataIterator it;
    for (it = this->_data.begin(); it != this->_data.end(); ++it) {
        //save only modified values
        ret.push_back(it->first.c_str());
    }

    return ret;
}

QStringList PropertyList::names(UIPropertyData* data1)
{
    QStringList ret;

    UIPropertyDataIterator it;
    for (it = data1->begin(); it != data1->end(); ++it) {
        //save only modified values
        ret.push_back(it->first.c_str());
    }

    return ret;
}

QStringList PropertyList::groupNames()
{
    QStringList ret;

    UIPropertyGroupIterator it;
    for (it = this->_groups.begin(); it != this->_groups.end(); ++it) {
        //save only modified values
        ret.push_back(it->first.c_str());
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
