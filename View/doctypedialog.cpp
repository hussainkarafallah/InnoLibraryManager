#include "doctypedialog.h"

DocTypeDialog::DocTypeDialog(QDialog *parent) : QDialog(parent) {
  bookButton = new QPushButton("Book");
  journalButton = new QPushButton("Journal");
  avButton = new QPushButton("Audio\\Video file");

  bookButton->setFixedSize(200, 150);
  journalButton->setFixedSize(200, 150);
  avButton->setFixedSize(200, 150);

  horizontal_Layout = new QHBoxLayout();
  horizontal_Layout->addWidget(bookButton);
  horizontal_Layout->addWidget(journalButton);
  horizontal_Layout->addWidget(avButton);

  connect(bookButton, SIGNAL(clicked()), this, SLOT(bookButton_clicked()));
  connect(journalButton, SIGNAL(clicked()), this,
          SLOT(journalButton_clicked()));
  connect(avButton, SIGNAL(clicked()), this, SLOT(avButton_clicked()));

  setLayout(horizontal_Layout);
  setWindowTitle("Choose document type");
}

void DocTypeDialog::bookButton_clicked() {
    emit submitDialogType(BOOKDIALOG);
}

void DocTypeDialog::journalButton_clicked() {
    emit submitDialogType(ARTICLEDIALOG);
}

void DocTypeDialog::avButton_clicked() {
    emit submitDialogType(AVDIALOG);
}
