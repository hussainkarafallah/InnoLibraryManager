#include "testsuite.h"
#include "View/loginwindow.h"
#include <Model/documententity.h>
#include <Model/documentmodel.h>
#include <View/librarianwindow.h>
#include <Model/usermodel.h>
#include <Model/usermodelentity.h>
#include<Model/librariancopymodel.h>
#include <QApplication>
#include <QDebug>
#include <Data/documentdataproxy.h>
#include <cassert>
#include <QTableView>
#include "View/usermodelview.h"
#include "View/adduserdialog.h"
#include "Model/documententity.h"
#include "Controller/usermanagerwidget.h"
#include "Model/documentmodel.h"
#include "View/adddialog_av.h"
#include "View/prevdocumentview.h"
#include <Controller/documentmanagerwidget.h>
#include "Model/documentmodel.h"
#include "View/adddialog_book.h"
#include <Controller/librariancopymanager.h>
#include <Controller/usercopymanager.h>
#include<View/userwindow.h>
#include <QFile>
#include <QTextStream>

bool TestSuite::look_in(QList<Copy* > v, Copy *copy){

    //this function takes a list of copies and look for a copy inside this list

    for(auto a : v){

        if(a->operator ==(copy)){
            return 1;
        }
    }
    return 0;
}

bool TestSuite::look_in(QList<Document *> v, Document *doc){
    //this function takes a list of documents and look for a document inside this list

    for(auto a : v)
        if(a->operator ==(doc))
            return 1;
    return 0;
}

bool TestSuite::look_in(QList<User *> v, User *u){
    //this function takes a list of users and look for a user inside this list
    for(auto a : v)
        if(a->operator ==(u))
            return 1;
    return 0;
}

void TestSuite::clear(){
    d1 = new Book(1901 , "Introduction to Algorithms" , "Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest and Clifford Stein" ,"algorithms,data structures,complexity,computational theory" , "MIT PRESS" , 5000 , 3 , 2009);
    d2 = new Book(1002 , "Algorithms + Data Structures = Programs","Niklaus Wirth","algorithms,data structures,search algorithms,pascal","Prentice Hall",5000,1,1978);
    d3 = new Book(1004 , "The Art of Computer Programming" , "Donald E. Knuth" , "algorithms,combinatorial algorithms,recursion" , "Addison Wesley Longman Publishing Co., Inc.",5000,3,1997);

    p1 = new Professor(1010 , "Sergey Afonso","Via Margutta 3","30001","sergey","afonso");
    p2 = new Professor(1011 , "Nadia Texeira" , "Via Sacra 13" , "30002" , "nadia" , "texeira");
    p3 = new Professor(1100 , "Elvira Espindola" , "Via del corso 22", "30003" , "elvira" , "espindola");
    s = new Student(1101 , "Andrey Velo" , "Avenida Mazatlan 250" , "30004" , "andrey" , "velo");
    v = new VisitingProfessor(1110 , "Veronika Rama" , "Stret Atocha 27" , "30005" , "veronika" , "rama");

    l1 = new Librarian(2345 , "Eugenia Rama" , "Moscow" , "999888" , "eugenia" , "rama" , 1);
    l2 = new Librarian(4567,"Luie Ramos" , "Barcelona" , "22222" , "luie" , "ramos" , 2);
    l3 = new Librarian(2233 , "Ramon Valdez" , "Italy" , "22211" , "ramon" , "valdez" , 3);


    admin = new Admin(1 , "Alexander Naumchev" , "Innopolis" , "123123" , "sasha" , "123456");

    docProxy = new DocumentDataProxy();
    userProxy = new UserDataProxy();

    docProxy->clearDatabase();


    testsDate = QDate(2018 , 4 , 2);

    c1 = new Copy(1 , d1 , "floor1");
    c2 = new Copy(2 , d1 , "floor1");
    c3 = new Copy(3 , d1 , "floor1");
    c4 = new Copy(4 , d2 , "floor2");
    c5 = new Copy(5 , d2 , "floor2");
    c6 = new Copy(6 , d2 , "floor2");
    c7 = new Copy(7 , d3 , "floor2");
    c8 = new Copy(8 , d3 , "floor2");
    c9 = new Copy(9 , d3 , "floor2");

}

void TestSuite::mytest(){
   init();
  // runnall();
   TC5();


}
TestSuite::TestSuite(){
    clear();
}

