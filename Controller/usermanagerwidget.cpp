#include "usermanagerwidget.h"
#include "Model/usermodel.h"
#include "Model/usermodelentity.h"
#include "View/adduserdialog.h"
#include "View/usermodelview.h"
#include <cassert>

UserManagerWidget::UserManagerWidget(QWidget *parent, User *U):UserManagerWidget(parent){
    user = U;
    model = new UserModel(this , U);
    view = new UserModelView(this , model , U);
    setupDisplay();
    setup();
}
UserManagerWidget::UserManagerWidget(QWidget *parent) : QWidget(parent)
{

}

void UserManagerWidget::setup(){
    connect(view , SIGNAL(requestNewId()) , this , SLOT(IdRequestHandler()) , Qt::UniqueConnection);
    connect(this , SIGNAL(submitNewId(int)) , view , SLOT(acceptNewId(int)) , Qt::UniqueConnection);
    connect(view , SIGNAL(addRequest(User*)) , this , SLOT(addRequestHandler(User*)) , Qt::UniqueConnection);

    connect(view , SIGNAL(deleteRequest(QModelIndex)) , this , SLOT(deleteRequestHandler(QModelIndex)) , Qt::UniqueConnection);
    connect(this , SIGNAL(submitDeleteReport(bool)) , view , SLOT(acceptDeleteQueryReport(bool)) , Qt::UniqueConnection);

    connect(view , SIGNAL(requestUserData(QModelIndex)) , this , SLOT(userDataRequestHandler(QModelIndex)) , Qt::UniqueConnection);
    connect(this , SIGNAL(submitUserData(User*)) , view , SLOT(acceptUserData(User*)) , Qt::UniqueConnection);
    connect(view , SIGNAL(updateRequest(User*)) , this , SLOT(updateRequestHandler(User*)) , Qt::UniqueConnection);

    connect(this , SIGNAL(confirmAddEdit(int)) , view , SLOT(receieveAEQueryState(int)));

    connect(view , SIGNAL(showUserDocsRequest(QModelIndex)) , this , SLOT(showCheckedRequestHandler(QModelIndex)) , Qt::UniqueConnection);
}
void UserManagerWidget::setupDisplay(){
}
void UserManagerWidget::updateRequestHandler(User *U){
    assert(U != nullptr);
    int report = model->updateUser(U);
    emit confirmAddEdit(report);
}
void UserManagerWidget::IdRequestHandler(){
    int x = model->getNewId();
    emit submitNewId(x);
}

void UserManagerWidget::addRequestHandler(User *U){
    assert(U != nullptr);
    int report = model->insertUser(U);
    emit confirmAddEdit(report);
}

void UserManagerWidget::deleteRequestHandler(QModelIndex index){
    auto rep =(model->deleteByIndex(index));

    emit submitDeleteReport(rep);
}

void UserManagerWidget::userDataRequestHandler(QModelIndex index){
    auto U = model->getByIndex(index);
    assert(U != nullptr);
    emit submitUserData(U);
}

void UserManagerWidget::showCheckedRequestHandler(QModelIndex index){
    auto U = model->getByIndex(index);
    assert(U != nullptr);
    emit submitRequestedUser(U);
}


