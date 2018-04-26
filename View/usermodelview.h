#ifndef USERMODELVIEW_H
#define USERMODELVIEW_H

#include "Model/usermodel.h"
#include <Model/usermodel.h>
#include <View/adduserdialog.h>
#include <View/librariandialog.h>


/*! \brief DocumentView this class is the view element that represents the user data model
 *
 *
 * This class represents the information in the user data model to the user interface. also the interface allows the librarian to interact with the system and do some queries related to users (add/edit/delete)
 *
 */
class UserModelView : public QWidget
{
    Q_OBJECT

public:
    UserModelView(QWidget *parent , UserModel *pModel , User *pUser); //!< a defailt constructor parametrized with the usermodel we want to present

    User *user;

    QTableView *view; //!< Qt tableview class that presents the data of a model into a table
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *editButton;
    QPushButton *showCheckedButton;
    QPushButton *addLibrarianButton;
    UserModel *model;
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;

    AddUserDialog *D; //!<  a dialog that's initialized whenever we want to add/edit user
    LibrarianDialog *LD;

    bool whichAdd;



public slots:
    void addButtonClicked();//!< a slot activated when the librarian requests to add a new user and it launches adding dialog
    void editButtonClicked(); //!< a slot activated when the librarian requests to edit a user so it launches a dialog and loads the user info inside
    void deleteButtonClicked(); //!< a slot activated when the librarian requests to delete a certain user
    void showButtonClicked(); //!< a slot activated when the librarian requests to show the associated docs with a certain user
    void acceptNewId(int id); //!< a slot that recieves the generated id of the new added user
    void fetchNewUser(User *U); //!< a slot that recieves the new added user information from the dialog
    void fetchUpdatedUser(User *U); //!< a slot that recieves the updated information about the edited user from the dialog
    void acceptUserData(User *U); //!< a slot that accepts a requested user data and loads it into dialog to view/edit
    void receieveAEQueryState(int report); //!< a slot that recieves the report of some add/edit query
    void acceptDeleteQueryReport(bool state); //!< a slot that recieves the report of deletion query
    void addLibrarianButtonClicked(); //!< a slot that activated when the admin decides to add new librarian and opens a dialog

signals:
    void requestNewId() const; //!< a slot activated when the librarian requests to delete a certain
    void addRequest(User *U) const; //!< a signal carrying a user that we want to add to the system
    void showUserDocsRequest(QModelIndex index); //!< a signal carrying a command to show the docs associated with a certain user
    void deleteRequest(QModelIndex index) const; //!< a signal carrying a command to delete a certain user
    void updateRequest(User *U) const; //!< a signal carrying a command to update the info of some document
    void requestUserData(QModelIndex index) const; //!< a signal carrying the request of some user's data the librarian wishes to edit/show

private:
    UserModelView(QWidget *parent , UserModel *pModel); //!< a defailt constructor parametrized with the usermodel we want to present
    UserModel *modelToView; //!<  the model this class is representing
    void setupDisplay(); //!< setting up display
    void setup(); //!<  setting up connections
    QModelIndex getCursorPosition(); //!< getting the index of the selected cell by user

};

#endif // USERMODELVIEW_H
