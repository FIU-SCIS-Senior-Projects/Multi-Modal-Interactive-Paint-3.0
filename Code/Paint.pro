#-------------------------------------------------
#
# Project created by QtCreator 2014-01-06T22:51:05
#-------------------------------------------------

QT       += core gui

qtHaveModule(printsupport)

#greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
QT += printsupport

TARGET = Paint
TEMPLATE = app
INSTALLS += target

SOURCES += main.cpp\
           mainwindow.cpp \
           document.cpp \
           shape.cpp \
           ellipse.cpp \
           rectangle.cpp \
           scribble.cpp \
           command.cpp \
           floodfill.cpp \
           fill.cpp \
           multiscribblearea.cpp \
           mainwindow2.cpp
	
HEADERS  += mainwindow.h \
            document.h \
            shape.h \
            command.h \
            floodfill.h \
            multiscribblearea.h \
            mainwindow2.h

OTHER_FILES += \
    README.md \
    UNLICENSE.txt \
    LICENSE.GPL