void TestSuite::init(){

    clear();

    docProxy->clearDatabase();

    //insert our admin inside the system
    assert(userProxy->addUser(admin) == UserDataProxy::Successful);
    //make sure that the admin was added successfully into the system
    qDebug()<<"System Initialized Successfully";

    //insert documents inside the library
    docProxy->addDocument(d1);
    docProxy->addDocument(d2);
    docProxy->addDocument(d3);

    auto vDocs = docProxy->getAll();

    //make sure every document was inserted successfully
    assert(look_in(vDocs , d1));
    assert(look_in(vDocs , d2));
    assert(look_in(vDocs , d3));

}

void TestSuite::TC1(){

    init();

    Admin *admin2 = new Admin(9999 , "Hussain" , "innopolis" , "123" , "hussain" , "hussain");
    //try to add a new admin
    assert(userProxy->addUser(admin2) != UserDataProxy::Successful);
    //make sure that the system couldn't add the user

    qDebug()<<"Test 1 Run successfully";


}

void TestSuite::TC2(){

    init();

    //make sure user l1 was added successfully
    assert(userProxy->addUser(l1 , admin) == UserDataProxy::Successful);
    //make sure user l2 was added successfully
    assert(userProxy->addUser(l2 , admin) == UserDataProxy::Successful);
    //make sure user l3 was added successfully
    assert(userProxy->addUser(l3 , admin) == UserDataProxy::Successful);

    //get all users from system
    auto userList = userProxy->gettAllUsers();

    //make sure each librarian is now in the system
    assert(look_in(userList , l1));
    assert(look_in(userList , l2));
    assert(look_in(userList , l3));


    qDebug()<<"Test 2 Run successfully";


}


void TestSuite::TC3(){

    TC2();

    //the librarian l1 tries to create each copy of the 9 copies
    //each time he must fail due to previliges
    assert(docProxy->addCopy(c1 , l1) == DocumentDataProxy::NOPREVELIGES);
    assert(docProxy->addCopy(c2 , l1) == DocumentDataProxy::NOPREVELIGES);
    assert(docProxy->addCopy(c3 , l1) == DocumentDataProxy::NOPREVELIGES);
    assert(docProxy->addCopy(c4 , l1) == DocumentDataProxy::NOPREVELIGES);
    assert(docProxy->addCopy(c5 , l1) == DocumentDataProxy::NOPREVELIGES);
    assert(docProxy->addCopy(c6 , l1) == DocumentDataProxy::NOPREVELIGES);
    assert(docProxy->addCopy(c7 , l1) == DocumentDataProxy::NOPREVELIGES);
    assert(docProxy->addCopy(c8 , l1) == DocumentDataProxy::NOPREVELIGES);
    assert(docProxy->addCopy(c9 , l1) == DocumentDataProxy::NOPREVELIGES);

    qDebug()<<"Test 3 Run successfully";


}

void TestSuite::TC4(){

    TC2();

    //make sure that librarian l2 created each of the copeis succesfully
    assert(docProxy->addCopy(c1 , l2) == DocumentDataProxy::SUCCESSFUL);
    assert(docProxy->addCopy(c2 , l2) == DocumentDataProxy::SUCCESSFUL);
    assert(docProxy->addCopy(c3 , l2) == DocumentDataProxy::SUCCESSFUL);
    assert(docProxy->addCopy(c4 , l2) == DocumentDataProxy::SUCCESSFUL);
    assert(docProxy->addCopy(c5 , l2) == DocumentDataProxy::SUCCESSFUL);
    assert(docProxy->addCopy(c6 , l2) == DocumentDataProxy::SUCCESSFUL);
    assert(docProxy->addCopy(c7 , l2) == DocumentDataProxy::SUCCESSFUL);
    assert(docProxy->addCopy(c8 , l2) == DocumentDataProxy::SUCCESSFUL);
    assert(docProxy->addCopy(c9 , l2) == DocumentDataProxy::SUCCESSFUL);

    auto vCopies = docProxy->getAllCopies();

    //make sure every copy exist as well and was inserted into the system correctly
    assert(look_in(vCopies , c1));
    assert(look_in(vCopies , c2));
    assert(look_in(vCopies , c3));
    assert(look_in(vCopies , c4));
    assert(look_in(vCopies , c5));
    assert(look_in(vCopies , c6));
    assert(look_in(vCopies , c7));
    assert(look_in(vCopies , c8));
    assert(look_in(vCopies , c9));



    //librarian l2 creates patrons p1 , p2 , p3 , s , v
    assert(userProxy->addUser(p1 , l2) == UserDataProxy::Successful);
    assert(userProxy->addUser(p2 , l2) == UserDataProxy::Successful);
    assert(userProxy->addUser(p3 , l2) == UserDataProxy::Successful);
    assert(userProxy->addUser(s , l2) == UserDataProxy::Successful);
    assert(userProxy->addUser(v , l2) == UserDataProxy::Successful);
    auto vUsers = userProxy->gettAllUsers();
    //make sure that each user was inserted (so it exists in the fetched list)
    assert(look_in(vUsers , p1));
    assert(look_in(vUsers , p2));
    assert(look_in(vUsers , p3));
    assert(look_in(vUsers , s));
    assert(look_in(vUsers , v));

    qDebug()<<"Test 4 Run successfully";


}

