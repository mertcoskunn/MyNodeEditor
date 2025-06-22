QT       += core gui widgets

TARGET = MyNodeEditor
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/mainwindow/MainWindow.cpp \
    src/editor/NodeEditorScene.cpp \
    src/editor/NodeEditorView.cpp \
    src/nodes/Node.cpp \
   
        
    

HEADERS += \
    src/mainwindow/MainWindow.h \
    src/editor/NodeEditorScene.h \
    src/editor/NodeEditorView.h \
    src/nodes/Node.h \

CONFIG += console

