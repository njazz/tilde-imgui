#include "LegacyParser.h"

#include <functional>
#include <unordered_map>

#include <algorithm>

const int _tokenMsg = 1;
const int _tokenText = 2;
const int _tokenFloatAtom = 3;
const int _tokenSymbolAtom = 4;
const int _tokenArray = 5;
const int _tokenObj = 6;

const int _objNameBng = 10;
const int _objNameTgl = 11;
const int _objNameHsl = 12;
const int _objNameVsl = 13;
const int _objNameNumber2 = 14;
const int _objNameHRadio = 15;
const int _objNameVRadio = 16;
const int _objNameCnv = 17;

FileParserList LegacyParser::convertLegacyString(FileParserList src)
{
    FileParserList ret = src;

    if (src.size() < 4) {
        return src;
    }

    auto token = src[0];
    auto objName = src[3];

    if (_selectors.find(token) != _selectors.end()) {
        return _selectors.at(token)(src);
    }

    if (_selectors.find(objName) != _selectors.end()) {
        return _selectors.at(objName)(src);
    }

    return ret;
}

// ==========

template <>
FileParserList LegacyParser::_converter<_tokenMsg>(FileParserList src)
{
    FileParserList ret = src;

    if (src.size() < 1)
        return ret;

    ret = src;

    ret[0] = "obj";
    ret.insert(ret.begin() + 3, "ui.msg");

    return ret;
}

template <>
FileParserList LegacyParser::_converter<_tokenFloatAtom>(FileParserList src)
{
    FileParserList ret;

    if (src.size() < 1)
        return ret;

    ret.push_back("obj");
    ret.push_back(src[1]);
    ret.push_back(src[2]);
    ret.push_back("ui.float");

    ret.push_back("@Size");
    ret.push_back(src[3]);
    ret.push_back("20");

    ret.push_back("@Min");
    ret.push_back(src[4]);

    ret.push_back("@Max");
    ret.push_back(src[5]);

    ret.push_back("@LabelPosition");
    ret.push_back(src[4]);
    ret.push_back("Left");
    ret.push_back("Right");
    ret.push_back("Top");
    ret.push_back("Bottom");

    ///\todo 'processLabels' separate function?

    if (src.size() > 8) {
        std::string lLabel = "";
        std::string lSend = "";
        std::string lReceive = "";

        lLabel = ((std::string)src.at(7));
        lSend = ((std::string)src.at(9));
        lReceive = ((std::string)src.at(8));

        ret.push_back("@LegacyLabel");
        ret.push_back(lLabel);
        ret.push_back("@SendSymbol");
        ret.push_back(lSend);
        ret.push_back("@ReceiveSymbol");
        ret.push_back(lReceive);
    }

    return ret;
}

template <>
FileParserList LegacyParser::_converter<_tokenSymbolAtom>(FileParserList src)
{
    ///\todo this is a stub. either make ui.symbolatom or embed in other object

    FileParserList ret = { "obj", "0", "0", "ui.msg", "<symbol>" };

    if (src.size() < 3)
        return ret;

    ret[1] = src[1];
    ret[2] = src[2];

    ret.push_back("@Size");
    ret.push_back(src[3]);
    ret.push_back("20");

    ret.push_back("@Min");
    ret.push_back(src[4]);

    ret.push_back("@Max");
    ret.push_back(src[5]);

    ret.push_back("@LabelPosition");
    ret.push_back(src[4]);
    ret.push_back("Left");
    ret.push_back("Right");
    ret.push_back("Top");
    ret.push_back("Bottom");

    ///\todo 'processLabels' separate function?

    if (src.size() > 8) {
        std::string lLabel = "";
        std::string lSend = "";
        std::string lReceive = "";

        lLabel = ((std::string)src.at(7));
        lSend = ((std::string)src.at(9));
        lReceive = ((std::string)src.at(8));

        ret.push_back("@LegacyLabel");
        ret.push_back(lLabel);
        ret.push_back("@SendSymbol");
        ret.push_back(lSend);
        ret.push_back("@ReceiveSymbol");
        ret.push_back(lReceive);
    }

    return ret;
}

