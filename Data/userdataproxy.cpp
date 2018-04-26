
#include <Model/usermodelentity.h>
#include <Data/userdataproxy.h>
#include <Model/documententity.h>

#include <cassert>

QVariant fqText(QString str){
    return QVariant(QString("\'" + str + "\'"));
}


User* UserDataProxy::getUserFromQuery(QSqlQuery query){
    User *ret = nullptr;

    if(query.value(TYPE) == "Professor")
        ret =  new Professor(query.value(ID).toInt() , query.value(NAME).toString() , query.value(ADDRESS).toString() , query.value(PHONE).toString() , query.value(USERNAME).toString() , query.value(PASSWORD).toString());
    else if(query.value(TYPE) == "TA")
        ret =  new TA(query.value(ID).toInt() , query.value(NAME).toString() , query.value(ADDRESS).toString() , query.value(PHONE).toString() , query.value(USERNAME).toString() , query.value(PASSWORD).toString());
    else if(query.value(TYPE) == "Instructor")
        ret =  new Instructor(query.value(ID).toInt() , query.value(NAME).toString() , query.value(ADDRESS).toString() , query.value(PHONE).toString() , query.value(USERNAME).toString() , query.value(PASSWORD).toString());
    else if(query.value(TYPE) == "Visiting Professor")
        ret =  new VisitingProfessor(query.value(ID).toInt() , query.value(NAME).toString() , query.value(ADDRESS).toString() , query.value(PHONE).toString() , query.value(USERNAME).toString() , query.value(PASSWORD).toString());
    else if(query.value(TYPE) == "Student") ret =  new Student(query.value(ID).toInt() , query.value(NAME).toString() , query.value(ADDRESS).toString() , query.value(PHONE).toString() , query.value(USERNAME).toString() , query.value(PASSWORD).toString());
    else if(query.value(TYPE) == "Admin") ret =  new Admin(query.value(ID).toInt() , query.value(NAME).toString() , query.value(ADDRESS).toString() , query.value(PHONE).toString() , query.value(USERNAME).toString() , query.value(PASSWORD).toString());

    else{
        QString t = QVariant(query.value(TYPE)).toString();
        int s = t.size();
        int p = t.at(s - 1).digitValue();

        ret = new Librarian(query.value(ID).toInt() , query.value(NAME).toString() , query.value(ADDRESS).toString() , query.value(PHONE).toString() , query.value(USERNAME).toString() , query.value(PASSWORD).toString() , p);
    }
    return ret;
}
UserDataProxy::UserDataProxy(){
    if(QSqlDatabase::contains("qt_sql_default_connection")){
        db = QSqlDatabase::database();
    }
    else {
        db = QSqlDatabase::addDatabase("QSQLITE");
    }

    db.setDatabaseName("Innodata.db");
    query = QSqlQuery(db);



}
User* UserDataProxy::getByCredentials(QString pUserName , QString pPassword){

    User *ret = nullptr;

    assert(db.open());

    query.prepare("SELECT * FROM USERS WHERE USERNAME = :username AND PASSWORD = :password ;");
    query.bindValue(":username",QVariant(pUserName));
    query.bindValue(":password" , QVariant(pPassword));


    if(query.exec()){

        if(query.next()){
            ret = getUserFromQuery(query);
        }

    }

    db.close();

    return ret;
}
User* UserDataProxy::getById(int pId){

    User *ret = nullptr;

    assert(db.open());

    query.prepare("SELECT * FROM USERS WHERE ID = :id ;");
    query.bindValue(":id",QVariant(pId));

    if(query.exec()){

        if(query.next()){
            ret = getUserFromQuery(query);
        }

    }else qDebug()<<"get by id query error";

    db.close();

    return ret;

}
int UserDataProxy:: getNewId(){
    int ret = 1;
    assert(db.open());
    query.prepare("SELECT MAX(ID) from USERS");
    if(query.exec()){
        if(query.next()){
            ret = query.value(0).toInt() + 1;
        }
        else qDebug()<<"empty users records";
    }
    else qDebug()<<"get new id query error";
    return ret;
}
bool UserDataProxy::checkDeletedUser(User *pUser){
    assert(db.open());

    query.prepare("SELECT * FROM COPIES WHERE USERID = :uid ;");

    query.bindValue(":uid" , pUser->getId());

    if(query.exec()){
        if(query.first())
            return false;
    }
    else qDebug()<<"checking user query error";

    return 1;
}
int UserDataProxy::checkAddedUser(User *pUser){
    assert(db.open());
    if(pUser->getType() == "Admin"){
        //qDebug()<<"yeah";
        query.prepare("SELECT * from USERS where TYPE = :type ;");
        query.bindValue(":type" , QVariant(pUser->getType()));
    }
    else{
        query.prepare("SELECT * from USERS where USERNAME = :uname AND ID != :uid ;");
        query.bindValue(":uname" , pUser->getUserName());
        query.bindValue(":uid" , pUser->getId());
    }
    if(query.exec()){
        if(query.first())
             return DuplicateUserName;
    }
    else qDebug()<<"check add edit user query error";
    return Successful;

}
void UserDataProxy::addEvent(LibraryEvent event){


    QSqlQuery query = QSqlQuery(db);

    assert(db.open());

    query.prepare("INSERT INTO LOG(DATE , EVENT) VALUES ( :date , :note ) ; ");
;
    query.bindValue(":note" , QVariant(event.getText()));
    query.bindValue(":date" , QVariant(event.getDate().toString(Qt::ISODate)));

    if(query.exec());
    else qDebug()<<"notification insertion error";

}
int UserDataProxy::checkUpdatedUser(User *pUser){
    return checkAddedUser(pUser);
}
int UserDataProxy::addUser(User *pUser , User *supervisor){

    assert(db.open());

    if(supervisor != nullptr){
        auto message = EventMessageBuilder::userCreation(pUser , supervisor);
        addEvent(LibraryEvent(message , QDate::currentDate()));
    }

    int ret =  checkAddedUser(pUser);

    if(ret != Successful) return ret;

    query.prepare("INSERT INTO USERS VALUES (:id , :name , :address , :phone , :type , :username , :password);");

    query.bindValue(":id" , QVariant(pUser->getId())); query.bindValue(":name",QVariant(pUser->getName()));
    query.bindValue(":address", QVariant(pUser->getAddress())); query.bindValue(":phone",QVariant(pUser->getPhoneNumber()));
    query.bindValue(":type" , QVariant(pUser->getType())); query.bindValue(":username",QVariant(pUser->getUserName())); query.bindValue(":password",QVariant(pUser->getPassword()));
    if(query.exec());
    else {
        qDebug()<<"adduser error query";


    }
    db.close();

    return ret;

}
int UserDataProxy::updateUser(User *pUser){


    assert(db.open());

    int ret = checkUpdatedUser(pUser);

    if(ret != Successful) return ret;

    query.prepare("UPDATE USERS SET NAME = :name , ADDRESS = :address , PHONE = :phone , TYPE = :type ,  USERNAME = :username , PASSWORD = :password WHERE ID = :id;");
    query.bindValue(":id" , QVariant(pUser->getId())); query.bindValue(":name",QVariant(pUser->getName()));
    query.bindValue(":address", QVariant(pUser->getAddress())); query.bindValue(":phone",QVariant(pUser->getPhoneNumber()));
    query.bindValue(":type" , QVariant(pUser->getType())); query.bindValue(":username",QVariant(pUser->getUserName())); query.bindValue(":password",QVariant(pUser->getPassword()));
    if(query.exec());
    else {
        qDebug()<<"edituser error query";
        for(int j = 0 ; j < 7 ; j++)
            qDebug()<<query.boundValue(j);
        qDebug()<<query.lastError().text();

    }
    db.close();

    return ret;

}
QList<User*>UserDataProxy::getAll(){
    QList< User* > ret;
    assert(db.open());

    query.prepare("SELECT * FROM USERS WHERE TYPE != \'Admin\' AND (NOT (TYPE LIKE \'%Librarian%\') ) ;");

    if(query.exec()){


        while(query.next()){

            auto pU = getUserFromQuery(query);
            ret.push_back(pU);
        }

    }

    db.close();
    return ret;
}

QList<User*>UserDataProxy::gettAllUsers(){
    QList< User* > ret;
    assert(db.open());

    query.prepare("SELECT * FROM USERS WHERE TYPE != \'Admin\' ;");

    if(query.exec()){


        while(query.next()){

            auto pU = getUserFromQuery(query);

            ret.push_back(pU);
        }

    }

    db.close();
    return ret;
}
bool UserDataProxy::deleteUser(User *pUser){

    if(!checkDeletedUser(pUser)) return 0;

    assert(db.open());
    query.prepare("DELETE FROM USERS where ID = :id ;");

    query.bindValue(":id" , QVariant(pUser->getId()));
    if(query.exec());
    else {
        qDebug()<<"delete user error query";
        for(int j = 0 ; j < 7 ; j++)
            qDebug()<<query.boundValue(j);
        qDebug()<<query.lastError().text();

    }
    db.close();
    return 1;
}
