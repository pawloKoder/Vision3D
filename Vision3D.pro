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
    src/delegates/basedelegate.cpp \
    src/base/filepath.cpp \
    src/delegates/spinboxdelegate.cpp \
    src/delegates/pathdelegate.cpp \
    src/widget/filepicker.cpp \
    src/renderers/nodes/colornode.cpp \
    src/delegates/proxydelegate.cpp \
    src/widget/plotarea.cpp \
    src/widget/view/viewdata.cpp \
	src/viewsettings.cpp \
    src/renderers/help/xyzloader.cpp \
    src/renderers/nodes/node.cpp \
    src/delegates/doublespinboxdelegate.cpp \
    src/renderers/nodes/filepathnode.cpp \
    src/renderers/isosurfacerenderer.cpp \
    src/renderers/miprenderer.cpp \
    src/renderers/help/xyzvloader.cpp \
    src/delegates/checkboxdelegate.cpp \
    src/renderers/pointsrenderer.cpp \
    src/renderers/help/rainbow.cpp \
    src/renderers/help/basicinterpolator.cpp \
    src/renderers/meshrenderer.cpp \
    src/renderers/mesh/savefile.cpp \
    src/renderers/help/meshloader.cpp \
    src/renderers/vectorrenderer.cpp

HEADERS  += src/mainwindow.h \
    src/leftmenu.h \
    src/model.h \
    src/renderers/renderer.h \
    src/renderers/renderers.h \
	src/widget/colorlisteditor.h \
    src/delegates/colorlistdelegate.h \
    src/renderers/trajectoryrenderer.h \
    src/renderers/brickmodel.h \
    src/delegates/basedelegate.h \
    src/base/filepath.h \
    src/delegates/spinboxdelegate.h \
    src/delegates/pathdelegate.h \
	src/widget/filepicker.h \
	src/renderers/nodes/colornode.h \
    src/delegates/proxydelegate.h \
    src/widget/plotarea.h \
    src/widget/view/viewdata.h \
	src/viewsettings.h \
    src/renderers/help/xyzloader.h \
    src/base/strings.h \
    src/renderers/nodes/node.h \
    src/delegates/doublespinboxdelegate.h \
    src/renderers/nodes/filepathnode.h \
    src/renderers/isosurfacerenderer.h \
    src/renderers/miprenderer.h \
    src/renderers/help/xyzvloader.h \
    src/delegates/checkboxdelegate.h \
    src/renderers/pointsrenderer.h \
    src/renderers/help/rainbow.h \
    src/renderers/help/basicinterpolator.h \
    src/renderers/meshrenderer.h \
    src/renderers/mesh/savefile.h \
    src/renderers/help/meshloader.h \
    src/renderers/vectorrenderer.h

RESOURCES += \
    rsc/icons.qrc