template <>
FileParserList LegacyParser::_converter<_tokenText>(FileParserList src)
{
    FileParserList ret = src;

    if (src.size() < 2)
        return ret;

    ret = src;
    ret[0] = "obj";
    ret.insert(ret.begin() + 3, "ui.text");
    ret.insert(ret.begin() + 4, "@Text");

    return ret;
}

template <>
FileParserList LegacyParser::_converter<_tokenArray>(FileParserList src)
{
    ///\todo this is a stub. returns array with name

    FileParserList ret = src;

    if (src.size() < 1)
        return ret;

    ret = { "obj ", "20 ", "20 ", "ui.array ", src.at(1) };

    return ret;
}

// ---

template <>
FileParserList LegacyParser::_converter<_objNameBng>(FileParserList src)
{
    FileParserList ret;

    ///\todo this is a stub

    if (src.size() < 2)
        return ret;

    ret = { "obj", "0", "0", "ui.bang" };

    ret[1] = src[1];
    ret[2] = src[2];

    ret.push_back("@Size " + src[4] + src[4]);

    return ret;
}

template <>
FileParserList LegacyParser::_converter<_objNameTgl>(FileParserList src)
{
    FileParserList ret;

    ///\todo this is a stub

    ret = { "obj", "0", "0", "ui.toggle" };

    ret[1] = src[1];
    ret[2] = src[2];

    ret.push_back("@Size " + src[4] + src[4]);

    return ret;
}

template <>
FileParserList LegacyParser::_converter<_objNameHsl>(FileParserList src)
{
    FileParserList ret;

    ///\todo this is a stub

    if (src.size() < 2)
        return ret;

    ret = { "obj", "0", "0", "ui.slider" };

    ret[1] = src[1];
    ret[2] = src[2];

    ///\ todo common code hsl/vsl
    if (src.size() > 5) {
        ret.push_back("@Size");
        ret.push_back(src[4]);
        ret.push_back(src[5]);
        ret.push_back("@Offset");
        ret.push_back(src[6]);
        ret.push_back("@Range");
        ret.push_back(src[7]);
    }

    return ret;
}

template <>
FileParserList LegacyParser::_converter<_objNameVsl>(FileParserList src)
{
    //    FileParserList ret;

    //    return ret;

    return _converter<_objNameHsl>(src);
}

template <>
FileParserList LegacyParser::_converter<_objNameHRadio>(FileParserList src)
{
    FileParserList ret = src;

    ///\todo this is a stub

    if (src.size() < 2)
        return ret;

    ret = { "obj", "0", "0", "ui.matrix" };

    ret[1] = src[1];
    ret[2] = src[2];

    ///\todo get size

    ret.push_back("@Columns");
    ret.push_back("5");
    ret.push_back("@Rows");
    ret.push_back("1");

    ///\todo size

    if (src.size() > 4) {
        ret.push_back("@Size");
        ret.push_back(src[4]);
        ret.push_back(std::to_string(std::stof(src[4]) * 5)); //lol}
    }

    return ret;
}

template <>
FileParserList LegacyParser::_converter<_objNameVRadio>(FileParserList src)
{
    FileParserList ret = src;

    ///\todo this is a stub

    if (src.size() < 2)
        return ret;

    ret = { "obj", "0", "0", "ui.matrix" };

    ret[1] = src[1];
    ret[2] = src[2];

    ///\todo get size

    ret.push_back("@Columns");
    ret.push_back("1");
    ret.push_back("@Rows");
    ret.push_back("5");

    ///\todo size

    if (src.size() > 4) {
        ret.push_back("@Size");
        ret.push_back(src[4]);
        ret.push_back(std::to_string(std::stof(src[4]) * 5)); //lol}
    }

    return ret;
}

template <>
FileParserList LegacyParser::_converter<_objNameNumber2>(FileParserList src)
{
    FileParserList ret = src;

    return ret;
}

