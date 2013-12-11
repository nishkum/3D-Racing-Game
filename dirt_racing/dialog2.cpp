/*!
  This window has options for various tracks of Easy level

 */

#include "dialog2.h"
#include "ui_dialog2.h"
#include "dialog1.h"
#include "dialog4.h"
#include "dialog8.h"
#include <QFile>
#include <QTextStream>

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);
}

Dialog2::~Dialog2()
{
    delete ui;
}

/*!
  Code executed when Track 1 is clicked
 */

void Dialog2::on_pushButton_clicked()
{

    QString fileName_tr = "tracks.txt";
    QFile file_tr(fileName_tr);
    file_tr.open(QIODevice::ReadOnly);
    QTextStream stream_tr(&file_tr);
    QString bools = stream_tr.readAll();
    file_tr.close();
    QStringList lst_tr = bools.split('\n');
    if ((lst_tr.at(0)).toInt() == 0) {
        Dialog8 mdialog_tr;
        mdialog_tr.setModal(true);
        //this->close();
        mdialog_tr.exec();
        return;
    }

    QString fileName = "curr_game.txt";  //!< A file is created which has track no. and player name

               if (!fileName.isEmpty()) {
                   QFile file(fileName);
                   if (!file.open(QIODevice::WriteOnly)) {
                       // error message
                   } else {

                       QTextStream stream(&file);
                       stream << "0";
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

void Dialog2::on_pushButton_2_clicked()
{

    QString fileName_tr = "tracks.txt";
    QFile file_tr(fileName_tr);
    file_tr.open(QIODevice::ReadOnly);
    QTextStream stream_tr(&file_tr);
    QString bools = stream_tr.readAll();
    file_tr.close();
    QStringList lst_tr = bools.split('\n');
    if ((lst_tr.at(1)).toInt() == 0) {
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
                       stream << "1";
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

void Dialog2::on_pushButton_3_clicked()
{
    QString fileName_tr = "tracks.txt";
    QFile file_tr(fileName_tr);
    file_tr.open(QIODevice::ReadOnly);
    QTextStream stream_tr(&file_tr);
    QString bools = stream_tr.readAll();
    file_tr.close();
    QStringList lst_tr = bools.split('\n');
    if ((lst_tr.at(2)).toInt() == 0) {
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
                       stream << "2";
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

void Dialog2::on_pushButton_4_clicked()
{
    QString fileName_tr = "tracks.txt";
    QFile file_tr(fileName_tr);
    file_tr.open(QIODevice::ReadOnly);
    QTextStream stream_tr(&file_tr);
    QString bools = stream_tr.readAll();
    file_tr.close();
    QStringList lst_tr = bools.split('\n');
    if ((lst_tr.at(3)).toInt() == 0) {
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
                       stream << "3";
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

void Dialog2::on_pushButton_5_clicked()
{
    QString fileName_tr = "tracks.txt";
    QFile file_tr(fileName_tr);
    file_tr.open(QIODevice::ReadOnly);
    QTextStream stream_tr(&file_tr);
    QString bools = stream_tr.readAll();
    file_tr.close();
    QStringList lst_tr = bools.split('\n');
    if ((lst_tr.at(4)).toInt() == 0) {
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
                       stream << "4";
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

void Dialog2::on_pushButton_6_clicked()
{
    Dialog1 mdialog;
    mdialog.setModal(true);
    this->close();
    mdialog.exec();
}
