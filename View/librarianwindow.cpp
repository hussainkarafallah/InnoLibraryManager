#include <Model/documentmodel.h>
#include <Model/usermodel.h>
#include <View/prevdocumentview.h>
#include <View/librarianwindow.h>
#include <View/loginwindow.h>
#include <View/userwindow.h>


LibrarianWindow::LibrarianWindow(QWidget *parent , User*U) : QMainWindow(parent)
{
  setFixedSize(800, 800);

  docManager = new DocumentManagerWidget(this , U);
  userManager = new UserManagerWidget(this , U);
  copyManager = new LibrarianCopyManager(this , U);
  logWidget = new LogWidget(this);

  setWindowTitle("Welcome " + U->getType() + "  " + U->getName());
  userManager->hide();
  QMenuBar *bar = new QMenuBar(this);

   setMenuBar(bar);

   QMenu *menu = bar->addMenu("Switch mode");

   QAction *a1 = menu->addAction("Manage Books");
   QAction *a2 = menu->addAction("Manage Users");
   QAction *a3 = menu->addAction("Manage Copies");
   QAction *a4 = new QAction("Library Log");


   stackedWidget = new QStackedWidget();

   stackedWidget->addWidget(docManager);
   stackedWidget->addWidget(userManager);
   stackedWidget->addWidget(copyManager);
   stackedWidget->addWidget(logWidget);

   if(U->getType() == "Admin") menu->addAction(a4);

   QAction *a5 = menu->addAction("Log Out");


   setCentralWidget(stackedWidget);

   connect(a1, SIGNAL(triggered(bool)), this, SLOT(switchToBooksMode()));
   connect(a2, SIGNAL(triggered(bool)), this, SLOT(switchToUsersMode()));
   connect(a3 , SIGNAL(triggered(bool)) , this , SLOT(switchToCopiesMode()));
   connect(a4 , SIGNAL(triggered(bool)) , this , SLOT(switchToLogMode()));
   connect(a5 , SIGNAL(triggered(bool)) , this , SLOT(logOut()));

   connect(userManager , SIGNAL(submitRequestedUser(User*)) , this , SLOT(switchToUserInfo(User*)) , Qt::UniqueConnection);

   connect(docManager , SIGNAL(copyChanged()) , copyManager , SLOT(refresh()) , Qt::UniqueConnection);


   //! Places the window to the screen center.
   setFixedSize(900 , 600);
   this->setGeometry(
       QStyle::alignedRect(
           Qt::LeftToRight,
           Qt::AlignCenter,
           this->size(),
           qApp->desktop()->availableGeometry()
       )
   );
}

void LibrarianWindow::switchToBooksMode() {
  stackedWidget->setCurrentWidget(docManager);
}

void LibrarianWindow::switchToUsersMode() {
  stackedWidget->setCurrentWidget(userManager);
}

void LibrarianWindow::switchToCopiesMode(){
    stackedWidget->setCurrentWidget(copyManager);
}
void LibrarianWindow::switchToUserInfo(User *U){
    copyManager->userInfoRequestHandler(U);
    stackedWidget->setCurrentWidget(copyManager);
}
void LibrarianWindow::switchToLogMode(){
    stackedWidget->setCurrentWidget(logWidget);
}
void LibrarianWindow::logOut(){
    LoginWindow *w = new LoginWindow();
    close();
    w->show();
}
