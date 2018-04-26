#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDesktopWidget>
#include <QMainWindow>
#include <QStyle>
#include "Data/userdataproxy.h"

/*! \brief loginwindow this class represents the login window object shown when program is started
 *
 *
 *
 */

namespace Ui
{
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);

    ~LoginWindow();

    void openMainWindow();

private slots:
    void on_loginButton_clicked();

private:
    Ui::LoginWindow *ui;
    UserDataProxy *udbProxy;

};

#endif // LOGINWINDOW_H
