#include "documentview.h"
#include "ui_documentview.h"
#include <View/prevdocumentview.h>
#include<View/copydialog.h>
#include <cassert>

DocumentView::DocumentView(QWidget *parent, DocumentModel *pModel):QWidget(parent),ui(new Ui::DocumentView){

    assert(pModel != nullptr);

    ui->setupUi(this);


    editButton = ui->editButton;
    bookButton = ui->bookButton;
    addButton = ui->addButton;
    deleteButton = ui->deleteButton;
    viewButton = ui->viewButton;
    addCopyButton = ui->addCopyButton;
    showQueueButton = ui->showQueueButton;

    authorSearch = ui->authorEdit;
    titleSearch = ui->titleEdit;
    keywordsSearch = ui->keywordsEdit;
    criteriaCheck = ui->radioButton;

    bookCheck = ui->bookCheck;
    avCheck = ui->avCheck;
    articleCheck = ui->articleCheck;

    view = ui->tableView;

    model = pModel;

    view->setModel(model);

    typeDialog = new DocTypeDialog(nullptr);

    copyDialog = new CopyDialog();
    copyDialog ->hide();

    docDialog = new AddDialog_book(nullptr , 0);
    docDialog->hide();

    setupDisplay();
    setup();

}

void DocumentView::setupDisplay() {
}

