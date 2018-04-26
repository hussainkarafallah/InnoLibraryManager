#ifndef QUEUEINFODIALOG_H
#define QUEUEINFODIALOG_H

#include <Model/documententity.h>

namespace Ui {
class QueueInfoDialog;
}

class QueueInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QueueInfoDialog(QWidget *parent = 0);

    QueueInfoDialog(QWidget *parent , Document *pDoc , QStringListModel *L);

    ~QueueInfoDialog();

    Document *doc;
    QListView *view;
    QLabel *label;
    QPushButton *cancelButton;


private:
    Ui::QueueInfoDialog *ui;
};

#endif // QUEUEINFODIALOG_H
