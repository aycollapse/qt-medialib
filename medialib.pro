QT += core gui widgets
CONFIG += c++17

INCLUDEPATH += src

SOURCES += $$files(src/*.cpp, true)
HEADERS += $$files(src/*.h, true)

OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui
DESTDIR = dist

TARGET = medialib
