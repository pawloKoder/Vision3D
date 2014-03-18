#-------------------------------------------------
#
# Project created by QtCreator 2014-03-11T17:07:39
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Vision3D
TEMPLATE = app
CONFIG += c++11


SOURCES += src/main.cpp\
	src/mainwindow.cpp \
    src/leftmenu.cpp \
    src/model.cpp \
    src/renderers/renderer.cpp \
	src/widget/colorlisteditor.cpp \
    src/delegates/colorlistdelegate.cpp \
    src/renderers/trajectoryrenderer.cpp \
    src/renderers/brickmodel.cpp \
	src/renderers/nodes/pathnode.cpp \
    src/delegates/basedelegate.cpp \
    src/base/filepath.cpp \
    src/delegates/spinboxdelegate.cpp \
    src/delegates/pathdelegate.cpp \
    src/widget/filepicker.cpp \
    src/renderers/nodes/colornode.cpp \
    src/delegates/proxydelegate.cpp \
    src/widget/plotarea.cpp \
    src/widget/view/viewdata.cpp \
	src/viewsettings.cpp

HEADERS  += src/mainwindow.h \
    src/leftmenu.h \
    src/model.h \
    src/renderers/renderer.h \
    src/renderers/renderers.h \
	src/widget/colorlisteditor.h \
    src/delegates/colorlistdelegate.h \
    src/renderers/trajectoryrenderer.h \
    src/renderers/brickmodel.h \
	src/renderers/nodes/pathnode.h \
    src/delegates/basedelegate.h \
    src/base/filepath.h \
    src/delegates/spinboxdelegate.h \
    src/delegates/pathdelegate.h \
	src/widget/filepicker.h \
	src/renderers/nodes/colornode.h \
    src/delegates/proxydelegate.h \
    src/widget/plotarea.h \
    src/widget/view/viewdata.h \
	src/viewsettings.h

RESOURCES += \
    rsc/icons.qrc