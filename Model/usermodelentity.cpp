#include "Model/usermodelentity.h"

User::User(int uId, QString uName, QString uAddress, QString uPhoneNumber, QString uUsername , QString uPassword){
    id = uId;
    name = uName;
    address = uAddress;
    phoneNumber = uPhoneNumber;
    username = uUsername;
    password = uPassword;
}

int User::getId() const {
    return id;
}

QString User::getAddress() const {
    return address;
}
QString User::getPhoneNumber() const {
    return phoneNumber;
}
QString User::getName() const {
    return name;
}

QString User::getUserName() const{
    return username;
}
QString User::getPassword() const{
    return password;
}

User::~User() {}

Patron::Patron(int pId, QString pName, QString pAddress, QString pPhoneNumber , QString pUsername , QString pPassword)
    : User(pId, pName, pAddress, pPhoneNumber , pUsername , pPassword) {}

QVariant User::operator[](int i) {

    if (i == 0)
        return QVariant(id);
    if (i == 1)
        return QVariant(name);
    if (i == 2)
        return QVariant(address);
    if (i == 3)
        return QVariant(phoneNumber);
    if (i == 4)
        return QVariant(getType());

    return QVariant();
}

Patron::~Patron() {}

Student::Student(int sId, QString sName, QString sAddress, QString sPhoneNumber, QString sUsername , QString sPassword)
    : Patron(sId, sName, sAddress, sPhoneNumber , sUsername , sPassword) {}

QString Student::getType() const {
    return "Student";
}

Student::~Student() {}

FacultyMember::FacultyMember(int fId, QString fName, QString fAddress,
                             QString fPhoneNumber, QString fUsername , QString fPassword)
    : Patron(fId, fName, fAddress, fPhoneNumber,fUsername , fPassword) {}

FacultyMember::~FacultyMember() {}

QString FacultyMember::getType() const {
    return "Faculty Member";
}


Professor::Professor(int pId, QString pName, QString pAddress, QString pPhoneNumber, QString pUsername, QString pPassword):
    FacultyMember(pId,  pName,  pAddress, pPhoneNumber, pUsername, pPassword){}

QString Professor::getType() const{
    return "Professor";
}

Professor::~Professor(){}


TA::TA(int taId, QString taName, QString taAddress, QString taPhoneNumber, QString taUsername, QString taPassword):
    FacultyMember( taId,  taName,  taAddress,  taPhoneNumber,  taUsername,  taPassword){}

QString TA::getType() const{
    return "TA";
}
TA::~TA(){}


Instructor::~Instructor(){}
Instructor::Instructor(int iId, QString iName, QString iAddress, QString iPhoneNumber, QString iUsername, QString iPassword):
    FacultyMember( iId,  iName,  iAddress,  iPhoneNumber,  iUsername,  iPassword){}
QString Instructor::getType() const{
    return "Instructor";
}

QString VisitingProfessor::getType() const{
    return "Visiting Professor";
}

VisitingProfessor::VisitingProfessor(int vpId, QString vpName, QString vpAddress, QString iPhoneNumber, QString iUsername, QString iPassword):
    User(vpId,  vpName, vpAddress,  iPhoneNumber,  iUsername, iPassword){}
VisitingProfessor::~VisitingProfessor(){}


Librarian::Librarian(int pId, QString pName, QString pAddress,
                     QString pPhoneNumber , QString lUsername , QString lPassword , int pPrev)
    : User(pId, pName, pAddress, pPhoneNumber , lUsername , lPassword) {
        previlige = pPrev;
}

Librarian::~Librarian() {}

Admin::~Admin(){}
Admin::Admin(int lId, QString lName, QString lAddress, QString lPhoneNumber, QString lUsername, QString lPassword):
    User(lId, lName, lAddress, lPhoneNumber , lUsername , lPassword){}
QString Admin::getType() const{
    return "Admin";
}


QString Librarian::getType() const {
    if(previlige == 1)
        return "Librarian1";
    if(previlige == 2)
        return "Librarian2";
    if(previlige == 3)
        return "Librarian3";
}

int Librarian::getPrevilige() const{
    return previlige;
}
bool User::operator == (User *u){
    for(int j = 0 ; j  < 5 ; j++)
        if(this->operator [](j) != u->operator [](j))
            return false;
    return true;
}
