#ifndef DOCUMENTMANAGERWIDGET_H
#define DOCUMENTMANAGERWIDGET_H

#include "Data/documentdataproxy.h"
#include "Model/documentmodel.h"
#include "View/prevdocumentview.h"
#include <cassert>
#include "Model/usermodelentity.h"


/*! \brief a controller class that links the document model and the document view
 *
 *  This class links the document view which displays the document model (representing document date in our library)
 * to the user. And links between them according to the user queries.
 */
class DocumentManagerWidget : public QWidget
{
    Q_OBJECT
public:
    /** Default constructor.
            */
    DocumentManagerWidget(QWidget *parent = nullptr);
    /** Default constructor which initializes the class for a certian user
            */
    DocumentManagerWidget(QWidget *parent , User *U);
private:

    User *user; //!< the user we are representing the data to
    DocumentDataProxy *ddb; //!< the proxy that links to the database
    DocumentModel *model; //!< The document model object which represents the documents information in our library
    DocumentView *view; //!< The document view object which presents the model to the user through an interface
    void setupDisplay(); //!< setting up the display
    void setup(); //!< initializer and setter for connections between model and view
signals:
    void submitNewId(int aId) const; //!< submits to the view an id of the new document the user wants to add
    void submitDocumentData(Document *doc) const;//!< submits to the view info about the document the user wants to add/edit
    void submitDeleteReport(int report) const; //!< submits to the view the deletion query report (successful or not and why)
    void submitNewCopyRespnse(int cId , Document *doc); //!< submits to the view the information of the document and the id of the new copy he wants to add (to show in dialog)
    void submitBookingStatusReport(int report , Copy *C); //!< submits to the view the result of the booking query whether it was possible or not (with justification) and the length of the period of checking out in case it was possible
    void copyChanged(); //!< a signal indicating a change happened to the copies data in our database (add/edit/delete/or anything)
    void submitQueueInfo(QStringListModel *model , Document *doc); //!< a signal that submits the queue related to a certain document
public slots:
    void idRequestHandler(); //!< a slot handling the view request of a new document ID to add
    void addRequestHandler(Document *doc); //!< a slot handling the view class request of adding a certain book after being loaded with information from the interface
    void addCopyRequestHandler(Copy *C); //!< a slot handling adding a new copy after the user inputs its data
    void documentDataRequestHandler(QModelIndex index); //!< a slot that fetches the information of the document the user wishes to edit or view
    void updateRequestHandler(Document *doc); //!< a slot that forwards the new updated data of a document after being edited by user
    void deleteRequestHandler(QModelIndex index); //!< a slot that requests the deletion of a document the user selects from the table
    void copyIdRequestHandler(QModelIndex index); //!< a slot that request a new id for a copy the user wishes to add
    void bookingStatusRequestHandler(QModelIndex index , User *U); //!< a slot that fetches the possibillity of booking a certain document the user selects
    void bookingRequestHandler(Copy *copy , User *U); //!< a slot that forwards the booking request to the model after being confirmed and reported to the user
    void queueInfoRequestHandler(QModelIndex index); //!< a slot that request the information about a certain document queue (which patrons are standing in queue)
    void filterRequestHandler(SearchSpecifier F);  //!< a slot that receives a search filter the user has asked to filter books according to
    void addEventRequestHandler(LibraryEvent event); //!< a slot that receives an event to add it to the library log

};

#endif // DOCUMENTMANAGERWIDGET_H
