#-------------------------------------------------
#
# Project created by QtCreator 2015-05-06T10:08:29
#
#-------------------------------------------------

QT       += core gui

QWT_INCLUDE_DIR: /usr/include/qwt
QWT_LIBRARY: /usr/local/qwt-6.1.3-svn/lib/

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = VNATest
TEMPLATE = app

CONFIG  += console

SOURCES += main.cpp       \
           mainwindow.cpp \
           vnalibrary.cpp

HEADERS += mainwindow.h             \
    $$PWD/../vnadll/akela_vna_dll.h \
    vnalibrary.h                    \
    wrapperclasses.h

FORMS    += mainwindow.ui

# TODO: executable requires the dll in the local directory. Build process puts dll in Release folder.
# Getting qt to put this executable in the Release folder would solve the problem.

# Also TODO: the Qwt dependency paths are hard-coded and windows-specific

win32:CONFIG(release, debug|release): {
    LIBS += -L$$PWD/qwt-build/lib/ -L$$PWD/../Debug/ -lqwt
}
else:win32:CONFIG(debug, debug|release): {
    LIBS += -L$$PWD/qwt-build/lib/ -L$$PWD/../Debug/ -lqwtd
}
else:unix:CONFIG(release, debug|release): {
    LIBS += -L/usr/lib
    LIBS += -L/usr/local/qwt-6.1.3-svn/lib/
    LIBS += -L$$PWD/../Debug/
    LIBS += -lqwt
    DEFINES *= "LINUX=true"
    QMAKE_CXXFLAGS += -g -Og
}
else:unix:CONFIG(debug, debug|release): {
    LIBS += -L/usr/lib
    LIBS += -L/usr/local/qwt-6.1.3-svn/lib/
    LIBS += -L$$PWD/../Debug/
    LIBS += -lqwt
    DEFINES *= "LINUX=true"
    QMAKE_CXXFLAGS += -g -Og
}


win32: {
    INCLUDEPATH += $$PWD/qwt-6.1/src
    DEPENDPATH  += $$PWD/qwt-6.1/src
}
else:unix:
{
    INCLUDEPATH += /usr/local/qwt-6.1.3-svn/include/
    DEPENDPATH  += /usr/local/qwt-6.1.3-svn/include/
}


# Copy the DLL into the output dir, so things actually work.
win32: {
    copydata.commands = cp \"$$PWD/../Debug/vnadll.dll\" \"$$OUT_PWD/debug/\"
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata
}
