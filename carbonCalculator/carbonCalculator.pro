#------------------------------------------------------
#
# Carbon Calculator library
# developed in the framework of GECO2 project
#
#-------------------------------------------------------

QT      += sql
QT      -= gui

unix:{
    CONFIG(debug, debug|release) {
        TARGET = debug/carbonCalculator
    } else {
        TARGET = release/carbonCalculator
    }
}

win32:{
    TARGET = carbonCalculator
}


TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    carbonCalculator.cpp \
    csvUtilities.cpp \
    dbQueries.cpp \
    dbUtilities.cpp \
    energyManagement.cpp \
    fertilisationAndSoil.cpp \
    soilmanagement.cpp \
    biomasstrees.cpp

HEADERS += \
    basicStructures.h \
    carbonCalculator.h \
    csvUtilities.h \
    dbQueries.h \
    dbUtilities.h \
    energyManagement.h \
    fertilisationAndSoil.h \
    soilManagement.h \
    biomasstrees.h
