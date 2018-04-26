#ifndef USERWINDOW_H
#define USERWINDOW_H

#include<Controller/documentmanagerwidget.h>
#include<Controller/usercopymanager.h>
#include <View/notificationswidget.h>

/*! \brief userwindow a simple class that represents the user window which consists of some other view widgets
 *
 * This class links these view components together so the user applies all his queries in the demanded way
 *
 */
class UserWindow : public QMainWindow
{
    Q_OBJECT

private:
    User *U;
    QVBoxLayout *mainLayout;
    QStackedWidget *stackedWidget;
    QScrollArea* scrollarea;

    DocumentManagerWidget *docManager;  //!< the complete unit of managing documents (the user mode) which is much more limited than librarin
    UserCopyManager *copyManager; //!<  the complete unit of managing copies. so the user could manage his own. This class is much more limited than librarin one
    NotificationsWidget *notif; //!< the widget that displays the notifications related to some user

public:
    UserWindow(QWidget *parent , User *U); //!< constructor
public slots:
    void switchToDocMode(); //!< a slot activated when the user wishes to take a look at documents in library and maybe book some of them
    void switchToMyBooksMode(); //!< a slot activated so the user window switches the widget to the copyview object that represents the copies associated with the user
    void switchToMyNotifMode();  //!< a slot activated so the user window switches to the notifications section
    void acceptNotifications();  //!< a slot that when activates notifies the user logging in that he has notifications
    void logOut(); //!< a slot that logs out
};
#endif // USERWINDOW_H
