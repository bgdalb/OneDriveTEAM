QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++latest

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    EditTrashBin.cpp \
    editrecyclebin.cpp \
    editwindow.cpp \
    folderchecking.cpp \
    loginscreen.cpp \
    main.cpp \
    mainwindow.cpp \
    recyclebindialog.cpp \
    recyclebinview.cpp \
    registerscreen.cpp \
    sendfile.cpp \
    serverconnector.cpp

HEADERS += \
    EditTrashBin.h \
    editrecyclebin.h \
    editwindow.h \
    folderchecking.h \
    loginscreen.h \
    mainwindow.h \
    recyclebindialog.h \
    recyclebinview.h \
    registerscreen.h \
    sendfile.h \
    serverconnector.h 

FORMS += \
    EditTrashBin.ui \
    editrecyclebin.ui \
    editwindow.ui \
    loginscreen.ui \
    mainwindow.ui \
    recyclebindialog.ui \
    recyclebinview.ui \
    registerscreen.ui  \
    sendFileWindow.ui \
    sendfile.ui \
    test.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

