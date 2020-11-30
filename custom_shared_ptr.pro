TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += \
        catch_amalgamated.cpp \
        main.cpp

HEADERS += \
    catch_amalgamated.hpp \
    custom_shared_ptr.h
