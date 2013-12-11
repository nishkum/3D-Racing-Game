/*!
  This window shows up when new high score is created
 */


#include "dialog5.h"
#include "ui_dialog5.h"

Dialog5::Dialog5(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog5)
{
    ui->setupUi(this);
    ui->textBrowser->setText("CONGRATS!!!!!!!! \n NEW HIGH SCORE");
}

Dialog5::~Dialog5()
{
    delete ui;
}
