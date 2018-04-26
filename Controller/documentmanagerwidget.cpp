#include "Controller/documentmanagerwidget.h"
#include "Data/documentdataproxy.h"
#include "Model/documentmodel.h"
#include "View/prevdocumentview.h"
#include <cassert>
#include "Model/usermodelentity.h"

DocumentManagerWidget::DocumentManagerWidget(QWidget *parent) : QWidget(parent)
{
    ddb = new DocumentDataProxy();
    model = new DocumentModel();
}
DocumentManagerWidget::DocumentManagerWidget(QWidget *parent, User *U):DocumentManagerWidget(parent){
    assert(U != nullptr);
    user = U;
    view = new DocumentView(this , model , U);
    setup();
}
void DocumentManagerWidget::setup(){

    connect(view , SIGNAL(requestNewId()) , this , SLOT(idRequestHandler()) , Qt::UniqueConnection);
    connect(this , SIGNAL(submitNewId(int)) , view , SLOT(acceptNewId(int)) , Qt::UniqueConnection);

    connect(view , SIGNAL(addRequest(Document*)) , this , SLOT(addRequestHandler(Document*)) , Qt::UniqueConnection);

    connect(view , SIGNAL(requestDocumentData(QModelIndex)) , this , SLOT(documentDataRequestHandler(QModelIndex)) , Qt::UniqueConnection);
    connect(this , SIGNAL(submitDocumentData(Document*)) , view , SLOT(acceptDocumentData(Document*)) , Qt::UniqueConnection);
    connect(view , SIGNAL(updateRequest(Document*)) , this , SLOT(updateRequestHandler(Document*)) , Qt::UniqueConnection);

    connect(view , SIGNAL(deleteRequest(QModelIndex)) , this , SLOT(deleteRequestHandler(QModelIndex)) , Qt::UniqueConnection);
    connect(this , SIGNAL(submitDeleteReport(int)) , view , SLOT(acceptDeleteQueryReport(int)) , Qt::UniqueConnection);

    connect(view , SIGNAL(requestNewCopyId(QModelIndex)) , this , SLOT(copyIdRequestHandler(QModelIndex)) , Qt::UniqueConnection);
    connect(this , SIGNAL(submitNewCopyRespnse(int,Document*)) , view , SLOT(accceptAddCopyQueryResponse(int,Document*)) , Qt::UniqueConnection);
    connect(view , SIGNAL(addCopyRequest(Copy*)) , this , SLOT(addCopyRequestHandler(Copy*)) , Qt::UniqueConnection);

    connect(view , SIGNAL(requestBookingStatus(QModelIndex,User*)) , this , SLOT(bookingStatusRequestHandler(QModelIndex,User*)) , Qt::UniqueConnection);
    connect(this , SIGNAL(submitBookingStatusReport(int,Copy*)) , view , SLOT(acceptBookingReport(int,Copy*)) , Qt::UniqueConnection);
    connect(view , SIGNAL(bookingRequest(Copy*,User*)) , this , SLOT(bookingRequestHandler(Copy*,User*)) , Qt::UniqueConnection);

    connect(view , SIGNAL(requestQueueInfo(QModelIndex)) , this , SLOT(queueInfoRequestHandler(QModelIndex)) , Qt::UniqueConnection);
    connect(this , SIGNAL(submitQueueInfo(QStringListModel*,Document*)) , view , SLOT(acceptQueueInfo(QStringListModel*,Document*)) , Qt::UniqueConnection);

    connect(view , SIGNAL(requestFilteredResults(SearchSpecifier)) , this , SLOT(filterRequestHandler(SearchSpecifier)) , Qt::UniqueConnection);
    connect(view , SIGNAL(submitEvent(LibraryEvent)) , this , SLOT(addEventRequestHandler(LibraryEvent)) , Qt::UniqueConnection);

}

void DocumentManagerWidget::filterRequestHandler(SearchSpecifier F){
    model->filterResults(F);
}

void DocumentManagerWidget::bookingRequestHandler(Copy *copy, User *U){
    assert(copy != nullptr && U != nullptr);
    ddb->updateCopy(copy);
    emit copyChanged();
}
void DocumentManagerWidget::addCopyRequestHandler(Copy *C){
    assert(C != nullptr);
    ddb->addCopy(C);
    emit copyChanged();

}
void DocumentManagerWidget::copyIdRequestHandler(QModelIndex index){
    assert(index.isValid());
    int x = model->getNewCopyId();
    emit submitNewCopyRespnse(x , model->getByIndex(index));
}
void DocumentManagerWidget::idRequestHandler(){
    int x = model->getNewId();
    emit submitNewId(x);
}

void DocumentManagerWidget::addRequestHandler(Document *doc){
    assert(doc != nullptr);
    model->insertDocument(doc);

}
void DocumentManagerWidget::updateRequestHandler(Document *doc){
    assert(doc != nullptr);
    model->updateDocument(doc);
}
void DocumentManagerWidget::documentDataRequestHandler(QModelIndex index){
    assert(index.isValid());
    auto doc = model->getByIndex(index);
    assert(doc != nullptr);
    emit submitDocumentData(doc);
}


void DocumentManagerWidget::bookingStatusRequestHandler(QModelIndex index, User *U){
    assert(index.isValid());

    auto doc = model->getByIndex(index);
    assert(doc != nullptr);
    auto res = ddb->checkBookingStatus(doc , U);
    emit submitBookingStatusReport(res.first , res.second);
}

void DocumentManagerWidget::queueInfoRequestHandler(QModelIndex index){
    assert(index.isValid());
    auto doc = model->getByIndex(index);
    auto res = ddb->getQueueInfo(doc);
    emit submitQueueInfo(res , doc);
}
void DocumentManagerWidget::deleteRequestHandler(QModelIndex index){
    assert(index.isValid());
    auto doc = model->getByIndex(index);
    int ok = model->deleteByIndex(index);
    if(ok == DocumentDataProxy::SUCCESSFUL_DELETE)
        ddb->addEvent(LibraryEvent(EventMessageBuilder::documentDeletion(doc , user) , QDate::currentDate()));
    emit submitDeleteReport(ok);
}

void DocumentManagerWidget::addEventRequestHandler(LibraryEvent event){
    //qDebug()<<event.getText();
    ddb->addEvent(event);
}
