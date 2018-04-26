#include <Model/documententity.h>
#include <cassert>
#include <algorithm>
Document::Document(int dId, QString dTitle, QString dAuthors,
                  QString dkeywords, QString dPublisher, int dPrice,
                  int dReference, int dBestSeller,
                  int dOutstandingRequest) {
    id = dId;
    title = dTitle;
    keywords = dkeywords;
    authors = dAuthors;
    price = dPrice;
    publisher = dPublisher;

    reference = dReference;
    bestSeller = dBestSeller;
    outstandingRequest = dOutstandingRequest;
}

int Document::getId() const {
    return id;
}

QString Document::getTitle() const {
    return title;
}

QString Document::getAuthors() const {
    return authors;
}

QString Document::getKeywords() const {
    return keywords;
}

int Document::getPrice() const {
    return price;
}

int Document::isReference() const {
    return reference;
}

int Document::isBestSeller() const {
    return bestSeller;
}
int Document::isOutstandingRequest() const{
    return outstandingRequest;
}

QString Document::getPublisher() const {
    return publisher;
}

QVariant Document::valueToBind(int index){
    assert(index < boundAttributes);

    if(index == 0) return QVariant(getId());

    if(index == 1) return QVariant(getType());

    if(index == 2) return QVariant(getTitle());

    if(index == 3) return QVariant(getKeywords());

    if(index == 4) return QVariant(getAuthors());

    if(index == 5) return QVariant(getPrice());

    if(index == 6) return QVariant(getPublisher());

    if(index == 7) return QVariant(isReference());

    if(index == 8) return QVariant(isBestSeller());

    if(index == 9) return QVariant(isOutstandingRequest());

    if(index == 10) return QVariant(getDetails());

    assert(false);

    qDebug()<<"error binder document";

    return 0;
}

QString Document::getColumnAttribute(int index) {
    assert(index < tableAttributes);
    if (index == 0)
        return QVariant(id).toString();
    if (index == 1)
        return getType();
    if (index == 2)
        return getTitle();
    if (index == 3)
        return getAuthors();
    if(index == 4)
        return getPublisher();
    if (index == 5)
        return QVariant(getPrice()).toString();
    if (index == 6) {
        if (isReference())
            return "Yes";
        else
            return "No";
    }
    if (index == 7) {
        if (isBestSeller())
            return "BestSeller";
        else
            return "NormalSeller";
    }
    if (index == 8){
        if(isOutstandingRequest())
            return "Outstanding Request";
        else return "Normal Request";
    }
    return "error";
}



void Document::setId(int dId) {
    id = dId;
}

void Document::setTitle(QString dtitle) {
    title = dtitle;
}

void Document::setAuthors(QString dAuthors) {
    authors = dAuthors;
}

void Document::setKeywords(QString dKeywords) {
    keywords = dKeywords;
}

void Document::setPrice(int dPrice) {
    price = dPrice;
}

void Document::setReference(int state) {
    reference = state;
}

void Document::setBestSeller(int state) {
    bestSeller = state;
}

void Document::setPublisher(QString dPublisher) {
    publisher = dPublisher;
}

void Document::setOutstandingRequest(int state){
    outstandingRequest = state;
}

int Document::getCheckOutPeriod(User *who) const {
    if (isReference())
        return unSuccessful;
    if(who->getType() == "Visiting Professor")
        return oneWeek;
    if (getType() == "AV")
        return twoWeeks;
    else if (who->getType() == "Professor" || who->getType() == "TA" || who->getType() == "Instructor")
        return fourWeeks;
    else if (isBestSeller())
        return twoWeeks;
    else
        return threeWeeks;
}



