#include <Model/documentmodel.h>
#include <View/prevdocumentview.h>
#include <View/userwindow.h>
#include <View/loginwindow.h>

 UserWindow::UserWindow(QWidget *parent, User *U):QMainWindow(parent){
    setFixedSize(900 , 600);


    docManager = new DocumentManagerWidget(this , U);
    copyManager = new UserCopyManager(this , U);
    notif = new NotificationsWidget( U , this);

    QMenuBar *bar = new QMenuBar(this);

    setMenuBar(bar);

     QMenu *menu = bar->addMenu("Switch mode");

     QAction *a1 = menu->addAction("Library Documents");
     QAction *a2 = menu->addAction("Manage My Documents");
     QAction *a3 = menu->addAction("My Notifications");
     QAction *a4 = menu->addAction("Log Out");

     setWindowTitle("Welcome Patron " + U->getName());

     stackedWidget = new QStackedWidget();

     stackedWidget->addWidget(docManager);
     stackedWidget->addWidget(copyManager);
     stackedWidget->addWidget(notif);

     setCentralWidget(stackedWidget);

     connect(a1, SIGNAL(triggered(bool)), this, SLOT(switchToDocMode()) , Qt::UniqueConnection);
     connect(a2, SIGNAL(triggered(bool)), this, SLOT(switchToMyBooksMode()) , Qt::UniqueConnection);
     connect(a3 , SIGNAL(triggered(bool)) , this , SLOT(switchToMyNotifMode()) , Qt::UniqueConnection);
     connect(a4 , SIGNAL(triggered(bool)) , this , SLOT(logOut()) , Qt::UniqueConnection);


     connect(docManager , SIGNAL(copyChanged()) , copyManager , SLOT(refresh()) , Qt::UniqueConnection);



     //! Places the window to the screen center.
     this->setGeometry(
         QStyle::alignedRect(
             Qt::LeftToRight,
             Qt::AlignCenter,
             this->size(),
             qApp->desktop()->availableGeometry()
         )
     );

     connect(notif , SIGNAL(newNotifications()) , this , SLOT(acceptNotifications()) , Qt::UniqueConnection);

     notif->updateData();
}
void UserWindow::switchToDocMode(){
    stackedWidget->setCurrentWidget(docManager);
}
void UserWindow::switchToMyBooksMode(){
    stackedWidget->setCurrentWidget(copyManager);
}

void UserWindow::switchToMyNotifMode(){
    stackedWidget->setCurrentWidget(notif);
}

void UserWindow::acceptNotifications(){
    QMessageBox::information(nullptr , "New Notifications" , "You have new notifications" , QMessageBox::Ok);
}
void UserWindow::logOut(){
    LoginWindow *w = new LoginWindow();
    close();
    w->show();
}
