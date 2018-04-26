#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "Data/userdataproxy.h"
#include "Data/documentdataproxy.h"
#include <View/librarianwindow.h>
#include <View/userwindow.h>

LoginWindow::LoginWindow(QWidget *parent) : ui(new Ui::LoginWindow) {
  ui->setupUi(this);
  ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
  udbProxy = new UserDataProxy();

  setFixedSize(800, 600);
  setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
                                  this->size(),
                                  qApp->desktop()->availableGeometry()));
}

LoginWindow::~LoginWindow() { delete ui; }

void LoginWindow::on_loginButton_clicked() { openMainWindow(); }

void LoginWindow::openMainWindow() {
    auto u = udbProxy->getByCredentials(ui->usernameLineEdit->text().trimmed() , ui->passwordLineEdit->text().trimmed());
    if(u == nullptr){
        QMessageBox::information(nullptr , "Failed To Login" , "No such credentials in the system" , QMessageBox::Ok);
    }
    else{
        if(u->getType() == "Admin" || u->getType().at(0) == 'L'){
            auto window = new LibrarianWindow(nullptr , u);
            window->show();
            close();
        }
        else{
            auto window = new UserWindow(nullptr , u);
            window->show();
            close();
        }
    }
}
