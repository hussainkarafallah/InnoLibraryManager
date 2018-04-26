#include "View/loginwindow.h"
#include <Model/documententity.h>
#include <Model/documentmodel.h>
#include <Model/usermodel.h>
#include <Model/usermodelentity.h>
#include <QApplication>
#include <QDebug>
#include <cassert>

/*!
 * \brief Test case 1.
 */
void runtest1()
{
    Document *A =
        new Book(1, "The godfather", new QList<QString>({"Francis Copolla"}),
                 new QList<QString>(), "Publisher", 1500, 10, 1970, false);
    Document *B =
        new Book(2, "The godfather", new QList<QString>({"Francis Copolla"}),
                 new QList<QString>(), "Publisher", 1500, 10, 1970, false);

    // in our system each book has a distinct id (also 2 copies of same books have
    // distinct ids as well)

    Patron *misha = new FacultyMember(1, "Misha", "Innopolis", "1234");

    DocumentModel *librariandata = new DocumentModel();

    librariandata->addDocument(A); // we should insert our books into the system
    // since we don't haven't got a data base yet.
    librariandata->addDocument(B);

    A->checkOut(QDate::currentDate(), misha);

    // Let's check the effect
    // We introduced a function in our data model get by id which returns a book
    // specified by id and all information
    // et customer name is a function returns the name of customer booking
    // document or special string instead

    assert(librariandata->getById(1)->getCustomerName() == "Misha" &&
           librariandata->getById(2)->isCheckedOut() == false);

    qDebug() << "test 1 successful";

    delete (librariandata);
}

/*!
 * \brief Test case 3.
 */
void runtest3()
{
    // faculty member
    Patron *alexander = new FacultyMember(1, "Alexander", "innopolis", "123");
    // normal non reference non bestseller book
    Document *D =
        new Book(1, "Intro to C++", new QList<QString>({"Bjarn Strostrup"}),
                 new QList<QString>(), "Publisher", 9999, 3, 2001, false);

    DocumentModel *librariandata = new DocumentModel();
    librariandata->addDocument(D);

    int ret = D->checkOut(QDate::currentDate(), alexander);
    assert(ret == Document::fourWeeks &&
           librariandata->getById(1)->getCustomerName() == "Alexander");

    qDebug() << "test 3 successful";
}

/*!
 * \brief Test case 4.
 */
void runtest4()
{
    // a note about test 4
    // written in the project description that the liomit for a faculty member
    // checking a book is 4 weeks regardless a best seller or not
    // in test description written 2 (I assumed it's 4)

    Patron *alexander = new FacultyMember(1, "Alexander", "innopolis", "123");

    // normal non reference BESTSELLER book specified by last argument
    Document *D =
        new Book(1, "Intro to C++", new QList<QString>({"Bjarn Strostrup"}),
                 new QList<QString>(), "Publisher", 9999, 3, 2001, false, true);

    DocumentModel *librariandata = new DocumentModel();

    librariandata->addDocument(D);

    int ret = D->checkOut(QDate::currentDate(), alexander);

    assert(ret == Document::fourWeeks &&
           librariandata->getById(1)->getCustomerName() == "Alexander");

    qDebug() << "test 4 successful";
}

/*!
 * \brief Test case 7.
 */
void runtest7()
{
    Document *D =
        new Book(1, "Intro to C++", new QList<QString>({"Bjarn Strostrup"}),
                 new QList<QString>(), "Publisher", 9999, 3, 2001, false);
    Document *E =
        new Book(2, "Intro to C++", new QList<QString>({"Bjarn Strostrup"}),
                 new QList<QString>(), "Publisher", 9999, 3, 2001, false);

    DocumentModel *librariandata = new DocumentModel();

    librariandata->addDocument(D);
    librariandata->addDocument(E);

    Patron *alex = new FacultyMember(1998, "Alex", "innopolis", "123456789");
    D->checkOut(QDate::currentDate(), alex);
    Patron *misha = new FacultyMember(1998, "Misha", "innopolis", "123456789");
    E->checkOut(QDate::currentDate(), misha);

    // let's check the effect
    // we introduced a function in our data model get by id which returns a book
    // specified by id and all information
    // get customer name is a function returns the name of customer booking
    // document or special string instead

    assert(librariandata->getById(1)->getCustomerName() == "Alex" &&
           librariandata->getById(2)->getCustomerName() == "Misha");

    qDebug() << "test 7 successful";
}

void runtest8()
{

    // a patron student misha

    Patron *misha = new Student(1, "Misha", "innopolis", "123");

    // a normal nonreference non bestseller book

    Document *D = new Book(1, "Enter Sandman", new QList<QString>({"Metallica"}),
                           new QList<QString>({}), "anyone", 1000, 10, 1900);

    DocumentModel *librariandata = new DocumentModel();

    librariandata->addDocument(D);

    int result = D->checkOut(QDate::currentDate(), misha);

    // ensure that result is 3 weeks and that the book was checked by misha and
    // that's tracked by librarian

    assert(result == Document::threeWeeks &&
           librariandata->getById(1)->getCustomerName() == "Misha");

    qDebug() << "test 8 successful";
}

/*!
 * \brief Test case 9.
 */
void runtest9()
{
    // a patron student misha
    Patron *misha = new Student(1, "Misha", "innopolis", "123");

    // a document as a best seller (specified in last argument)
    Document *D =
        new Book(1, "Blackwater Park", new QList<QString>({"Opeth"}),
                 new QList<QString>({}), "anyone", 1000, 10, 1900, false, true);
    DocumentModel *librariandata = new DocumentModel();

    librariandata->addDocument(D);

    int result = D->checkOut(QDate::currentDate(), misha);

    // ensure that result is 2 weeks and that the book was checked by misha and
    // that's tracked by librarian

    assert(result == Document::twoWeeks &&
           librariandata->getById(1)->getCustomerName() == "Misha");

    qDebug() << "test 9 successful";
}

/*!
 * \brief Test case 10.
 */
void runtest10()
{
    // a student misha
    Patron *misha = new Student(1, "Misha", "innopolis", "123");

    // a reference book (specified by last parameter)
    Document *E = new Book(1, "Ghost Of Perdition", new QList<QString>({"Opeth"}),
                           new QList<QString>({}), "anyone", 400, 5, 250, true);

    // a non reference book
    Document *D = new Book(2, "The Trooper", new QList<QString>({"Iron maiden"}),
                           new QList<QString>({}), "anyone", 231, 8, 100, false);

    DocumentModel *librariandata = new DocumentModel();

    librariandata->addDocument(D);

    librariandata->addDocument(E);

    int Dret = D->checkOut(QDate::currentDate(), misha);
    int Eret = E->checkOut(QDate::currentDate(), misha);

    //    qDebug() << Dret << Eret;

    assert(Eret == Document::unSuccessful && Dret == Document::threeWeeks);
    assert(librariandata->getById(1)->getCustomerName() == "In Library" &&
           librariandata->getById(2)->getCustomerName() == "Misha");

    qDebug() << "test 10 successful";
}

/*int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    runtest1();
    runtest3();
    runtest4();
    runtest7();
    runtest8();
    runtest9();
    runtest10();

    return a.exec();
}*/
