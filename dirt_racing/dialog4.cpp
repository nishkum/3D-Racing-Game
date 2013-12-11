/*!
  This window has options for entering name, starting the game, and viewing high scores

 */


using namespace::std;
//bool tre = false;
#include "dialog4.h"
#include "dialog2.h"
#include "dialog3.h"
#include "ui_dialog4.h"
#include "dialog5.h"
#include "dialog6.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <string.h>
#include <sstream>


#ifdef _WIN32
#include "windows.h"
bool env = true;
#else
bool env = false;
#endif


Dialog4::Dialog4(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog4)
{
    ui->setupUi(this);
}

Dialog4::~Dialog4()
{
    delete ui;
}

/*!
  Code executed when name is entered
 */

void Dialog4::on_pushButton_clicked()
{
    QString fileName = "curr_game.txt";     //!< Name is written to this file

               if (!fileName.isEmpty()) {
                   QFile file(fileName);
                   if (!file.open(QIODevice::Append)) {
                       // error message
                   } else {

                       QTextStream stream(&file);
                       stream << '\n';
                       stream << ui->lineEdit->text();  //! Reading contents of text box
                       stream.flush();
                       file.close();
                   }
               }
               QString track_no;
               QFile file(fileName);
               if (!file.open(QIODevice::ReadOnly)) {
                   // error message
               } else {

                   QTextStream stream(&file);
                   track_no = stream.readLine();
                   //std::cout << track_no.toStdString() << std::endl;
                   file.close();
               }


     this->close();

     stringstream st ;
     st<<track_no.toInt()<<ends;
     if(env) {
         string tempw = "cd ..\\project1 && product_game " + st.str();
         system( tempw.c_str() );   //!< Game started
     }
     else{
         string tempu = "cd ../project1 && ./product_game " + st.str();
         system(tempu.c_str());     //!< Game started
     }

     QString score, time, name;
     if (!file.open(QIODevice::ReadOnly)) {
         // error message
     } else {

         QTextStream stream(&file);     //!< Reading score and score from file
         score = stream.readAll();
         QStringList lst = score.split('\n');
         if (lst.length() < 4) {
             file.close();
             return;
         }
         name = lst.at(1);
         score = lst.at(2);
         time = lst.at(3);
         file.close();
         //std::cout << score.toStdString() << std::endl;

         QString fileName_tr = "track"+track_no+".txt";
         QFile file(fileName_tr);
         if (!file.open(QIODevice::ReadWrite)) {
             // error message
         } else {

             QTextStream stream(&file);
             QString contents = stream.readAll();
             QStringList lsta = contents.split('\n',QString::SkipEmptyParts);
             file.close();

             if (lsta.length() < 5) {       //!< If high scores less than 5, then add to high scores
                 lsta.append(name + " " + score + " " + time);
                 Dialog5 mdialog;
                 mdialog.setModal(true);
                 mdialog.exec();
             }
             else {                        //!< If current score higher than any high score, replace that high score with current score
                 int i=0;
                 while (i < lsta.length()) {
                     QString token = lsta[i];
                     i++;
                     QStringList lstb = token.split(' ');
                     if((lstb.at(1)).toInt() < score.toInt()) {
                         lstb[i-1] = name + " " + score + " " + time;
                         Dialog5 mdialog;
                         mdialog.setModal(true);
                         mdialog.exec();
                         break;
                     }
                 }
             }
             //QTextStream stream(&file);
             file.open(QIODevice::WriteOnly);
             stream << lsta[0];
             int i=1;
             while (i < lsta.length()){
                 QString token = lsta[i];
                 i++;
                 stream << '\n';
                 stream << token;

             }

             stream.flush();
             file.close();
         }
     }

     QString fileName_tr = "tracks.txt";
     QFile file_tr(fileName_tr);
     file_tr.open(QIODevice::ReadOnly);
     QTextStream stream_tr(&file_tr);
     QString bools = stream_tr.readAll();
     file_tr.close();
     QStringList lst_tr = bools.split('\n');
     if(track_no.toInt() < 9) {
         lst_tr[track_no.toInt()+1] = "1";
     }
     file_tr.open(QIODevice::WriteOnly);
     QTextStream stream_tr1(&file_tr);
     stream_tr1 << lst_tr[0];
     int i=1;
     while (i < lst_tr.length()){
         QString token = lst_tr[i];
         i++;
         stream_tr1 << '\n';
         stream_tr1 << token;

     }

     stream_tr1.flush();
     file_tr.close();
 }


/*!
  Code executed when High scores is clicked
 */

void Dialog4::on_pushButton_2_clicked()
{
    Dialog6 mdialog;
    mdialog.setModal(true);
    mdialog.exec();
}

/*!
  Code executed when Back is clicked
 */

void Dialog4::on_pushButton_3_clicked()
{
    QString fileName = "curr_game.txt";
    QString track_no;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        // error message
    } else {

        QTextStream stream(&file);
        track_no = stream.readLine();
        file.close();
    }

    if(track_no.toInt() < 5) {
        Dialog2 mdialog;
        mdialog.setModal(true);
        this->close();
        mdialog.exec();
    }
    else {
        Dialog3 mdialog;
        mdialog.setModal(true);
        this->close();
        mdialog.exec();
    }

}