Book::Book(int bId, QString bTitle, QString bAuthors,
     QString bKeywords, QString bPublisher, int bPrice, int bEdition,
     int bYear, int bReference, int bBestSeller,
     int bOutstandingRequest):Document(bId , bTitle , bAuthors,bKeywords,bPublisher,bPrice,bReference,bBestSeller,bOutstandingRequest) {
    edition = bEdition;
    year = bYear;
}
Book::Book(int bId, QString bTitle, QString bAuthors, QString bKeywords, QString bPublisher, int bPrice, QString bDetails, int bReference, int bBestSeller, int bOutstandingRequest):
    Document(bId , bTitle , bAuthors,bKeywords,bPublisher,bPrice,bReference,bBestSeller,bOutstandingRequest){
    setDetails(bDetails);
}

int Book::getEdition() const {
    return edition;
}

int Book::getYear() const {
    return year;
}

void Book::setEdition(int bEdition) {
    edition = bEdition;
}

void Book::setYear(int bYear) {
    year = bYear;
}

QString Book::getType() const {
    return QString("Book");
}

QString Book::getDetails() const{
    QString ret;
    ret += QVariant(edition).toString();
    ret += '\n';
    ret += QVariant(year).toString();
    return ret;
}

void Book::setDetails(QString bDetails){
    QTextStream stream(&bDetails);
    auto editionStr = stream.readLine();
    edition = QVariant(editionStr).toInt();
    auto yearStr = stream.readLine();
    year = QVariant(yearStr).toInt();

}
Book::~Book() {}

Article::Article(int aId, QString aTitle, QString aAuthors, QString aKeywords, QString aPublisher, int aPrice, QString aJournalName, QDate aIssueDate, QString aEditors, int aReference, int aBestSeller, int aOutstandingRequest):
    Document(aId , aTitle , aAuthors , aKeywords , aPublisher , aPrice , aReference , aBestSeller , aOutstandingRequest){
    journalName = aJournalName;
    issueDate = aIssueDate;
    editors = aEditors;
}

Article::Article(int aId, QString aTitle, QString aAuthors, QString aKeywords, QString aPublisher, int aPrice, QString aDetails, int aReference, int aBestSeller, int aOutstandingRequest):
    Document(aId , aTitle , aAuthors , aKeywords , aPublisher , aPrice , aReference , aBestSeller , aOutstandingRequest){
        setDetails(aDetails);
}


QString Article::getJournalName() const{
    return journalName;
}
QDate Article::getJournalIssueDate() const{
    return issueDate;
}
QString Article::getEditors() const{
    return editors;
}
void Article::setJournaltName(QString aName){
    journalName = aName;
}
void Article::setEditors(QString aEditors){
    editors = aEditors;
}
void Article::setIssueDate(QDate aIssueDate){
    issueDate = aIssueDate;
}

QString Article::getDetails() const {
    QString ret;
    ret += journalName;
    ret += '\n';
    ret += issueDate.toString(Qt::ISODate);
    ret += '\n';
    ret += editors;
    return ret;
}
void Article::setDetails(QString aDetails){
    QTextStream stream(&aDetails);
    auto jName = stream.readLine(); journalName = jName;
    auto jDate = stream.readLine(); issueDate = QDate::fromString(jDate , Qt::ISODate);
    auto jEditors = stream.readLine(); editors = jEditors;
}
QString Article::getType() const {
    return QString("Article");
}

Article::~Article() {}

AV::~AV() {}

AV::AV(int aId, QString aTitle, QString aAuthors,
   QString aKeywords, QString aPublisher, int aPrice,
       int aReference  , int aBestSeller , int aOutstandingRequest):Document(aId , aTitle , aAuthors , aKeywords , aPublisher , aPrice , aReference , aBestSeller , aOutstandingRequest){}

QString AV::getDetails() const{
    return "";
}
void AV::setDetails(QString aDetails){
    aDetails = "";
}
QString AV::getType() const {
    return QString("AV");
}


Copy::Copy(int pId, Document *pDoc, QString pSection){
    id = pId;
    doc = pDoc;
    state = NOTBOOKED;
    section = pSection;
    expectedTime = fine  = 0;
    userId = 0;
    bookingDate = returnDate =  QDate();

}

