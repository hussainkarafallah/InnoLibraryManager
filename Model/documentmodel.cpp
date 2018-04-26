#include <Model/documententity.h>
#include <Model/documentmodel.h>
#include <cassert>
#include <QDebug>

DocumentModel::DocumentModel(QObject *parent):QStandardItemModel(parent){
    ddbProxy = new DocumentDataProxy();
    documentsList.clear();
    setRowCount(0);
    setColumnCount(Document::tableAttributes);
    setHeaderData(0, Qt::Horizontal, QString("Id"), Qt::DisplayRole);
    setHeaderData(1, Qt::Horizontal, QString("Type"), Qt::DisplayRole);
    setHeaderData(2, Qt::Horizontal, QString("Title"), Qt::DisplayRole);
    setHeaderData(3, Qt::Horizontal, QString("Authors"), Qt::DisplayRole);
    setHeaderData(4, Qt::Horizontal, QString("Publisher"), Qt::DisplayRole);
    setHeaderData(5, Qt::Horizontal, QString("Price"), Qt::DisplayRole);
    setHeaderData(6, Qt::Horizontal, QString("Reference"), Qt::DisplayRole);
    setHeaderData(7, Qt::Horizontal, QString("Best Seller"), Qt::DisplayRole);
    setHeaderData(8, Qt::Horizontal, QString("Outstanding Request"), Qt::DisplayRole);
    updateData();
}

int DocumentModel::getNewId() const{
    return ddbProxy->getNewId();
}

int DocumentModel::getNewCopyId()const{
    return ddbProxy->getNewCopyId();
}

void DocumentModel::appendDocument(Document *doc){
    assert(doc != nullptr);
    int row = documentsList.size();
    documentsList.push_back(doc);
    insertRow(row , QModelIndex());
    for(int column = 0 ; column < columnCount() ; column++)
        setData(index(row , column) , QVariant(doc->getColumnAttribute(column)));
}
void DocumentModel::updateData(){
    setRowCount(0);
    documentsList.clear();
    auto L = ddbProxy->getAll();
    for(auto it = L.begin() ; it != L.end() ; it++)
        appendDocument(*it);
}

void DocumentModel::insertDocument(Document *doc){
    assert(doc != nullptr);
    ddbProxy->addDocument(doc);
    updateData();
}
Document* DocumentModel::getByIndex(QModelIndex index){
    assert(index.isValid());
    return documentsList.at(index.row());
}
int DocumentModel::deleteByIndex(QModelIndex index){
    assert(index.isValid());
    int row = index.row();
    int ret = ddbProxy->deleteDocument(documentsList.at(row));
    updateData();
    return ret;
    //return 0;
}
void DocumentModel::updateDocument(Document *doc){
    assert(doc != nullptr);
    ddbProxy->updateDocument(doc);
    if(doc->isOutstandingRequest())
        ddbProxy->placeOutstandingRequest(doc , QDate::currentDate());
    updateData();
}
void DocumentModel::filterResults(SearchSpecifier F){
    setRowCount(0);
    documentsList.clear();
    auto L = ddbProxy->getSpecific(F);
    for(auto it = L.begin() ; it != L.end() ; it++)
        appendDocument(*it);
}
