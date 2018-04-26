#include "documentdataproxy.h"
#include <Model/usermodelentity.h>
#include <Data/userdataproxy.h>
#include <Model/documententity.h>
#include <cassert>




DocumentDataProxy::DocumentDataProxy(){

    udb = new UserDataProxy();

    if(QSqlDatabase::contains("qt_sql_default_connection")){
        db = QSqlDatabase::database();
    }
    else {
        db = QSqlDatabase::addDatabase("QSQLITE");
    }

    db.setDatabaseName("Innodata.db");



}

void DocumentDataProxy::clearDatabase(){
    QSqlQuery query = QSqlQuery(db);


    assert(db.open());
    query.prepare("DELETE from COPIES");
    if(query.exec());
    else qDebug()<<"copy clear errorr";

    assert(db.open());
    query.prepare("DELETE from DOCUMENTS");
    if(query.exec());
    else qDebug()<<"documents clear errorr";


    assert(db.open());
    query.prepare("DELETE from USERS");
    if(query.exec());
    else qDebug()<<"user clear errorr";

    assert(db.open());
    query.prepare("DELETE from QUEUE");
    if(query.exec());
    else qDebug()<<"user clear errorr";


    assert(db.open());
    query.prepare("DELETE from NOTIF");
    if(query.exec());
    else qDebug()<<"notif clear errorr";

    assert(db.open());
    query.prepare("DELETE from LOG");
    if(query.exec());
    else qDebug()<<"log clear errorr";


}
int DocumentDataProxy::getNewCopyId(){
    QSqlQuery query = QSqlQuery(db);

    int ret = 1;
    assert(db.open());
    query.prepare("SELECT MAX(ID) from COPIES");
    if(query.exec()){
        if(query.next()){
            ret = query.value(0).toInt() + 1;
        }
        else qDebug()<<"empty docs records";
    }
    else qDebug()<<"get new id from docs query error";
    return ret;
}
int DocumentDataProxy::getNewId(){
    QSqlQuery query = QSqlQuery(db);

    int ret = 1;
    assert(db.open());
    query.prepare("SELECT MAX(ID) from DOCUMENTS");
    if(query.exec()){
        if(query.next()){
            ret = query.value(0).toInt() + 1;
        }
        else qDebug()<<"empty docs records";
    }
    else qDebug()<<"get new id from docs query error";
    return ret;
}

void DocumentDataProxy::addDocument(Document *doc){
    QSqlQuery query = QSqlQuery(db);

    assert(db.open());
    query.prepare("INSERT INTO DOCUMENTS VALUES (:id , :type , :title , :keywords , :authors , :price , :publisher , :reference , :bestseller , :request , :details);");
    for(int j = 0 ; j < Document::boundAttributes ; j++)
        query.bindValue(j , doc->valueToBind(j));
    if(query.exec());
    else {
        qDebug()<<"add document error query"<<' '<<query.lastError().text();

    }
    db.close();

}


int DocumentDataProxy::checkDeletedDocumnet(Document *doc){

    QSqlQuery query = QSqlQuery(db);

    assert(db.open() && doc != nullptr);

    query.prepare("SELECT * FROM COPIES where DOCUMENTID = :id ;");

    query.bindValue(":id" , QVariant(doc->getId()));

    if(query.exec()){
        if(query.first()) return EXISTCOPIES;
    }
    else {
        qDebug()<<"check delete document error query";

    }
    db.close();

    return SUCCESSFUL_DELETE;

}
int DocumentDataProxy::deleteDocument(Document *doc){
    QSqlQuery query = QSqlQuery(db);

    int report = checkDeletedDocumnet(doc);

    if(report != SUCCESSFUL_DELETE) return report;

    assert(db.open() && doc != nullptr);

    query.prepare("DELETE FROM DOCUMENTS where ID = :id ;");

    query.bindValue(":id" , QVariant(doc->getId()));

    if(query.exec());
    else {
        qDebug()<<"delete document error query";

    }
    db.close();

    return report;
}

