#include "librariancopyview.h"

LibrarianCopyView::LibrarianCopyView(QWidget *parent , LibrarianCopyModel *pModel):QWidget(parent){
    assert(pModel != nullptr);

    deleteButton = new QPushButton("Delete Copy");
    returnButton = new QPushButton("Ask For Immediate Return");
    confirmButton = new QPushButton("Confirm Request");
    resetButton = new QPushButton("Reset");

    view = new QTableView(this);

    model = pModel;

    view->setModel(model);

    mainLayout = new QVBoxLayout();
    buttonLayout = new QHBoxLayout();

    setupDisplay();
    setup();

}

void LibrarianCopyView::setup(){
    connect(deleteButton , SIGNAL(clicked(bool)) , this , SLOT(deleteButtonClicked()) , Qt::UniqueConnection);
    connect(confirmButton , SIGNAL(clicked(bool)) , this , SLOT(confirmButtonClicked()), Qt::UniqueConnection);
    connect(returnButton , SIGNAL(clicked(bool)) , this , SLOT(returnButtonClicked()), Qt::UniqueConnection);
    connect(resetButton , SIGNAL(clicked(bool)) , this , SLOT(resetButtonClicked()) , Qt::UniqueConnection);

    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void LibrarianCopyView::setupDisplay(){
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(returnButton);
    buttonLayout->addWidget(confirmButton);
    buttonLayout->addWidget(resetButton);

    mainLayout->setContentsMargins(0, 25, 0, 0);
    mainLayout->addWidget(view);
    mainLayout->addLayout(buttonLayout);

    view->setFixedSize(800, 450);
    setLayout(mainLayout);
}

QModelIndex LibrarianCopyView::getCursorPosition(){
    QItemSelectionModel *selection = view->selectionModel();

    if (selection->hasSelection()) {
        if (selection->isRowSelected(selection->currentIndex().row(),QModelIndex())){
          return selection->currentIndex();
        }
    }
    return QModelIndex();
}


void LibrarianCopyView::deleteButtonClicked(){
    auto index = getCursorPosition();
    if(index.isValid())
       emit deleteRequest(index);
    else QMessageBox::information(nullptr , "Selection Failed" , "Select at least one copy from the table" , QMessageBox::Ok);
}

void LibrarianCopyView::returnButtonClicked(){
    auto index = getCursorPosition();
    if(index.isValid())
       emit returnRequest(index);
    else QMessageBox::information(nullptr , "Selection Failed" , "Select at least one copy from the table" , QMessageBox::Ok);
}

void LibrarianCopyView::confirmButtonClicked(){
    auto index = getCursorPosition();
    if(index.isValid())
       emit confirmRequest(index);
    else QMessageBox::information(nullptr , "Selection Failed" , "Select at least one copy from the table" , QMessageBox::Ok);
}

void LibrarianCopyView::acceptConfirmReport(bool state){
    if(state)
         QMessageBox::information(nullptr , "Successful Operation" , "Pending request was approved successfully" , QMessageBox::Ok);
    else QMessageBox::information(nullptr , "Failed Operation" , "You must select a pending request (renewal or return)", QMessageBox::Ok);
}
void LibrarianCopyView::acceptDeleteReport(bool state){
    if(state)
         QMessageBox::information(nullptr , "Successful Deletion" , "Copy was deleted successfully" , QMessageBox::Ok);
    else QMessageBox::information(nullptr , "Failed Deletion" , "The copy you selected cannot be deleted because it's associated with a user", QMessageBox::Ok);
}
void LibrarianCopyView::acceptReturnReport(bool state){
    if(state)
        QMessageBox::information(nullptr , "Successful Request" , "Copy was requested for immediate return successfully" , QMessageBox::Ok);
    else  QMessageBox::information(nullptr , "Unuccessful Request" , "This copy is still in library" , QMessageBox::Ok);

}
void LibrarianCopyView::resetButtonClicked(){
    emit resetRequest();
}
