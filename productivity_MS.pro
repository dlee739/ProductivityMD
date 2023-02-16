QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
LIBS += -lsqlite3

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Authenticate.cpp \
    Database.cpp \
    calendar.cpp \
    calendar_task.cpp \
    loginui.cpp \
    main.cpp \
    mainwindow.cpp \
    sha512.cpp \
    task_form.cpp \
    todo_form.cpp \
    todo_list.cpp \
    todo_list_task.cpp \
    update_form_dialog.cpp \
    user.cpp

HEADERS += \
    Authenticate.h \
    Database.h \
    calendar.h \
    calendar_task.h \
    loginui.h \
    mainwindow.h \
    sha512.h \
    task_form.h \
    todo_form.h \
    todo_list.h \
    todo_list_task.h \
    update_form_dialog.h \
    user.h

FORMS += \
    loginui.ui \
    mainwindow.ui \
    task_form.ui \
    todo_form.ui \
    update_form_dialog.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