void DocumentDataProxy::updateDocument(Document *doc){
    QSqlQuery query = QSqlQuery(db);

    assert(db.open());
    query.prepare("UPDATE DOCUMENTS SET ID = :id , TYPE = :type , TITLE = :title ,  KEYWORDS = :keywords , AUTHORS = :authors , PRICE = :price , PUBLISHER = :publisher ,  REFERENCE = :reference , BESTSELLER = :bestseller , REQUEST = :request , DETAILS = :details WHERE ID = :docid ;");
    query.bindValue(":docid",QVariant(doc->getId()));
    for(int j = 0 ; j < Document::boundAttributes ; j++)
        query.bindValue(j , doc->valueToBind(j));

    if(query.exec());
    else {
        qDebug()<<"document edit error query"<<query.lastError().text();

    }


    db.close();

}


Document* DocumentDataProxy::getById(int pId){
    QSqlQuery query = QSqlQuery(db);


    Document *ret = nullptr;

    assert(db.open());

    query.prepare("SELECT * FROM DOCUMENTS WHERE ID = :id ;");

    query.bindValue(":id",QVariant(pId));

    if(query.exec()){

        if(query.next()){
            if(query.value(TYPE) == "AV")
                ret = new AV(query.value(ID).toInt() , query.value(TITLE).toString(),query.value(AUTHORS).toString(),query.value(KEYWORDS).toString(),query.value(PUBLISHER).toString(),query.value(PRICE).toInt(),query.value(REFERENCE).toInt(),query.value(BESTSELLER).toInt(),query.value(REQUEST).toInt());
            else if(query.value(TYPE) == "Book")
                ret = new Book(query.value(ID).toInt() , query.value(TITLE).toString(),query.value(AUTHORS).toString(),query.value(KEYWORDS).toString(),query.value(PUBLISHER).toString(),query.value(PRICE).toInt(),query.value(DETAILS).toString(),query.value(REFERENCE).toInt(),query.value(BESTSELLER).toInt(),query.value(REQUEST).toInt());
            else ret = new Article(query.value(ID).toInt() , query.value(TITLE).toString(),query.value(AUTHORS).toString(),query.value(KEYWORDS).toString(),query.value(PUBLISHER).toString(),query.value(PRICE).toInt(),query.value(DETAILS).toString(),query.value(REFERENCE).toInt(),query.value(BESTSELLER).toInt(),query.value(REQUEST).toInt());
        }

    }else qDebug()<<"get by id docs query error";

    db.close();

    return ret;

}