int Copy::getId() const{
    return id;
}
int Copy::getDocumentId() const{
    return doc->getId();
}
int Copy::getState() const{
    return state;
}
int Copy::getExpectedTime() const{
    return expectedTime;
}
int Copy::getOverDueDays(QDate Date) const{
    return Date.toJulianDay() - returnDate.toJulianDay();
}
int Copy::getFine(QDate date) const{
    if(!date.isValid())
        return fine;
    else return std::min( getOverDueDays(date) * 100 , doc->getPrice());
}
int Copy::getUserId() const{
    return userId;
}
QDate Copy::getBookingDate() const{
    return bookingDate;
}
QDate Copy::getReturnDate() const{
    return returnDate;
}
QString Copy::getSection() const{
    return section;
}

int Copy::stateMapper(QString str){
    if(str == "FREE") return 0;
    if(str == "BOOKED") return 1;
    if(str == "PENDINGRETURN") return 2;
    if(str == "PENDINGRENEWAL") return 3;
    if(str == "RENEWED") return 4;
    return 5;

}
QVariant Copy::valueToBind(int index){
    assert(index < BoundAttributes);


    if(index == 0)
        return QVariant(id);
    if(index == 1)
        return QVariant(getDocumentId());
    if(index == 2)
        return QVariant(doc->getType());
    if(index == 3)
        return QVariant(section);
    if(index == 4){
        if(state == 0)
            return QVariant("FREE");
        if(state == 1)
            return QVariant("BOOKED");
        if(state == 2)
             return QVariant("PENDINGRETURN");
        if(state == 3)
            return QVariant("PENDINGRENEWAL");
        if(state == 4)
            return QVariant("RENEWED");
        return QVariant("IMMEDIATERETURN");
    }
    if(index == 5){
        if(state == 0) return QVariant("NULL");
        else return QVariant(userId);
    }
    if(index == 6){
        if(state == 0) return QVariant("NULL");
        else return QVariant(expectedTime);
    }
    if(index == 7){
        if(state == 0) return QVariant("NULL");
        else return QVariant(bookingDate.toString(Qt::ISODate));
    }
    if(index == 8){
        if(state == 0) return QVariant("NULL");
        else return QVariant(returnDate.toString(Qt::ISODate));
    }
    qDebug()<<"binder error";
    assert(false);
    return QVariant("error");

}

QString Copy::getColumnAttribute(int index){
    assert(index < tableAttributes);
    if(index == 0)
        return QVariant(id).toString();
    if(index == 1)
        return QVariant(doc->getId()).toString();
    if(index == 2)
        return doc->getTitle();
    if(index == 3)
        return doc->getType();
    if(index == 4)
        return section;
    if(index == 5){

        if(state == 0) return "Not Booked";
        if(state == 1) return "Booked Once";
        if(state == 2) return "Pending Return";
        if(state == 3) return "Pending Renewal";
        if(state == 4) return "Booked & Renewed";
        if(state == 5) return "Return Immediately";
    }
    if(index == 6){
        if(state == 0)
            return "";
        else return QVariant(userId).toString();
    }
    if(index == 7){
        if(!bookingDate.isValid()) return "";
        else return bookingDate.toString(Qt::ISODate);
    }
    if(index == 8){
        if(!returnDate.isValid()) return "";
        else return returnDate.toString(Qt::ISODate);

    }
    if(index == 9){
        if(state == 0) return "";
        if(returnDate.isValid()){
            if(returnDate.toJulianDay() < QDate::currentDate().toJulianDay())
                return "OVERDUE";
        }
        return "DUE";
    }
    if(index == 10)
        return QVariant(fine).toString();
    return "ERROR";
}

