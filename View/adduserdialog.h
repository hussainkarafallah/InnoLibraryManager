#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include "Model/usermodelentity.h"



/*! \brief adduserdialog class for representing users information (Input/output)
 *
 *  This dialog is used by librarian to add users to the system, as well viewing their details and maybe editing them
 * it serves as a part of the view component
 *
 *
 *
 */

class AddUserDialog : public QDialog
{
    Q_OBJECT

public:
    AddUserDialog(QWidget *parent = nullptr);
    AddUserDialog(QWidget *parent , int id);
    AddUserDialog(QWidget *parent , User *U);

    ~AddUserDialog();

    User *getUser();

private:
    enum modes{ADDMODE = 0 , EDITMODE = 1};
    int mode;
    void setUser(User *U);

    QGridLayout *gLayout;
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;

    QLineEdit *lineEdit_name;
    QLineEdit *lineEdit_card;
    QLineEdit *lineEdit_phoneNumber;
    QLineEdit *usernameBox;
    QLineEdit *passwordBox;
    QPlainTextEdit *plainText_address;

    QLabel *label_name;
    QLabel *label_card;
    QLabel *label_address;
    QLabel *label_phoneNumber;
    QLabel *label_userType;
    QLabel *usernameLabel;
    QLabel *passwordLabel;

    QComboBox *comboBox_userType;

    QPushButton *actionButton;
    QPushButton *cancelButton;

    bool validate();

private slots:
    void actionButton_clicked();
    void cancelButton_clicked();
signals:
    void submitNewUser(User *U) const;
    void submitUpdatedUser(User *U) const;
};

#endif // ADDDIALOG_H
