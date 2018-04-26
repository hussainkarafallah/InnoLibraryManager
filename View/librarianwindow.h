#ifndef LIBRARIANWINDOW_H
#define LIBRARIANWINDOW_H

#include <Model/documentmodel.h>
#include <View/prevdocumentview.h>
#include <Controller/documentmanagerwidget.h>
#include <Controller/usermanagerwidget.h>
#include <Controller/librariancopymanager.h>
#include <View/logwidget.h>

/*! \brief librarianwindow this class repreesnts the window object that shows when a librarian logs.
 *
 * This class contains the model view classes that represents data to the librarian and allows him to perform queries described in project
 * and links these widgets together
 */


class LibrarianWindow : public QMainWindow
{
    Q_OBJECT

private:
    User *U;
    QVBoxLayout *mainLayout;
    QStackedWidget *stackedWidget;
    QScrollArea* scrollarea;

    DocumentManagerWidget *docManager; //!< the complete unit for managing documents (mode/view)
    UserManagerWidget *userManager; //!< the complete   unit for managing users (usermode/usermodelview)
    LibrarianCopyManager *copyManager; //!< the complete unit for managing copies (librarian version)
    LogWidget *logWidget;

public:
    LibrarianWindow(QWidget *parent , User *U);
public slots:
    void switchToBooksMode(); //!<a slot activated to switch the view to the books viewing widget
    void switchToUsersMode();  //!< a slot activated to switch the view to the users view widget
    void switchToCopiesMode(); //!< a slot activated to switch the view to the copies manager widget
    void switchToUserInfo(User *U); //!< a slot activated when librarian asks to show docs associated with certain users so it switches the active widget and initializes the copymodel presenter with docs associated to this particular user
    void switchToLogMode(); //!< a slot activated when the admin asks to show the library log
    void logOut();
};
#endif // LIBRARIANWINDOW_H
