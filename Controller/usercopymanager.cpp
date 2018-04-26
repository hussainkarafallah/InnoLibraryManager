#include "usercopymanager.h"
#include <cassert>
UserCopyManager::UserCopyManager(QWidget *parent):QWidget(parent){
    ddbProxy = new DocumentDataProxy();

}

UserCopyManager::UserCopyManager(QWidget *parent , User *U):UserCopyManager(parent){
    assert(U != nullptr);
    user = U;
    model = new UserCopyModel(this , U);
    view = new UserCopyView(this , model);
    view->setFixedSize(800, 450);
    setup();
}

void UserCopyManager::setup(){

    connect(view , SIGNAL(returnRequest(QModelIndex)) , this , SLOT(returnRequestHandler(QModelIndex)) , Qt::UniqueConnection);
    connect(this , SIGNAL(submitReturnReport(bool)) , view , SLOT(acceptReturnReport(bool)) , Qt::UniqueConnection);


    connect(view , SIGNAL(refreshRequest()) , this , SLOT(refresh()) , Qt::UniqueConnection);

    connect(view , SIGNAL(renewRequest(QModelIndex)) , this , SLOT(renewRequestHandler(QModelIndex)) , Qt::UniqueConnection);
    connect(this , SIGNAL(submitRenewReport(int)) , view , SLOT(acceptRenewReport(int)) , Qt::UniqueConnection);

}

void UserCopyManager::returnRequestHandler(QModelIndex index){
    emit submitReturnReport(model->returnByIndex(index));
}

void UserCopyManager::renewRequestHandler(QModelIndex index){
    emit submitRenewReport(model->renewByIndex(index , user));
}

void UserCopyManager::refresh(){
    model->updateData();
}
