#ifndef DOCUMENTENTITY_H
#define DOCUMENTENTITY_H

#include "Model/usermodelentity.h"
#include "Model/validators.h"


/*! \brief Document object.
 *
 *  This class represents the document object along with all setters/getters and other useful functions.
 *
 */
class Document
{

private:
    int id;
    QString title, publisher;
    QString authors, keywords;
    int price;
    int bestSeller;
    int reference;
    int outstandingRequest;

public:
    enum checkingPeriod{unSuccessful = 0 , oneWeek = 1 , twoWeeks = 2 , threeWeeks = 3 , fourWeeks = 4};

    const static int boundAttributes = 11;
    const static int tableAttributes = 9;

    QString getColumnAttribute(int index);

    QVariant valueToBind(int index);

    Document(int dId, QString dTitle, QString dAuthors,
             QString dkeywords, QString dPublisher, int dPrice,
             int dReference = 0, int dBestSeller = 0,
             int dOutstandingRequest = 0);

    virtual QString getType() const = 0;

    int getId() const;
    QString getTitle() const;
    QString getAuthors() const;
    QString getKeywords() const;
    QString getPublisher() const;
    int getPrice() const;

    int isReference() const;
    int isBestSeller() const;
    int isOutstandingRequest() const;
    int getCheckOutPeriod(User *who) const;
    void setId(int dId);
    void setTitle(QString dtitle);

    void setAuthors(QString dAuthors);
    void setKeywords(QString dKeywords);


    void setPrice(int dPrice);
    void setReference(int state);
    void setBestSeller(int state);
    void setOutstandingRequest(int state);
    void setPublisher(QString dPublisher);

    virtual QString getDetails() const = 0;
    virtual void setDetails(QString bDetails) = 0;
    bool operator == (Document *d2);
};

/*! \brief Book object.
 *
 *  This class represents the book object along with all setters/getters and other useful functions.
 *
 */
class Book : public Document
{
public:
    Book(int bId, QString bTitle, QString bAuthors,
         QString bKeywords, QString bPublisher, int bPrice, int bEdition,
         int bYear, int bReference = 0, int bBestSeller = 0,
         int bOutstandingRequest = 0);
    Book(int bId, QString bTitle, QString bAuthors, QString bKeywords, QString bPublisher, int bPrice, QString bDetails, int bReference = 0, int bBestSeller = 0, int bOutstandingRequest = 0);

    int getEdition() const;
    int getYear() const;
    void setEdition(int bEdition);
    void setYear(int bYear);

    QString getDetails() const;
    void setDetails(QString bDetails);

    QString getType() const;
    ~Book();

private:
    int edition, year;
};

/*! \brief Article object.
 *
 *  This class represents the Article object along with all setters/getters and other useful functions.
 *
 */


class Article : public Document{
private:
    QString journalName , editors;
    QDate issueDate;


public:
    Article(int aId, QString aTitle, QString aAuthors,
       QString aKeywords, QString aPublisher, int aPrice, QString aJournalName , QDate aIssueDate , QString aEditors,
       int aReference = 0 , int aBestSeller = 0, int aOutstandingRequest = 0);
    Article(int aId, QString aTitle, QString aAuthors,
       QString aKeywords, QString aPublisher, int aPrice, QString aDetails,
       int aReference = 0 , int aBestSeller = 0, int aOutstandingRequest = 0);

    QString getJournalName() const;
    QDate getJournalIssueDate() const;
    QString getEditors() const;

    void setJournaltName(QString aName);
    void setIssueDate(QDate aIssueDate);
    void setEditors(QString aEditors);


    QString getDetails() const;
    void setDetails(QString aDetails);

    QString getType() const;

    ~Article();
};


/*! \brief AV object.
 *
 *  This class represents the AV object along with all setters/getters and other useful functions.
 *
 */
class AV : public Document
{
public:
    AV(int aId, QString aTitle, QString aAuthors,
       QString aKeywords, QString aPublisher, int aPrice,
       int aReference = 0 , int aBestSeller = 0, int aOutstandingRequest = 0);

    QString getDetails() const;
    void setDetails(QString aDetails);

    QString getType() const;
    ~AV();
};

/*! \brief Document copy object.
 *
 *  This class represents the document copy object along with all setters/getters and other useful functions.
 *
 */
class Copy{
private:


    int id;
    Document *doc;
    int state , expectedTime , fine , userId;
    QString section;
    QDate bookingDate;
    QDate returnDate;

public:

    enum checkingPeriod{unSuccessful = 0 , oneWeek = 1 , twoWeeks = 2 , threeWeeks = 3 , fourWeeks = 4};

