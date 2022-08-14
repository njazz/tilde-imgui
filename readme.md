## tilde~ / imgui

archived, to be replaced with third JUCE-based version

Development repository, early prototype.

[![Build Status](https://travis-ci.org/njazz/tilde-imgui.svg?branch=master)](https://travis-ci.org/njazz/tilde-imgui)
[![codecov](https://codecov.io/gh/njazz/tilde-imgui/branch/master/graph/badge.svg)](https://codecov.io/gh/njazz/tilde-imgui)

tilde~ is a new integrated GUI for Puredata.

Meanwhile check out this Pd library and build:
https://github.com/uliss/pure-data

Build:



mkdir tilde_imgui && cd tilde_imgui

mkdir imgui && cd imgui

git clone --depth=50 --branch=master https://github.com/njazz/imgui-mvc-wrap.git

cd ..

mkdir tilde && cd tilde

git clone --depth=50 --branch=master https://github.com/njazz/tilde-imgui.git

mkdir build && cd build && cmake ..