Copy::Copy(const Copy &X){
    id = X.id;
    doc = X.doc;
    state = X.state;
    expectedTime = X.expectedTime;
    fine = X.fine;
    section = X.section;
    userId = X.userId;
    bookingDate = X.bookingDate;
    returnDate = X.returnDate;
}
void Copy::checkOut(User *U, QDate date){
    state = BOOKED;
    expectedTime = doc->getCheckOutPeriod(U);
    fine = 0;
    userId = U->getId();
    bookingDate = date;
    int daysTobook = expectedTime * 7;
    if(daysTobook < 0) daysTobook = 0;
    returnDate = bookingDate.addDays(daysTobook);
    if(returnDate.isValid()){
        auto cur = QDate::currentDate();
        auto dif = cur.toJulianDay() - returnDate.toJulianDay();
        fine = dif * 100;
        fine = std::min(fine , getDoc()->getPrice());
        fine = std::max(fine , 0);
    }
}

void Copy::renew(User *U , QDate date){
    if(doc->isOutstandingRequest()){
        outstandingImmediateReturn(date);
    }
    else{
        checkOut(U , date);
        state = RENEWED;
    }
}
Document* Copy::getDoc() const{
    return doc;
}
Copy::Copy(int pId, Document *pDoc, int pState, int pExpectedTime, int pUserId, QString pSection, QDate pBookingDate, QDate pReturnDate){
    id = pId;
    doc = pDoc;
    state = pState;
    expectedTime = pExpectedTime;
    userId = pUserId;
    section = pSection;
    bookingDate = pBookingDate;
    returnDate = pReturnDate;
    fine = 0;
    if(returnDate.isValid()){
        auto cur = QDate::currentDate();
        auto dif = cur.toJulianDay() - returnDate.toJulianDay();
        fine = dif * 100;
        fine = std::min(fine , pDoc->getPrice());
        fine = std::max(fine , 0);
    }

}
void Copy::requestImmediateReturn(QDate date){
    outstandingImmediateReturn(date);
}
void Copy::customerRequestForReturn(){
    state = PENDINGRETURN;
}
void Copy::customerRequestForRenew(){
    state = PENDINGRENEWAL;
}

void Copy::outstandingImmediateReturn(QDate date){
    if(state != IMMEDIATERETURN){
        state = IMMEDIATERETURN;
        if(returnDate.operator >(date))
            returnDate = date;
        if(returnDate.isValid()){
            auto cur = QDate::currentDate();
            auto dif = cur.toJulianDay() - returnDate.toJulianDay();
            fine = dif * 100;
            fine = std::min(fine , getDoc()->getPrice());
            fine = std::max(fine , 0);
        }
    }
}
void Copy::returnToLibrary(){
    state = NOTBOOKED;
    expectedTime = 0;
    fine = 0;
    userId = 0;
    bookingDate = QDate();
    returnDate = QDate();

}
bool Copy::isOverDue() const{
    if(returnDate.isValid() == false) return 0;
    return returnDate.toJulianDay() < QDate::currentDate().toJulianDay();
}

QString Copy::getDueState() const{
    if(isOverDue()) return "OVERDUE";
    else return "DUE";
}

int Copy::getRenewalStatus(User *U){

    if(doc->isOutstandingRequest()) return OUTSTANDINGREQ;


    if(state == PENDINGRENEWAL)
        return ONLYONCE;

    if(state == RENEWED){
        if(U->getType() != "Visiting Professor")
            return ONLYONCE;
    }

    return SUCCESSFULRENEW;

}


