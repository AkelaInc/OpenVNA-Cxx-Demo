#-------------------------------------------------
#
# Project created by QtCreator 2015-05-06T10:08:29
#
#-------------------------------------------------

QT       += core gui

QWT_INCLUDE_DIR: $$PWD/../qwt/src/
QWT_LIBRARY: /usr/local/qwt-6.1.3-svn/lib/

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = VNATest
TEMPLATE = app

DEFINES += VNA_BUILD

CONFIG  += console

SOURCES += main.cpp       \
           mainwindow.cpp \
           vnalibrary.cpp

HEADERS += mainwindow.h             \
    $$PWD/../../../../dlls/vnadll/akela_vna_dll.h \
    vnalibrary.h                    \
    wrapperclasses.h

FORMS    += mainwindow.ui

# TODO: executable requires the dll in the local directory. Build process puts dll in Release folder.
# Getting qt to put this executable in the Release folder would solve the problem.

# Also TODO: the Qwt dependency paths are hard-coded and windows-specific

win32:CONFIG(release, debug|release): {
    LIBS += -L"$$_PRO_FILE_PWD_/../../build-out/qwt/lib/"
    LIBS += -L$$PWD/../Debug/
    LIBS += -lqwt
}
else:win32:CONFIG(debug, debug|release): {
    LIBS += -L"$$_PRO_FILE_PWD_/../../build-out/qwt/lib/"
    LIBS += -L$$PWD/../Debug/
	LIBS += -lqwtd
}
else:unix:CONFIG(release, debug|release): {
    LIBS += -L/usr/lib
    LIBS += -L"$$_PRO_FILE_PWD_/../../build-VNA_Base-Desktop_Qt_5_5_1_GCC_64bit-Debug/qwt/lib/"
    LIBS += -L$$PWD/../Debug/
    LIBS += -lqwt
    DEFINES *= "LINUX=true"
    QMAKE_CXXFLAGS += -g -Og
}
else:unix:CONFIG(debug, debug|release): {
    LIBS += -L/usr/lib
    LIBS += -L"$$_PRO_FILE_PWD_/../../build-VNA_Base-Desktop_Qt_5_5_1_GCC_64bit-Debug/qwt/lib/"
    LIBS += -L$$PWD/../Debug/
	LIBS += -lqwtd
    DEFINES *= "LINUX=true"
    QMAKE_CXXFLAGS += -g -Og
}



INCLUDEPATH += $$PWD/../qwt/src
DEPENDPATH  += $$PWD/../qwt/src

win32: {
  copydata.commands = cp \"$$PWD/../../../../Win32/Release/vnadll.dll\" \"$$OUT_PWD\"
  first.depends = $(first) copydata
  export(first.depends)
  export(copydata.commands)
  QMAKE_EXTRA_TARGETS += first copydata
}

# # Copy the DLL into the output dir, so things actually work.
# win32:CONFIG(release, debug|release): {
# 	copydata.commands = cp \"$$PWD/../../../Win32/Release/vnadll.dll\" \"$$OUT_PWD\"
# 	first.depends = $(first) copydata
# 	export(first.depends)
# 	export(copydata.commands)
# 	QMAKE_EXTRA_TARGETS += first copydata
# }
# else:win32:CONFIG(debug, debug|release): {
# 	copydata.commands = cp \"$$PWD/../../../Win32/Debug/vnadll.dll\" \"$$OUT_PWD/debug/\"
# 	first.depends = $(first) copydata
# 	export(first.depends)
# 	export(copydata.commands)
# 	QMAKE_EXTRA_TARGETS += first copydata
# }

