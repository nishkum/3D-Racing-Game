/*!
  This window has options for easy and hard levels

 */

#include "dialog1.h"
#include "ui_dialog1.h"
#include "dialog2.h"
#include "dialog3.h"
#include "dialog.h"

Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    ui->setupUi(this);
}

Dialog1::~Dialog1()
{
    delete ui;
}


/*!
  Code executed when Easy is clicked
 */

void Dialog1::on_pushButton_clicked()
{
    Dialog2 mdialog;
    mdialog.setModal(true);
    this->close();
    mdialog.exec();
}

/*!
  Code executed when Hard is clicked
 */

void Dialog1::on_pushButton_2_clicked()
{
    Dialog3 mdialog;
    mdialog.setModal(true);
    this->close();
    mdialog.exec();
}

/*!
  Code executed when Back is clicked
 */

void Dialog1::on_pushButton_3_clicked()
{
    Dialog mdialog;
    mdialog.setModal(true);
    this->close();
    mdialog.exec();
}