void TestSuite::TC5(){

    TC4();

    //make sure that librarian l3 deleted one copy of d1 successfully
    assert(docProxy->deleteCopy(c1 , l3) == DocumentDataProxy::SUCCESSFUL);

    auto vCopies = docProxy->getAllCopies();
    int in =0;
    for(auto C : vCopies)
        if(C->getDoc()->operator ==(d1))
            ++in;
    //make sure that the number of copies of documents d1 are exactly 2
    assert(in == 2);


    qDebug()<<"Test 5 Run successfully";

}

void TestSuite::TC6(){


    TC4();

    //p1 checks out d3
    int booking1 = docProxy->performBooking(d3 , p1 , QDate(2018 , 4 , 22));
    //make sure it's successful
    assert(booking1 == DocumentDataProxy::SUCCESSFUL);

    //p2 checks out d3
    int booking4 = docProxy->performBooking(d3 , p2 , QDate(2018 , 4 , 22));
    //make sure it's successful
    assert(booking4 == DocumentDataProxy::SUCCESSFUL);

    //s checks out d3
    int booking2 = docProxy->performBooking(d3 , s , QDate(2018 , 4 , 22));
    //make sure s was inserted into queue for d3
    assert(booking2 == DocumentDataProxy::SUCCESSFUL);

    //v checks out d3
    int booking3 = docProxy->performBooking(d3 , v , QDate(2018 , 4 , 22));
    //make sure user v was inserted into queue for d3
    assert(booking3 == DocumentDataProxy::INQUEUE);

    //p3 checks out d3
    int booking5 = docProxy->performBooking(d3 , p3 , QDate(2018 , 4 , 22));
    //make sure user p3 was inserted into queue for d3
    assert(booking5 == DocumentDataProxy::INQUEUE);

    //make sure that l1 cannot set outstanding request because of his preveliges
    assert(docProxy->placeOutstandingRequest(d3 , QDate(2018 , 4 , 25) , l1) == DocumentDataProxy::NOPREVELIGES);

    qDebug()<<"Test 6 Run successfully";



}

