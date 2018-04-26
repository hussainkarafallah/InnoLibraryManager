#ifndef TESTSUITE_H
#define TESTSUITE_H

#include "View/loginwindow.h"
#include <Model/documententity.h>
#include <Model/documentmodel.h>
#include <View/librarianwindow.h>
#include <Model/usermodel.h>
#include <Model/usermodelentity.h>
#include<Model/librariancopymodel.h>
#include <QApplication>
#include <QDebug>
#include <Data/documentdataproxy.h>
#include <cassert>
#include <QTableView>
#include "View/usermodelview.h"
#include "View/adduserdialog.h"
#include "Model/documententity.h"
#include "Controller/usermanagerwidget.h"
#include "Model/documentmodel.h"
#include "View/adddialog_av.h"
#include "View/prevdocumentview.h"
#include <Controller/documentmanagerwidget.h>
#include "Model/documentmodel.h"
#include "View/adddialog_book.h"
#include <Controller/librariancopymanager.h>
#include <Controller/usercopymanager.h>
#include<View/userwindow.h>
#include <QFile>
#include <QTextStream>

class TestSuite{
private:
    Book *d1 , *d2 , *d3;
    User *p1 , *p2 , *p3 , *s , *v;
    Librarian *l1 , *l2 , *l3;
    Admin *admin;

    QDate testsDate;

    DocumentDataProxy *docProxy;
    UserDataProxy *userProxy;

    Copy *c1 , *c2 , *c3 , *c4 , *c5 , *c6 , *c7 , *c8 , *c9;

//    UserModel *userModel;
  //  DocumentModel *docModel;
   // LibrarianCopyModel *copyModel;

    bool look_in(QList < Document* > v , Document *doc);
    bool look_in(QList < User* > v , User *u);
    bool look_in(QList < Copy* > v , Copy *copy);
public:
    void init();
    void TC1();
    void TC2();
    void TC3();
    void TC4();
    void TC5();
    void TC6();
    void TC7();
    void TC8();
    void TC9();
    void TC10();
    void TC11();
    void TC12();
    void TC13();
    void TC14();
    void mytest();
    void runnall();
    void clear();
    TestSuite();
};


#endif // TESTSUITE_H
