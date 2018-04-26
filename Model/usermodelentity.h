#ifndef USERMODELENTITY_H
#define USERMODELENTITY_H

/*! \brief User deferred class
 *
 *  This class represents the user object along with all setters/getters and other necessary functions.
 *
 */
class User
{
protected:
    int id;

    QString name, address, phoneNumber;
    QString username , password;
    User(int uId, QString uName, QString uAddress, QString uPhoneNumber, QString uUsername , QString uPassword);
    ~User();

public:
    int getId() const;
    QString getAddress() const;
    QString getPhoneNumber() const;
    QString getName() const;
    QString getUserName() const;
    QString getPassword() const;
    virtual QString getType() const = 0;
    QVariant operator[](int i);
    bool operator == (User *u);
};

/*! \brief Patron deferred class
 *
 *  This class represents the patron object along with all setters/getters and other necessary functions.
 *
 */
class Patron : public User
{
protected:
    Patron(int pId, QString pName, QString pAddress, QString pPhoneNumber , QString pUsername , QString pPassword);

    ~Patron();


};
/*! \brief faculty member object
 *
 *  This class represents the faculty member object along with all setters/getters and other necessary functions.
 *
 */
class FacultyMember : public Patron
{

public:
    FacultyMember(int fId, QString fName, QString fAddress, QString fPhoneNumber, QString fUsername , QString fPassword);
    QString getType() const;
    ~FacultyMember();
};


class Professor : public FacultyMember
{
public:
    Professor(int pId, QString pName, QString pAddress, QString pPhoneNumber, QString pUsername , QString pPassword);
    QString getType() const;
    ~Professor();
};

class TA : public FacultyMember
{
public:
    TA(int taId, QString taName, QString taAddress, QString taPhoneNumber, QString taUsername , QString taPassword);
    QString getType() const;
    ~TA();
};

class Instructor : public FacultyMember{
public:
    Instructor(int iId, QString iName, QString iAddress, QString iPhoneNumber, QString iUsername , QString iPassword);
    QString getType() const;
    ~Instructor();
};

class VisitingProfessor : public User{

public:
    VisitingProfessor(int vpId, QString vpName, QString vpAddress, QString iPhoneNumber, QString iUsername , QString iPassword);
    QString getType() const;
    ~VisitingProfessor();
};



/*! \brief student object
 *
 *  This class represents the stundet object along with all setters/getters and other necessary functions.
 *
 */

class Student : public Patron
{
public:
    Student(int sId, QString sName, QString sAddress, QString sPhoneNumber, QString sUsername , QString sPassword);

    QString getType() const;

    ~Student();
};
/*! \brief Librarian object
 *
 *  This class represents the librarian object along with all setters/getters and other necessary functions.
 *
 */
class Librarian : public User
{
    int previlige;
public:
    Librarian(int lId, QString lName, QString lAddress, QString lPhoneNumber ,QString lUsername , QString lPassword , int pPrev = 1);
    int getPrevilige() const;

    QString getType() const;

    ~Librarian();
};

class Admin : public User
{

public:
    Admin(int lId, QString lName, QString lAddress, QString lPhoneNumber ,QString lUsername , QString lPassword);

    QString getType() const;

    ~Admin();
};

#endif // USERMODELENTITY_H
