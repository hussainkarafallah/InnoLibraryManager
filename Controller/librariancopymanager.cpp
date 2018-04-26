#include "librariancopymanager.h"

LibrarianCopyManager::LibrarianCopyManager(QWidget *parent) : QWidget(parent)
{
    ddb = new DocumentDataProxy();
    model = new LibrarianCopyModel(this);
}
LibrarianCopyManager::LibrarianCopyManager(QWidget *parent , User *U):LibrarianCopyManager(parent){
    assert(U != nullptr);
    user = U;
    view = new LibrarianCopyView(this , model);
    view->show();

    setup();
}

void LibrarianCopyManager::setup(){
    connect(view , SIGNAL(confirmRequest(QModelIndex)) , this , SLOT(confirmRequestHandler(QModelIndex)) ,Qt::UniqueConnection);
    connect(this , SIGNAL(submitConfirmReport(bool)) , view , SLOT(acceptConfirmReport(bool)),Qt::UniqueConnection);

    connect(view , SIGNAL(deleteRequest(QModelIndex)) , this , SLOT(deleteRequestHandler(QModelIndex)),Qt::UniqueConnection);
    connect(this , SIGNAL(submitDeleteReport(bool)) , view , SLOT(acceptDeleteReport(bool)),Qt::UniqueConnection);

    connect(view , SIGNAL(returnRequest(QModelIndex)) , this , SLOT(returnRequestHandler(QModelIndex)) ,Qt::UniqueConnection);
    connect(this , SIGNAL(submitReturnReport(bool)) , view , SLOT(acceptReturnReport(bool)) , Qt::UniqueConnection);

    connect(view , SIGNAL(resetRequest()) , this , SLOT(resetRequestHandler()),Qt::UniqueConnection);
}


void LibrarianCopyManager::deleteRequestHandler(QModelIndex index){
    emit submitDeleteReport(model->deleteByIndex(index));
}

void LibrarianCopyManager::confirmRequestHandler(QModelIndex index){
    emit submitConfirmReport(model->confirmPendingRequestByIndex(index));
}


void LibrarianCopyManager::returnRequestHandler(QModelIndex index){
    emit submitReturnReport(model->immediateReturnByIndex(index));

}

void LibrarianCopyManager::userInfoRequestHandler(User *U){
    model->updateDataAWUser(U);
}
void LibrarianCopyManager::resetRequestHandler(){
    model->updateData();
}

void LibrarianCopyManager::refresh(){
    model->updateData();
}

