#include "View/adddialog_journal.h"
#include "Model/documententity.h"


AddDialog_journalArticle::AddDialog_journalArticle(QWidget *parent, int Id) : AddDialog_journalArticle(parent) {
    mode = ADDMODE;
    idLineEdit->setText(QVariant(Id).toString());
    actionButton->setText("Add");
    setWindowTitle("Add New Article");
}

AddDialog_journalArticle::AddDialog_journalArticle(QWidget *parent, Article *article, int pMode, User *U) : AddDialog_journalArticle(parent) {
    assert(article != nullptr && (pMode == VIEWMODE || pMode == EDITMODE));
    mode = pMode;

    if(U->getType() == "Librarian1")
        requestCheckBox->setDisabled(true);

    if (mode == EDITMODE) {
        actionButton->setText("Confirm Edit");
        setWindowTitle("Edit Article");
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
        journalNameLineEdit->setReadOnly(true);
        publicationDateLineEdit->setReadOnly(true);
        editorsTextEdit->setReadOnly(true);
        setWindowTitle("Article Details");
        actionButton->hide();
    }
    setDocument(article);
}

AddDialog_journalArticle::AddDialog_journalArticle(QWidget *parent) : AddDialog_docs(parent) {


    journalNameLabel = new QLabel("Journal Name");
    publicationDateLabel = new QLabel("Publication Date");
    editorsLabel = new QLabel("Editors");

    journalNameLineEdit = new QLineEdit();
    editorsTextEdit = new QPlainTextEdit();
    publicationDateLineEdit = new QLineEdit();

    gLayout->addWidget(titleLabel, 0, 0);
    gLayout->addWidget(titleLineEdit, 0, 1);
    gLayout->addWidget(idLabel, 1, 0);
    gLayout->addWidget(idLineEdit, 1, 1);

    gLayout->addWidget(publicationDateLabel, 2, 0);
    gLayout->addWidget(publicationDateLineEdit, 2, 1);

    gLayout->addWidget(publisherLabel, 3, 0);
    gLayout->addWidget(publisherLineEdit, 3, 1);

    gLayout->addWidget(editorsLabel, 4, 0);
    gLayout->addWidget(editorsTextEdit, 4, 1);

    gLayout->addLayout(checkBoxLayout, 5, 0, Qt::AlignTop);
    gLayout->addWidget(authorsPlainText, 5, 1);

    gLayout->addWidget(journalNameLabel, 6, 0);
    gLayout->addWidget(journalNameLineEdit, 6, 1);

    gLayout->addWidget(priceLabel, 7, 0);
    gLayout->addWidget(priceLineEdit, 7, 1);
    gLayout->addWidget(keywordsLabel, 8, 0);
    gLayout->addWidget(keywordsLineEdit, 8, 1);

    connect(actionButton, SIGNAL(clicked()), this, SLOT(actionButtonClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));

    buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(actionButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(gLayout);
    mainLayout->addLayout(buttonLayout);

    idLineEdit->setReadOnly(true);

    setLayout(mainLayout);
    setModal(true);
    setWindowTitle("New Journal Article");
}


Document* AddDialog_journalArticle::getDocument() {

    int Id = idLineEdit->text().trimmed().toInt();
    QString title = titleLineEdit->text().trimmed();
    QString authors = authorsPlainText->toPlainText().trimmed();
    QString publisher = publisherLineEdit->text().trimmed();
    QString keywords = keywordsLineEdit->text().trimmed();
    bool reference = referenceCheckBox->isChecked();
    bool bestSeller = bestsellerCheckBox->isChecked();
    bool outstandingRequest = requestCheckBox->isChecked();
    int price = QVariant(priceLineEdit->text().trimmed()).toInt();
    QString journalName = journalNameLineEdit->text().trimmed();
    QString editors = editorsTextEdit->toPlainText().trimmed();
    QDate date = QDate::fromString(publicationDateLineEdit->text().trimmed(),Qt::ISODate);

    return new Article(Id, title, authors, keywords, publisher,
                               price, journalName, date, editors, reference,
                               bestSeller, outstandingRequest);
}

void AddDialog_journalArticle::setDocument(Document *doc){
    assert(doc != nullptr);
    auto article = dynamic_cast<Article*> (doc);
    assert(article != nullptr);

    titleLineEdit->setText(article->getTitle());
    idLineEdit->setText(QVariant(article->getId()).toString());
    keywordsLineEdit->setText(article->getKeywords());
    priceLineEdit->setText(QVariant(article->getPrice()).toString());
    publisherLineEdit->setText(article->getPublisher());
    authorsPlainText->setPlainText(article->getAuthors());
    bestsellerCheckBox->setChecked(article->isBestSeller());
    requestCheckBox->setChecked(article->isOutstandingRequest());
    referenceCheckBox->setChecked(article->isReference());
    journalNameLineEdit->setText(article->getJournalName());
    publicationDateLineEdit->setText(article->getJournalIssueDate().toString(Qt::ISODate));
    editorsTextEdit->setPlainText(article->getEditors());
}

bool AddDialog_journalArticle::validate(){
    auto datetext = publicationDateLineEdit->text().trimmed();
    auto date = QDate::fromString(datetext , Qt::ISODate);
    if(date.isValid()){
        return true;
    }
    else qDebug()<<"input a valid date please";
    return false;
}

