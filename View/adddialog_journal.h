#ifndef ADDDIALOG_JOURNAL_H
#define ADDDIALOG_JOURNAL_H

#include "View/adddialog_docs.h"

/*! \brief journaldialog class for representing (input/output) of journal document information
 *
 *  This class is inherited from the general documents dialog which has all common feature along with the addition attributes represented in journal article
 *
 */

class AddDialog_journalArticle : public AddDialog_docs
{
    Q_OBJECT

public:

    AddDialog_journalArticle(QWidget *parent, int Id); // Add
    AddDialog_journalArticle(QWidget *parent, Article *article, int pMode , User *U); // Edit and view
    AddDialog_journalArticle(QWidget *parent);

    void setDocument(Document *D); //!< a pure virtual function to set dialog fields according to the document

    Document* getDocument(); //!< a pure virtual function to normalize the information inside the dialog each attribute to its corresponding field

protected:
    QLineEdit *publicationDateLineEdit;
    QPlainTextEdit *editorsTextEdit;
    QLineEdit *journalNameLineEdit;

    QLabel *publicationDateLabel;
    QLabel *editorsLabel;
    QLabel *journalNameLabel;

   bool validate(); //!< declaration of the pure virtual inherited validate function (here it validates the journal)
};

#endif // ADDDIALOG_JOURNAL_H
