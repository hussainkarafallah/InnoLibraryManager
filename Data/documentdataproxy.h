#ifndef DOCUMENTDATAPROXY_H
#define DOCUMENTDATAPROXY_H


#include <Model/usermodelentity.h>
#include <Model/documententity.h>
#include <Data/userdataproxy.h>

/*! \brief a proxy that links our application to the database.
 *
 *  This class links our application data models (presenters) to the database. It's responsible for all queries regarding documents and copies
 *
 */
class DocumentDataProxy{

private:

    QSqlDatabase db; //!< the database connection
    enum attribute {ID = 0 , TYPE = 1 , TITLE = 2 , KEYWORDS = 3 , AUTHORS = 4 , PRICE = 5 , PUBLISHER = 6 , REFERENCE = 7 , BESTSELLER = 8 , REQUEST = 9 , DETAILS = 10}; //!< enumerators for documents attributes
    UserDataProxy *udb;

public:
    DocumentDataProxy(); //!< default constructor

    enum DeleteReports{SUCCESSFUL_DELETE = 0 , EXISTCOPIES = 1 , NOPREVELIGES = 100}; //!< reports for deleting queries

    enum BOOKINGREPORTS{SUCCESSFUL = 0 , NOCOPIES = 1 , ALREADYBOOKED = 2 , CANNOTBECHECKED = 6 , NOSUCHUSER = 7 , INQUEUE = 8 , ALREADYINQUEUE = 9}; //!< reports for booking queries

    Document* getById(int pId); //!< gets a document from the database by its ID

    Copy* getCopyFromQuery(QSqlQuery Q , Document *doc); //!< fetches the document item (copy) information from a record loaded from the database

    int getNewId(); //!< fetches a new id for a document which doesn't exist in the database

    void addDocument(Document *doc); //!< adds a new document to the database

    int addCopy(Copy *C , User* supervisor = nullptr); //!< adds a new document copy (item) to the database

    void updateDocument(Document *doc); //!< updates the information of a document in the database

    void updateCopy(Copy *C); //!< updates the information of a copy in the database

    int deleteCopy(Copy *C , User* supervisor = nullptr); //!< deletes a copy from the database

    int deleteDocument(Document *doc); //!< deletes a document from the database

    int checkDeletedDocumnet(Document *doc); //!< checks whether it's safe to remove a document from the database without losing information about certian bookings done by patrons

    QPair < int , Copy* > checkBookingStatus(Document *doc , User *U); //!< checks whether a patron is able to book a copy from a certain document. returns the report along with the copy information in case it was possible to book


    Notification* getNotifFromQuery(QSqlQuery Q); //!< a function that fetches the notification info from the notification in the record

    int getNewCopyId(); //!< gets an id for a new copy that doesn't exist int he database

    QList <Document*> getAll(); //!< gets a list of all documents in our database

    QList < Document* > getSpecific(SearchSpecifier F);  //!< a function that gets a list of books from the library according to some search filter

    QList <Copy*> getAllCopies(); //!< gets a list of all copies in our database

    QList <Copy*> getAllCopiesWUser(User *U); //!< gets a list of all copies associated with a patron in our database

    QList <QueueEntry> getQueueForDoc(Document *doc); //!< a function that fetches the waiting queue related to a single document from the database

    int performBooking(Document *doc , User *U , QDate date); //!< this function performs a booking request such that passed user books a copy of the passed document in particular specified date

    void performReturn(Copy *C , QDate date = QDate::currentDate()); //!< this function returns a certain copy to the library

    void performImmediateReturn(Copy *C , QDate date); //!< this function requests immediate return of a certain copy

    int renewCopy(Copy *C , User *U , QDate date); //!< function that renews the checking out of a certain copy for additional period according to patron type

    int placeOutstandingRequest(Document *doc , QDate date , User* supervisor = nullptr); //!< places outstanding request on a certain document

    void placeInQueue(Document *doc , User *U); //!< places a certain user in a certain document waiting queue

    void clearNotifForUser(User *U); //!< clears notifications of a certain user

    QList <Notification*> getNotifForUser(User *U); //!< gets the notifications from the system related to a certain user

    void clearDatabase(); //!< function that clears database

    void addNotification(Notification *note); //!< add a certain notification to a user list of notifications

    void clearQueue(Document *doc, QDate date); //!< clears the waiting queue of a certain document

    void returnAllCopies(Document *doc , QDate date); //!< requests the return of all copies of a certain doc after it was marked as an outstanding request document

    void checkQueue(Document *doc , QDate date); //!< a function that checks the queue of a document if it has waiting users and notify the one at the front if there is

    void addEvent(LibraryEvent event);  //!< a function that adds a certain event to the database (library log)

    LibraryEvent* getEventFromQuery(QSqlQuery Q); //!< a function that fetches the even information from the record

    QList <LibraryEvent*> getEventLog();  //!< a function that fetches the event log from the database

    QStringListModel* getQueueInfo(Document *doc); //!< a function that gets the info of a certain document queue

};
#endif // DOCUMENTDATAPROXY_H
