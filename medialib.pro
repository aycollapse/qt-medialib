QT += core gui widgets
CONFIG += c++17

INCLUDEPATH += src

SOURCES += $$files(src/*.cpp) \
           $$files(src/core/models/*.cpp) \
           $$files(src/core/visitors/*.cpp) \
           $$files(src/core/*.cpp) \
           $$files(src/gui/*.cpp)

HEADERS += $$files(src/*.h) \
           $$files(src/core/models/*.h) \
           $$files(src/core/visitors/*.h) \
           $$files(src/core/*.h) \
           $$files(src/gui/*.h)

OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui
DESTDIR = bin

TARGET = medialib
