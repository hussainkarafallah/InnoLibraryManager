#include "View/copydialog.h"

CopyDialog::CopyDialog():QDialog()
{
    docIdLabel = new QLabel("Document ID");
    copyIdLabel = new QLabel("Copy Id");
    titleLabel = new QLabel("Document Title");
    sectionLabel = new QLabel("Library Section");
    docTypeLabel = new QLabel("Document Type");

    docIdLineEdit = new QLineEdit();
    copyIdLineEdit = new QLineEdit();
    titleLineEdit = new QLineEdit();
    sectionLineEdit = new QLineEdit();
    docTypeLineEdit = new QLineEdit();

    docIdLineEdit->setReadOnly(true);
    copyIdLineEdit->setReadOnly(true);
    titleLineEdit->setReadOnly(true);
    docTypeLineEdit->setReadOnly(true);

    addButton = new QPushButton("Add Copy");
    cancelButton = new QPushButton("Cancel");

    gLayout = new QGridLayout();
    buttonLayout = new QHBoxLayout();
    mainLayout = new QVBoxLayout();

    gLayout->addWidget(copyIdLabel , 0 , 0);
    gLayout->addWidget(copyIdLineEdit , 0 , 1);
    gLayout->addWidget(docIdLabel , 1 , 0);
    gLayout->addWidget(docIdLineEdit , 1 , 1);
    gLayout->addWidget(docTypeLabel , 2 , 0);
    gLayout->addWidget(docTypeLineEdit , 2 , 1);
    gLayout->addWidget(titleLabel , 3 , 0);
    gLayout->addWidget(titleLineEdit , 3 , 1);
    gLayout->addWidget(sectionLabel , 4 , 0);
    gLayout->addWidget(sectionLineEdit , 4 , 1);


    connect(addButton , SIGNAL(clicked()) , this , SLOT(addButtonClicked()) , Qt::UniqueConnection);
    connect(cancelButton , SIGNAL(clicked()) , this , SLOT(cancelButtonclicked()) , Qt::UniqueConnection);

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(gLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    setModal(true);
    setWindowTitle("Add New Copy");
}

CopyDialog::CopyDialog(int pId, Document *pDoc):CopyDialog(){

    copyIdLineEdit->setText(QVariant(pId).toString());
    docIdLineEdit->setText(QVariant(pDoc->getId()).toString());
    titleLineEdit->setText(pDoc->getTitle());
    docTypeLineEdit->setText(pDoc->getType());

    doc = pDoc;

}

void CopyDialog::endDialog(){
    close();
    emit dialogEnded();
}
void CopyDialog::addButtonClicked(){
    if(validate()){
        int cId = copyIdLineEdit->text().trimmed().toInt();
        QString dType = docTypeLineEdit->text().trimmed();
        QString section = sectionLineEdit->text().trimmed();
        auto C = new Copy(cId , doc , section);
        emit submitNewCopy(C);
        QMessageBox::information(nullptr , "Successful Adding" , "Copy was added successfully to the library" , QMessageBox::Ok);
        endDialog();
    }
}

void CopyDialog::cancelButtonclicked(){
    endDialog();
}
bool CopyDialog::validate(){
    return true;
}
