#include "queueinfodialog.h"
#include "ui_queueinfodialog.h"

QueueInfoDialog::QueueInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueueInfoDialog)
{
    ui->setupUi(this);
}

QueueInfoDialog::QueueInfoDialog(QWidget *parent, Document *pDoc, QStringListModel *L):QueueInfoDialog(parent){
    cancelButton = ui->pushButton;
    label = ui->label;
    view = ui->listView;
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    doc = pDoc;
    label->setText("Queue Information For Document" + doc->getTitle());
    view->setModel(L);
    connect(cancelButton , SIGNAL(clicked(bool)) , this , SLOT(close()));
}

QueueInfoDialog::~QueueInfoDialog()
{
    delete ui;
}