QPair < int , Copy* > DocumentDataProxy::checkBookingStatus(Document *doc, User *U){
    QSqlQuery query = QSqlQuery(db);


    assert(doc != nullptr && U != nullptr);

    Copy* retCopy = nullptr;

    assert(db.open());

    query.prepare("SELECT * FROM USERS WHERE ID = :uid ;");

    query.bindValue(":uid" , QVariant(U->getId()));

    if(query.exec()){
        if(!query.next()){
            return QPair < int , Copy* >(NOSUCHUSER , retCopy);
         }
    }
    else qDebug()<<"check user existence subpart error"<<query.lastError().text()<<query.boundValue(0)<<' '<<query.boundValue(1);

    assert(db.open());

    query.prepare("SELECT * FROM COPIES WHERE DOCUMENTID = :docid AND STATE <> \'FREE\' AND USERID = :uId ;");

    query.bindValue(":docid" , QVariant(doc->getId()));
    query.bindValue(":uId" , QVariant(U->getId()));

    if(query.exec()){
        if(query.next()){
            qDebug()<<"feh already booked";
            return QPair < int , Copy* >(ALREADYBOOKED , retCopy);
         }
    }
    else qDebug()<<"check first subpart error"<<query.lastError().text()<<query.boundValue(0)<<' '<<query.boundValue(1);


    if(doc->getCheckOutPeriod(U) == Document::unSuccessful)
        return QPair < int , Copy* >(CANNOTBECHECKED , retCopy);





    assert(db.open());

    query.prepare("SELECT * FROM COPIES WHERE DOCUMENTID = :docid AND STATE = \'FREE\' ;");

    query.bindValue(":docid" , QVariant(doc->getId()));

    bool tryQueue = 0;

    bool putinQueue = 0;
    if(query.exec()){
        if(!query.next()){
            if(doc->isOutstandingRequest())
                return QPair < int , Copy* >(NOCOPIES , retCopy);
            else {
                tryQueue = 1;
            }
         }
    }
    else qDebug()<<"check second subpart error"<<query.lastError().text();


    if(tryQueue){
        assert(db.open());

        query.prepare("SELECT * FROM QUEUE WHERE DOCID = :docid AND USERID = :uId ;");

        query.bindValue(":docid" , QVariant(doc->getId()));
        query.bindValue(":uId" , QVariant(U->getId()));


        if(query.exec()){
            if(query.next()){
                return QPair < int , Copy* >(ALREADYINQUEUE , retCopy);
            }
            else putinQueue = 1;
        }
        else qDebug()<<"queue duplicate check error";

    }
    if(putinQueue){
        placeInQueue(doc , U);
        return QPair < int , Copy* >(INQUEUE , retCopy);

    }


    assert(db.open());


    query.prepare("SELECT * FROM COPIES WHERE DOCUMENTID = :docid AND STATE = \'FREE\' ;");

    query.bindValue(":docid" , QVariant(doc->getId()));

    int targetDoc = 0;

    if(query.exec()){
        if(query.next()){
            targetDoc = query.value(1).toInt();
        }
    }
    else qDebug()<<"check third subpart error";

    auto mydoc = getById(targetDoc);

    assert(db.open());


    assert(db.open());

    query.prepare("SELECT * FROM COPIES WHERE DOCUMENTID = :docid AND STATE = \'FREE\' ;");

    query.bindValue(":docid" , QVariant(doc->getId()));

    if(query.exec()){
        if(query.next()){
            retCopy = getCopyFromQuery(query , mydoc);
        }
    }


    return {SUCCESSFUL , retCopy};




}

Copy* DocumentDataProxy::getCopyFromQuery(QSqlQuery Q , Document *doc){

    int copyId = Q.value(0).toInt();

    QString section = Q.value(3).toString();
    int state = Copy::stateMapper(Q.value(4).toString());
    int userId , expectedTime;
    QDate bookingDate , returnDate;
    if(Q.value(5) == "NULL") userId = 0;
    else userId = Q.value(5).toInt();
    if(Q.value(6) == "NULL") expectedTime = 0;
    else expectedTime = Q.value(6).toInt();
    if(Q.value(7) == "NULL") bookingDate = QDate();
    else bookingDate = QDate(QDate::fromString(Q.value(7).toString() , Qt::ISODate));
    if(Q.value(8) == "NULL") returnDate = QDate();
    else returnDate = QDate(QDate::fromString(Q.value(8).toString() , Qt::ISODate));



    return new Copy(copyId , doc , state , expectedTime , userId , section , bookingDate , returnDate);
}

void DocumentDataProxy::checkQueue(Document *doc , QDate date){
    auto L = getQueueForDoc(doc);
    if(L.empty()) return;
    int u = L[0].getUserId();
    addNotification(Notification::BookingNotif(u , date , doc));
}
int DocumentDataProxy::addCopy(Copy *C , User* supervisor){
    QSqlQuery query = QSqlQuery(db);
    if(supervisor != nullptr){
        if(supervisor->getType() == "Librarian1")
            return NOPREVELIGES;
        auto eventNote = EventMessageBuilder::copyCreation(C->getDoc() , supervisor);
        addEvent(LibraryEvent(eventNote , QDate::currentDate()));
    }
    assert(db.open());
    query.prepare("INSERT INTO COPIES VALUES (:copyid , :docid , :doctype , :section , :state , :userid  , :expectedtime , :bookingdate , :returndate);");
    for(int j = 0 ; j < Copy::BoundAttributes ; j++)
        query.bindValue(j , C->valueToBind(j));
    if(query.exec());
    else {
        qDebug()<<"add copy error query"<<' '<<query.lastError().text();

    }
    checkQueue(C->getDoc() , QDate::currentDate());
    db.close();
    return SUCCESSFUL;
}


