#-------------------------------------------------
#
# Project created by QtCreator 2018-01-31T12:36:46
#
#-------------------------------------------------

QT       += core gui
QT += sql
QT += gui
QT += widgets

CONFIG   +=  precompile_header
PRECOMPILED_HEADER = precomp.h
TARGET = InnoLibraryManager
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

precompile_header:!isEmpty(PRECOMPILED_HEADER) {
DEFINES += USING_PCH
}

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        Model/usermodel.cpp \
        Model/usermodelentity.cpp \
   #     Model/validators.cpp \
        View/adduserdialog.cpp \
        View/loginwindow.cpp \
        View/usermodelview.cpp \
        main.cpp \
    Model/documentmodel.cpp \
    Model/documententity.cpp \
    View/adddialog_book.cpp \
    View/adddialog_av.cpp \
    View/adddialog_journal.cpp \
    View/adddialog_docs.cpp \
    View/doctypedialog.cpp \
    View/userwindow.cpp \
    View/librarianwindow.cpp \
   # View/searchfilters.cpp \
    #test.cpp
    Data/userdataproxy.cpp \
    Controller/usermanagerwidget.cpp \
    Data/documentdataproxy.cpp \
    Controller/documentmanagerwidget.cpp \
    View/copydialog.cpp \
    Model/librariancopymodel.cpp \
    View/librariancopyview.cpp \
    Controller/librariancopymanager.cpp \
    Model/usercopymodel.cpp \
    View/usercopyview.cpp \
    Controller/usercopymanager.cpp \
    testsuite.cpp \
    View/notificationswidget.cpp \
    View/queueinfodialog.cpp \
 #   View/prevdocview.cpp \
    View/documentview.cpp \
    View/librariandialog.cpp \
    View/logwidget.cpp

HEADERS += \
        Model/usermodel.h \
        Model/usermodelentity.h \
     #   Model/validators.h \
        View/adduserdialog.h \
        View/loginwindow.h \
        View/usermodelview.h \
    Model/documentmodel.h \
    Model/documententity.h \
    View/adddialog_book.h \
    View/adddialog_av.h \
    View/adddialog_journal.h \
    View/adddialog_docs.h \
    View/doctypedialog.h \
    View/userwindow.h \
    View/librarianwindow.h \
#    View/searchfilters.h
    Data/userdataproxy.h \
    Controller/usermanagerwidget.h \
    Data/documentdataproxy.h \
    Controller/documentmanagerwidget.h \
    View/copydialog.h \
    Model/librariancopymodel.h \
    View/librariancopyview.h \
    Controller/librariancopymanager.h \
    Model/usercopymodel.h \
    View/usercopyview.h \
    Controller/usercopymanager.h \
    testsuite.h \
    precomp.h \
    View/notificationswidget.h \
    View/queueinfodialog.h \
    #View/prevdocumentview.h \
    View/documentview.h \
    View/librariandialog.h \
    View/logwidget.h

FORMS += \
        View/loginwindow.ui \
    View/notificationswidget.ui \
    View/queueinfodialog.ui \
    View/documentview.ui \
    View/logwidget.ui
#        View/usermodelview.ui \
#        View/userview.ui

DISTFILES += \
        README.md

RESOURCES += \
    CSS/style.qrc
