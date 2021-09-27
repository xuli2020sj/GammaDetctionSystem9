QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    command.cpp \
    connectplc.cpp \
    controller.cpp \
    detector.cpp \
    log.cpp \
    main.cpp \
    mainwindow.cpp \
    manager.cpp \
    setting.cpp \
    snap7.cpp \
    utilities.cpp

HEADERS += \
    command.h \
    connectplc.h \
    controller.h \
    detector.h \
    log.h \
    mainwindow.h \
    manager.h \
    setting.h \
    snap7.h \
    utilities.h

FORMS += \
    connectplc.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32: LIBS += -L$$PWD/snap7/ -lsnap7

INCLUDEPATH += $$PWD/snap7
DEPENDPATH += $$PWD/snap7
