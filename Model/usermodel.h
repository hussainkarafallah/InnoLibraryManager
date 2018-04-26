#ifndef USERMODEL_H
#define USERMODEL_H

#include "Model/usermodelentity.h"
#include "Data/userdataproxy.h"

/*! \brief User Model which we represent the information of our library users inside
 *
 *  This class is linked to the database and it stores the information requested by the librarian throught the view, and is presented to the librarian through the view object that maintains the interface
 *  and let him interact with the users information (add/edit/delete/etc) . It's a table styled model.
 *
 */
class UserModel : public QStandardItemModel
{
    Q_OBJECT

private:
    QList<User*> usersList; //!< a list containing users in our model
    UserDataProxy *udbProxy; //!< a proxy that links to the database
    void updateData(); //!< a function that updates the data in our model
    void appendUser(User* P); //!< a functiont hat appends a certain user to our model
    explicit UserModel(QObject *parent = nullptr); //!< constructor
    User *user;


public:
    UserModel(QObject *parent , User *U);
    int getNewId(); //!<  a function that gets a new id for a new added user to the library
    int insertUser(User *U); //!< a function that inserts a new user into the model as well into the library
    bool deleteByIndex(QModelIndex index); //!< a function that deletes a user from the library the librarian referring to through the view
    bool deleteUser(User *U); //!< a function that deletes a user passed to this function as a parameter
    User* getByIndex(QModelIndex index); //!<  a function that gets the information of a certain user the librarian referring to
    int updateUser(User *U); //!<  a function that updates a certain user information in the model as well in the library records (database)
public slots:

};

#endif
