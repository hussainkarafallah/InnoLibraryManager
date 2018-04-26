#ifndef USERCOPYVIEW_H
#define USERCOPYVIEW_H



#include <Model/usercopymodel.h>
#include <Model/documententity.h>

/*! \brief usercopyview this class is the view element that represents the copies data model for user
 *
 * This class represents the information about copies in our data model to the user. this class is for usage with user. it allows the user to interact with the system and perform certain queries(return,renew...etc)
 *
 */


class UserCopyView : public QWidget
{
    Q_OBJECT

    QPushButton *renewButton , *returnButton , *refreshButton;

    QTableView *view;  //!< qt table view class which loads the representer model data into it and show it to user

    UserCopyModel *model; //!< the data model this view is presenting

    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;

    void setup(); //!< setting up connections and initializing objects
    void setupDisplay(); //!< setting up display
    QModelIndex getCursorPosition(); //!< getting the index of the selected cell by user



signals:

    void returnRequest(QModelIndex index); //!< a slot that carries the index of some copy our user wants to return
    void renewRequest(QModelIndex index);
    void refreshRequest(); //!< a slot that carries the command to the model to refresh all information (this was introduced for making testing easier)


public:
    UserCopyView(QWidget *parent , UserCopyModel *pModel); //!< a constructor initialized with the model we want to present

public slots:

    void returnButtonClicked(); //!< a signal that carries the index of the copy our user wishes to return
    void renewButtonClicked(); //!< a signal that carries the index of the copy our user wishes to renew
    void refreshButtonClicked(); //!< a signal that's submitted to the controller so it asks the model to refresh the data (note that this feature was added to make testing easier)

    void acceptReturnReport(bool state); //!< a slot that recieves the status of the return request (accepted or not)
    void acceptRenewReport(int state); //!< a slot that reveies the status of a renewal request if it was successful or not




};

#endif // USERCOPYVIEW_H