int DocumentDataProxy::deleteCopy(Copy *C, User *supervisor){
    QSqlQuery query = QSqlQuery(db);

    if(supervisor != nullptr){
        if(supervisor->getType() != "Librarian3"){
            return NOPREVELIGES;
        }
    }

    assert(C != nullptr);
    assert(db.open());
    query.prepare("DELETE FROM COPIES WHERE ID = :copid ;");
    query.bindValue(":copid",C->getId());

    if(query.exec());
    else {
        qDebug()<<"DELETE copy error query"<<' '<<query.lastError().text();

    }
    db.close();
    return SUCCESSFUL;
}
void DocumentDataProxy::updateCopy(Copy *C){
    QSqlQuery query = QSqlQuery(db);

    assert(C != nullptr);
    assert(db.open());
    query.prepare("UPDATE COPIES SET STATE = :state , USERID = :userid  , EXPECTEDTIME = :expectedtime , BOOKINGDATE = :bookingdate , RETURNDATE = :returndate WHERE ID = :copid ;");
    query.bindValue(":copid",C->getId());

    for(int j = 4 ; j < Copy::BoundAttributes ; j++)
        query.bindValue(j - 4 , C->valueToBind(j));

    if(query.exec());
    else {
        qDebug()<<"update copy error query"<<' '<<query.lastError().text();

    }
    db.close();
}


QList <Copy*> DocumentDataProxy::getAllCopiesWUser(User *U){
    assert(U != nullptr);

    QSqlQuery query = QSqlQuery(db);


    assert(db.open());

    QList < Copy* > ret;

    QList < int > docsIds;

    QList < Document * > docs;

    query.prepare("SELECT * FROM COPIES where USERID = :userid ;");
    query.bindValue(":userid" , QVariant(U->getId()));

    if(query.exec()){
        while(query.next()){
            docsIds.push_back(query.value(1).toInt());
        }
    }
    else qDebug()<<"copies WUSER first subquery getting query error";


    for(auto it = docsIds.begin() ; it != docsIds.end() ; ++it)
        docs.push_back(getById(*it));


    assert(db.open());

    query.prepare("SELECT * FROM COPIES where USERID = :userid ;");
    query.bindValue(":userid" , QVariant(U->getId()));

    int current = 0;

    if(query.exec()){
        while(query.next()){
            ret.push_back(getCopyFromQuery(query , docs.at(current++)));
        }
    }
    else qDebug()<<"copies WUSER first subquery getting query error";

    db.close();
    return ret;
}
QList <Copy*> DocumentDataProxy::getAllCopies(){
    QSqlQuery query = QSqlQuery(db);


    assert(db.open());

    QList < Copy* > ret;

    QList < int > docsIds;

    QList < Document * > docs;

    query.prepare("SELECT * FROM COPIES;");

    if(query.exec()){
        while(query.next()){
            docsIds.push_back(query.value(1).toInt());
        }
    }
    else qDebug()<<"copies getting query error";


    for(auto it = docsIds.begin() ; it != docsIds.end() ; ++it)
        docs.push_back(getById(*it));



    assert(db.open());

    query.prepare("SELECT * FROM COPIES;");

    int current = 0;

    if(query.exec()){
        while(query.next()){
            ret.push_back(getCopyFromQuery(query , docs.at(current++)));
        }
    }
    else qDebug()<<"copies getting query error";

    db.close();
    return ret;
}

