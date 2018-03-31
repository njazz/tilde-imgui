// (c) 2017 Alex Nadzharov
// License: GPL3

#include "Property.h"
//#include <QDebug>

//#include <QVariantList>

using namespace std;

namespace tilde {

// ----------

Property::Property()
{
    _readOnly = false;
    _type = ptList; //?
    _applyToPd = false;
};

Property::Property(const Property& rval)
{
    _readOnly = false;
    _type = ptList; //?
    _applyToPd = false;

    Property* src = const_cast<Property*>(&rval);

    setGroup(src->group());
    setVersion(src->version());
    setType(src->type());

    setRawData(src->data());
    setRawDefaultData(src->defaultData());
}

// -------

template <>
void Property::set(bool value)
{
    _data = QVariantList() << value;
    setDefaultType(ptBool);

    emit changed();
}

template <>
void Property::set(QPoint point)
{
    _data = QVariantList() << point.x() << point.y();
    setDefaultType(ptVec2);
    emit changed();
}

template <>
void Property::set(QPointF point)
{

    _data = QVariantList() << point.x() << point.y();
    setDefaultType(ptVec2);

    emit changed();
}

template <>
void Property::set(QRect rect)
{
    _data = QVariantList() << rect.left() << rect.top() << rect.width() << rect.height();
    setDefaultType(ptVector);

    emit changed();
}

template <>
void Property::set(QRectF rect)
{
    _data = QVariantList() << rect.left() << rect.top() << rect.width() << rect.height();
    setDefaultType(ptVector);

    emit changed();
}
template <>
void Property::set(QSize size)
{
    _data = QVariantList() << size.width() << size.height();
    setDefaultType(ptVec2);

    emit changed();
}

template <>
void Property::set(QSizeF size)
{
    _data = QVariantList() << size.width() << size.height();
    setDefaultType(ptVec2);

    emit changed();
}

template <>
void Property::set(QColor color)
{
    _data = QVariantList() << color.red() << color.green() << color.blue() << color.alpha();
    setDefaultType(ptColor);

    //qDebug() << "set" << sL;

    emit changed();
}

template <>
void Property::set(float val)
{
    _data = QVariantList() << val;
    setDefaultType(ptFloat);

    emit changed();
}

template <>
void Property::set(double val)
{
    _data = QVariantList() << val;
    setDefaultType(ptFloat);

    emit changed();
}

template <>
void Property::set(int val)
{
    _data = QVariantList() << val;
    setDefaultType(ptInt);

    emit changed();
}

template <>
void Property::set(QStringList strlist)
{
    _data = QVariantList();
    for (int i = 0; i < strlist.size(); i++)
        _data << strlist.at(i);
    setDefaultType(ptStringList);
    emit changed();
}

template <>
void Property::set(QString string)
{
    set(string.split(" "));
}

template <>
void Property::set(string string)
{
    set(QString(string.c_str()));
}

template <>
void Property::set(char const* string)
{
    set(QString(string));
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

// -------

Property::Property(Property& src)
{
    //Property* src = const_cast<Property*>(&rval);

    setGroup(src.group());
    setVersion(src.version());
    setType(src.type());

    setRawData(src.data());
    setRawDefaultData(src.defaultData());
}

const Property Property::operator=(const Property& rval)
{
    Property ret(rval);
    //qDebug() << "const" << ret.asQString();
    return ret;
}

Property Property::operator=(Property& rval)
{
    Property ret(rval);
    qDebug() << "non const" << ret.asQString();
    return Property(rval);
}

// -------

void Property::setDefaultType(UIPropertyType type)
{
    if (_defaultData == QVariant())
        _type = type;
}

void Property::copyDataToDefault()
{
    _defaultData = _data;
}

void Property::setVersion(string version)
{
    _version = version;
}

void Property::setGroup(string grp)
{
    _group = grp;
}

void Property::setType(UIPropertyType type)
{
    _type = type;
}

void Property::setRawData(std::vector<_pType> data)
{
    _data = data;
}

void Property::setRawDefaultData(std::vector<_pType> data)
{
    _defaultData = data;
}

std::string Property::version() { return _version; }
std::string Property::group() { return _group; }

// ----------

void Property::setReadonly(bool v) { _readOnly = v; }
bool Property::readOnly() { return _readOnly; };

// ----------

UIPropertyType Property::type() { return _type; };

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
