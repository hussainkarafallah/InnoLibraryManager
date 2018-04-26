#ifndef COPYDIALOG_H
#define COPYDIALOG_H


#include<Model/documententity.h>

/*! \brief copydialog this is a simple dialog for specifying the information of the copy we want to add to the system
 *
 *
 *
 *
 */
class CopyDialog : public QDialog
{
    Q_OBJECT
private:

    Document *doc;
    QGridLayout *gLayout;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *mainLayout;

    QPushButton *addButton;
    QPushButton *cancelButton;

    QLabel *sectionLabel;
    QLabel *docIdLabel;
    QLabel *copyIdLabel;
    QLabel *docTypeLabel;
    QLabel *titleLabel;

    QLineEdit *docIdLineEdit;
    QLineEdit *copyIdLineEdit;
    QLineEdit *titleLineEdit;
    QLineEdit *docTypeLineEdit;
    QLineEdit *sectionLineEdit;

    void endDialog(); //!< a function to close the dialog and emit the signal stating that our dialog has ended
    bool validate(); //!< a simple validator
signals:
    void submitNewCopy(Copy *C); //!< a signal emitted to the controller that carries the information about the copy we are adding to the system
    void dialogEnded(); //!< signal emitted to disconnect the dialog from all objects before deletion
public slots:
    void addButtonClicked(); //!< a slot that is activated when we click add button so the dialog submits the information of the copy
    void cancelButtonclicked(); //!< a slot to end the dialog when we click cancel

public:
    CopyDialog(); //!< default constructor
    CopyDialog(int pId , Document *pDoc); //!< a constructor which initializes our dialog with the copy generated ID and little info about the doc this copy represents

};

#endif // COPYDIALOG_H
