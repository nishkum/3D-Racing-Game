/*!
  This window has options for new game and practice mode

 */

#include "dialog.h"
#include "ui_dialog.h"
#include "dialog1.h"
#include "dialog9.h"
#include "mainwindow.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

/*!
  Code executed when Back is clicked
 */

void Dialog::on_pushButton_2_clicked()
{
    this->close();
    //MainWindow w;
    //w.show();
}

/*!
  Code executed when New Game is clicked
 */

void Dialog::on_pushButton_clicked()
{
    Dialog1 mdialog;
    mdialog.setModal(true);
    this->close();
    mdialog.exec();
}

/*!
  Code executed when Practice mode is clicked
 */

void Dialog::on_pushButton_3_clicked()
{
    this->close();
    system("cd ../project1 && ./product_game 11");

}

/*!
  Code executed when Controls is clicked
 */


void Dialog::on_pushButton_4_clicked()
{
    Dialog9 mdialog;
    mdialog.setModal(true);
    this->close();
    mdialog.exec();
}
