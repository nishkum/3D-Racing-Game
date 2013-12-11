/*!
  This window displays the gaming controls
 */


#include "dialog9.h"
#include "dialog.h"
#include "ui_dialog9.h"

Dialog9::Dialog9(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog9)
{
    ui->setupUi(this);
}

Dialog9::~Dialog9()
{
    delete ui;
}

/*!
  Code executed when Back is clicked
 */

void Dialog9::on_pushButton_clicked()
{
    Dialog mdialog;
    mdialog.setModal(true);
    this->close();
    mdialog.exec();
}
