#include "searchfilters.h"

SearchFilters::SearchFilters(QWidget *parent) : QDialog(parent) {
  mainLayout = new QGridLayout();
  labelLayout = new QVBoxLayout();
  lineEditLayout = new QVBoxLayout();

  lineEdit_authorKeys = new QLineEdit();
  lineEdit_keyWords = new QLineEdit();
  lineEdit_titleKeys = new QLineEdit();

  label_authorKeys = new QLabel("Author keys");
  label_keyWords = new QLabel("Key words");
  label_titleKeys = new QLabel("Title keys");

  cancelButton = new QPushButton("Cancel");

  lineEditLayout->addWidget(lineEdit_authorKeys);
  lineEditLayout->addWidget(lineEdit_keyWords);
  lineEditLayout->addWidget(lineEdit_titleKeys);

  labelLayout->addWidget(label_authorKeys);
  labelLayout->addWidget(label_keyWords);
  labelLayout->addWidget(label_titleKeys);

  mainLayout->addLayout(labelLayout, 0, 0);
  mainLayout->addLayout(lineEditLayout, 0, 1);
  mainLayout->addWidget(cancelButton, 1, 1, Qt::AlignJustify);

  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelButton_clicked()));

  setLayout(mainLayout);
  setWindowTitle("Search filters");
}

SearchFilters::~SearchFilters() {}

void SearchFilters::cancelButton_clicked() { done(0); }
