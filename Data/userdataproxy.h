#ifndef USERDATAPROXY_H
#define USERDATAPROXY_H

#include <Model/usermodelentity.h>
#include <Model/documententity.h>

/*! \brief a proxy that links our application to the database.
 *
 *  This class links our application data models (presenters) to the database. It's responsible for all queries regarding users
 *
 */
class UserDataProxy{
private:
    QSqlDatabase db; //!< database connection
    enum attribute {ID = 0 , NAME = 1 , ADDRESS = 2 , PHONE = 3 , TYPE = 4 , USERNAME = 5 , PASSWORD = 6}; //!< enumerators for users attributes
    QSqlQuery query; //!< Qtsql query object
public:
    enum userQueryRep{Successful = 0 , DuplicateUserName = 1}; //!< report for adding/editing user name if it's possible or some problem occurred

    UserDataProxy(); //!< default constructor
    User* getByCredentials(QString pUserName , QString pPassword); //!<  gets a user from database by his credentials
    User* getById(int pId); //!<  gets a user from database by his ID
    int getNewId(); //!< gets an ID which doesn't exist in the database for a new user
    int addUser(User *pUser, User *supervisor = nullptr); //!<  adds a new user to the database
    int updateUser(User *pUser); //!<  updates the info about a user in the database
    int checkAddedUser(User *pUser); //!< checks whether we can add this user to the database without confliction
    int checkUpdatedUser(User *pUser); //!<  checks whether we can update this user in the database without confliction
    bool deleteUser(User *pUser); //!<  deletes a user from the database
    QList <User*> getAll(); //!<  gets all patrons from the database
    bool checkDeletedUser(User *pUser); //!< checks whether we can delete this user from system
    QList <User*> gettAllUsers(); //!<  gets all users from the database
    void addEvent(LibraryEvent event);  //!< a function that adds an event to the library log
    User* getUserFromQuery(QSqlQuery query); //!< gets the user object from inside a record

};
#endif // USERDATAPROXY_H
