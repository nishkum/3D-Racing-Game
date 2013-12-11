/*!
  This window has options for various tracks of Hard level

 */

#include "dialog3.h"
#include "ui_dialog3.h"
#include "dialog1.h"
#include "dialog4.h"
#include "dialog8.h"
#include <QFile>
#include <QTextStream>

Dialog3::Dialog3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog3)
{
    ui->setupUi(this);
}

Dialog3::~Dialog3()
{
    delete ui;
}

/*!
  Code executed when Track 1 is clicked
 */

void Dialog3::on_pushButton_clicked()
{
    QString fileName_tr = "tracks.txt";
    QFile file_tr(fileName_tr);
    file_tr.open(QIODevice::ReadOnly);
    QTextStream stream_tr(&file_tr);
    QString bools = stream_tr.readAll();
    file_tr.close();
    QStringList lst_tr = bools.split('\n');
    if ((lst_tr.at(5)).toInt() == 0) {
        Dialog8 mdialog_tr;
        mdialog_tr.setModal(true);
        //this->close();
        mdialog_tr.exec();
        return;
    }


    QString fileName = "curr_game.txt";         //!< A file is created which has track no. and player name

               if (!fileName.isEmpty()) {
                   QFile file(fileName);
                   if (!file.open(QIODevice::WriteOnly)) {
                       // error message
                   } else {

                       QTextStream stream(&file);
                       stream << "5";
                       stream.flush();
                       file.close();
                   }
               }

    Dialog4 mdialog;
    mdialog.setModal(true);
    this->close();
    mdialog.exec();
}
/*!
  Code executed when Track 2 is clicked
 */

void Dialog3::on_pushButton_2_clicked()
{
    QString fileName_tr = "tracks.txt";
    QFile file_tr(fileName_tr);
    file_tr.open(QIODevice::ReadOnly);
    QTextStream stream_tr(&file_tr);
    QString bools = stream_tr.readAll();
    file_tr.close();
    QStringList lst_tr = bools.split('\n');
    if ((lst_tr.at(6)).toInt() == 0) {
        Dialog8 mdialog_tr;
        mdialog_tr.setModal(true);
        //this->close();
        mdialog_tr.exec();
        return;
    }

    QString fileName = "curr_game.txt";

               if (!fileName.isEmpty()) {
                   QFile file(fileName);
                   if (!file.open(QIODevice::WriteOnly)) {
                       // error message
                   } else {

                       QTextStream stream(&file);
                       stream << "6";
                       stream.flush();
                       file.close();
                   }
               }

    Dialog4 mdialog;
    mdialog.setModal(true);
    this->close();
    mdialog.exec();
}

/*!
  Code executed when Track 3 is clicked
 */

void Dialog3::on_pushButton_3_clicked()
{
    QString fileName_tr = "tracks.txt";
    QFile file_tr(fileName_tr);
    file_tr.open(QIODevice::ReadOnly);
    QTextStream stream_tr(&file_tr);
    QString bools = stream_tr.readAll();
    file_tr.close();
    QStringList lst_tr = bools.split('\n');
    if ((lst_tr.at(7)).toInt() == 0) {
        Dialog8 mdialog_tr;
        mdialog_tr.setModal(true);
        //this->close();
        mdialog_tr.exec();
        return;
    }

    QString fileName = "curr_game.txt";

               if (!fileName.isEmpty()) {
                   QFile file(fileName);
                   if (!file.open(QIODevice::WriteOnly)) {
                       // error message
                   } else {

                       QTextStream stream(&file);
                       stream << "7";
                       stream.flush();
                       file.close();
                   }
               }

    Dialog4 mdialog;
    mdialog.setModal(true);
    this->close();
    mdialog.exec();
}

/*!
  Code executed when Track 4 is clicked
 */

void Dialog3::on_pushButton_4_clicked()
{
    QString fileName_tr = "tracks.txt";
    QFile file_tr(fileName_tr);
    file_tr.open(QIODevice::ReadOnly);
    QTextStream stream_tr(&file_tr);
    QString bools = stream_tr.readAll();
    file_tr.close();
    QStringList lst_tr = bools.split('\n');
    if ((lst_tr.at(8)).toInt() == 0) {
        Dialog8 mdialog_tr;
        mdialog_tr.setModal(true);
        //this->close();
        mdialog_tr.exec();
        return;
    }

    QString fileName = "curr_game.txt";

               if (!fileName.isEmpty()) {
                   QFile file(fileName);
                   if (!file.open(QIODevice::WriteOnly)) {
                       // error message
                   } else {

                       QTextStream stream(&file);
                       stream << "8";
                       stream.flush();
                       file.close();
                   }
               }

    Dialog4 mdialog;
    mdialog.setModal(true);
    this->close();
    mdialog.exec();
}

/*!
  Code executed when Track 5 is clicked
 */

void Dialog3::on_pushButton_5_clicked()
{
    QString fileName_tr = "tracks.txt";
    QFile file_tr(fileName_tr);
    file_tr.open(QIODevice::ReadOnly);
    QTextStream stream_tr(&file_tr);
    QString bools = stream_tr.readAll();
    file_tr.close();
    QStringList lst_tr = bools.split('\n');
    if ((lst_tr.at(9)).toInt() == 0) {
        Dialog8 mdialog_tr;
        mdialog_tr.setModal(true);
        //this->close();
        mdialog_tr.exec();
        return;
    }

    QString fileName = "curr_game.txt";

               if (!fileName.isEmpty()) {
                   QFile file(fileName);
                   if (!file.open(QIODevice::WriteOnly)) {
                       // error message
                   } else {

                       QTextStream stream(&file);
                       stream << "9";
                       stream.flush();
                       file.close();
                   }
               }

    Dialog4 mdialog;
    mdialog.setModal(true);
    this->close();
    mdialog.exec();
}

/*!
  Code executed when Back is clicked
 */

void Dialog3::on_pushButton_6_clicked()
{
    Dialog1 mdialog;
    mdialog.setModal(true);
    this->close();
    mdialog.exec();
}