void TestSuite::TC7(){
    TC4();

    //p1 checks out d3
    int booking1 = docProxy->performBooking(d3 , p1 , QDate(2018 , 4 , 22));
    //make sure it's successful
    assert(booking1 == DocumentDataProxy::SUCCESSFUL);

    //p2 checks out d3
    int booking4 = docProxy->performBooking(d3 , p2 , QDate(2018 , 4 , 22));
    //make sure it's successful
    assert(booking4 == DocumentDataProxy::SUCCESSFUL);

    //s checks out d3
    int booking2 = docProxy->performBooking(d3 , s , QDate(2018 , 4 , 22));
    //make sure s was inserted into queue for d3
    assert(booking2 == DocumentDataProxy::SUCCESSFUL);

    //v checks out d3
    int booking3 = docProxy->performBooking(d3 , v , QDate(2018 , 4 , 22));
    //make sure user v was inserted into queue for d3
    assert(booking3 == DocumentDataProxy::INQUEUE);

    //p3 checks out d3
    int booking5 = docProxy->performBooking(d3 , p3 , QDate(2018 , 4 , 22));
    //make sure user p3 was inserted into queue for d3
    assert(booking5 == DocumentDataProxy::INQUEUE);

    assert(docProxy->placeOutstandingRequest(d3,QDate(2018 , 4 , 25),l3) == DocumentDataProxy::SUCCESSFUL);

    auto L = docProxy->getQueueForDoc(d3);
    //make sure that queue for D3 is empty
    assert(L.empty());

    //check notifications of p1
    auto Lp1 = docProxy->getNotifForUser(p1);
    //make sure he has only one notif
    assert(Lp1.size() == 1);
    //make sure that it says to return d3 to library
    assert(Lp1[0]->getType() == "RETURN");


    //check notifications of p2
    auto Lp2 = docProxy->getNotifForUser(p2);
    //make sure he has only one notif
    assert(Lp2.size() == 1);
    //make sure that it says to return d3 to library
    assert(Lp2[0]->getType() == "RETURN");

    //check notifications of s
    auto Lp4 = docProxy->getNotifForUser(s);
    //make sure he has only one notif
    assert(Lp4.size() == 1);
    //make sure that it says he must return d3 to library
    assert(Lp4[0]->getType() == "RETURN");



    //check notifications of p3
    auto Lp3 = docProxy->getNotifForUser(p3);
    //make sure he has only one notif
    assert(Lp3.size() == 1);
    //make sure that it says that he was removed from queue
    assert(Lp3[0]->getType() == "OUTQUEUE");

    //check notifications of v
    auto Lp5 = docProxy->getNotifForUser(v);
    //make sure he has only one notif
    assert(Lp5.size() == 1);
    //make sure that it says he was removed from d3 queue
    assert(Lp5[0]->getType() == "OUTQUEUE");

    qDebug()<<"Test 7 Run successfully";

}

