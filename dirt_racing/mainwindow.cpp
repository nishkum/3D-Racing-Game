/*!
  Main window of the gui
  remains open until the game is exited

 */


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "dialog7.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*!
  Code executed when Next is clicked
 */

void MainWindow::on_pushButton_2_clicked()
{
    Dialog mdialog;
    mdialog.setModal(true);
    mdialog.exec();     //!< next window is called

}

/*!
  Code executed when Credits is clicked
 */

void MainWindow::on_pushButton_3_clicked()
{
    Dialog7 mdialog;
    mdialog.setModal(true);
    mdialog.exec();     //!< next window is called
}