template <>
FileParserList LegacyParser::_converter<_objNameCnv>(FileParserList src)
{
    FileParserList ret;

    if (src.size() < 10)
        return src;

    std::string fontSize = (src.size() > 13) ? (src.at(13)) : "11";


    long color2;
    color2 = (src.size() > 14) ? std::stol(src.at(14)) : 0;
    long color1;
    color1 = (src.size() > 15) ? std::stol(src.at(15)) : 0;

    //    std::cout << "*** colors" << color1 << color2;

    union color {
        int32_t c_int;
        struct {
            uint8_t b[8];
        } c_byte;
    };

    color c1;
    c1.c_int = color1;
    color c2;
    c2.c_int = color2;

    //    std::cout << "*** colors" << c1.c_int << c2.c_int;

    c1.c_int = -1 - c1.c_int;
    c1.c_int = ((c1.c_int & 0x3f000) << 6) | ((c1.c_int & 0xfc0) << 4) | ((c1.c_int & 0x3f) << 2);

    c2.c_int = -1 - c2.c_int;
    c2.c_int = ((c2.c_int & 0x3f000) << 6) | ((c2.c_int & 0xfc0) << 4) | ((c2.c_int & 0x3f) << 2);

    //    std::cout << (c1.c_int & 0xFF) << ((c1.c_int >> 8) & 0xFF) << ((c1.c_int >> 16) & 0xFF) << ((c1.c_int >> 24) & 0xFF);

    std::string lcolor1 = std::to_string(c1.c_byte.b[2]) + " " + std::to_string(c1.c_byte.b[1]) + " " + std::to_string(c1.c_byte.b[0]) + " 255";
    std::string lcolor2 = std::to_string(c2.c_byte.b[2]) + " " + std::to_string(c2.c_byte.b[1]) + " " + std::to_string(c2.c_byte.b[0]) + " 255";

    //    std::cout << lcolor1 << lcolor2 << " ***";

    std::string lLabel = "";
    lLabel = ((std::string)src.at(7));
    if (lLabel == "empty")
        lLabel = "";

    ret.push_back("obj");
    ret.push_back(src.at(1));
    ret.push_back(src.at(2));
    ret.push_back("ui.text");
    ret.push_back("@Text");
    ret.push_back(lLabel);
    ret.push_back("@FontSize");
    ret.push_back(fontSize);
    ret.push_back("@TextColor");
    ret.push_back(lcolor1);
    ret.push_back("@BackgroundColor");
    ret.push_back(lcolor2);
    ret.push_back("@AutoResizeToText");
    ret.push_back("0");
    ret.push_back("@Size");
    ret.push_back(src.at(5));
    ret.push_back(src.at(6));


    std::string lSend = "";
    std::string lReceive = "";


    lSend = ((std::string)src.at(9));
    lReceive = ((std::string)src.at(8));

//    ret.push_back("@LegacyLabel");
//    ret.push_back(lLabel);
    ret.push_back("@SendSymbol");
    ret.push_back(lSend);
    ret.push_back("@ReceiveSymbol");
    ret.push_back(lReceive);

    return ret;
}

//
const std::unordered_map<std::string, std::function<FileParserList(FileParserList)> > LegacyParser::_selectors = {
    { "msg", &LegacyParser::_converter<_tokenMsg> },
    { "floatatom", &LegacyParser::_converter<_tokenFloatAtom> },
    { "symbolatom", &LegacyParser::_converter<_tokenSymbolAtom> },
    { "text", &LegacyParser::_converter<_tokenText> },
    { "array", &LegacyParser::_converter<_tokenArray> },
    //
    { "bng", &LegacyParser::_converter<_objNameBng> },
    { "tgl", &LegacyParser::_converter<_objNameTgl> },
    { "hsl", &LegacyParser::_converter<_objNameHsl> },
    { "vsl", &LegacyParser::_converter<_objNameVsl> },
    { "hradio", &LegacyParser::_converter<_objNameHRadio> },
    { "vradio", &LegacyParser::_converter<_objNameVRadio> },
    { "number2", &LegacyParser::_converter<_objNameNumber2> },
    { "cnv", &LegacyParser::_converter<_objNameCnv> }

};
