QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = carbonCalculator

INCLUDEPATH += ../carbonCalculatorLib

CONFIG(release, debug|release) {
    LIBS += -L../carbonCalculatorLib/release -lcarbonCalculatorLib
} else {
    LIBS += -L../carbonCalculatorLib/debug -lcarbonCalculatorLib
}


SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
