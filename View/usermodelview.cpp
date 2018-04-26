
#include "Model/usermodel.h"
#include "View/usermodelview.h"
#include "View/adduserdialog.h"
#include "View/librariandialog.h"
#include "View/librariandialog.h"
#include <cassert>

UserModelView::UserModelView(QWidget *parent, UserModel *pModel, User *pUser):UserModelView(parent , pModel){
    user = pUser;
    if(user->getType() == "Librarian1"){
        addLibrarianButton->hide();
        deleteButton->hide();
        addButton->hide();
    }
    else if(user->getType() == "Librarian2"){
        addLibrarianButton->hide();
        addButton->hide();
    }
}
UserModelView::UserModelView(QWidget *parent , UserModel *pModel) : QWidget(parent) {
    assert(pModel != nullptr);
    addButton = new QPushButton("Add Patron", this);
    addLibrarianButton = new QPushButton("Add Librarian" , this);
    deleteButton = new QPushButton("Delete User", this);
    editButton = new QPushButton("Edit User" , this);
    showCheckedButton = new QPushButton("Show Checked Out Documents");

    buttonLayout = new QHBoxLayout();
    mainLayout = new QVBoxLayout();

    model = pModel;
    view = new QTableView(this);

    whichAdd =0;

    D = new AddUserDialog(nullptr);
    D->hide();
    LD = new LibrarianDialog(nullptr);
    LD->hide();

    view->setModel(model);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);

    setupDisplay();

    setup();
}

void UserModelView::fetchNewUser(User *U){
    emit addRequest(U);
}

void UserModelView::acceptNewId(int id){

    if(whichAdd == 0){

        D = new AddUserDialog(nullptr , id);

        connect(D , SIGNAL(submitNewUser(User*)) , this , SLOT(fetchNewUser(User*)) , Qt::UniqueConnection);

        D->exec();
    }
    else{
        LD = new LibrarianDialog(nullptr , id);

        connect(LD , SIGNAL(submitNewUser(User*)) , this , SLOT(fetchNewUser(User*)) , Qt::UniqueConnection);

        LD->exec();

    }


}

void UserModelView::receieveAEQueryState(int report){
    if(report == UserDataProxy::Successful){
        disconnect(D , SIGNAL(submitNewUser(User*)) , this , SLOT(fetchNewUser(User*)));
        disconnect(LD , SIGNAL(submitNewUser(User*)) , this , SLOT(fetchNewUser(User*)));

        QMessageBox::information(nullptr , "Successful Request" , "The user data was modified into the system successfully" , QMessageBox::Ok);

        D->close();
        LD->close();
    }
    else if(report == UserDataProxy::DuplicateUserName)
        QMessageBox::information(nullptr , "Reuquest failed" , "The user name you specified already exist in the system" , QMessageBox::Ok);


}

void UserModelView::acceptDeleteQueryReport(bool state){
    if(!state)  QMessageBox::information(nullptr , "Deletion failed" , "The user cannot be deleted because there are items associated with him" , QMessageBox::Ok);
    else  QMessageBox::information(nullptr , "Deletion Successful" , "The user was deleted successfully" , QMessageBox::Ok);

}
void UserModelView::setup() {

    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(addButton , SIGNAL(clicked(bool)) , this , SLOT(addButtonClicked()) , Qt::UniqueConnection);
    connect(editButton , SIGNAL(clicked(bool)) , this , SLOT(editButtonClicked()) , Qt::UniqueConnection);
    connect(deleteButton , SIGNAL(clicked(bool)) , this , SLOT(deleteButtonClicked()) , Qt::UniqueConnection);
    connect(showCheckedButton , SIGNAL(clicked(bool)) , this , SLOT(showButtonClicked()) , Qt::UniqueConnection);
    connect(addLibrarianButton , SIGNAL(clicked(bool)) , this , SLOT(addLibrarianButtonClicked()) , Qt::UniqueConnection);


}
void UserModelView::showButtonClicked(){
    auto index = getCursorPosition();
    if(index.isValid())
        emit showUserDocsRequest(index);
    else  QMessageBox::information(nullptr , "Selection Failed" , "Select at least one user from the table" , QMessageBox::Ok);
}

void UserModelView::setupDisplay(){

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(addLibrarianButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(showCheckedButton);


    mainLayout->setContentsMargins(0, 25, 0, 0);
    mainLayout->addWidget(view);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    view->setFixedSize(800, 450);
    adjustSize();
}

void UserModelView::addButtonClicked(){
    whichAdd =0;
    emit requestNewId();
}

void UserModelView::addLibrarianButtonClicked(){
    whichAdd = 1;
    emit requestNewId();
}

void UserModelView::editButtonClicked(){
    auto index = getCursorPosition();
    if(index.isValid())
        emit requestUserData(index);
    else  QMessageBox::information(nullptr , "Selection Failed" , "Select at least one user from the table" , QMessageBox::Ok);

}
void UserModelView::deleteButtonClicked(){
    auto index = getCursorPosition();
    if(index.isValid())
        emit deleteRequest(index);
    else  QMessageBox::information(nullptr , "Selection Failed" , "Select at least one user from the table" , QMessageBox::Ok);
}

void UserModelView::fetchUpdatedUser(User *U){
    emit updateRequest(U);
}
void UserModelView::acceptUserData(User *U){
    if(U->getType().at(0) != 'L'){

        D = new AddUserDialog(nullptr , U);

        connect(D , SIGNAL(submitUpdatedUser(User*)) , this , SLOT(fetchUpdatedUser(User*)) , Qt::UniqueConnection);

        D->exec();

    }
    else{
        LD = new LibrarianDialog(nullptr , U);

        D->hide();

        connect(LD , SIGNAL(submitUpdatedUser(User*)) , this , SLOT(fetchUpdatedUser(User*)) , Qt::UniqueConnection);

        LD->exec();

    }


}


QModelIndex UserModelView::getCursorPosition() {

    QItemSelectionModel *selection = view->selectionModel();

    if (selection->hasSelection()) {
        if (selection->isRowSelected(selection->currentIndex().row(),QModelIndex())){
          return selection->currentIndex();
        }
    }
    return QModelIndex();
}