void TestSuite::TC8(){

    TC6();

    auto eventLog = docProxy->getEventLog();

    //confirm the event log is identical message by message

    //qDebug()<<eventLog.at(0)->getText()<<' '<<eventLog.at(0)->getd;

    //admin created l1
    assert(eventLog.at(0)->getText() == EventMessageBuilder::userCreation(l1 , admin));
    //admin created l2
    assert(eventLog.at(1)->getText() == EventMessageBuilder::userCreation(l2 , admin));
    //admin created l3
    assert(eventLog.at(2)->getText() == EventMessageBuilder::userCreation(l3 , admin));

    //one copy of d1 is created by l2
    assert(eventLog.at(3)->getText() == EventMessageBuilder::copyCreation(d1 , l2));
    //second copy of d1 is created by l2
    assert(eventLog.at(4)->getText() == EventMessageBuilder::copyCreation(d1 , l2));
    //third copy of d1 is created by l2 so total is 3 copies
    assert(eventLog.at(5)->getText() == EventMessageBuilder::copyCreation(d1 , l2));

    //one copy of d2 is created by l2
    assert(eventLog.at(6)->getText() == EventMessageBuilder::copyCreation(d2 , l2));
    //one copy of d2 is created by l2
    assert(eventLog.at(7)->getText() == EventMessageBuilder::copyCreation(d2 , l2));
    //one copy of d2 is created by l2 so total is 3 copies
    assert(eventLog.at(8)->getText() == EventMessageBuilder::copyCreation(d2 , l2));

    //one copy of d3 is created by l2
    assert(eventLog.at(9)->getText() == EventMessageBuilder::copyCreation(d3 , l2));
    //one copy of d3 is created by l2
    assert(eventLog.at(10)->getText() == EventMessageBuilder::copyCreation(d3 , l2));
    //one copy of d3 is created by l2
    assert(eventLog.at(11)->getText() == EventMessageBuilder::copyCreation(d3 , l2));
    //one copy of d3 is created by l2 so total is 3 copies

    //librarian l2 created patron p1
    assert(eventLog.at(12)->getText() == EventMessageBuilder::userCreation(p1 , l2));
    //librarian l2 created patron p2
    assert(eventLog.at(13)->getText() == EventMessageBuilder::userCreation(p2 , l2));
    //librarian l2 created patron p3
    assert(eventLog.at(14)->getText() == EventMessageBuilder::userCreation(p3 , l2));
    //librarian l2 created patron s
    assert(eventLog.at(15)->getText() == EventMessageBuilder::userCreation(s , l2));
    //librarian l2 created patron v
    assert(eventLog.at(16)->getText() == EventMessageBuilder::userCreation(v , l2));

    //make sure that p1 checked out d3
    assert(eventLog.at(17)->getText() == EventMessageBuilder::checkOut(d3 , p1));
    //make sure that p2 checked out d3
    assert(eventLog.at(18)->getText() == EventMessageBuilder::checkOut(d3 , p2));
    //make sure that s checked out d3
    assert(eventLog.at(19)->getText() == EventMessageBuilder::checkOut(d3 , s));
    //make sure that v was placed into waiting queue for doc3
    assert(eventLog.at(20)->getText() == EventMessageBuilder::inQueuePlacement(d3 , v));
    //make sure that p3 was placed into waiting queue for doc3
    assert(eventLog.at(21)->getText() == EventMessageBuilder::inQueuePlacement(d3 , p3));


    //make sure that librarian l1 failed to place outstanding request on d3
    assert(eventLog.at(22)->getText() == EventMessageBuilder::outstandingRequestCheck(d3 , l1 , false));

    qDebug()<<"Test 8 Run successfully";

    /*
    */


}
void TestSuite::TC9(){
    TC7();

    auto eventLog = docProxy->getEventLog();

    //confirm the event log is identical message by message

    //qDebug()<<eventLog.at(0)->getText()<<' '<<eventLog.at(0)->getd;

    //admin created l1
    assert(eventLog.at(0)->getText() == EventMessageBuilder::userCreation(l1 , admin));
    //admin created l2
    assert(eventLog.at(1)->getText() == EventMessageBuilder::userCreation(l2 , admin));
    //admin created l3
    assert(eventLog.at(2)->getText() == EventMessageBuilder::userCreation(l3 , admin));

    //one copy of d1 is created by l2
    assert(eventLog.at(3)->getText() == EventMessageBuilder::copyCreation(d1 , l2));
    //second copy of d1 is created by l2
    assert(eventLog.at(4)->getText() == EventMessageBuilder::copyCreation(d1 , l2));
    //third copy of d1 is created by l2 so total is 3 copies
    assert(eventLog.at(5)->getText() == EventMessageBuilder::copyCreation(d1 , l2));

    //one copy of d2 is created by l2
    assert(eventLog.at(6)->getText() == EventMessageBuilder::copyCreation(d2 , l2));
    //one copy of d2 is created by l2
    assert(eventLog.at(7)->getText() == EventMessageBuilder::copyCreation(d2 , l2));
    //one copy of d2 is created by l2 so total is 3 copies
    assert(eventLog.at(8)->getText() == EventMessageBuilder::copyCreation(d2 , l2));

    //one copy of d3 is created by l2
    assert(eventLog.at(9)->getText() == EventMessageBuilder::copyCreation(d3 , l2));
    //one copy of d3 is created by l2
    assert(eventLog.at(10)->getText() == EventMessageBuilder::copyCreation(d3 , l2));
    //one copy of d3 is created by l2
    assert(eventLog.at(11)->getText() == EventMessageBuilder::copyCreation(d3 , l2));
    //one copy of d3 is created by l2 so total is 3 copies

    //librarian l2 created patron p1
    assert(eventLog.at(12)->getText() == EventMessageBuilder::userCreation(p1 , l2));
    //librarian l2 created patron p2
    assert(eventLog.at(13)->getText() == EventMessageBuilder::userCreation(p2 , l2));
    //librarian l2 created patron p3
    assert(eventLog.at(14)->getText() == EventMessageBuilder::userCreation(p3 , l2));
    //librarian l2 created patron s
    assert(eventLog.at(15)->getText() == EventMessageBuilder::userCreation(s , l2));
    //librarian l2 created patron v
    assert(eventLog.at(16)->getText() == EventMessageBuilder::userCreation(v , l2));

    //make sure that p1 checked out d3
    assert(eventLog.at(17)->getText() == EventMessageBuilder::checkOut(d3 , p1));
    //make sure that p2 checked out d3
    assert(eventLog.at(18)->getText() == EventMessageBuilder::checkOut(d3 , p2));
    //make sure that s checked out d3
    assert(eventLog.at(19)->getText() == EventMessageBuilder::checkOut(d3 , s));
    //make sure that v was placed into waiting queue for doc3
    assert(eventLog.at(20)->getText() == EventMessageBuilder::inQueuePlacement(d3 , v));
    //make sure that p3 was placed into waiting queue for doc3
    assert(eventLog.at(21)->getText() == EventMessageBuilder::inQueuePlacement(d3 , p3));

    //make sure that librarian l3 placed outstanding request on d3
    assert(eventLog.at(22)->getText() == EventMessageBuilder::outstandingRequestCheck(d3 , l3 , true));


    //make sure that waiting queue for d3 was deleted from system
    assert(eventLog.at(23)->getText() == EventMessageBuilder::queueDeletion(d3));

    //make sure that v was notified that he was removed from doc3 waiting queue
    assert(eventLog.at(24)->getText() == EventMessageBuilder::userOutOfQueue(d3 , v));
    //make sure that v was notified that he was removed from doc3 waiting queue
    assert(eventLog.at(25)->getText() == EventMessageBuilder::userOutOfQueue(d3 , p3));

    //make sure that p1 was notified to return the document d3 immediately
    assert(eventLog.at(26)->getText() == EventMessageBuilder::immediateReturnNotif(d3 , p1));
    //make sure that p2 was notified to return the document d3 immediately
    assert(eventLog.at(27)->getText() == EventMessageBuilder::immediateReturnNotif(d3 , p2));
    //make sure that s was notified to return the document d3 immediately
    assert(eventLog.at(28)->getText() == EventMessageBuilder::immediateReturnNotif(d3 , s));



    qDebug()<<"Test 9 Run successfully";


}

