#ifndef DOCUMENTVIEW_H
#define DOCUMENTVIEW_H


#include<View/queueinfodialog.h>
#include<View/copydialog.h>
#include<View/doctypedialog.h>
#include<View/adddialog_docs.h>
#include<View/doctypedialog.h>

/*! \brief DocumentView this class is the view element that represents the document model
 *
 * This class represents the information in the document model to the user interface. It also provides some buttons so the user/librarian
 * interact with the model and do some queries. It has 2 modes one for librarian and one for user. basically we initialize the mode according to the user type
 * if it's a normal patron we just disable some features
 *
 */

class DocumentView : public QWidget
{
    Q_OBJECT

public:
    User *user; //!< the user this view is representing information to

    enum MODES{ LIBRARIANMODE = 0 , USERMODE = 1 }; //!< enumerators for modes

    enum SELECTION{NOSELECTION = -1}; //!< a flag that indicates that there is no cell selected by user

    QPushButton *editButton, *bookButton, *addButton, *deleteButton, *viewButton,
                *addCopyButton , *showQueueButton;

    QTableView *view; //!< a QT tableview class that loads a QT itemmodel and loads its data automatically

    DocumentModel *model; //!< the model this view is representing

    int mode , newId;

    QVBoxLayout *mainLayout;

    QHBoxLayout *buttonLayout;

    QueueInfoDialog *infoDialog;

    DocTypeDialog *typeDialog; //!< a doctype dialog that we show when librarian requests to add a document

    AddDialog_docs *docDialog; //!< a document dialog that we show when librarian request to add or edit a certain document, or maybe the user wants to view information of some document.

    CopyDialog *copyDialog; //!< a copy dialog that we show when librarian requests to add a new copy



public:
    explicit DocumentView(QWidget *parent , DocumentModel *pModel , User *pUser); //!<  default constructor


private:
    DocumentView(QWidget *parent , DocumentModel *pModel); //!< a constructor parametrized with the user logged to the system and representing this view to
    void setup(); //!< setting up connections
    void setupDisplay(); //!<  settiong up display
    QModelIndex getCursorPosition(); //!< a function for getting the table index of the cell user is pointing to
    int requestType;

signals:
    void requestNewId() const; //!< a signal that's submitted to the model through controller that requests a new doc id
    void addRequest(Document *doc) const; //!< a signal that's submitted to the model through controller that requests adding a new document to the system
    void deleteRequest(QModelIndex index) const; //!< a signal that's submitted to the model through controller that requests deleting of the document the selected cell is representing
    void updateRequest(Document *U) const; //!< a signal that's submitted to the model through controller that requests updating the information of a certain doc
    void requestDocumentData(QModelIndex index) const; //!< a signal that's submitted to the model through controller that requests the information of a certain document to show to the user
    void requestNewCopyId(QModelIndex index) const; //!< a signal that's submitted to the model through controller that requests a new id for the new added copy
    void addCopyRequest(Copy *C); //!< a signal that's submitted to the model through controller that requests adding a certain copy passed along with signal to the system
    void requestBookingStatus(QModelIndex index , User *U); //!< a signal that's submitted to the model through controller that asks for the status (availability or not along with justification) of a booking request for some document along with the user who made the request
    void bookingRequest(Copy *C , User *U); //!< a signal that's submitted to the model through controller that asks to do a booking action for a certain document for a certain user after checking the possibillity
    void requestQueueInfo(QModelIndex index) const; //!< a signal submitted to the model through controller that asks for the info about a certain document's waiting queue

   // void addCopyRequest(QModelIndex index) const;

public slots:
    void addButtonClicked(); //!< a slot that's activated when add button is clikced to open dialogs for adding new document
    void editButtonClicked(); //!< a slot that's activated when edit button is clikced to submit signal and load the doc information into the dialog
    void deleteButtonClicked(); //!< a slot that's activated when delete button is clicked to delete a certain selected doc
    void addCopyButtonClicked(); //!< a slot that's activated when addcopy button is clicked to open dialogs so the user specify copy information
    void bookButtonClicked(); //!< a slot that's activated when book button is clicked so the system checks the possibillity of booking the document and doing so in case
    void viewButtonClicked(); //!< a slot that's activated when view button is clicked to load a doc information into a dialog to show it
    void showQueueButtonClicked(); //!< a slot that's activated when queue info button is clicked
    void disconnectDialog(); //!< a slot that's activated when document dialog are destroyed so we disconnect them before deleting
    void disconnectCopyDialog(); //!< a slot that's activated when addcopy dialog is destroyed so we disconnect it before deleting

    void acceptNewId(int id); //!< a slot that accepts the generated document ID from the model
    void fetchNewDocument(Document *doc); //!< a slot that's activated when document dialog is done that recieves the signal carrying document info from the dialog
    void fetchUpdatedDocument(Document *doc); //!< a slot that recieves the information of our edited document so we forward it to the model
    void acceptDocumentData(Document *doc); //!< a slot that receives the signal carrying a document information from model that we wish to present in dialog
    void createDialog(int type); //!< a slot that creates a dialog according to the chosen type
    void acceptDeleteQueryReport(int report); //!< a slot that receives the report of the deleting query whether successful or not
    void accceptAddCopyQueryResponse(int id , Document *doc); //!< a slot that receieves the report of adding a copy request
    void fetchNewCopy(Copy *C); //!< a slot that recieves the information of the new added copy from the dialog
    void acceptBookingReport(int report , Copy *copy); //!< a slot that receieves the signal carrying the report of the booking request wheter successful or not with reasons
    void acceptQueueInfo(QStringListModel *model , Document *doc); //!<  a slot that receives the queue information about the document we had asked about


};

#endif // DOCUMENTVIEW_H
