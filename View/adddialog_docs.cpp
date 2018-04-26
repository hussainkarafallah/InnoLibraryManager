
#include "View/adddialog_docs.h"

AddDialog_docs::AddDialog_docs(QWidget *parent):QDialog(parent){
  keywordsLabel = new QLabel("Key words");
  authorsLabel = new QLabel("Authors");
  priceLabel = new QLabel("Price");
  bestsellerLabel = new QLabel("Bestseller");
  referenceLabel = new QLabel("Reference");
  requestLabel = new QLabel("Outstanding");
  publisherLabel = new QLabel("Publisher");
  idLabel = new QLabel("Id");
  titleLabel = new QLabel("Title");

  idLineEdit = new QLineEdit();
  titleLineEdit = new QLineEdit();
  authorsPlainText = new QPlainTextEdit();
  keywordsLineEdit = new QLineEdit();
  priceLineEdit = new QLineEdit();
  publisherLineEdit = new QLineEdit();
  bestsellerCheckBox = new QCheckBox();
  referenceCheckBox = new QCheckBox();
  requestCheckBox = new QCheckBox();

  actionButton = new QPushButton();
  cancelButton = new QPushButton("Cancel");

  checkBoxLayout = new QGridLayout();
  gLayout = new QGridLayout();
  mainLayout = new QVBoxLayout();
  buttonLayout = new QHBoxLayout();

  checkBoxLayout->addWidget(authorsLabel, 0, 0);
  checkBoxLayout->addWidget(bestsellerLabel, 1, 0);
  checkBoxLayout->addWidget(bestsellerCheckBox, 1, 1);
  checkBoxLayout->addWidget(referenceLabel, 2, 0);
  checkBoxLayout->addWidget(referenceCheckBox, 2, 1);
  checkBoxLayout->addWidget(requestLabel, 3, 0);
  checkBoxLayout->addWidget(requestCheckBox, 3, 1);
}

void AddDialog_docs::endDialog(){
    close();
    emit dialogEnded();
}
void AddDialog_docs::cancelButtonClicked(){
    endDialog();
}

void AddDialog_docs::actionButtonClicked(){
    if(validate()){
        if(mode == EDITMODE){
            QMessageBox::information(nullptr , "Successful Edit" , "The document was successfully edited",QMessageBox::Ok);
            emit submitModifiedDocument(getDocument());
        }
        else{
            QMessageBox::information(nullptr , "Successful Add" , "The document was successfully added",QMessageBox::Ok);
            emit submitNewDocument(getDocument());
        }
        endDialog();
    }

}
