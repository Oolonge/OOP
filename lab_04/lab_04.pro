QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += Button/ Cabin/ Controller/ Doors/ Elevator/ Elevators/ HallCtrl/

SOURCES += \
    Button/button.cpp \
    Cabin/cabin.cpp \
    Controller/controller.cpp \
    Controller/controller2.cpp \
    Doors/doors.cpp \
    Elevator/elevator.cpp \
    Elevators/elevators.cpp \
    HallCtrl/hall_buttons_controller.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Button/button.h \
    Cabin/cabin.h \
    Controller/controller.h \
    definitions.h \
    Doors/doors.h \
    Elevator/elevator.h \
    Elevators/elevators.h \
    HallCtrl/hall_buttons_controller.h \
    mainwindow.h \
    #p.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
