#include "usercopymodel.h"
#include <cassert>
UserCopyModel::UserCopyModel(QObject *parent , User *U):QStandardItemModel(parent){
    assert(U != nullptr);
    user = U;
    ddbProxy = new DocumentDataProxy();
    copiesList.clear();
    setRowCount(0);
    setColumnCount(Copy::tableAttributes);
    setHeaderData(0, Qt::Horizontal, QString("Copy Id"), Qt::DisplayRole);
    setHeaderData(1, Qt::Horizontal, QString("Document Id"), Qt::DisplayRole);
    setHeaderData(2, Qt::Horizontal, QString("Document Title"), Qt::DisplayRole);
    setHeaderData(3, Qt::Horizontal, QString("Document Type"), Qt::DisplayRole);
    setHeaderData(4, Qt::Horizontal, QString("Library Section"), Qt::DisplayRole);
    setHeaderData(5, Qt::Horizontal, QString("Copy State"), Qt::DisplayRole);
    setHeaderData(6, Qt::Horizontal, QString("Customer Id"), Qt::DisplayRole);
    setHeaderData(7, Qt::Horizontal, QString("Booking Date"), Qt::DisplayRole);
    setHeaderData(8, Qt::Horizontal, QString("Expected Return Date"), Qt::DisplayRole);
    setHeaderData(9, Qt::Horizontal, QString("Due State"), Qt::DisplayRole);
    setHeaderData(10, Qt::Horizontal, QString("Fine"), Qt::DisplayRole);
    updateData();

}
void UserCopyModel::appendCopy(Copy *copy){
    assert(copy != nullptr);
    int row = copiesList.size();
    copiesList.push_back(copy);
    insertRow(row , QModelIndex());
    for(int column = 0 ; column < Copy::tableAttributes ; column++)
        setData(index(row , column) , copy->getColumnAttribute(column));
}
void UserCopyModel::updateData(){
    copiesList.clear();
    setRowCount(0);
    auto L = ddbProxy->getAllCopiesWUser(user);
    for(auto it = L.begin() ; it != L.end() ; it++)
        appendCopy(*it);
}

bool UserCopyModel::returnByIndex(QModelIndex pIndex){
    assert(pIndex.isValid());

    auto nCopy = new Copy(*copiesList.at(pIndex.row()));
    nCopy->customerRequestForReturn();
    ddbProxy->updateCopy(nCopy);
    updateData();
    return 1;
}

int UserCopyModel::renewByIndex(QModelIndex pIndex , User *U){

    assert(pIndex.isValid());

    auto nCopy = new Copy(*copiesList.at(pIndex.row()));

    int ret = ddbProxy->renewCopy(nCopy , U , QDate::currentDate());

    assert(U->getId() == nCopy->getUserId());

    updateData();

    return ret;

}

