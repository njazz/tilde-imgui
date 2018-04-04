// (c) 2017 Alex Nadzharov
// License: GPL3

#include "Property.h"

#include "imgui.h"

template <>
void Variant::set<std::string>(std::string val)
{
    _stringValue = val;
    _intValue = std::stoi(val);
    _floatValue = std::stof(val);
}

template <>
std::string Variant::get<std::string>()
{
    return _stringValue;
}

template <>
int Variant::get<int>()
{
    return _intValue;
}

Variant::Variant(int v)
{
    set<int>(v);
}
Variant::Variant(bool b)
{
    set<int>(b);
}
Variant::Variant(float f)
{
    set<float>(f);
}

Variant::Variant(double f)
{
    set<double>(f);
}

Variant::Variant(long f)
{
    set<long>(f);
}

Variant::Variant(std::string s)
{
    set<std::string>(s);
}

// -------

Property::Property()
{
    readOnly = false;
    type = ptNull; //?
    _applyToPd = false;
};

Property::Property(const Property& rval)
{
    readOnly = false;
    type = ptNull; //?
    _applyToPd = false;

    Property* src = const_cast<Property*>(&rval);

    group = (src->group);
    version = (src->version);
    type = (src->type);

    _data = (src->_data);
    _defaultData = (src->_defaultData);
}

Property::Property(Property& src)
{
    group = (src.group);
    version = (src.version);
    type = (src.type);

    _data = (src._data);
    _defaultData = (src._defaultData);
}

const Property Property::operator=(const Property& rval)
{
    Property ret(rval);
    return ret;
}

Property Property::operator=(Property& rval)
{
    Property ret(rval);
    return Property(rval);
}

// ----------

template <>
void Property::set<bool>(bool value)
{
    _data.clear();
    _data.push_back(Variant(value));

    type = (ptBool);
    _updated();
}

template <>
void Property::set<ImVec2>(ImVec2 value)
{
    _data.clear();
    _data.push_back(Variant(value.x));
    _data.push_back(Variant(value.y));

    type = (ptVec2);
    _updated();
}

// -------

template <>
void Property::set<float>(float value)
{
    _data.clear();
    _data.push_back(Variant(value));

    type = (ptFloat);
    _updated();
}

template <>
void Property::set<double>(double value)
{
    _data.clear();
    _data.push_back(Variant(value));

    type = (ptFloat);
    _updated();
}

template <>
void Property::set<int>(int value)
{
    _data.clear();
    _data.push_back(Variant(value));

    type = (ptInt);
    _updated();
}

template <>
void Property::set<long>(long value)
{
    _data.clear();
    _data.push_back(Variant(value));

    type = (ptInt);
    _updated();
}

// -------

template <>
void Property::set<std::string>(std::string value)
{
    _data.clear();
    _data.push_back(Variant(value));

    type = (ptString);
    _updated();
}

/*

// -------


template <>
void Property::set(QRect rect)
{
    _data = QVariantList() << rect.left() << rect.top() << rect.width() << rect.height();
    type = (ptVector);

    emit changed();
}

template <>
void Property::set(QRectF rect)
{
    _data = QVariantList() << rect.left() << rect.top() << rect.width() << rect.height();
    type = (ptVector);

    emit changed();
}


template <>
void Property::set(QColor color)
{
    _data = QVariantList() << color.red() << color.green() << color.blue() << color.alpha();
    type = (ptColor);

    //qDebug() << "set" << sL;

    emit changed();
}


template <>
void Property::set(QStringList strlist)
{
    _data = QVariantList();
    for (int i = 0; i < strlist.size(); i++)
        _data << strlist.at(i);
    type = (ptStringList);
    emit changed();
}



// -------

QSize Property::asQSize()
{
    if (_data.size() < 2)
        return QSize(0, 0);

    return QSize(_data.at(0).toInt(), _data.at(1).toInt());
}

QPoint Property::asQPoint()
{
    if (_data.size() < 2)
        return QPoint(0, 0);

    return QPoint(_data.at(0).toInt(), _data.at(1).toInt());
}

QSizeF Property::asQSizeF()
{
    if (_data.size() < 2)
        return QSizeF(0, 0);

    return QSizeF(_data.at(0).toFloat(), _data.at(1).toFloat());
}

QPointF Property::asQPointF()
{
    if (_data.size() < 2)
        return QPointF(0, 0);

    return QPointF(_data.at(0).toFloat(), _data.at(1).toFloat());
}

float Property::asFloat()
{
    if (_data.size() < 1)
        return 0.;

    return _data.at(0).toFloat();
}

int Property::asInt()
{
    if (_data.size() < 1)
        return 0.;

    return _data.at(0).toInt();
}

bool Property::asBool()
{
    if (_data.size() < 1)
        return 0.;

    return _data.at(0).toInt() > 0;
}

float Property::asFontSize()
{
    if (_data.size() < 1)
        return 8;

    return (_data.at(0).toFloat() < 8) ? 8 : _data.at(0).toFloat();
}

QColor Property::asQColor()
{
    if (_data.size() < 4)
        return QColor(0, 0, 0, 0);

    return QColor(_data.at(0).toInt(), _data.at(1).toInt(), _data.at(2).toInt(), _data.at(3).toInt());
}

QStringList Property::asQStringList()
{
    QStringList ret;

    for (int i = 0; i < _data.toVector().size(); i++)
        ret << _data.at(i).toString();

    return ret;
}

QString Property::asQString()
{
    return asQStringList().join(" ");
}

string Property::asStdString()
{
    return asQString().toStdString();
}

string Property::asPdSaveString()
{
    QString ret = asQString();

    ret = escapeString(ret);
    return ret;
}



// ----------

void Property::copyDataToDefault()
{
    _defaultData = _data;
}



void Property::setRawData(std::vector<_pType> data)
{
    _data = data;
}

void Property::setRawDefaultData(std::vector<_pType> data)
{
    _defaultData = data;
}


// ----------


QVariantList Property::data()
{
    return _data;
}

QVariantList Property::defaultData()
{
    return _defaultData;
}

// ----------

QString Property::escapeString(QString input)
{
    // todo regexp

    QString ret;

    ret = input.split(" ").join("\\ ");
    ret = ret.split("\n").join("\\n");
    ret = ret.split("\r").join("");
    ret = ret.split(",").join("\\,");
    ret = ret.split(".").join("\\.");
    ret = ret.split("@").join("\\@");
    ret = ret.split(";").join("\\;");
    return ret;
}

QString Property::unescapeString(QString input)
{
    // todo regexp

    QString ret;

    ret = input.split("\\ ").join(" ");
    ret = ret.split("\\n").join("\n");
    ret = ret.split("\\,").join(",");
    ret = ret.split("\\.").join(".");
    ret = ret.split("\\@").join("@");
    ret = ret.split("\\;").join(";");
    return ret;
}
}

*/
