#ifndef USERMANAGERWIDGET_H
#define USERMANAGERWIDGET_H

#include "Model/usermodel.h"
#include "Model/usermodelentity.h"
#include "View/usermodelview.h"

/*! \brief a controller class that links the user data model and the user data view
 *
 *  This class links the document userdata view which displays the userdata model which presents the information about all users in the library
 * to the Librarian . And links between them according to the librarian queries
 */
class UserManagerWidget : public QWidget
{
    Q_OBJECT

public:
    UserManagerWidget(QWidget *parent , User *U);
private:
    explicit UserManagerWidget(QWidget *parent = 0); //!< default constructor
    User *user;  //!< the user which this widget is related to (currently logging into the system)
    UserModel *model; //!<the data model which represents the information about all users
    UserModelView *view; //!< the view class which shows the model to the librarian through an interface and allow him to interact through queries described
    void setupDisplay(); //!< setting up display
    void setup(); //!< setting up connections between model and view

private slots:
signals:
    void submitNewId(int sId) const; //!< submitting the id of the new user the librarian wants to add to the system
    void submitUserData(User *U) const; //!< submitting the information of the user the librarian wants to edit to the view
    void confirmAddEdit(int report) const; //!< submitting the status of the add/edit query whether successful or not
    void submitDeleteReport(bool state) const; //!< submitting the status of the deleting query
    void submitRequestedUser(User *U) const; //!< submitting the user that librarian requested his information (this signal is used to interact with the window)
public slots:
    void addRequestHandler(User *U); //!< a slot handles adding a new user to the library
    void IdRequestHandler(); //!< a slot handles the user query about a new ID
    void deleteRequestHandler(QModelIndex index); //!< a slot handles the user query of deleting a selected user
    void userDataRequestHandler(QModelIndex index); //!< a slot handles the user request of information about certain user selected from the interface
    void updateRequestHandler(User *U); //!< a slot handles the update request of the information of a certain user
    void showCheckedRequestHandler(QModelIndex index); //!< a slot handles the librarian request of showing certain user checked out documents
};

#endif // USERMANAGERWIDGET_H
