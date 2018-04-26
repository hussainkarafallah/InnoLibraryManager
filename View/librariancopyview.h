#ifndef LIBRARIANCOPYVIEW_H
#define LIBRARIANCOPYVIEW_H

#include<QWidget>
#include <Model/documententity.h>
#include<View/copydialog.h>
#include <Model/documentmodel.h>
#include <Model/usermodelentity.h>
#include <Model/usermodel.h>
#include <View/doctypedialog.h>
#include <View/adddialog_docs.h>
#include <View/searchfilters.h>
#include <Model/librariancopymodel.h>

/*! \brief librariancopyview this class is the view element that represents the copies data model for librarian
 *
 * This class represents the information about copies in our data model. this class is for usage with librarian only. it allows the librarian to interact with the system through the interface and perform certain queries.
 *
 */

class LibrarianCopyView : public QWidget
{
    Q_OBJECT

    QPushButton *deleteButton , *returnButton , *confirmButton , *resetButton;

    QTableView *view;

    LibrarianCopyModel *model; //!< the data model this view is presenting

    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;

    void setup(); //!< setting up connections and initializing objects
    void setupDisplay(); //!< setting up display
    QModelIndex getCursorPosition(); //!< getting the index of the selected cell by user



signals:
    void deleteRequest(QModelIndex index); //!< a signal that carries the index of the copy our librarian wishes to delete
    void returnRequest(QModelIndex index); //!< a signal that carries the index of the copy our librarian wishes to return
    void confirmRequest(QModelIndex index);  //!< signal that carries the index of the copy our librarian wishes confirm its pending request (renew/return)
    void resetRequest(); //!< a signal that requests that the model which repreesents the data from the database initalizes its information again


public:
    LibrarianCopyView(QWidget *parent , LibrarianCopyModel *pModel); //!< constructor

public slots:

    void deleteButtonClicked(); //!< a slot activated when the librarian requests to delete a certain copy
    void returnButtonClicked(); //!< a slot activated when librarian asks for an urgent return of a certain copy
    void confirmButtonClicked(); //!< a slot activated when the librarian confirms a pending request
    void resetButtonClicked(); //!< a slot activated when reset button is clikced and the librarian wishes to reload all data from database

    void acceptDeleteReport(bool state); //!< a slot that recieves the deleting query report
    void acceptReturnReport(bool state); //!< a slot that receieves the asking for immediate return report
    void acceptConfirmReport(bool state); //!< a slot that recieves the report of confirmation query





};

#endif // LIBRARIANCOPYVIEW_H
