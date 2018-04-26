#ifndef USERCOPYMODEL_H
#define USERCOPYMODEL_H


#include <Model/documententity.h>
#include <Data/documentdataproxy.h>


/*! \brief user copy Model class which we represent the information about documents copies of our library associated with a certain user inside this model
 *
 *  This class is linked to the database and it stores the information  about document copies associated with a certain user throught the view, and is presented to the patron through the view object that maintains the interface maintains his queries (return/renew)
 *  It's a table styled model.
 *
 */
class UserCopyModel : public QStandardItemModel
{
    Q_OBJECT
private:
    User *user; //!< the user associated with the copies inside our model
    QList <Copy*> copiesList; //!<  list of copies inside our model
    DocumentDataProxy *ddbProxy; //!< a proxy that links the model to the database
    void appendCopy(Copy *copy); //!< a function that appends a copy to our model


public:
    UserCopyModel(QObject *parent , User *U); //!<  constructor

    void updateData(); //!< a function that updates the data of our model

    bool returnByIndex(QModelIndex pIndex); //!< a function that asks for returning a booked item by our user which he is referring to through the view (interface) along with the report (successful/not)

    int renewByIndex(QModelIndex pIndex , User *U); //!< a function that renews a certain item selected from the table



};

#endif
