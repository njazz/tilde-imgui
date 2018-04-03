// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <string>
#include <vector>

////
/// \brief The Clipboard class - just a string list with Pd strings for objects
class Clipboard {

private:
    std::vector<std::string> _data;

public:
    void append(std::vector<std::string> data);

    std::vector<std::string> data();
    size_t size();
    void clear();

    void setStringAt(int idx, std::string str);
    std::string get(int idx);
};

#endif // CLIPBOARD_H