QList<Document*>DocumentDataProxy::getSpecific(SearchSpecifier F){
    QSqlQuery query = QSqlQuery(db);

    QList< Document* > ret;
    assert(db.open());

    QString queryText = "SELECT * FROM DOCUMENTS ";

    auto conditions = F.getQuery();
    if(!conditions.isEmpty())
        queryText += " WHERE " + conditions + " ; ";

    query.prepare(queryText);

    if(query.exec()){
        while(query.next()){
            if(query.value(TYPE) == "AV")
                ret.push_back(new AV(query.value(ID).toInt() , query.value(TITLE).toString(),query.value(AUTHORS).toString(),query.value(KEYWORDS).toString(),query.value(PUBLISHER).toString(),query.value(PRICE).toInt(),query.value(REFERENCE).toInt(),query.value(BESTSELLER).toInt(),query.value(REQUEST).toInt()));
            else if(query.value(TYPE) == "Book")
                ret.push_back(new Book(query.value(ID).toInt() , query.value(TITLE).toString(),query.value(AUTHORS).toString(),query.value(KEYWORDS).toString(),query.value(PUBLISHER).toString(),query.value(PRICE).toInt(),query.value(DETAILS).toString(),query.value(REFERENCE).toInt(),query.value(BESTSELLER).toInt(),query.value(REQUEST).toInt()));
            else ret.push_back(new Article(query.value(ID).toInt() , query.value(TITLE).toString(),query.value(AUTHORS).toString(),query.value(KEYWORDS).toString(),query.value(PUBLISHER).toString(),query.value(PRICE).toInt(),query.value(DETAILS).toString(),query.value(REFERENCE).toInt(),query.value(BESTSELLER).toInt(),query.value(REQUEST).toInt()));
        }
    }
    else {
        qDebug()<<"document filter query error";

    }

    db.close();
    return ret;
}
QList<Document*>DocumentDataProxy::getAll(){
    QSqlQuery query = QSqlQuery(db);

    QList< Document* > ret;
    assert(db.open());

    query.prepare("SELECT * FROM DOCUMENTS;");

    if(query.exec()){


        while(query.next()){
            if(query.value(TYPE) == "AV")
                ret.push_back(new AV(query.value(ID).toInt() , query.value(TITLE).toString(),query.value(AUTHORS).toString(),query.value(KEYWORDS).toString(),query.value(PUBLISHER).toString(),query.value(PRICE).toInt(),query.value(REFERENCE).toInt(),query.value(BESTSELLER).toInt(),query.value(REQUEST).toInt()));
            else if(query.value(TYPE) == "Book")
                ret.push_back(new Book(query.value(ID).toInt() , query.value(TITLE).toString(),query.value(AUTHORS).toString(),query.value(KEYWORDS).toString(),query.value(PUBLISHER).toString(),query.value(PRICE).toInt(),query.value(DETAILS).toString(),query.value(REFERENCE).toInt(),query.value(BESTSELLER).toInt(),query.value(REQUEST).toInt()));
            else ret.push_back(new Article(query.value(ID).toInt() , query.value(TITLE).toString(),query.value(AUTHORS).toString(),query.value(KEYWORDS).toString(),query.value(PUBLISHER).toString(),query.value(PRICE).toInt(),query.value(DETAILS).toString(),query.value(REFERENCE).toInt(),query.value(BESTSELLER).toInt(),query.value(REQUEST).toInt()));
        }
    }
    else qDebug()<<"document getting query error";

    db.close();
    return ret;
}

int DocumentDataProxy::performBooking(Document *doc, User *U, QDate date){
    auto ret = checkBookingStatus(doc , U);
    if(ret.first != SUCCESSFUL) return ret.first;
    auto c = ret.second;
    c->checkOut(U , date);
    updateCopy(c);
    auto eventNote = EventMessageBuilder::checkOut(doc , U);
    addEvent(LibraryEvent(eventNote , date));
    return SUCCESSFUL;
}

QStringListModel* DocumentDataProxy::getQueueInfo(Document *doc){
    auto ret = new QStringListModel();
    auto l = new QStringList();
    auto q = getQueueForDoc(doc);
    for(auto u : q)
        l->operator <<(u.getUser()->getName());
    ret->setStringList(*l);
    return ret;
}
void DocumentDataProxy::performReturn(Copy *C , QDate date){
    C->returnToLibrary();
    updateCopy(C);
    checkQueue(C->getDoc() , date);
}


