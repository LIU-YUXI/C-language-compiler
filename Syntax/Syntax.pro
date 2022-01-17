QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Project1lexer/ActionAndGoto.cpp \
    ../Project1lexer/LexicalAnalysis.cpp \
    ../Project1lexer/LexicalToken.cpp \
    ../Project1lexer/SemanticAnalysis.cpp \
    ../Project1lexer/SyntaxAnalyzer.cpp \
    childwindow.cpp \
    main.cpp \
    syntax.cpp

HEADERS += \
    ../Project1lexer/ActionAndGoto.h \
    ../Project1lexer/LexicalAnalysis.h \
    ../Project1lexer/SemanticAnalysis.h \
    ../Project1lexer/SyntaxAnalyzer.h \
    childwindow.h \
    syntax.h

FORMS += \
    childwindow.ui \
    syntax.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
