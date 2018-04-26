#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Model/delegates.h"
#include "Model/usermodel.h"
#include "View/usermanagerwidget.h"
#include "View/usermodelview.h"

#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QStandardItemModel>
#include <QStyle>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{

    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    UsersManagerWidget *usersManagerWidget;
};

#endif // MAINWINDOW_H