void DocumentDataProxy::performImmediateReturn(Copy *C, QDate date){

    C->outstandingImmediateReturn(date);

    updateCopy(C);

    addNotification(Notification::ReturnImmediatelyNotif(C->getUserId() , date , C->getDoc()));

    addEvent(LibraryEvent(EventMessageBuilder::immediateReturnNotif(C->getDoc() , udb->getById(C->getUserId())) ,date));

}
int DocumentDataProxy::renewCopy(Copy *C, User *U, QDate date){

    //qDebug()<<C->getDoc()->isOutstandingRequest();

    int rep = C->getRenewalStatus(U);

    if(rep == Copy::ONLYONCE) return rep;

    if(rep == Copy::OUTSTANDINGREQ){
        C->outstandingImmediateReturn(date);
    }

    if(rep == Copy::SUCCESSFULRENEW ){
        C->customerRequestForRenew();
    }

    if(rep == Copy::SUCCESSFULRENEW){
        C->renew(U , date);
    }

    updateCopy(C);

    return rep;
}

void DocumentDataProxy::returnAllCopies(Document *doc, QDate date){
    QSqlQuery query = QSqlQuery(db);

    assert(db.open());

    query.prepare("SELECT * FROM COPIES WHERE DOCUMENTID = :did AND STATE != \'FREE\' ;");
    query.bindValue(":did" , doc->getId());

    QList <Copy*> cList;

    if(query.exec()){
        while(query.next()){
            cList.push_back(getCopyFromQuery(query , doc));
        }

    }else qDebug()<<"outstanding request return all error";

    for(auto c : cList)
        performImmediateReturn(c , date);
}
void DocumentDataProxy::clearQueue(Document *doc , QDate date){

    QSqlQuery query = QSqlQuery(db);

    assert(db.open());

    query.prepare("SELECT * FROM QUEUE WHERE DOCID = :did ;");
    query.bindValue(":did" , doc->getId());

    QList < int > uList;

    if(query.exec()){
        while(query.next()){
            uList.push_back(query.value(2).toInt());
        }

    }else qDebug()<<"clear queue part 1 error";

    assert(db.open());

    query.prepare("DELETE FROM QUEUE WHERE DOCID = :did ;");
    query.bindValue(":did" , doc->getId());

    if(query.exec());
    else qDebug()<<"clear queue part 2 error";

    addEvent(LibraryEvent(EventMessageBuilder::queueDeletion(doc) , date));

    for(auto user : uList){
        addNotification(Notification::OutQueueNotif(user , date , doc));
        addEvent(LibraryEvent(EventMessageBuilder::userOutOfQueue(doc , udb->getById(user)) , date));
    }
}
int DocumentDataProxy::placeOutstandingRequest(Document *doc, QDate date, User *supervisor){

    if(supervisor != nullptr){
        if(supervisor->getType() != "Librarian2" && supervisor->getType() != "Librarian3" ){
            addEvent(LibraryEvent(EventMessageBuilder::outstandingRequestCheck(doc , supervisor , false) , date));
            return NOPREVELIGES;
        }
    }

    doc->setOutstandingRequest(1);

   // qDebug()<<doc->getTitle()<<' '<<doc->getId();
    if(supervisor != nullptr){
        addEvent(LibraryEvent(EventMessageBuilder::outstandingRequestCheck(doc , supervisor , true) , date));
    }

    updateDocument(doc);

    clearQueue(doc , date);

    returnAllCopies(doc , date);


    return SUCCESSFUL;



}

void DocumentDataProxy::placeInQueue(Document *doc, User *U){

    QSqlQuery query = QSqlQuery(db);

    assert(db.open());

    query.prepare("INSERT INTO QUEUE (DOCID , USERID) VALUES( :dId , :uId ) ;");
    query.bindValue(":dId" , QVariant(doc->getId()));
    query.bindValue(":uId" , QVariant(U->getId()));

    if(query.exec());

    else qDebug()<<"place in queue query error";

    addEvent(LibraryEvent(EventMessageBuilder::inQueuePlacement(doc , U), QDate::currentDate()));

}

void DocumentDataProxy::clearNotifForUser(User *U){
    assert(U != nullptr);
    QSqlQuery query = QSqlQuery(db);

    assert(db.open());

    query.prepare("DELETE FROM NOTIF WHERE USERID = :uid ;");
    query.bindValue(":uid" , QVariant(U->getId()));

    if(query.exec());
    else qDebug()<<"clear notif query error";
}