void TestSuite::TC10(){
    TC4();
    //construct a search specifer to search for books which
    //contains "introduction to algorithms" in its title and search for such books
    auto searchResult = docProxy->getSpecific(SearchSpecifier("" , "" , "Introduction to Algorithms" , 0 , 0 , 0));
    //make sure the result is only one doc and it's book d1
    assert(searchResult.size() == 1 && searchResult.at(0)->operator ==(d1));
    qDebug()<<"Test 10 Run successfully";


}


void TestSuite::TC11(){
    TC4();
    //construct a search specifer to search for books which
    //contains "algorithms" in its title and search for such books
    auto searchResult = docProxy->getSpecific(SearchSpecifier("" , "" , "Algorithms" , 0 , 0 , 0));
    //make sure the result is 2 documents
    assert(searchResult.size() == 2);
    //make sure that these documents are d1 , d2
    assert(look_in(searchResult , d1) && look_in(searchResult , d2));
    qDebug()<<"Test 11 Run successfully";

}


void TestSuite::TC12(){
    TC4();
    //construct a search specifer to search for books which
    //contains "algorithms" in its keywords and search for such books
    auto searchResult = docProxy->getSpecific(SearchSpecifier("" , "Algorithms" , "" , 0 , 0 , 0));
    //make sure the result is 2 documents
    assert(searchResult.size() == 3);
    //make sure that these documents are d1 , d2 , d3
    assert(look_in(searchResult , d1) && look_in(searchResult , d2)  && look_in(searchResult , d3));
    qDebug()<<"Test 12 Run successfully";

}

void TestSuite::TC13(){
    TC4();
    //construct a search specifer to search for books which
    //contains "algorithms" AND "programming" in its title and search for such books
    auto searchResult = docProxy->getSpecific(SearchSpecifier("" , "" , "Algorithms#Programming" , 0 , 0 , 0 , 1));
    //make sure the result is empty list
    assert(searchResult.isEmpty());
    qDebug()<<"Test 13 Run successfully";
}

void TestSuite::TC14(){
    TC4();
    //construct a search specifer to search for books which
    //contains "algorithms" OR "programming" in its title and search for such books
    auto searchResult = docProxy->getSpecific(SearchSpecifier("" , "" , "Algorithms#Programming" , 0 , 0 , 0 , 0));
    //make sure the search results in 3 documents
    assert(searchResult.size() == 3);
    //make sure that these documents are d1 , d2 , d3
    assert(look_in(searchResult , d1) && look_in(searchResult , d2)  && look_in(searchResult , d3));
    qDebug()<<"Test 14 Run successfully";
}

void TestSuite::runnall(){
    TC1();
    TC2();
    TC3();
    TC4();
    TC5();
    TC6();
    TC7();
    TC8();
    TC9();
    TC10();
    TC11();
    TC12();
    TC13();
    TC14();
}