    static const int BoundAttributes = 9;
    static const int tableAttributes = 11;

    enum COPYSTATE{NOTBOOKED = 0 , BOOKED = 1 , PENDINGRETURN = 2 , PENDINGRENEWAL = 3 , RENEWED = 4 , IMMEDIATERETURN = 5};
    enum RENEWALSTATE{SUCCESSFULRENEW = 0 , OUTSTANDINGREQ = 1 , ONLYONCE = 2};

    Copy(int pId , Document *pDoc , QString pSection);
    Copy(int pId , Document *pDoc , int pState , int pExpectedTime , int pUserId , QString pSection , QDate pBookingDate , QDate pReturnDate);
    Copy(const Copy &X);
    void checkOut(User *U , QDate date = QDate::currentDate());
    int getRenewalStatus(User *U);
    void renew(User *U , QDate date);
    Document* getDoc() const;
    int getId() const;
    int getDocumentId() const;
    int getState() const;
    int getExpectedTime() const;
    int getFine(QDate Date = QDate(0,0,0)) const;
    int getUserId() const;
    int getOverDueDays(QDate Date = QDate::currentDate()) const;
    bool isOverDue() const;
    QString getDueState() const;
    QString getSection() const;
    QDate getBookingDate() const;
    QDate getReturnDate() const;
    QVariant valueToBind(int index);
    static int stateMapper(QString str);
    void requestImmediateReturn(QDate date);
    void customerRequestForReturn();
    void customerRequestForRenew();
    void returnToLibrary();
    void outstandingImmediateReturn(QDate date);

    //id docid doctitle doctype section state userid bookindate returndate fine

    QString getColumnAttribute(int index);
    bool operator == (Copy *c2);

};

class Notification{

    int id , userId;
    QString type , text;
    QDate startDate , endDate;

    Notification(){}

public:
    Notification(int pId , QString pType , int pUserId , QString pText , QDate pStartDate , QDate pEndDate){
        id = pId;
        type = pType;
        userId = pUserId;
        startDate = pStartDate;
        endDate = pEndDate;
        text = pText;
    }
    static Notification* OutQueueNotif(int uId , QDate sDate , Document *doc){
        QString rType = "OUTQUEUE";
        int rUserId = uId;
        QDate rStartDate = sDate;
        QDate rEndDate = QDate(2020 , 1 , 1);
        QString rText = "You were removed from document " + doc->getTitle() + " because it's no longer available";
        return new Notification(1 , rType , rUserId , rText , rStartDate , rEndDate);
    }
    static Notification* ReturnImmediatelyNotif(int uId , QDate sDate , Document *doc){
        QString rType = "RETURN";
        int rUserId = uId;
        QDate rStartDate = sDate;
        QDate rEndDate = QDate(2020 , 1 , 1);
        QString rText = "You must return document " + doc->getTitle() + " immediately because it's under outstanding request";
        return new Notification(1 , rType , rUserId , rText , rStartDate , rEndDate);
    }
    static Notification* BookingNotif(int uId , QDate sDate , Document *doc){
        QString rType = "AVAILABLE";
        int rUserId = uId;
        QDate rStartDate = sDate;
        QDate rEndDate = rStartDate;
        rEndDate.addDays(1);
        QString rText = "Document " + doc->getTitle() + " is available for booking. Please check out your copy before" + rEndDate.toString(Qt::ISODate);
        return new Notification(1 , rType , rUserId , rText , rStartDate , rEndDate);
    }
    int getId(){
        return id;
    }
    int getUserId(){
        return userId;
    }
    QString getType(){
        return type;
    }
    QString getText(){
        return text;
    }
    QDate getStartDate(){
        return startDate;
    }
    QDate getEndDate(){
        return endDate;
    }

};
class QueueEntry{

    int id;
    int userId , docId;
    User *user;
    Document *doc;
public:
    QueueEntry(){}
    QueueEntry(int pId , int dId , int uId){
        userId = uId;
        docId = dId;
        id = pId;
    }
    QueueEntry(int pId , User *u , Document *d){
        userId = u->getId();
        docId = d->getId();
        id = pId;
        user = u;
        doc = d;
    }
    int getId(){
        return id;
    }
    int getUserId(){
        return userId;
    }
    int getDocId(){
        return docId;
    }
    User *getUser(){
        return user;
    }
    Document *getDoc(){
        return doc;
    }
    bool operator < (QueueEntry &other){

        if(user->getType() == "Student") return 1;

        if(other.getUser()->getType() == "Student") return 0;

        if(user->getType() == "Instructor") return 1;

        if(other.getUser()->getType() == "Instructor") return 0;

        if(user->getType() == "TA") return 1;

        if(other.getUser()->getType() == "TA") return 0;

        if(user->getType() == "Visiting Professor") return 1;

        if(other.getUser()->getType() == "Visiting Professor") return 0;

        return id < other.id;

    }

};

