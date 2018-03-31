// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef CM_PROPERTY_H
#define CM_PROPERTY_H

//using namespace std;
#include <string>
#include <utility>
#include <vector>

namespace tilde {


typedef enum {
    ptBool,
    ptFloat,
    ptInt,
    ptSymbol,
    ptList,
    ptString,
    ptVector,
    ptColor,
    ptVec2,
    ptStringList,
    ptPath,         ///> file or directory
    ptPathList,
    ptEnum,         ///> index and option list
    ptText          ///< multiline text for comments, script

} UIPropertyType;

//class _pType : public std::variant<int,float>;

class _pType{};

////
/// \brief property handling class for ui object.
/// \details this is different from CEAMMC library property handling library - later merge / unify that
///
class Property {


private:
    std::vector<_pType>_data;
    std::vector<_pType>_defaultData;

    std::string _group;
    std::string _version;

    UIPropertyType _type;

    bool _readOnly;

    bool _applyToPd; ///> true if property value should be passed to pd object

public:
    explicit Property();
    Property(const Property& src);
    Property( Property& src);

    const Property operator=(const Property& rval);
    Property operator=(Property& rval);

    // -------

    template <typename T>
    void set(T val);

    void copyDataToDefault(); ///> copy current value to default value

    void setVersion(std::string version);
    void setGroup(std::string grp);
    void setType(UIPropertyType t);

    void setRawData(std::vector<_pType> data);
    void setRawDefaultData(std::vector<_pType> data);

    void setReadonly(bool v);
    bool readOnly();

    // -------

    void setDefaultType(UIPropertyType type);

    // -------

    std::vector<_pType> data();
    std::vector<_pType> defaultData();
    std::string group();
    std::string version();
    UIPropertyType type();

//    // -------

//    QSize asQSize();
//    QSizeF asQSizeF();
//    QPoint asQPoint();
//    QPointF asQPointF();
//    float asFloat();
//    int asInt();
//    bool asBool();
//    float asFontSize();
//    QColor asQColor();
//    QStringList asQStringList();
//    string asStdString();
//    QString asQString();

    std::string asPdSaveString();

    // -------

    // todo move?
//    static QString escapeString(QString input);
//    static QString unescapeString(QString input);

//signals:
//    void changed();
};
}

#endif // CM_PROPERTY_H
