#ifndef ADDDIALOG_BOOK_H
#define ADDDIALOG_BOOK_H

#include "Model/documententity.h"
#include "View/adddialog_docs.h"
#include <Model/validators.h>

/*! \brief bookdialog class for representing (input/output) of book document information
 *
 *  This class is inherited from the general documents dialog which has all common feature along with the addition attributes represented in book
 *
 */

class AddDialog_book : public AddDialog_docs
{
    Q_OBJECT

public:

    AddDialog_book(QWidget *parent, int Id); //!<  constructor of the blank dialog the librarian uses to input the information of the new book along with the id of the new added book to set

    AddDialog_book(QWidget *parent, Book *book, int pMode , User *U); //!< a constructor of the dialog that shows the information of a certain book we wish to edit/view

    AddDialog_book(QWidget *parent); //!<  a defaul constructor


    QLabel *editionLabel;
    QLineEdit *editionLineEdit;

    void setDocument(Document *D); //!<  a function that sets the dialog fields to the corresponding information of the book

    Document* getDocument(); //!<  a function that gets all the information (inputted/recorded) in the dialog and normalize it a s abook object

protected:
    QLineEdit *publicationYearLineEdit;
    QLabel *publicationYearLabel;


    bool validate(); //!<  input validator

public slots:

};

#endif // ADDDIALOG_BOOK_H
