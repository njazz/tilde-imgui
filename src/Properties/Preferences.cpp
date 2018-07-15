#include "Preferences.h"

Preferences::Preferences()
    : PropertyList()
{
    create("Version", "System", "0", std::string(APP_VERSION));
    create("Search Paths", "PureData", "0", std::vector<std::string>({ "~/" }));

    get("Version")->readOnly = true;
}
