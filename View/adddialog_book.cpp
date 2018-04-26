#include "View/adddialog_book.h"
#include "View/adddialog_docs.h"

AddDialog_book::AddDialog_book(QWidget* parent, int Id) : AddDialog_book(parent) {
    mode = ADDMODE;
    idLineEdit->setText(QVariant(Id).toString());
    actionButton->setText("Add");
    setWindowTitle("Add New Book");

}

AddDialog_book::AddDialog_book(QWidget *parent, Book *book, int pMode, User *U) : AddDialog_book(parent) {
    assert(book != nullptr && (pMode == EDITMODE || pMode == VIEWMODE));
    mode = pMode;
    if(U->getType() == "Librarian1")
        requestCheckBox->setDisabled(true);
    if (mode == EDITMODE) {
        actionButton->setText("Confirm Edit");
        setWindowTitle("Edit Book");
    } else if (mode == VIEWMODE) {
        keywordsLineEdit->setReadOnly(true);
        priceLineEdit->setReadOnly(true);
        publisherLineEdit->setReadOnly(true);
        titleLineEdit->setReadOnly(true);
        publicationYearLineEdit->setReadOnly(true);
        editionLineEdit->setReadOnly(true);
        authorsPlainText->setReadOnly(true);
        bestsellerCheckBox->setDisabled(true);
        requestCheckBox->setDisabled(true);
        referenceCheckBox->setDisabled(true);
        actionButton->setText("OK");
        setWindowTitle("Book Details");
        actionButton->hide();
    }
    setDocument(book);
}

AddDialog_book::AddDialog_book(QWidget *parent) : AddDialog_docs(parent) {


  publicationYearLineEdit = new QLineEdit();
  editionLineEdit = new QLineEdit();


  publicationYearLabel = new QLabel("Publication Year");
  editionLabel = new QLabel("Edition");

  gLayout->addWidget(titleLabel, 0, 0);
  gLayout->addWidget(titleLineEdit, 0, 1);
  gLayout->addWidget(idLabel, 1, 0);
  gLayout->addWidget(idLineEdit, 1, 1);
  gLayout->addWidget(publicationYearLabel, 2, 0);
  gLayout->addWidget(publicationYearLineEdit, 2, 1);
  gLayout->addWidget(publisherLabel, 3, 0);
  gLayout->addWidget(publisherLineEdit, 3, 1);
  gLayout->addLayout(checkBoxLayout, 4, 0, Qt::AlignTop);
  gLayout->addWidget(authorsPlainText, 4, 1);
  gLayout->addWidget(editionLabel, 5, 0);
  gLayout->addWidget(editionLineEdit, 5, 1);
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
  setWindowTitle("Add New Book");
}

Document* AddDialog_book::getDocument() {
    int Id = idLineEdit->text().trimmed().toInt();
    QString title = titleLineEdit->text().trimmed();
    QString authors = authorsPlainText->toPlainText().trimmed();
    QString publisher = publisherLineEdit->text().trimmed();
    QString keywords = keywordsLineEdit->text().trimmed();
    int year = QVariant(publicationYearLineEdit->text().trimmed()).toInt();
    bool reference = referenceCheckBox->isChecked();
    bool bestSeller = bestsellerCheckBox->isChecked();
    bool outstandingRequest = requestCheckBox->isChecked();
    int price = QVariant(priceLineEdit->text().trimmed()).toInt();
    int edition = QVariant(editionLineEdit->text().trimmed()).toInt();
    return new Book(Id, title, authors, keywords, publisher, price, edition, year , reference, bestSeller, outstandingRequest);
}

void AddDialog_book::setDocument(Document *D){

    Book *book = dynamic_cast<Book*>(D);

    assert(book != nullptr);

    titleLineEdit->setText(D->getTitle());
    editionLineEdit->setText(QVariant(book->getEdition()).toString());
    idLineEdit->setText(QVariant(book->getId()).toString());
    keywordsLineEdit->setText(book->getKeywords());
    priceLineEdit->setText(QVariant(book->getPrice()).toString());
    publisherLineEdit->setText(book->getPublisher());
    publicationYearLineEdit->setText(QVariant(book->getYear()).toString());
    authorsPlainText->setPlainText(book->getAuthors());
    bestsellerCheckBox->setChecked(book->isBestSeller());
    requestCheckBox->setChecked(book->isOutstandingRequest());
    referenceCheckBox->setChecked(book->isReference());
}

bool AddDialog_book::validate() { return true; }



