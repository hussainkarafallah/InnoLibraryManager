#ifndef USERCOPYMANAGER_H
#define USERCOPYMANAGER_H


#include<View/usercopyview.h>
#include<Model/usercopymodel.h>
#include<Data/documentdataproxy.h>

/*! \brief a controller class that links the copies model shown to the patron and its corresponding view class
 *
 *  This class links the copies model shown to the patron which represents the information about the copies of documents he has checked out or he has to return or asked for renewal.
 *  The view class provides an interface to show information to the patron and apply some queries described in project.
 */
class UserCopyManager: public QWidget
{
    Q_OBJECT
private:
    User *user; //!< the default constructor
    DocumentDataProxy *ddbProxy; //!< the proxy that links our class to the database
    UserCopyModel *model; //!<the copies model which repreesnts information about items associated with the user
    UserCopyView *view; //!<the view object which will represent the model to the patron through an interface
    void setupDisplay(); //!<setting up display
    void setup(); //!<setting up connections between model and view and initializing members
public:
    UserCopyManager(QWidget *parent = nullptr); //!<default constructor
    UserCopyManager(QWidget *parent , User *U); //!<default constructor along with the patron associated
signals:
    void submitReturnReport(bool report); //!< submitting the status of the return request of a certian item (successful / not)
    void submitRenewReport(int report); //!< submitting the status of the renewal request of certain item
public slots:
    void returnRequestHandler(QModelIndex index); //!< a slot handling the return request of a certain item selected by the patron
    void renewRequestHandler(QModelIndex index); //!< a slot that handles the request of renewing an item
    void refresh(); //!< a slot refreshing the data presented to our patron

};

#endif // USERCOPYMANAGER_H
