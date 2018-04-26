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
#include<testsuite.h>
#include <QStandardPaths>
#include <QDesktopServices>
#include <QDir>


/*!
 *
 *  \authors Hussain Kara Fallah
 *  \version 1.0
 *  \mainpage InnoLibraryManager
 *
 *  \warning Project is based and tested on Qt 5.10.0
 *
 *  \date 2018, March
 *
 */



void runapp(){
    TestSuite T = TestSuite();

    T.runnall();
    T.TC4();

    LoginWindow *w = new LoginWindow();

    w->show();

}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile f("CSS/style.qss");
    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        a.setStyleSheet(ts.readAll());
    }
    runapp();
    return a.exec();
}
