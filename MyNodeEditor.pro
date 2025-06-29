QT       += core gui widgets

TARGET = MyNodeEditor
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/mainwindow/MainWindow.cpp \
    src/editor/NodeEditorScene.cpp \
    src/editor/NodeEditorView.cpp \
    src/nodes/Node.cpp \
    src/nodes/Pin.cpp \
    src/nodes/ConnectionLine.cpp \
    src/nodes/nodetypes/DataPin.cpp \
    src/nodes/nodetypes/ExecutionPin.cpp \
   
        
    

HEADERS += \
    src/mainwindow/MainWindow.h \
    src/editor/NodeEditorScene.h \
    src/editor/NodeEditorView.h \
    src/nodes/Node.h \
    src/nodes/Pin.h \
    src/nodes/ConnectionLine.h \
    src/nodes/nodetypes/DataPin.h \
    src/nodes/nodetypes/ExecutionPin.h \

CONFIG += console

