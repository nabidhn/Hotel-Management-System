TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    date.cpp \
    hotel.cpp \
    cli.cpp \
    person.cpp \
    room.cpp \
    utils.cpp \
    visit.cpp

HEADERS += \
    date.hh \
    hotel.hh \
    cli.hh \
    person.hh \
    room.hh \
    utils.hh \
    visit.hh
