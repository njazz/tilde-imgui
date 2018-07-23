#ifndef LEGACY_PARSER_H
#define LEGACY_PARSER_H

#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

typedef std::vector<std::string> FileParserList;

class LegacyParser{

    static const std::unordered_map<std::string, std::function<FileParserList(FileParserList)> > _selectors;

    template <int I>
    static FileParserList _converter(FileParserList src);

public:
  static FileParserList convertLegacyString(FileParserList src);
};


#endif
