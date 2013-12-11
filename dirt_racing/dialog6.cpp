/*!
  This window shows up when high scores are viewed for any track
 */

#include "dialog6.h"
#include "ui_dialog6.h"
#include <QFile>
#include <QTextStream>

Dialog6::Dialog6(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog6)
{
    ui->setupUi(this);
    QString text;

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

               QString fileName_tr = "track"+track_no+".txt";   //!< Read high scores for the current track
               QFile file1(fileName_tr);
               if (!file1.open(QIODevice::ReadOnly)) {
                   // error message
               } else {

                   QTextStream stream(&file1);
                   QString contents = stream.readAll();
                   QStringList lst = contents.split('\n',QString::SkipEmptyParts);
                   int i=0;
                   while (i < lst.length()) {
                       QString token = lst[i];
                       i++;
                       QStringList lst1 = token.split(' ');
                       text += lst1[0] + "\t \t" + lst1[1] + "\t \t" + lst1[2] + "\n";

                       }
               }

               file1.close();


    ui->textBrowser->setText(text);
}

Dialog6::~Dialog6()
{
    delete ui;
}
