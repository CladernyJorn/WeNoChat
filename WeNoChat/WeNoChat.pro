#-------------------------------------------------
#
# Project created by QtCreator 2022-08-18T21:50:15
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WeNoChat
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        login.cpp \
    mainwindow.cpp \
    regist.cpp \
    jsoncpp.cpp \
    user.cpp \
    question.cpp \
    password.cpp \
    chatmessagewidget.cpp \
    communicate_utils.cpp \
    searchfriends.cpp \
    friendlist.cpp \
    messagerecord.cpp \
    viewfullmessage.cpp \
    wncimage.cpp

HEADERS  += login.h \
    mainwindow.h \
    regist.h \
    json/json.h \
    json/json-forwards.h \
    user.h \
    question.h \
    password.h \
    chatmessagewidget.h \
    communicate_utils.h \
    searchfriends.h \
    friendlist.h \
    messagerecord.h \
    viewfullmessage.h \
    wncimage.h

FORMS    += login.ui \
    mainwindow.ui \
    regist.ui \
    user.ui \
    question.ui \
    password.ui \
    searchfriends.ui \
    viewfullmessage.ui

RESOURCES += \
    uires.qrc
