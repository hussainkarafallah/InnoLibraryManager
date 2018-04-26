#ifndef LIBRARIANCOPYMODEL_H
#define LIBRARIANCOPYMODEL_H

#include <Model/documententity.h>
#include <Data/documentdataproxy.h>
#include <Data/userdataproxy.h>

/*! \brief Librarian copy Model class which we represent the documents copies information of our library inside this model
 *
 *  This class is linked to the database and it stores the information  about document copies requested by the librarian throught the view, and is presented to the librarian through the view object that maintains the interface that interacts with librarian
 *  It's a table styled model.
 *
 */
class LibrarianCopyModel : public QStandardItemModel
{
    Q_OBJECT
private:
    QList <Copy*> copiesList;  //!< list of copies presented in the model
    DocumentDataProxy *ddbProxy; //!< a proxy that connects to the database
    UserDataProxy *udbProxy;  //!< a proxy responsible for users queries that connects to the database
    void appendCopy(Copy *copy); //!< appending a new copy with its information to our model


public:
    explicit LibrarianCopyModel(QObject *parent = nullptr); //!<constructor
    bool deleteByIndex(QModelIndex pIndex); //!< deleting a certain copy the librarian referring to along with report (successful/not)
    bool immediateReturnByIndex(QModelIndex pIndex); //!< asking for immediate return of a copy the librarian referring to along with report (successful/not)
    bool deleteCopy(Copy *copy); //!< deleting a certain copy passed along this function along with report (successful/not)

    bool confirmPendingRequestByIndex(QModelIndex pIndex); //!< confirming the renewal/return of a copy librarian regerring to along with report (successful/not)
    void updateData(); //!< a function that updates data presented in the model
    void updateDataAWUser(User *U); //!< a function that updates data presented in the model and get information about documents associated with user
    void insertCopy(Copy *copy); //!< a function that inserts a copy into the model and forwards the request to the database


};

#endif // LIBRARIANCOPYMODEL_H
