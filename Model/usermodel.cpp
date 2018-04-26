#include "Model/usermodel.h"
#include <cassert>

UserModel::UserModel(QObject *parent) : QStandardItemModel(parent) {
    usersList.clear();
    udbProxy = new UserDataProxy();
    setRowCount(0);
    setColumnCount(5);
    setHeaderData(0, Qt::Horizontal, QString("Id"), Qt::DisplayRole);
    setHeaderData(1, Qt::Horizontal, QString("Name"), Qt::DisplayRole);
    setHeaderData(2, Qt::Horizontal, QString("Address"), Qt::DisplayRole);
    setHeaderData(3, Qt::Horizontal, QString("Phone"), Qt::DisplayRole);
    setHeaderData(4, Qt::Horizontal, QString("Role"), Qt::DisplayRole);

}

UserModel::UserModel(QObject *parent, User *U):UserModel(parent){
    assert(U != nullptr);
    user = U;
    updateData();
}
int UserModel::getNewId(){
    return udbProxy->getNewId();
}

void UserModel::appendUser(User* P) {

    int currentRow = usersList.size();

    usersList.push_back(P);

    insertRow(currentRow, QModelIndex());

    for (int column = 0; column < columnCount(QModelIndex()); ++column)
        setData(index(currentRow , column) , QVariant(P->operator[](column)).toString());
}

void UserModel::updateData(){

    setRowCount(0);

    usersList.clear();

    auto L = udbProxy->gettAllUsers();

    if(user->getType() != "Admin")
        L = udbProxy->getAll();


    for(auto it = L.begin() ; it != L.end() ; it++)
        appendUser(*it);
}
bool UserModel::deleteByIndex(QModelIndex index){
    assert(index.isValid());
    int r = index.row();
    bool ret = udbProxy->deleteUser(usersList.at(r));
    updateData();
    return ret;
}
int UserModel::insertUser(User *U){
    int rep = udbProxy->addUser(U);
    if(rep == UserDataProxy::Successful)
        udbProxy->addEvent(LibraryEvent(EventMessageBuilder::userCreation(U , user) , QDate::currentDate()));

    updateData();
    return rep;
}

User* UserModel::getByIndex(QModelIndex index){
    assert(index.isValid());
    return usersList.at(index.row());
}

int UserModel::updateUser(User *U){
    assert(U != nullptr);
    int rep = udbProxy->updateUser(U);
    if(rep == UserDataProxy::Successful)
        udbProxy->addEvent(LibraryEvent(EventMessageBuilder::userModification(U , user) , QDate::currentDate()));
    updateData();
    return rep;
}

bool UserModel::deleteUser(User *U){
    assert(U != nullptr);
    bool ret = udbProxy->deleteUser(U);
    if(ret)
        udbProxy->addEvent(LibraryEvent(EventMessageBuilder::userDeletion(U , user) , QDate::currentDate()));
    updateData();
    return ret;

}