DocumentView::~DocumentView(){
    delete ui;
}
DocumentView::DocumentView(QWidget *parent , DocumentModel *pModel , User *pUser):DocumentView(parent , pModel){

    assert(pUser != nullptr && pModel != nullptr);

    user = pUser;

    if(user->getType() == "Admin" || user->getType() == "Librarian3"){
        mode = LIBRARIANMODE;
        bookButton->hide();
    }
    else if(user->getType() == "Librarian1"){
        deleteButton->hide();
        addButton->hide();
        bookButton->hide();
    }
    else if(user->getType() == "Librarian2"){
        deleteButton->hide();
        bookButton->hide();
    }
    else{
        mode = USERMODE;
        editButton->hide();
        addButton->hide();
        deleteButton->hide();
        addCopyButton->hide();
        showQueueButton->hide();
    }


}
void DocumentView::setup(){

    connect(addButton , SIGNAL(clicked(bool)) , this , SLOT(addButtonClicked()) , Qt::UniqueConnection);
    connect(editButton , SIGNAL(clicked(bool)) , this , SLOT(editButtonClicked()) , Qt::UniqueConnection);
    connect(addCopyButton , SIGNAL(clicked(bool)) , this , SLOT(addCopyButtonClicked()) , Qt::UniqueConnection);
    connect(deleteButton , SIGNAL(clicked(bool)) , this , SLOT(deleteButtonClicked()) , Qt::UniqueConnection);
    connect(viewButton , SIGNAL(clicked(bool)) , this , SLOT(viewButtonClicked()) , Qt::UniqueConnection);
    connect(bookButton , SIGNAL(clicked(bool)) , this , SLOT(bookButtonClicked()) , Qt::UniqueConnection);
    connect(showQueueButton , SIGNAL(clicked(bool)) , this , SLOT(showQueueButtonClicked()) , Qt::UniqueConnection);

    connect(authorSearch , SIGNAL(textChanged(QString)) , this , SLOT(getFilters()) , Qt::UniqueConnection);
    connect(titleSearch , SIGNAL(textChanged(QString)) , this , SLOT(getFilters()) , Qt::UniqueConnection);
    connect(keywordsSearch , SIGNAL(textChanged(QString)) , this , SLOT(getFilters()) , Qt::UniqueConnection);

    connect(bookCheck , SIGNAL(stateChanged(int)) , this , SLOT(getFilters()) , Qt::UniqueConnection);
    connect(avCheck , SIGNAL(stateChanged(int)) , this , SLOT(getFilters()) , Qt::UniqueConnection);
    connect(articleCheck , SIGNAL(stateChanged(int)) , this , SLOT(getFilters()) , Qt::UniqueConnection);

    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

QModelIndex DocumentView::getCursorPosition(){
    QItemSelectionModel *selection = view->selectionModel();

    if (selection->hasSelection()) {
        if (selection->isRowSelected(selection->currentIndex().row(),QModelIndex())){
          return selection->currentIndex();
        }
    }
    return QModelIndex();
}





void DocumentView::disconnectDialog(){
    disconnect(docDialog , SIGNAL(submitNewDocument(Document*)) , this , SLOT(fetchNewDocument(Document*)));
    disconnect(docDialog , SIGNAL(submitModifiedDocument(Document*)) , this , SLOT(fetchUpdatedDocument(Document*)));

}


void DocumentView::createDialog(int type){

    disconnect(typeDialog , SIGNAL(submitDialogType(int)) , this , SLOT(createDialog(int)));
    typeDialog->close();
    if(type == DocTypeDialog::BOOKDIALOG)
        docDialog = new AddDialog_book(nullptr , newId);
    else if(type == DocTypeDialog::AVDIALOG)
        docDialog = new AddDialog_av(nullptr , newId);
    else if(type == DocTypeDialog::ARTICLEDIALOG)
        docDialog = new AddDialog_journalArticle(nullptr , newId);

    connect(docDialog , SIGNAL(submitNewDocument(Document*)) , this , SLOT(fetchNewDocument(Document*)) , Qt::UniqueConnection);
    connect(docDialog , SIGNAL(dialogEnded()) , this , SLOT(disconnectDialog()) , Qt::UniqueConnection);

    docDialog->exec();


}

void DocumentView::disconnectCopyDialog(){
    disconnect(copyDialog , SIGNAL(submitNewCopy(Copy*)) , this , SLOT(fetchNewCopy(Copy*)));
    disconnect(copyDialog , SIGNAL(dialogEnded()) , this , SLOT(disconnectCopyDialog()));
}


void DocumentView::addButtonClicked(){
    emit requestNewId();
}
void DocumentView::editButtonClicked(){
    requestType = AddDialog_docs::EDITMODE;
    auto index = getCursorPosition();
    if(index.isValid())
        emit(requestDocumentData(index));
    else QMessageBox::information(nullptr , "Selection Failed" , "Select at least one document from the table" , QMessageBox::Ok);

}
void DocumentView::viewButtonClicked(){
    requestType = AddDialog_docs::VIEWMODE;
    auto index = getCursorPosition();
    if(index.isValid())
        emit(requestDocumentData(index));
    else QMessageBox::information(nullptr , "Selection Failed" , "Select at least one document from the table" , QMessageBox::Ok);
}
void DocumentView::deleteButtonClicked(){
    auto index = getCursorPosition();
    if(index.isValid())
        emit(deleteRequest(index));
    else QMessageBox::information(nullptr , "Selection Failed" , "Select at least one document from the table" , QMessageBox::Ok);

}
void DocumentView::addCopyButtonClicked(){
    auto index = getCursorPosition();
    if(index.isValid())
        emit(requestNewCopyId(index));
    else QMessageBox::information(nullptr , "Selection Failed" , "Select at least one document from the table" , QMessageBox::Ok);
}

void DocumentView::showQueueButtonClicked(){
    auto index = getCursorPosition();
    if(index.isValid())
        emit(requestQueueInfo(index));
    else QMessageBox::information(nullptr , "Selection Failed" , "Select at least one document from the table" , QMessageBox::Ok);
}
void DocumentView::bookButtonClicked(){
    auto index = getCursorPosition();
    if(index.isValid())
        emit(requestBookingStatus(index , user));
    else QMessageBox::information(nullptr , "Selection Failed" , "Select at least one document from the table" , QMessageBox::Ok);
}

void DocumentView::acceptQueueInfo(QStringListModel *model, Document *doc){
    infoDialog = new QueueInfoDialog(nullptr , doc , model);
    infoDialog->exec();
}

void DocumentView::acceptBookingReport(int report, Copy *copy){
    if(report == DocumentDataProxy::ALREADYBOOKED){
        QMessageBox::information(nullptr , "Unsuccessful Booking Request" , "You had already booked one copy of this document" , QMessageBox::Ok);
        return;
    }
    if(report == DocumentDataProxy::NOCOPIES){
        QMessageBox::information(nullptr , "Unsuccessful Booking Request" , "There are no available copies" , QMessageBox::Ok);
        return;
    }

    if(report == DocumentDataProxy::CANNOTBECHECKED){
        QMessageBox::information(nullptr , "Unsuccessful Booking Request" , "This document cannot be checked" , QMessageBox::Ok);
        return;
    }
    if(report == DocumentDataProxy::ALREADYINQUEUE){
        QMessageBox::information(nullptr , "Unsuccessful Booking Request" , "You are already in queue for this document" , QMessageBox::Ok);
        return;
    }
    if(report == DocumentDataProxy::INQUEUE){
        QMessageBox::information(nullptr , "Inserted into queue successfully" , "You were placed in queue for this document" , QMessageBox::Ok);
        return;
    }
   auto ncopy = new Copy(*copy);
   ncopy->checkOut(user);
   QMessageBox::information(nullptr , "Successful Booking Request" , "Document has been successfully booked for " + QVariant(ncopy->getExpectedTime()).toString() + " weeks" , QMessageBox::Ok);
   emit bookingRequest(ncopy , user);
   emit submitEvent(LibraryEvent(EventMessageBuilder::checkOut(copy->getDoc() , user), QDate::currentDate()));
}

void DocumentView::acceptDeleteQueryReport(int report){
    if(report == DocumentDataProxy::SUCCESSFUL_DELETE){
        QMessageBox::information(nullptr , "Successful Deletion" , "The document was successfully deleted",QMessageBox::Ok);
    }
    if(report == DocumentDataProxy::EXISTCOPIES)
        QMessageBox::information(nullptr , "Unsuccessful Deletion" , "There are certian copies of this document in the library. Cannot be deleted",QMessageBox::Ok);
}


void DocumentView::acceptNewId(int id){
    newId = id;
    connect(typeDialog , SIGNAL(submitDialogType(int)) , this , SLOT(createDialog(int)) , Qt::UniqueConnection);
    typeDialog->exec();
}

void DocumentView::fetchNewDocument(Document *doc){
    assert(doc != nullptr);
    emit addRequest(doc);
    emit submitEvent(LibraryEvent(EventMessageBuilder::documentAdding(doc , user), QDate::currentDate()));


}


void DocumentView::fetchNewCopy(Copy *C){
    emit addCopyRequest(C);
    emit submitEvent(LibraryEvent(EventMessageBuilder::copyCreation(C->getDoc() , user), QDate::currentDate()));

}

void DocumentView::accceptAddCopyQueryResponse(int id , Document *doc){
    assert(doc != nullptr);
    copyDialog = new CopyDialog(id , doc);
    connect(copyDialog , SIGNAL(submitNewCopy(Copy*)) , this , SLOT(fetchNewCopy(Copy*)) , Qt::UniqueConnection);
    connect(copyDialog , SIGNAL(dialogEnded()) , this , SLOT(disconnectCopyDialog()) , Qt::UniqueConnection);
    copyDialog->exec();
}


void DocumentView::fetchUpdatedDocument(Document *doc){

    assert(doc != nullptr);
    emit submitEvent(LibraryEvent(EventMessageBuilder::documentModification(doc , user), QDate::currentDate()));
    emit updateRequest(doc);

}
void DocumentView::acceptDocumentData(Document *doc){
    assert(doc != nullptr);
    bool ok = 1;
    if(user->getType() == "Librarian1")
        ok = 0;
    if(doc->getType() == "Book"){
        auto book = dynamic_cast<Book*>(doc);

        docDialog = new AddDialog_book(nullptr , book , requestType , user);
    }
    else if(doc->getType() == "AV"){
        auto av = dynamic_cast <AV*> (doc);
        assert(av != nullptr);
        docDialog = new AddDialog_av(nullptr , av , requestType , user);
    }
    else{
        assert(doc->getType() == "Article");
        auto article = dynamic_cast <Article*> (doc);
        assert(article != nullptr);
        docDialog = new AddDialog_journalArticle(nullptr , article , requestType , user);
    }

    connect(docDialog , SIGNAL(dialogEnded()) , this , SLOT(disconnectDialog()) , Qt::UniqueConnection);
    connect(docDialog , SIGNAL(submitModifiedDocument(Document*)) , this , SLOT(fetchUpdatedDocument(Document*)) , Qt::UniqueConnection);

    docDialog->exec();
}


void DocumentView::getFilters(){

    SearchSpecifier F (authorSearch->text().simplified() , keywordsSearch->text().simplified() , titleSearch->text().simplified() , bookCheck->isChecked() , articleCheck->isChecked() , avCheck->isChecked() , criteriaCheck->isChecked());
    emit requestFilteredResults(F);

}
