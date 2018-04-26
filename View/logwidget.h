#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QWidget>
#include <Model/documententity.h>
#include <Data/documentdataproxy.h>

/*! \brief Log widget is a widget that's included in the admin window
 *
 *  This widget has a read-only plain text editor displays the whole log of the library
 *  It also features a timer so this log updates every few seconds
 *
 *
 *
 */
namespace Ui {
class LogWidget;
}

class LogWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LogWidget(QWidget *parent = 0);
    ~LogWidget();
    void updateData();

private:
    Ui::LogWidget *ui;
    DocumentDataProxy *ddb;
    QPlainTextEdit *textEdit;
    QTimer *timer;
    void appendEvent(LibraryEvent note);

public slots:
    void refresh();
};

#endif // LOGWIDGET_H