void DocumentDataProxy::addNotification(Notification *note){

    assert(note != nullptr);

    QSqlQuery query = QSqlQuery(db);

    assert(db.open());

    query.prepare("INSERT INTO NOTIF(TYPE , USERID , NOTE , STARTDATE , ENDDATE) VALUES ( :type , :uid , :note , :startdate , :enddate ) ; ");

    query.bindValue(":type" , QVariant(note->getType()));
    query.bindValue(":uid" , QVariant(note->getUserId()));
    query.bindValue(":note" , QVariant(note->getText()));
    query.bindValue(":startdate" , QVariant(note->getStartDate().toString(Qt::ISODate)));
    query.bindValue(":enddate" , QVariant(note->getEndDate().toString(Qt::ISODate)));

    if(query.exec());
    else qDebug()<<"notification insertion error";

}
void DocumentDataProxy::addEvent(LibraryEvent event){


    QSqlQuery query = QSqlQuery(db);

    assert(db.open());

    query.prepare("INSERT INTO LOG(DATE , EVENT) VALUES ( :date , :note ) ; ");
;
    query.bindValue(":note" , QVariant(event.getText()));
    query.bindValue(":date" , QVariant(event.getDate().toString(Qt::ISODate)));

    if(query.exec());
    else qDebug()<<"notification insertion error";

}

LibraryEvent* DocumentDataProxy::getEventFromQuery(QSqlQuery Q){
    QDate date = QDate::fromString(Q.value(1).toString(),Qt::ISODate);
    QString note = Q.value(2).toString();
 //   qDebug()<<note;
    return new LibraryEvent(note , date);

}

QList <LibraryEvent*> DocumentDataProxy::getEventLog(){

    QSqlQuery query = QSqlQuery(db);

    assert(db.open());

    query.prepare("SELECT * FROM LOG");
    QList<LibraryEvent*> ret;

    if(query.exec()){
        while(query.next()){
            ret.push_back(getEventFromQuery(query));
        }
    }
    else qDebug()<<"get events from log error";

    return ret;

}
Notification* DocumentDataProxy::getNotifFromQuery(QSqlQuery Q){
    int id = Q.value(0).toInt();
    QString type = Q.value(1).toString();
    int uId = Q.value(2).toInt();
    QString note = Q.value(3).toString();
    QDate sDate = QDate::fromString(Q.value(4).toString(),Qt::ISODate);
    QDate eDate = QDate::fromString(Q.value(5).toString(),Qt::ISODate);
    return new Notification(id , type , uId , note , sDate , eDate);
}
QList <Notification*> DocumentDataProxy::getNotifForUser(User *U){

    assert(U != nullptr);

    QSqlQuery query = QSqlQuery(db);

    assert(db.open());

    query.prepare("SELECT * FROM NOTIF WHERE USERID = :uid ;");
    query.bindValue(":uid" , QVariant(U->getId()));

    QList<Notification*> ret;
    if(query.exec()){
        while(query.next()){
            ret.push_back(getNotifFromQuery(query));
        }
    }
    else qDebug()<<"get notifications error";

    return ret;

}
QList <QueueEntry> DocumentDataProxy::getQueueForDoc(Document *doc){

    QList <QueueEntry*>  tempRes;
    QList <QueueEntry> ret;


    QSqlQuery query = QSqlQuery(db);

    assert(db.open());

    query.prepare("SELECT * FROM  QUEUE WHERE DOCID = :dId ;");
    query.bindValue(":dId" , QVariant(doc->getId()));

    if(query.exec()){
        while(query.next()){
            tempRes.push_back(new QueueEntry(query.value(0).toInt() , query.value(1).toInt() , query.value(2).toInt()));

        }
    }

    else qDebug()<<"fetching queue error";

    for(auto E : tempRes){
        int id = E->getId();
        int docId = E->getDocId();
        int userId = E->getUserId();

        //qDebug()<<id<<' '<<docId<<' '<<userId;

        auto doc = getById(docId);
        auto user = udb->getById(userId);

        ret.push_back(QueueEntry(id , user , doc));
    }

    std::sort(ret.begin() , ret.end());

    return ret;


}
