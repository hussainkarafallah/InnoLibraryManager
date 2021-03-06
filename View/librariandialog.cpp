#include "View/LibrarianDialog.h"
#include "Model/usermodelentity.h"
#include "Model/validators.h"
#include <cassert>

LibrarianDialog::LibrarianDialog(QWidget *parent, int id):LibrarianDialog(parent){
    mode = ADDMODE;

    setWindowTitle("Add Librarian");
    lineEdit_card->setText(QVariant(id).toString());
    actionButton->setText("Add");


}
LibrarianDialog::LibrarianDialog(QWidget *parent, User *U):LibrarianDialog(parent){
    assert(U != nullptr);
    mode = EDITMODE;
    lineEdit_card->setText(QVariant(U->getId()).toString());
    setWindowTitle("Edit Librarian");
    actionButton->setText("Confirm Edit");
    setUser(U);


}
LibrarianDialog::LibrarianDialog(QWidget *parent) : QDialog(parent) {



  lineEdit_card = new QLineEdit();
  lineEdit_name = new QLineEdit();
  lineEdit_phoneNumber = new QLineEdit();
  plainText_address = new QPlainTextEdit();

  lineEdit_card->setReadOnly(true);

  label_card = new QLabel("Card");
  label_address = new QLabel("Address");
  label_name = new QLabel("Name");
  label_phoneNumber = new QLabel("Phone Number");
  label_userType = new QLabel("Previliges");

  passwordLabel = new QLabel("Password");
  usernameLabel = new QLabel("UserName");
  usernameBox = new  QLineEdit();
  passwordBox = new QLineEdit();

  comboBox_userType = new QComboBox();

  comboBox_userType->addItem("Prev1");
  comboBox_userType->addItem("Prev2");
  comboBox_userType->addItem("Prev3");

  gLayout = new QGridLayout();
  gLayout->addWidget(label_name, 0, 0);
  gLayout->addWidget(lineEdit_name, 0, 1);
  gLayout->addWidget(label_card, 1, 0);
  gLayout->addWidget(lineEdit_card, 1, 1);
  gLayout->addWidget(label_userType, 2, 0);
  gLayout->addWidget(comboBox_userType, 2, 1);
  gLayout->addWidget(label_phoneNumber, 3, 0);
  gLayout->addWidget(lineEdit_phoneNumber, 3, 1);
  gLayout->addWidget(label_address, 4, 0, Qt::AlignTop);
  gLayout->addWidget(plainText_address, 4, 1);
  gLayout->addWidget(usernameLabel , 5 , 0);
  gLayout->addWidget(usernameBox , 5 , 1);
  gLayout->addWidget(passwordLabel , 6 , 0);
  gLayout->addWidget(passwordBox , 6 , 1);

  actionButton = new QPushButton("Add");
  cancelButton = new QPushButton("Cancel");

  buttonLayout = new QHBoxLayout();
  buttonLayout->addWidget(actionButton);
  buttonLayout->addWidget(cancelButton);

  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelButton_clicked()));
  connect(actionButton, SIGNAL(clicked()), this, SLOT(actionButton_clicked()));

  gLayout->addLayout(buttonLayout, 7, 1, Qt::AlignCenter);
  mainLayout = new QVBoxLayout();
  mainLayout->addLayout(gLayout);
  setLayout(mainLayout);
  setWindowTitle("Add a Librarian");


}

void LibrarianDialog::actionButton_clicked() {
    if(validate()){
        if(mode == EDITMODE)
            emit submitUpdatedUser(getUser());
        else emit submitNewUser(getUser());
    }
}

void LibrarianDialog::cancelButton_clicked() { done(0); }

bool LibrarianDialog::validate() {

  /*QString name = lineEdit_name->text().trimmed();
  QString phone_number = lineEdit_phoneNumber->text().trimmed();

  if (!InputValidator::isValidUserName(name)) {
    QMessageBox::information(
        0, "Incorrect input",
        "Write both last and first names starting with capital letters and "
        "without numbers");
    return false;
  } else if (!InputValidator::isValidPhoneNumber(phone_number)) {
    QMessageBox::information(0, "Incorrect input",
                             "Phone number should be 11 symbols long");
    return false;
  }*/
  return true;
}
void LibrarianDialog::setUser(User *U){
    lineEdit_name->setText(U->getName());
    lineEdit_phoneNumber->setText(U->getPhoneNumber());
    plainText_address->setPlainText(U->getAddress());
    passwordBox->setText(U->getPassword());
    usernameBox->setText(U->getUserName());
    if(U->getType() == "Librarian1") comboBox_userType->setCurrentIndex(0);
    if(U->getType() == "Librarian2") comboBox_userType->setCurrentIndex(1);
    if(U->getType() == "Librarian3") comboBox_userType->setCurrentIndex(2);



}
User *LibrarianDialog::getUser()
{
    int Id = lineEdit_card->text().toInt();
    QString name = lineEdit_name->text();
    QString phoneNumber = lineEdit_phoneNumber->text();
    QString adress = plainText_address->toPlainText();
    QString password = passwordBox->text();
    QString username = usernameBox->text();

    int idx = comboBox_userType->currentIndex();

    return new Librarian(Id, name, adress, phoneNumber,username,password , idx + 1);


    assert(false);
    return nullptr;
}

LibrarianDialog::~LibrarianDialog() {}
