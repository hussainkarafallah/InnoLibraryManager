#include "notificationswidget.h"
#include "ui_notificationswidget.h"
#include <cassert>

NotificationsWidget::NotificationsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NotificationsWidget)
{
    ui->setupUi(this);
}

NotificationsWidget::NotificationsWidget(User *pUser, QWidget *parent):NotificationsWidget(parent){
    assert(pUser != nullptr);

    U = pUser;

    ddb = new DocumentDataProxy();

    userLabel = ui->label;

    userLabel->setText("Notifications Log For User" + U->getName());

    dismissButton = ui->pushButton;

    textEdit = ui->plainTextEdit;

    textEdit->setReadOnly(true);

    connect(dismissButton , SIGNAL(clicked(bool)) , this , SLOT(dismissButtonClicked(bool)));

    updateData();
}

void NotificationsWidget::updateData(){
    textEdit->setPlainText("");
    auto L = ddb->getNotifForUser(U);
    if(L.size() > 0)
        emit newNotifications();
    for(auto note : L)
        appendNotif(*note);
}
void NotificationsWidget::dismissButtonClicked(bool){
    ddb->clearNotifForUser(U);
    updateData();

}
void NotificationsWidget::appendNotif(Notification note){
    auto cur = textEdit->toPlainText();
    cur += note.getStartDate().toString(Qt::ISODate);
    cur += "\n";
    cur += note.getText();
    cur += "\n";
    cur += "\n";

    textEdit->setPlainText(cur);

}
NotificationsWidget::~NotificationsWidget()
{
    delete ui;
}
