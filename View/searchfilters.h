#ifndef SEARCHFILTERS_H
#define SEARCHFILTERS_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class SearchFilters : public QDialog
{
    Q_OBJECT

public:
    SearchFilters(QWidget *parent = 0);
    ~SearchFilters();

    QGridLayout *mainLayout;
    QVBoxLayout *labelLayout;
    QVBoxLayout *lineEditLayout;

    QLineEdit *lineEdit_titleKeys;
    QLineEdit *lineEdit_keyWords;
    QLineEdit *lineEdit_authorKeys;

    QLabel *label_titleKeys;
    QLabel *label_keyWords;
    QLabel *label_authorKeys;

    QPushButton *cancelButton;

private slots:
    void cancelButton_clicked();
};

#endif // SEARCHFILTERS_H
