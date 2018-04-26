#ifndef NOTIFICATIONSWIDGET_H
#define NOTIFICATIONSWIDGET_H

#include<model/documententity.h>
#include <Model/usermodelentity.h>
#include <Data/documentdataproxy.h>

/*! \brief Notificationswidget class for displaying the notifications related to each user
 *
 *  This class is added to each user widget so it displays his notifications and allowing him to dismiss if he wants
 *
 *
 *
 */
namespace Ui {
class NotificationsWidget;
}

class NotificationsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NotificationsWidget(QWidget *parent = 0);
    ~NotificationsWidget();
    NotificationsWidget(User *pUser , QWidget *parent = 0);
    void updateData();


private:
    Ui::NotificationsWidget *ui;
    User *U; //!< the user which these notifications are related to
    DocumentDataProxy *ddb; //!< a proxy responsible for user queries inside the system
    QLabel *userLabel;
    QPushButton *dismissButton;
    QPlainTextEdit *textEdit; //!< the text edit that show notifications
    void appendNotif(Notification note); //!< add new notification to the list
public slots:
    void dismissButtonClicked(bool); //!< a slot activated when the user decides to dismiss his notifications
signals:
    void newNotifications() const; //!< a signal indicating that there are new notifications for this user

};

#endif // NOTIFICATIONSWIDGET_H

