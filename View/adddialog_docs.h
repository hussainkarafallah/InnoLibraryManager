#ifndef ADDDIALOG_DOCS_H
#define ADDDIALOG_DOCS_H

#include "Model/validators.h"
#include <Model/documententity.h>
#include <cassert>

/*! \brief docsdialog class for representing (input/output) of common information of all our documents types
 *
 *  This class is deferred and it's a dialog that we may use to show the user informaton through or to get infomration from user. It simply has fields for all common attrubutes of documents.
 *
 *  and it's inherited by each document type dialog that adds the additional fields and features.
 * This class and its descendants has 3 modes :  [ADDMODE : an empty dialog with only docID set so user inputs information] , [EDITMODE : a dialog with infomration about a certain document our librarian wants to edit] , [VIEWMODE : a readonly dialog presented to the patron who wants to see a certain document information]
 *
 *
 */

class AddDialog_docs : public QDialog
{
    Q_OBJECT

public:

    int mode;

    AddDialog_docs(QWidget *parent); //!< constructor

    enum modes{ADDMODE = 0 , EDITMODE = 1, VIEWMODE = 2};  //!< corresponding mode

    QGridLayout *gLayout;
    QHBoxLayout *buttonLayout;
    QGridLayout *checkBoxLayout;
    QVBoxLayout *mainLayout;

    QLineEdit *titleLineEdit;
    QLineEdit *idLineEdit;
    QPlainTextEdit *authorsPlainText;
    QLineEdit *keywordsLineEdit;
    QLineEdit *priceLineEdit;
    QLineEdit *publisherLineEdit;
    QCheckBox *bestsellerCheckBox;
    QCheckBox *referenceCheckBox;
    QCheckBox *requestCheckBox;

    QLabel *titleLabel;
    QLabel *idLabel;
    QLabel *authorsLabel;
    QLabel *keywordsLabel;
    QLabel *priceLabel;
    QLabel *bestsellerLabel;
    QLabel *referenceLabel;
    QLabel *requestLabel;
    QLabel *publisherLabel;

    QPushButton *actionButton;
    QPushButton *cancelButton;

    virtual void setDocument(Document *D) = 0; //!< a pure virtual function to set dialog fields according to the document
    virtual Document* getDocument() = 0; //!< a pure virtual function to normalize the information inside the dialog into the correspnding document tyep

    void endDialog(); //!< a function to end the dialog
    virtual bool validate() = 0; //!< input validator

signals:
    void submitNewDocument(Document *D) const; //!< a function that gets the document information from the dialog and submits it to the controller
    void submitModifiedDocument(Document *D) const; //!< a function that gets the modified document information from the dialog and submits it to the controller so it's forwarded to the view
    void dialogEnded() const; //!< a signal emitted to disconnect dialog from all objects before deletion
public slots:
    virtual void actionButtonClicked(); //!< the corresponding action to take when the action button (add/edit) is clicked (according to the mode)
    void cancelButtonClicked(); //!< the action to take when cancel button is clicked
};

#endif // VIEWDIALOG_H