/*! \brief This class takes user search filters as arguments and generates the coresponding sql query
 *
 *
 *
 */
class SearchSpecifier{
    QList < QString > authors , keyWords , title;
    bool isBook , isAv , isArticle , isAnd;
public:
    SearchSpecifier(){
        authors.clear();
        keyWords.clear();
        title.clear();
        isBook =0 ;
        isAv = 0;
        isArticle = 0;
        isAnd = 0;
    }
    void tokenize(QList < QString > &tokens , QString buffer){

        tokens.clear();

        QString cur;
        for(auto ch : buffer){
            if(ch == '#'){
                if(cur.isEmpty() == false){
                    tokens.push_back(cur);
                }
                cur.clear();
            }
            else cur.push_back(ch);
        }

        if(!cur.isEmpty())
            tokens.push_back(cur);


    }
    SearchSpecifier(QString pAuthors , QString pKeyWords , QString pTitles , bool bookPar , bool articlePar , bool avPar , bool isAndPar = 0){

        isBook = bookPar;
        isArticle = articlePar;
        isAv = avPar;
        isAnd = isAndPar;

        tokenize(authors , pAuthors);
        tokenize(keyWords , pKeyWords);
        tokenize(title , pTitles);


    }
    QString getQuery(){

        QString ret;

        if(!title.empty()){

            if(!ret.isEmpty()) ret += " AND ";

            ret += "( ";

            bool st = 0;

            for(auto token : title){
                if(st){
                    if(isAnd) ret += " AND ";
                    else ret += " OR ";
                }
                st = 1;
                ret += " TITLE LIKE \'%" + token + "%\' ";
            }

            ret += " )";
        }

        if(!keyWords.isEmpty()){

            if(!ret.isEmpty()) ret += " AND ";

            ret += "( ";

            bool st = 0;

            for(auto token : keyWords){
                if(st){
                    if(isAnd) ret += " AND ";
                    else ret += " OR ";
                }
                st = 1;
                ret += " KEYWORDS LIKE \'%" + token + "%\' ";
            }

            ret += " )";
        }

        if(!authors.isEmpty()){

            if(!ret.isEmpty()) ret += " AND ";

            ret += "( ";

            bool st = 0;

            for(auto token : authors){
                if(st){
                    if(isAnd) ret += " AND ";
                    else ret += " OR ";
                }
                st = 1;
                ret += " AUTHORS LIKE \'%" + token + "%\' ";
            }

            ret += " )";
        }

        if(isBook || isAv || isArticle){

            if(!ret.isEmpty()) ret += " AND ";

            ret += "( ";

            bool st = 0;

            if(isBook){

                if(st){
                    if(isAnd) ret += " AND ";
                    else ret += " OR ";
                }
                st = 1;
                ret += " TYPE = \'Book\' ";

            }

            if(isArticle){

                if(st){
                    if(isAnd) ret += " AND ";
                    else ret += " OR ";
                }
                st = 1;
                ret += " TYPE = \'Article\' ";

            }

            if(isAv){

                if(st){
                    if(isAnd) ret += " AND ";
                    else ret += " OR ";
                }
                st = 1;
                ret += " TYPE = \'AV\' ";

            }

            ret += " )";
        }
        return ret;

    }

};

/*! \brief This class generates an event to be added in library log, it takes users and documents as arguments
 *  each function name corresponds to the event
 *
 *
 */
class LibraryEvent{
    QString text;
    QDate date;
public:
    QString getText(){
        return text;
    }
    QDate getDate(){
        return date;
    }
    LibraryEvent(QString pText , QDate pDate){
        text = pText;
        date = pDate;
    }

};

class EventMessageBuilder{
public:
    static QString userCreation(User *user , User *supervisor);
    static QString copyCreation(Document *doc , User *supervisor);
    static QString userDeletion(User *user , User *supervisor);
    static QString userModification(User *user , User *supervisor);

    static QString checkOut(Document *doc , User *checker);
    static QString outstandingRequestCheck(Document *doc , User *checker , bool ok);
    static QString queueDeletion(Document *doc);
    static QString inQueuePlacement(Document *doc , User *U);
    static QString immediateReturnNotif(Document *doc , User *U);
    static QString userOutOfQueue(Document *doc , User *U);
    static QString documentDeletion(Document *doc , User *U);
    static QString documentAdding(Document *doc , User *U);
    static QString documentModification(Document *doc , User *U);


};



#endif // DOCUMENTENTITY_H