bool Copy::operator ==(Copy *c2){
    for(int j = 0 ; j < tableAttributes ; j++){
        if(getColumnAttribute(j) != c2->getColumnAttribute(j)){
            return false;
        }
    }
    return 1;
}
bool Document::operator ==(Document *d2){
    for(int j = 0 ; j < tableAttributes ; j++)
        if(getColumnAttribute(j) != d2->getColumnAttribute(j))
            return 0;
    return 1;
}


 QString  EventMessageBuilder::userCreation(User *user , User *supervisor){
    QString message;
    if(supervisor->getType().at(0) == 'L')
        message += "Librarian ";
    else message += supervisor->getType() + " ";

    message += supervisor->getName();
    message += " created new ";
    if(user->getType().at(0) == 'L')
        message += "Librarian ";
    message += user->getName();
    return message;
}
 QString  EventMessageBuilder::userModification(User *user , User *supervisor){
    QString message;
    if(supervisor->getType().at(0) == 'L')
        message += "Librarian ";
    else message += supervisor->getType() + " ";

    message += supervisor->getName();
    message += " modified ";
    if(user->getType().at(0) == 'L')
        message += "Librarian ";
    message += user->getName();
    return message;
}
 QString  EventMessageBuilder::userDeletion(User *user , User *supervisor){
    QString message;
    if(supervisor->getType().at(0) == 'L')
        message += "Librarian ";
    else message += supervisor->getType() + " ";

    message += supervisor->getName();
    message += " deleted ";
    if(user->getType().at(0) == 'L')
        message += "Librarian ";
    message += user->getName();
    return message;
}
 QString  EventMessageBuilder::copyCreation(Document *doc , User *supervisor){
    QString message;
    if(supervisor->getType().at(0) == 'L')
        message += "Librarian ";
    else message += supervisor->getType() + " ";
    message += supervisor->getName();
    message += " created new copy of document ";
    message += doc->getTitle();
    return message;
}
 QString  EventMessageBuilder::checkOut(Document *doc , User *checker){
    QString message;
    message += checker->getType() + " ";
    message += checker->getName();
    message += " checked out on copy of ";
    message += doc->getTitle();
    return message;
}
 QString  EventMessageBuilder::outstandingRequestCheck(Document *doc , User *checker , bool ok){
    QString message;
    if(checker->getType().at(0) == 'L')
        message += "Librarian ";
    else message += checker->getType() + " ";

    if(ok) message += " placed outstanding request on document ";
    else message += " failed to place outstanding request on document ";
    message += doc->getTitle();
    return message;
}
 QString  EventMessageBuilder::queueDeletion(Document *doc){
    QString message;
    message += "Waiting queue for document ";
    message += doc->getTitle();
    message += " was deleted due to outstanding request";
    return message;
}
 QString  EventMessageBuilder::inQueuePlacement(Document *doc , User *U){
    QString message;
    if(U->getType().at(0) == 'L')
        message += "Librarian ";
    else message += U->getType() + " ";
    message += " was placed into the waiting queue of the document";
    message += doc->getTitle();
    return message;
}
 QString  EventMessageBuilder::immediateReturnNotif(Document *doc , User *U){
    QString message;
    message += U->getType() + " ";
    message += U->getName();
    message += " was notified to return document ";
    message += doc->getTitle();
    message += " immediately ";
    return message;
}
 QString  EventMessageBuilder::userOutOfQueue(Document *doc , User *U){
    QString message;
    message += U->getType() + " ";
    message += U->getName();
    message += " was notiified that he was removed out of document  ";
    message += doc->getTitle();
    message += " waiting queue ";
    return message;
}
 QString  EventMessageBuilder::documentDeletion(Document *doc , User *U){
    QString message;
    message += U->getType() + " ";
    message += U->getName();
    message += " deleted the document ";
    message += doc->getTitle();
    message += " from the library ";
    return message;
}
 QString EventMessageBuilder::documentModification(Document *doc , User *U){
    QString message;
    message += U->getType() + " ";
    message += U->getName();
    message += " modified the document ";
    message += doc->getTitle();
    message += " information ";
    return message;
}
 QString EventMessageBuilder::documentAdding(Document *doc , User *U){
    QString message;
    message += U->getType() + " ";
    message += U->getName();
    message += " added the document ";
    message += doc->getTitle();
    message += " into the library ";
    return message;
}




