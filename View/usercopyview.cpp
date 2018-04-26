#include "usercopyview.h"
#include <cassert>

UserCopyView::UserCopyView(QWidget *parent , UserCopyModel *pModel):QWidget(parent){

    assert(pModel != nullptr);

    returnButton = new QPushButton("Return Document");
    renewButton = new QPushButton("Renew Document");
    refreshButton = new QPushButton("Refresh");

    view = new QTableView(this);

    model = pModel;

    view->setModel(model);

    mainLayout = new QVBoxLayout();
    buttonLayout = new QHBoxLayout();

    setupDisplay();
    setup();

}

void UserCopyView::setup(){
    connect(returnButton , SIGNAL(clicked(bool)) , this , SLOT(returnButtonClicked()) , Qt::UniqueConnection);
    connect(renewButton , SIGNAL(clicked(bool)) , this , SLOT(renewButtonClicked()) , Qt::UniqueConnection);
    connect(refreshButton , SIGNAL(clicked(bool)) , this , SLOT(refreshButtonClicked()) , Qt::UniqueConnection);


    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);

    view->hideColumn(0);
    view->hideColumn(4);
    view->hideColumn(6);

}

void UserCopyView::setupDisplay(){

    buttonLayout->addWidget(returnButton);
    buttonLayout->addWidget(renewButton);
    buttonLayout->addWidget(refreshButton);


    mainLayout->setContentsMargins(0, 25, 0, 0);
    mainLayout->addWidget(view);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    setFixedSize(800 , 450);

}

QModelIndex UserCopyView::getCursorPosition(){
    QItemSelectionModel *selection = view->selectionModel();

    if (selection->hasSelection()) {
        if (selection->isRowSelected(selection->currentIndex().row(),QModelIndex())){
          return selection->currentIndex();
        }
    }
    return QModelIndex();
}


void UserCopyView::returnButtonClicked(){
    auto index = getCursorPosition();
    if(index.isValid())
       emit returnRequest(index);
    else QMessageBox::information(nullptr , "Selection Failed" , "Select at least one copy from the table" , QMessageBox::Ok);
}


void UserCopyView::acceptReturnReport(bool state){
    if(state)
        QMessageBox::information(nullptr , "Successful Request" , "The copy was requested to be returned successfully" , QMessageBox::Ok);
    else  QMessageBox::information(nullptr , "Unuccessful Request" , "Well this should never happen :v" , QMessageBox::Ok);
}


void UserCopyView::refreshButtonClicked(){
    emit refreshRequest();
}

void UserCopyView::acceptRenewReport(int state){
    if(state == Copy::SUCCESSFULRENEW)
        QMessageBox::information(nullptr , "Renewal Request Successful" , "Your renewal request was submitted to librarians" , QMessageBox::Ok);
    else if(state == Copy::ONLYONCE)
        QMessageBox::information(nullptr , "Renewal Failed" , "You Cannot renew more than once" , QMessageBox::Ok);
    else if(state == Copy::OUTSTANDINGREQ)
         QMessageBox::information(nullptr , "Renewal Failed" , "This item must be returned immediately to library" , QMessageBox::Ok);

}

void UserCopyView::renewButtonClicked(){
    auto index = getCursorPosition();
    if(index.isValid())
       emit renewRequest(index);
    else QMessageBox::information(nullptr , "Selection Failed" , "Select at least one copy from the table" , QMessageBox::Ok);
}
