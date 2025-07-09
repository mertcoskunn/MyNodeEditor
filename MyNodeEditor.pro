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
    src/nodes/pintypes/DataPin.cpp \
    src/nodes/pintypes/ExecutionPin.cpp \
    src/nodes/nodetypes/math/SumNode.cpp \
    src/nodes/nodetypes/math/MultiplyNode.cpp \
    src/nodes/nodetypes/math/SubtractionNode.cpp \
    src/nodes/nodetypes/math/DivisionNode.cpp \
    src/nodes/nodetypes/PrintNode.cpp \
    src/nodes/nodetypes/StartNode.cpp \
    src/nodes/nodetypes/ConstantNode.cpp \
    src/nodes/nodetypes/BranchNode.cpp \
   
        
    

HEADERS += \
    src/mainwindow/MainWindow.h \
    src/editor/NodeEditorScene.h \
    src/editor/NodeEditorView.h \
    src/nodes/Node.h \
    src/nodes/Pin.h \
    src/nodes/ConnectionLine.h \
    src/nodes/pintypes/DataPin.h \
    src/nodes/pintypes/ExecutionPin.h \
    src/core/DataType.h \
    src/nodes/nodetypes/math/SumNode.h \
    src/nodes/nodetypes/math/MultiplyNode.h \
    src/nodes/nodetypes/math/SubtractionNode.h \
    src/nodes/nodetypes/math/DivisionNode.h \
    src/nodes/nodetypes/PrintNode.h \
    src/nodes/nodetypes/StartNode.h \
    src/nodes/nodetypes/ConstantNode.h \
    src/nodes/nodetypes/BranchNode.h \

CONFIG += console

