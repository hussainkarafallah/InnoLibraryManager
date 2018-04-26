#include "logwidget.h"
#include "ui_logwidget.h"
#include <Model/documententity.h>
#include <Data/documentdataproxy.h>

LogWidget::LogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogWidget)
{

    ui->setupUi(this);
    ddb = new DocumentDataProxy();
    textEdit = ui->plainTextEdit;
    textEdit->setReadOnly(true);
    timer = new QTimer();
    connect(timer , SIGNAL(timeout()) , this , SLOT(refresh()) , Qt::UniqueConnection);
    timer->start(5000);
    updateData();
}

void LogWidget::updateData(){
    textEdit->setPlainText("");
    auto L = ddb->getEventLog();
    for(auto ev : L)
        appendEvent(*ev);
}

void LogWidget::refresh(){
    timer->start(5000);
    updateData();
}
void LogWidget::appendEvent(LibraryEvent ev){
    auto cur = textEdit->toPlainText();

    cur += ev.getDate().toString(Qt::ISODate);
    cur += "\n";
    cur += ev.getText();
    cur += "\n";
    cur += "\n";

    textEdit->setPlainText(cur);

}
LogWidget::~LogWidget()
{
    delete ui;
}
