#ifndef LIBRARIANCOPYMANAGER_H
#define LIBRARIANCOPYMANAGER_H


#include "Data/documentdataproxy.h"
#include "Model/librariancopymodel.h"
#include "View/librariancopyview.h"

/*! \brief a controller class that links the copies model shown to the librarian and its corresponding view class
 *
 *  This class links the copies model shown to the librarian which represents the information about the copies of documents available
 * in our library. The view class provides an interface to show information to the librarian and apply some queries described in project.
 */
class LibrarianCopyManager : public QWidget
{
    Q_OBJECT
public:
    LibrarianCopyManager(QWidget *parent = nullptr); //!<  Default Constructor
    LibrarianCopyManager(QWidget *parent , User *U); //!<  A constructor along with the librarian that will be reacting with the model/view
    void userInfoRequestHandler(User *U); //!< a slot that handles the request of certain user checked out documents information

private:
    User *user; //!< the librarian which the model will be presented to
    DocumentDataProxy *ddb; //!< the proxy which links our controller to the database
    LibrarianCopyModel *model; //!< the copies model which represents information about copies in our database
    LibrarianCopyView *view; //!< the view class which will represent the model to the librarian through an interface

    void setupDisplay(); //!< setting up the display of the widget
    void setup(); //!< setting up connections between model and view

signals:
    void submitDeleteReport(bool report); //!< submits to the interface the result of deleting query (possible/not)
    void submitConfirmReport(bool report); //!< submits to the interface the result of (return/renewal confirmation) confirmed by the librarian
    void submitReturnReport(bool report); //!< submits to the interface the result of a emergency return request by the librarian (successful or not)
public slots:
    void resetRequestHandler(); //!< a slot that handles the librarian request of updating the information
    void deleteRequestHandler(QModelIndex index); //!< a slot that handles the librarian request of deleting a certian selected copy
    void confirmRequestHandler(QModelIndex index); //!< a slot that handles the librarian confirmation of a renewal/return request
    void returnRequestHandler(QModelIndex index); //!< a slot that handles the librarian emergency request of immediate return of a certain item
    void refresh(); //!< a slot that updates the data presented to the librarian
};

#endif // LIBRARIANCOPYMANAGER_H
