#include "View/adddialog_av.h"


AddDialog_av::AddDialog_av(QWidget* parent, int Id) : AddDialog_av(parent)
{
    mode = ADDMODE;
    idLineEdit->setText(QVariant(Id).toString());
    setWindowTitle("New AV");
    actionButton->setText("Add");
}

AddDialog_av::AddDialog_av(QWidget* parent, AV* newAv, int pMode, User *U) : AddDialog_av(parent)
{
    assert(newAv != nullptr && (pMode == EDITMODE || pMode == VIEWMODE));
    mode = pMode;
    if(U->getType() == "Librarian1")
        requestCheckBox->setDisabled(true);
    if (mode == EDITMODE) {
        actionButton->setText("Confirm Edit");
        setWindowTitle("Edit AV");
    } else if (mode == VIEWMODE) {
        keywordsLineEdit->setReadOnly(true);
        priceLineEdit->setReadOnly(true);
        publisherLineEdit->setReadOnly(true);
        titleLineEdit->setReadOnly(true);
        authorsPlainText->setReadOnly(true);
        bestsellerCheckBox->setDisabled(true);
        requestCheckBox->setDisabled(true);
        referenceCheckBox->setDisabled(true);
        actionButton->setText("OK");
        setWindowTitle("AV Details");
        actionButton->hide();
    }
    setDocument(newAv);
}

AddDialog_av::AddDialog_av(QWidget* parent) : AddDialog_docs(parent) {

    gLayout->addWidget(titleLabel, 0, 0);
    gLayout->addWidget(titleLineEdit, 0, 1);
    gLayout->addWidget(idLabel, 1, 0);
    gLayout->addWidget(idLineEdit, 1, 1);
    gLayout->addWidget(publisherLabel, 3, 0);
    gLayout->addWidget(publisherLineEdit, 3, 1);
    gLayout->addLayout(checkBoxLayout, 4, 0, Qt::AlignTop);
    gLayout->addWidget(authorsPlainText, 4, 1);
    gLayout->addWidget(priceLabel, 6, 0);
    gLayout->addWidget(priceLineEdit, 6, 1);
    gLayout->addWidget(keywordsLabel, 7, 0);
    gLayout->addWidget(keywordsLineEdit, 7, 1);

    connect(actionButton, SIGNAL(clicked()), this, SLOT(actionButtonClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));

    buttonLayout->addWidget(actionButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(gLayout);
    mainLayout->addLayout(buttonLayout);

    idLineEdit->setReadOnly(true);

    setLayout(mainLayout);
    setModal(true);
    setWindowTitle("New AV");
}

void AddDialog_av::setDocument(Document *D){

    AV *av = dynamic_cast<AV*>(D);

    assert(av != nullptr);

    titleLineEdit->setText(D->getTitle());
    idLineEdit->setText(QVariant(av->getId()).toString());
    keywordsLineEdit->setText(av->getKeywords());
    priceLineEdit->setText(QVariant(av->getPrice()).toString());
    publisherLineEdit->setText(av->getPublisher());
    authorsPlainText->setPlainText(av->getAuthors());
    bestsellerCheckBox->setChecked(av->isBestSeller());
    requestCheckBox->setChecked(av->isOutstandingRequest());
    referenceCheckBox->setChecked(av->isReference());
}
Document* AddDialog_av::getDocument() {
    int Id = idLineEdit->text().trimmed().toInt();
    QString title = titleLineEdit->text().trimmed();
    QString authors = authorsPlainText->toPlainText().trimmed();
    QString publisher = publisherLineEdit->text().trimmed();
    QString keywords = keywordsLineEdit->text().trimmed();
    bool reference = referenceCheckBox->isChecked();
    bool bestSeller = bestsellerCheckBox->isChecked();
    bool outstandingRequest = requestCheckBox->isChecked();
    int price = QVariant(priceLineEdit->text().trimmed()).toInt();
    return new AV(Id, title, authors, keywords, publisher, price, reference,
                 bestSeller, outstandingRequest);
}

bool AddDialog_av::validate() { return true; }
