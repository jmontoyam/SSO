#-------------------------------------------------
#
# Project created by QtCreator 2014-09-08T15:33:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Android_Compute_Only_C
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

CONFIG += mobility
MOBILITY = 

#Path to Eigen Library
INCLUDEPATH += "/home/user/Documents/ProgrammingLibraries/Cplusplus/eigen_3_2_2"

#Path to SSO folder
INCLUDEPATH += "/home/user/Desktop/SSO_Git"

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -DNDEBUG

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml


