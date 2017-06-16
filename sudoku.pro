#-------------------------------------------------
#
# Project created by QtCreator 2017-03-17T14:48:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sudoku
TEMPLATE = app

CONFIG  += warn_on
CONFIG  += c++11
QMAKE_CXXFLAGS += -W -Wall -Wextra -pedantic


INCLUDEPATH += ./include
DEPENDPATH += ./include
MOC_DIR  = moc
OBJECTS_DIR  = obj
SOURCES += src/main.cpp \
    src/controller.cpp \
    src/displayer.cpp \
    src/model.cpp \
    src/playcommand.cpp \
    src/sudokuedit.cpp \
    src/sudokumainwindow.cpp \
    src/level.cpp \
    src/difficulty.cpp \
    src/scoremanager.cpp

HEADERS  += \
    include/controller.h \
    include/displayer.h \
    include/model.h \
    include/playcommand.h \
    include/sudokuedit.h \
    include/sudokumainwindow.h \
    include/level.h \
    include/difficulty.h \
    include/scoremanager.h


FORMS    += sudokuwindow.ui


TRANSLATIONS = langs/sudoku_en.ts langs/sudoku_fr.ts

RESOURCES += \
    resources/levels.qrc
