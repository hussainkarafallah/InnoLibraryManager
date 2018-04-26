#include "librariancopymodel.h"
#include<cassert>

LibrarianCopyModel::LibrarianCopyModel(QObject *parent):QStandardItemModel(parent){
    ddbProxy = new DocumentDataProxy();
    udbProxy = new UserDataProxy();
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
    setHeaderData(9, Qt::Horizontal, QString("Due Status"), Qt::DisplayRole);
    setHeaderData(10, Qt::Horizontal, QString("Fine"), Qt::DisplayRole);
    updateData();

}
void LibrarianCopyModel::appendCopy(Copy *copy){
    assert(copy != nullptr);
    int row = copiesList.size();
    copiesList.push_back(copy);
    insertRow(row , QModelIndex());
    for(int column = 0 ; column < Copy::tableAttributes ; column++)
        setData(index(row , column) , copy->getColumnAttribute(column));
}
void LibrarianCopyModel::updateData(){
    copiesList.clear();
    setRowCount(0);
    auto L = ddbProxy->getAllCopies();
    for(auto it = L.begin() ; it != L.end() ; it++)
        appendCopy(*it);
}

bool LibrarianCopyModel::deleteByIndex(QModelIndex pIndex){
    assert(pIndex.isValid());
    if(data(index(pIndex.row() , 5)).toString() != "Not Booked")
        return 0;
    ddbProxy->deleteCopy(copiesList.at(pIndex.row()));
    updateData();
    return 1;
}


bool LibrarianCopyModel::deleteCopy(Copy *copy){
    assert(copy != nullptr);
    ddbProxy->deleteCopy(copy);
    updateData();
    return 1;
}
void LibrarianCopyModel::updateDataAWUser(User *U){
    assert(U != nullptr);
    copiesList.clear();
    setRowCount(0);
    auto L = ddbProxy->getAllCopiesWUser(U);
    for(auto it = L.begin() ; it != L.end() ; it++)
        appendCopy(*it);
}

bool LibrarianCopyModel::immediateReturnByIndex(QModelIndex pIndex){
    assert(pIndex.isValid());
    if(data(index(pIndex.row() , 5)).toString() == "Not Booked")
        return 0;
    auto nCopy = new Copy(*copiesList.at(pIndex.row()));
    ddbProxy->performImmediateReturn(nCopy , QDate::currentDate());
    updateData();
    return 1;
}

bool LibrarianCopyModel::confirmPendingRequestByIndex(QModelIndex pIndex){
    assert(pIndex.isValid());
    if(data(index(pIndex.row() , 5)).toString() != "Pending Renewal" && data(index(pIndex.row() , 5)).toString() != "Pending Return")
        return 0;
    auto nCopy = new Copy(*copiesList.at(pIndex.row()));
    if(nCopy->getState() == 2)
        nCopy->returnToLibrary();
    else {
        auto userToRenew = udbProxy->getById(nCopy->getUserId());
        qDebug()<<userToRenew->getName();
        nCopy->renew(userToRenew , nCopy->getReturnDate());
    }
    ddbProxy->updateCopy(nCopy);
    updateData();
    return 1;
}
void LibrarianCopyModel::insertCopy(Copy *copy){
    assert(copy != nullptr);
    ddbProxy->addCopy(copy);
}
