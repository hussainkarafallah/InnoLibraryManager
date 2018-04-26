#ifndef DOCTYPECHOICEDIALOG_H
#define DOCTYPECHOICEDIALOG_H



#include <View/adddialog_av.h>
#include <View/adddialog_book.h>
#include <View/adddialog_journal.h>


/*! \brief doctypedialog this is a simple dialog that lets librarian choose which kind of documents he want to add
 *
 *
 *
 *
 */
class DocTypeDialog : public QDialog
{
    Q_OBJECT

public:
    DocTypeDialog(QDialog *parent);
    enum DialogType {BOOKDIALOG = 0 , ARTICLEDIALOG = 1 , AVDIALOG = 2};
private:
    QHBoxLayout *horizontal_Layout;
    QPushButton *bookButton;
    QPushButton *journalButton;
    QPushButton *avButton;
private slots:
    void bookButton_clicked();   //!< a slot activated when the librarian chooses to add a book
    void journalButton_clicked();  //!<  a slot activated when librarian chooses to add a journal article
    void avButton_clicked();  //!< a slot activated when librarian chooses to add an AV
signals:
    void submitDialogType(int type);  //!< a signal that carries the type of document the librarian wants to add
};

#endif // DOCTYPECHOICEDIALOG_H
