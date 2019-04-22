#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtCore>
#include<QtGui>
#include<QMessageBox>
#include<QComboBox>
#include<QString>
#include<QColor>
#include<stdio.h>
#include<iostream>
#include<QFile>
#include<QTextStream>
#include<string>
#include<sstream>
#include<stdlib.h>
#include<QPainter>
#include<QPixmap>
#include<QStringList>
#include<QTextEdit>
#include<QList>
#include<QPalette>
#include<QPrinter>
#include<QPrintDialog>

#define PI 3.14159265


 QString fileNames="Inputs/output_sarabjeet_(copy).txt";
 QString fileNames_exe="/home/sarab/Downloads/booksim2-classes/src/booksim";
 QString fileNames_config="/home/sarab/Desktop/final/code/Results/log";
using namespace std;
QString b[7];
int c;
int d;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->comboBox->addItem("mesh");
    ui->comboBox->addItem("torus");
    ui->comboBox->addItem("ring");
    ui->comboBox->addItem("bus");
    ui->comboBox->addItem("anynet");
    ui->comboBox->addItem("cmesh");
    ui->comboBox->addItem("dragonfly");
    ui->comboBox->addItem("fattree");
    ui->comboBox->addItem("flatfly_onchip");
    ui->comboBox->addItem("fly");
    ui->comboBox->addItem("kncube");
    ui->comboBox->addItem("qtree");
    ui->comboBox->addItem("tree4");
    ui->comboBox->setEditable(1);
    ui->comboBox_3->setEditable(1);
    ui->comboBox_4->setEditable(1);
    ui->comboBox_5->setEditable(1);
    ui->lineEdit_24->setDisabled(1);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_radioButton_clicked()
{
    ui->lineEdit_21->setDisabled(1);
    ui->comboBox_6->setEnabled(1);
}

void MainWindow::on_radioButton_2_clicked()
{
    ui->comboBox_6->setDisabled(1);
    ui->lineEdit_21->setEnabled(1);
}

void MainWindow::on_checkBox_4_clicked()
{
    if(!ui->checkBox_4->isChecked())
        ui->lineEdit_24->setDisabled(1);
    else
        ui->lineEdit_24->setEnabled(1);

}

void MainWindow::on_run_clicked()
{
    QProcess process;
    process.start("mkdir", QStringList() << "Results");
    process.waitForFinished();

    on_build_clicked();
    create_exe_command();

    process.start("gnome-terminal -e \"chmod u+x Results/exec_command\"");
    process.waitForFinished();
    process.start("gnome-terminal -e \"bash -c \\\"Results/exec_command \\\"\"");
    process.waitForFinished();

    process.start("mv", QStringList() << "output_booksim"<<"Results");
    process.waitForFinished();
}

void MainWindow::create_exe_command()
{
    QFile fileout_command("Results/exec_command");
    if (!fileout_command.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out_command(&fileout_command);
    out_command<<fileNames_exe<<" "<<fileNames_config<<"&>output_booksim";
}

void MainWindow::on_browse_clicked()
{
    fileNames = QFileDialog::getOpenFileName(this, tr("Open File"));
    ui->lineEdit_browse->setText(fileNames);
}
void MainWindow::on_browse_exe_clicked()
{
    fileNames_exe = QFileDialog::getOpenFileName(this, tr("Open File"));
    ui->lineEdit_browse_2->setText(fileNames_exe);
}
void MainWindow::on_browse_config_clicked()
{
    fileNames_config = QFileDialog::getOpenFileName(this, tr("Open File"));
    ui->lineEdit_browse_3->setText(fileNames_config);
}

void MainWindow::on_build_clicked()
{
   QProcess process;
   process.start("mkdir", QStringList() << "Results");
   process.waitForFinished();

    QMessageBox msgBox;
     msgBox.setText("Error Opening File");
     QFile file(fileNames);
     if(!file.open(QIODevice::ReadOnly |  QIODevice::Text)) {
        msgBox.exec();
        return;
     }
     QFile fileout("Results/log");
     if (!fileout.open(QIODevice::WriteOnly | QIODevice::Text))
     {
         msgBox.exec();
         return;
     }

     QTextStream out(&fileout);
     QTextStream in(&file);
    int cycletime=0;
    int count=0;
    int i=0;
    int flitnum=-1;
    int temp;
    int j;

    QChar packet_size='0';
    while(!in.atEnd()) {
              if(in.readLine().startsWith("Time:"))
              count++;

    }
       in.seek(0);//Moving back to begining of document

      QStringList *list;               //Dynamic Qlist

      list = new QStringList[count];

      while(!in.atEnd())
      {
         QString line = in.readLine();

         if(line.startsWith("Time:"))  //Reads lines with Generation of a Flit
        {
           list[i]=line.split(',');
           if(QString::compare(list[i][1],QString::number(cycletime)))    //Calculates total cycle time
                 cycletime++;

           temp=0;
           for(j=1;list[i][3][j]!=']';j++)
           {
               temp=temp*10 + (list[i][3][j].toLatin1() - 48);
           }

           if(flitnum<temp)
               flitnum=temp;
           i++;
         }
         else if(line.startsWith("packet_size"))
         {
             packet_size = line[14];
         }

       }

    qDebug()<<"\nTotal time is "<<cycletime<<" cycles"<<"\nNo of lines: "<<count<<"\nNo of flits: "<<flitnum;
        qDebug()<<"List items format: "<<list[0][0]<<list[0][1]<<list[0][2]<<list[0][3]<<list[0][4]<<list[0][5];
        qDebug()<<"Packet Size = "<<packet_size;

//-----------------------------------------------------------------------------------------------------

qDebug()<<"Number of VC's = "<<ui->lineEdit_5->text();
qDebug()<<"VC Buffer Size = "<<ui->lineEdit_8->text();

//Log File
out<<"\n//Topology";
out<<"\ntopology = "<<ui->comboBox->currentText()<<";";
out<<"\nk = "<<ui->lineEdit->text()<<";";
out<<"\nn= "<<ui->lineEdit_2->text()<<";";
//out<<"\nno_of_endpts = "<<ui->lineEdit_3->text()<<";";
out<<"\n\n//Routing";
out<<"\nrouting_function = "<<ui->lineEdit_4->text()<<";";
out<<"\n\n//Flow Control";
out<<"\nnum_vcs = "<<ui->lineEdit_5->text()<<";";
out<<"\nvc_buf_size = "<<ui->lineEdit_8->text()<<";";
if(ui->checkBox_2->isChecked())
   out<<"\nwait_for_tail_credit = 1;";
else
   out<<"\nwait_for_tail_credit = 0;";
out<<"\n\n//Router Architecture";

out<<"\nvc_allocator = "<<ui->comboBox_4->currentText()<<";";
out<<"\nsw_allocator = "<<ui->comboBox_5->currentText()<<";";   //alloc_iters missing
out<<"\n\ncredit_delay = "<<ui->lineEdit_12->text()<<";";
out<<"\nrouting_delay = "<<ui->lineEdit_13->text()<<";";
out<<"\nvc_alloc_delay = "<<ui->lineEdit_14->text()<<";";
out<<"\nsw_alloc_delay = "<<ui->lineEdit_15->text()<<";";
out<<"\n\ninput_speedup = "<<ui->lineEdit_16->text()<<";";
out<<"\noutput_speedup = "<<ui->lineEdit_17->text()<<";";
out<<"\ninternal_speedup = "<<ui->lineEdit_18->text()<<";";
if(ui->checkBox_3->isChecked())
   out<<"\n\nvc_busy_when_full = 1;";   //Not in the manual
else
   out<<"\n\nvc_busy_when_full = 0;";
//out<<"\n\n//Traffic";
//out<<"\ntraffic = "<<ui->lineEdit_19->text()<<";";
out<<"\npacket_size = "<<ui->lineEdit_20->text()<<";";
out<<"\n\n//Simulation";
out<<"\nsim_type = "<<ui->comboBox_2->currentText()<<";";

if(ui->radioButton->isChecked())
{
    out<<"\n\n//Simulation Data";                   //Not in the manual
    out<<"\ntraffic = "<<ui->comboBox_6->currentText()<<";"<<"\t//Synthetic";
}
else if(ui->radioButton_2->isChecked())
{
    out<<"\n\n//Simulation Data";                   //Not in the manual
    out<<"\ntraffic = \""<<ui->lineEdit_21->text()<<"\""<<";<<\t//Real";
}
if(ui->checkBox_4->isChecked())
   out<<"\n\n//Power Calculation"<<"\n//Path to the Tech file:\""<<ui->lineEdit_24->text()<<"\"";  //Not in the manual
out<<"\n\nmax_samples = "<<ui->lineEdit_22->text()<<";";
out<<"\n\ninjection_rate = "<<ui->lineEdit_23->text()<<";";
out<<"\n\n//Explicit Data";
out<<"\n//total_time = "<<cycletime<<";";
out<<"\n//total_no_of_flits = "<<flitnum<<";\n";

}

void MainWindow::on_print_clicked()
{

    QProcess process;
    process.start("mkdir", QStringList() << "Results");
    process.waitForFinished();

                 QMessageBox msgBox;
                  msgBox.setText("Error Opening File");

                  QFile file(fileNames);
                  if(!file.open(QIODevice::ReadOnly |  QIODevice::Text)) {
                     msgBox.exec();
                     return;
                  }
                  QFile fileout("Results/log");
                  if (!fileout.open(QIODevice::WriteOnly | QIODevice::Text))
                  {
                      msgBox.exec();
                      return;
                  }

                  QTextStream out(&fileout);
                  QTextStream in(&file);
                 int cycletime=0;
                 int count=0;
                 int i=0;
                 int flitnum=-1;
                 int temp;
                 int j,k,index;
                 int x,y,m,n,c,d,m1,n1,start,end;

                 QChar packet_size='0';
                 while(!in.atEnd()) {
                           if(in.readLine().startsWith("Time:"))
                           count++;

                 }
                    in.seek(0);//Moving back to begining of document

                   QStringList *list;               //Dynamic Qlist

                   list = new QStringList[count];

                   while(!in.atEnd())
                   {
                      QString line = in.readLine();

                      if(line.startsWith("Time:"))  //Reads lines with Generation of a Flit
                     {
                        list[i]=line.split(',');
                        if(QString::compare(list[i][1],QString::number(cycletime)))    //Calculates total cycle time
                              cycletime++;

                        temp=0;
                        for(j=1;list[i][3][j]!=']';j++)
                        {
                            temp=temp*10 + (list[i][3][j].toLatin1() - 48);
                        }

                        if(flitnum<temp)
                            flitnum=temp;
                        i++;
                      }
                      else if(line.startsWith("packet_size"))
                      {
                          packet_size = line[14];
                      }

                    }

                 qDebug()<<"\nTotal time is "<<cycletime<<" cycles"<<"\nNo of lines: "<<count<<"\nNo of flits: "<<flitnum;
                     qDebug()<<"List items format: "<<list[0][0]<<list[0][1]<<list[0][2]<<list[0][3]<<list[0][4]<<list[0][5];
                     qDebug()<<"Packet Size = "<<packet_size;

 //-----------------------------------------------------------------------------------------------------
                     scene = new QGraphicsScene(this);
                                 ui->graphicsView->setScene(scene);
                                 QPen black(Qt::black);
                                black.setWidth(0);
                                QPen redd(Qt::red);
                                redd.setWidth(6);
                                QGraphicsTextItem *text ;


            QString b[7];
            int flit_id,flag=-1;
            //Inputs
            b[0]=ui->lineEdit->text();
            b[1]=ui->lineEdit_2->text();
            ui->lineEdit_3->setText("not valid in this topology");
            b[2]=ui->lineEdit_5->text();
            b[3]=ui->lineEdit_8->text();
            qDebug()<<"Number of VC's = "<<b[2];
            qDebug()<<"VC Buffer Size = "<<b[3];
            b[4]=ui->lineEdit_9->text();
            b[5]=ui->lineEdit_10->text();
            b[6]=ui->lineEdit_11->text();

            if(QString::compare(b[6],"\0")==0)
                flit_id=-1;
            else
                flit_id=b[6].toInt();
            if(QString::compare(b[4],"\0")==0)
                start=0;
            else
                start=b[4].toInt();
            if(QString::compare(b[5],"\0")==0)
                end=cycletime;
            else
                end=b[5].toInt();
            if(start>end)
            {
                 msgBox.setText("Invalid Input of Cycle Time");
                 msgBox.exec();
                 return;

            }
            c=b[0].toInt();
            d=b[1].toInt();

            //Log File
            out<<"\n//Topology";
            out<<"\ntopology = "<<ui->comboBox->currentText()<<";";
            out<<"\nk = "<<ui->lineEdit->text()<<";";
            out<<"\nn= "<<ui->lineEdit_2->text()<<";";
            //out<<"\nno_of_endpts = "<<ui->lineEdit_3->text()<<";";
            out<<"\n\n//Routing";
            out<<"\nrouting_function = "<<ui->lineEdit_4->text()<<";";
            out<<"\n\n//Flow Control";
            out<<"\nnum_vcs = "<<ui->lineEdit_5->text()<<";";
            out<<"\nvc_buf_size = "<<ui->lineEdit_8->text()<<";";
            if(ui->checkBox_2->isChecked())
               out<<"\nwait_for_tail_credit = 1;";
            else
               out<<"\nwait_for_tail_credit = 0;";
            out<<"\n\n//Router Architecture";

            out<<"\nvc_allocator = "<<ui->comboBox_4->currentText()<<";";
            out<<"\nsw_allocator = "<<ui->comboBox_5->currentText()<<";";   //alloc_iters missing
            out<<"\n\ncredit_delay = "<<ui->lineEdit_12->text()<<";";
            out<<"\nrouting_delay = "<<ui->lineEdit_13->text()<<";";
            out<<"\nvc_alloc_delay = "<<ui->lineEdit_14->text()<<";";
            out<<"\nsw_alloc_delay = "<<ui->lineEdit_15->text()<<";";
            out<<"\n\ninput_speedup = "<<ui->lineEdit_16->text()<<";";
            out<<"\noutput_speedup = "<<ui->lineEdit_17->text()<<";";
            out<<"\ninternal_speedup = "<<ui->lineEdit_18->text()<<";";
            if(ui->checkBox_3->isChecked())
               out<<"\n\nvc_busy_when_full = 1;";   //Not in the manual
            else
               out<<"\n\nvc_busy_when_full = 0;";
            //out<<"\n\n//Traffic";
            //out<<"\ntraffic = "<<ui->lineEdit_19->text()<<";";
            out<<"\npacket_size = "<<ui->lineEdit_20->text()<<";";
            out<<"\n\n//Simulation";
            out<<"\nsim_type = "<<ui->comboBox_2->currentText()<<";";

            if(ui->radioButton->isChecked())
            {
                out<<"\n\n//Simulation Data";                   //Not in the manual
                out<<"\ntraffic = "<<ui->comboBox_6->currentText()<<";"<<"\t//Synthetic";
            }
            else if(ui->radioButton_2->isChecked())
            {
                out<<"\n\n//Simulation Data";                   //Not in the manual
                out<<"\ntraffic = \""<<ui->lineEdit_21->text()<<"\""<<";<<\t//Real";
            }
            if(ui->checkBox_4->isChecked())
               out<<"\n\n//Power Calculation"<<"\n//Path to the Tech file:\""<<ui->lineEdit_24->text()<<"\"";  //Not in the manual
            out<<"\n\nmax_samples = "<<ui->lineEdit_22->text()<<";";
            out<<"\n\ninjection_rate = "<<ui->lineEdit_23->text()<<";";
            out<<"\n\n//Explicit Data";
            out<<"\n//total_time = "<<cycletime<<";";
            out<<"\n//total_no_of_flits = "<<flitnum<<";\n";

            if(ui->comboBox->currentText()!="mesh")
            {
                msgBox.setText("Invalid Topology");
                msgBox.exec();
                return;
            }

            QPrinter printer(QPrinter::HighResolution);
            printer.setPageSize(QPrinter::A4);
            printer.setOrientation(QPrinter::Portrait);
            QPrintDialog dlg(&printer);
         if(dlg.exec()==QDialog::Accepted)
         {
            QPainter p(&printer);

            if("mesh"==ui->comboBox->currentText())
            {
                   QString genflit[c*d];
                   QString receiveflit[c*d];
                   QString inputq0[c*d];
                   QString inputq1[c*d];
                   QString inputq2[c*d];
                   QString inputq3[c*d];
                   QString vcupdate[c*d];
                   QString swupdate[c*d];
                   QString sendingflit[c*d];
                   QString returnflit[c*d];

                 //  QColor windowColor( 248, 249, 249 );           //For coloured routers
                  // QBrush brush( Qt::yellow, Qt::SolidPattern );


                     for(i=0,j=0;j<=cycletime;)
                     {

             //Ploting and Updating Values
                         x=0;
                         y=0;
                         m=0;
                         n=0;
                         temp=0;
                         for(k=1;list[i][3][k]!=']';k++)
                         {
                             temp=temp*10 + (list[i][3][k].toLatin1() - 48);
                         }
                         //Checking presence of flit
                        if(flit_id==temp)
                            flag=0;

                     while(m <c)
                         {
                             while(n < d)
                             {
                                 line=scene->addLine(x, y,x+700,y,black);
                                 line=scene->addLine(x, y+700,x+700,y+700,black);

                                 line=scene->addLine(x+700, y+350,x+900,y+350,black);
                                 if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"RetFlit")==0))
                                 {
                                     returnflit[m*c+n].append(list[i][3]);
                                     returnflit[m*c+n].append(",");
                                     if(sendingflit[m*c+n].contains(list[i][3]))
                                         sendingflit[m*c+n].remove((list[i][3])+",");
                                 }
                                 if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"SendingFlit")==0))
                                 {
                                     sendingflit[m*c+n].append(list[i][3]);
                                     sendingflit[m*c+n].append(",");
                                     if(swupdate[m*c+n].contains(list[i][3]))
                                         swupdate[m*c+n].remove((list[i][3])+",");
                                 }
                                 if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"SWUpdate")==0))
                                 {
                                     swupdate[m*c+n].append(list[i][3]);
                                     swupdate[m*c+n].append(",");
                                     if(vcupdate[m*c+n].contains(list[i][3]))
                                         vcupdate[m*c+n].remove((list[i][3])+",");

                                     if(inputq0[m*c+n].contains(list[i][3]))
                                         inputq0[m*c+n].remove((list[i][3])+",");
                                     if(inputq1[m*c+n].contains(list[i][3]))
                                         inputq1[m*c+n].remove((list[i][3])+",");
                                     if(inputq2[m*c+n].contains(list[i][3]))
                                         inputq2[m*c+n].remove((list[i][3])+",");
                                     if(inputq3[m*c+n].contains(list[i][3]))
                                         inputq3[m*c+n].remove((list[i][3])+",");
                                 }
                                 if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"VCUpdate")==0))
                                 {
                                     vcupdate[m*c+n].append(list[i][3]);
                                     vcupdate[m*c+n].append(",");

                                     if(inputq0[m*c+n].contains(list[i][3]))
                                         inputq0[m*c+n].remove((list[i][3])+",");
                                     if(inputq1[m*c+n].contains(list[i][3]))
                                         inputq1[m*c+n].remove((list[i][3])+",");
                                     if(inputq2[m*c+n].contains(list[i][3]))
                                         inputq2[m*c+n].remove((list[i][3])+",");
                                     if(inputq3[m*c+n].contains(list[i][3]))
                                         inputq3[m*c+n].remove((list[i][3])+",");
                                 }
                                 if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"InputQueueing")==0))
                                 {
                                     if(QString::compare(list[i][5],"0")==0)
                                     {
                                         inputq0[m*c+n].append(list[i][3]);
                                         inputq0[m*c+n].append(",");
                                      }
                                     if(QString::compare(list[i][5],"1")==0)
                                     {
                                         inputq1[m*c+n].append(list[i][3]);
                                         inputq1[m*c+n].append(",");
                                     }
                                     if(QString::compare(list[i][5],"2")==0)
                                     {
                                         inputq2[m*c+n].append(list[i][3]);
                                         inputq2[m*c+n].append(",");
                                     }
                                     if(QString::compare(list[i][5],"3")==0)
                                     {
                                         inputq3[m*c+n].append(list[i][3]);
                                         inputq3[m*c+n].append(",");
                                     }
                                     if(receiveflit[m*c+n].contains(list[i][3]))
                                         receiveflit[m*c+n].remove((list[i][3])+",");
                                 }
                                 if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"ReceiveFlit")==0))
                                 {
                                     receiveflit[m*c+n].append(list[i][3]);
                                     receiveflit[m*c+n].append(",");
                                     if(genflit[m*c+n].contains(list[i][3]))
                                         genflit[m*c+n].remove((list[i][3])+",");
                                     for(m1=0;m1<c;m1++)
                                     {
                                         for(n1=0;n1<d;n1++)
                                         {
                                             if(sendingflit[m1*c+n1].contains(list[i][3]))
                                             {
                                                 text = scene->addText(list[i][3]);
                                                 if(m==m1)
                                                 {
                                                     if(n>n1)
                                                     {
                                                         text->setPos(450*(n+n1)+350 - 70,450*(m+m1)+350-30);
                                                         text->setFont(QFont("serif",13));
                                                         text->setDefaultTextColor(Qt::darkMagenta);
                                                         text = scene->addText("---->");
                                                         text->setPos(450*(n+n1)+350 + 50,450*(m+m1)+350-30);
                                                     }
                                                     else
                                                     {
                                                         text->setPos(450*(n+n1)+350 - 40,450*(m+m1)+350);
                                                         text->setFont(QFont("serif",13));
                                                         text->setDefaultTextColor(Qt::darkMagenta);
                                                         text = scene->addText("<----");
                                                         text->setPos(450*(n+n1)+350 - 80,450*(m+m1)+350);
                                                     }
                                                 }
                                                 else
                                                 {
                                                     if(m>m1)
                                                     {
                                                         text->setPos(450*(n+n1)+350,450*(m+m1)+350);
                                                         text->setFont(QFont("serif",13));
                                                         text->setDefaultTextColor(Qt::darkMagenta);
                                                         text = scene->addText("|");
                                                         text->setPos(450*(n+n1)+350+20,450*(m+m1)+350 + 20);
                                                         text = scene->addText("|");
                                                         text->setPos(450*(n+n1)+350+20,450*(m+m1)+350 + 30);
                                                         text = scene->addText("\\/");
                                                         text->setPos(450*(n+n1)+350+16,450*(m+m1)+350 + 35);
                                                     }
                                                     else
                                                     {
                                                         text->setPos(450*(n+n1)+350-160,450*(m+m1)+350);
                                                         text->setFont(QFont("serif",13));
                                                         text->setDefaultTextColor(Qt::darkMagenta);
                                                         text = scene->addText("/\\");
                                                         text->setPos(450*(n+n1)+350-28-50-60,450*(m+m1)+350 -30);
                                                         text = scene->addText("|");
                                                         text->setPos(450*(n+n1)+350-25 -50-60,450*(m+m1)+350 -25);
                                                         text = scene->addText("|");
                                                         text->setPos(450*(n+n1)+350-25-50-60,450*(m+m1)+350 -20);
                                                     }
                                                 }
                                                 sendingflit[m1*c+n1].remove((list[i][3])+",");
                                                 //text->setPos(450*(n+n1)+350,450*(m+m1)+350); ->Change coordinates in terms of wire factor
                                                 //wire[count_wire++]<<list[i][3]<<m<<n<<m1<<n1;
                                             }
                                         }
                                     }
                                 }
                                 if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"GenFlit")==0))
                                 {
                                     genflit[m*c+n].append(list[i][3]);
                                     genflit[m*c+n].append(",");

                                 }




                                 x=x+900;
                                 n++;
                                 if (n==d-1)
                                 {
                                      line=scene->addLine(x, y,x+700,y,black);
                                        line=scene->addLine(x, y+700,x+700,y+700,black);
                                        if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"RetFlit")==0))
                                        {
                                            returnflit[m*c+n].append(list[i][3]);
                                            returnflit[m*c+n].append(",");
                                            if(sendingflit[m*c+n].contains(list[i][3]))
                                                sendingflit[m*c+n].remove((list[i][3])+",");
                                        }
                                        if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"SendingFlit")==0))
                                        {
                                            sendingflit[m*c+n].append(list[i][3]);
                                            sendingflit[m*c+n].append(",");
                                            if(swupdate[m*c+n].contains(list[i][3]))
                                                swupdate[m*c+n].remove((list[i][3])+",");
                                        }
                                        if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"SWUpdate")==0))
                                        {
                                            swupdate[m*c+n].append(list[i][3]);
                                            swupdate[m*c+n].append(",");
                                            if(vcupdate[m*c+n].contains(list[i][3]))
                                                vcupdate[m*c+n].remove((list[i][3])+",");

                                            if(inputq0[m*c+n].contains(list[i][3]))
                                                inputq0[m*c+n].remove((list[i][3])+",");
                                            if(inputq1[m*c+n].contains(list[i][3]))
                                                inputq1[m*c+n].remove((list[i][3])+",");
                                            if(inputq2[m*c+n].contains(list[i][3]))
                                                inputq2[m*c+n].remove((list[i][3])+",");
                                            if(inputq3[m*c+n].contains(list[i][3]))
                                                inputq3[m*c+n].remove((list[i][3])+",");
                                        }
                                        if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"VCUpdate")==0))
                                        {
                                            vcupdate[m*c+n].append(list[i][3]);
                                            vcupdate[m*c+n].append(",");

                                            if(inputq0[m*c+n].contains(list[i][3]))
                                                inputq0[m*c+n].remove((list[i][3])+",");
                                            if(inputq1[m*c+n].contains(list[i][3]))
                                                inputq1[m*c+n].remove((list[i][3])+",");
                                            if(inputq2[m*c+n].contains(list[i][3]))
                                                inputq2[m*c+n].remove((list[i][3])+",");
                                            if(inputq3[m*c+n].contains(list[i][3]))
                                                inputq3[m*c+n].remove((list[i][3])+",");
                                        }
                                        if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"InputQueueing")==0))
                                        {

                                            if(QString::compare(list[i][5],"0")==0)
                                            {
                                                inputq0[m*c+n].append(list[i][3]);
                                                inputq0[m*c+n].append(",");
                                            }
                                            if(QString::compare(list[i][5],"1")==0)
                                            {
                                                inputq1[m*c+n].append(list[i][3]);
                                                inputq1[m*c+n].append(",");
                                            }
                                            if(QString::compare(list[i][5],"2")==0)
                                            {
                                                inputq2[m*c+n].append(list[i][3]);
                                                inputq2[m*c+n].append(",");
                                            }
                                            if(QString::compare(list[i][5],"3")==0)
                                            {
                                                inputq3[m*c+n].append(list[i][3]);
                                                inputq3[m*c+n].append(",");
                                            }
                                            if(receiveflit[m*c+n].contains(list[i][3]))
                                                receiveflit[m*c+n].remove((list[i][3])+",");
                                        }
                                        if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"ReceiveFlit")==0))
                                        {
                                            receiveflit[m*c+n].append(list[i][3]);
                                            receiveflit[m*c+n].append(",");
                                            if(genflit[m*c+n].contains(list[i][3]))
                                                genflit[m*c+n].remove(list[i][3]+",");
                                            for(m1=0;m1<c;m1++)
                                            {
                                                for(n1=0;n1<d;n1++)
                                                {
                                                    if(sendingflit[m1*c+n1].contains(list[i][3]))
                                                    {
                                                        text = scene->addText(list[i][3]);
                                                        if(m==m1)
                                                        {
                                                            if(n>n1)
                                                            {
                                                                text->setPos(450*(n+n1)+350 - 70,450*(m+m1)+350-30);
                                                                text->setFont(QFont("serif",13));
                                                                text->setDefaultTextColor(Qt::darkMagenta);
                                                                text = scene->addText("---->");
                                                                text->setPos(450*(n+n1)+350 + 50,450*(m+m1)+350-30);
                                                            }
                                                            else
                                                            {
                                                                text->setPos(450*(n+n1)+350 -40,450*(m+m1)+350);
                                                                text->setFont(QFont("serif",13));
                                                                text->setDefaultTextColor(Qt::darkMagenta);
                                                                text = scene->addText("<----");
                                                                text->setPos(450*(n+n1)+350 - 80,450*(m+m1)+350);
                                                            }
                                                        }
                                                        else
                                                        {
                                                            if(m>m1)
                                                            {
                                                                text->setPos(450*(n+n1)+350,450*(m+m1)+350);
                                                                text->setFont(QFont("serif",13));
                                                                text->setDefaultTextColor(Qt::darkMagenta);
                                                                text = scene->addText("|");
                                                                text->setPos(450*(n+n1)+350+20,450*(m+m1)+350 + 20);
                                                                text = scene->addText("|");
                                                                text->setPos(450*(n+n1)+350+20,450*(m+m1)+350 + 30);
                                                                text = scene->addText("\\/");
                                                                text->setPos(450*(n+n1)+350+16,450*(m+m1)+350 + 35);
                                                            }
                                                            else
                                                            {
                                                                text->setPos(450*(n+n1)+350-160,450*(m+m1)+350);
                                                                text->setFont(QFont("serif",13));
                                                                text->setDefaultTextColor(Qt::darkMagenta);
                                                                text = scene->addText("/\\");
                                                                text->setPos(450*(n+n1)+350-28-50-60,450*(m+m1)+350 -30);
                                                                text = scene->addText("|");
                                                                text->setPos(450*(n+n1)+350-25 -50-60,450*(m+m1)+350 -25);
                                                                text = scene->addText("|");
                                                                text->setPos(450*(n+n1)+350-25-50-60,450*(m+m1)+350 -20);
                                                            }
                                                        }
                                                        sendingflit[m1*c+n1].remove((list[i][3])+",");
                                                        //text->setPos(450*(n+n1)+350,450*(m+m1)+350); ->Change coordinates in terms of wire factor
                                                        //wire[count_wire++]<<list[i][3]<<m<<n<<m1<<n1;
                                                    }
                                                }
                                            }

                                        }
                                        if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"GenFlit")==0))
                                        {

                                            genflit[m*c+n].append(list[i][3]);
                                            genflit[m*c+n].append(",");

                                        }



                                     break;
                                 }
                                 else
                                 {
                                     continue;
                                 }

                             }
                             y=y+900;
                             m++;
                             n=0;
                             x=0;
                         }

                         x=0;
                         y=0;
                         n=0;
                         m=0;
                         while(m<d)
                         {
                             while(n<c)
                             {

                                   line=scene->addLine(x, y,x,y+700,black);
                                    line=scene->addLine(x+700, y,x+700,y+700,black);

                                    line=scene->addLine(x+350, y+700,x+350,y+900,black);


                                 y=y+900;
                                 n++;
                                 if(n==(c-1))
                                 {
                                     line=scene->addLine(x, y,x,y+700,black);
                                     line=scene->addLine(x+700, y,x+700,y+700,black);
                                      break;

                                 }
                                 else
                                 {
                                     continue;
                                 }

                             }
                             x=x+900;
                             m++;
                             n=0;
                             y=0;
                         }

    /*              //Background--See Mystery Conversion
                         brush.setColor( windowColor );              // set this brush color

                         y=0;
                         for(m=0;m<c;m++)
                         {
                             x=0;
                             for(n=0;n<d;n++)
                             {
                                 p.setBrush( brush );
                                    p.drawRect(x,y,700*3.83,700*3.83);
                                    x+=900*3.83;
                             }
                             y+=900*3.83;
                         }
    */

                  //Constraint Update

                         if(i<count-1)      //Next Line
                            i++;
                         else               //Last Line
                         {
                             //Printing values
                                          x=0;
                                          y=0;
                                          m=0;
                                          n=0;

                                      while(m<c)
                                          {
                                              while(n < d)
                                              {
                                                  //ReturnFlit
                                                      text = scene->addText("ReturnFlit:");
                                                      text->setPos(x, y+630);
                                                      text->setFont(QFont("serif",14));
                                                      text->setDefaultTextColor(Qt::darkCyan);
                                                      if(flit_id!=-1)
                                                      {
                                                          if(returnflit[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                            {
                                                              index=returnflit[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                              k=index;
                                                              for(;returnflit[m*c+n][index]!=']';index++)
                                                              {
                                                                  if(k*10+20>680)
                                                                      line=scene->addLine(x+index*10-680+20, y+710,x+index*10+40-680+20,y+710,redd);
                                                                  else
                                                                      line=scene->addLine(x+index*10, y+690,x+index*10+40,y+690,redd);
                                                              }

                                                          }
                                                      }
                                                      text = scene->addText(returnflit[m*c+n]);
                                                      text->setPos(x, y+660);
                                                      text->setFont(QFont("serif",14));
                                                      text->setDefaultTextColor(Qt::red);
                                                  //SendingFlit
                                                      text = scene->addText("SendingFlit:");
                                                      text->setPos(x, y+540);
                                                      text->setFont(QFont("serif",14));
                                                      text->setDefaultTextColor(Qt::darkCyan);
                                                      if(flit_id!=-1)
                                                      {
                                                          if(sendingflit[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                            {
                                                              index=sendingflit[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                              k=index;
                                                              for(;sendingflit[m*c+n][index]!=']';index++)
                                                              {
                                                                  if(k*10+20>680)
                                                                      line=scene->addLine(x+index*10-680+20, y+620,x+index*10+40-680+20,y+620,redd);
                                                                  else
                                                                      line=scene->addLine(x+index*10, y+600,x+index*10+40,y+600,redd);
                                                              }

                                                          }
                                                      }
                                                      text = scene->addText(sendingflit[m*c+n]);
                                                      text->setPos(x, y+570);
                                                      text->setFont(QFont("serif",14));
                                                      text->setTextWidth(680);
                                                  //SWUpdate
                                                      text = scene->addText("SWUpdate:");
                                                      text->setPos(x, y+480);
                                                      text->setFont(QFont("serif",14));
                                                      text->setDefaultTextColor(Qt::darkCyan);
                                                      if(flit_id!=-1)
                                                      {
                                                          if(swupdate[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                            {
                                                              index=swupdate[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                              k=index;
                                                              for(;swupdate[m*c+n][index]!=']';index++)
                                                              {
                                                                  if(k*10+20>680)
                                                                      line=scene->addLine(x+index*10-680+20, y+560,x+index*10+40-680+20,y+560,redd);
                                                                  else
                                                                      line=scene->addLine(x+index*10, y+540,x+index*10+40,y+540,redd);
                                                              }

                                                          }
                                                      }
                                                      text = scene->addText(swupdate[m*c+n]);
                                                      text->setPos(x, y+510);
                                                      text->setFont(QFont("serif",14));
                                                  //VCUpdate
                                                      text = scene->addText("VCUpdate:");
                                                      text->setPos(x, y+420);
                                                      text->setFont(QFont("serif",14));
                                                      text->setDefaultTextColor(Qt::darkCyan);
                                                      text = scene->addText(vcupdate[m*c+n]);
                                                      text->setPos(x, y+450);
                                                      text->setFont(QFont("serif",14));
                                                      //InputQueueing
                                                          text = scene->addText("InputQueueing:");
                                                          text->setPos(x, y+150);
                                                          text->setFont(QFont("serif",14));
                                                          text->setDefaultTextColor(Qt::darkCyan);

                                                          text = scene->addText("VC  0: ");
                                                          text->setPos(x, y+180);
                                                          text->setFont(QFont("serif",14));
                                                          text->setDefaultTextColor(Qt::darkYellow);
                                                          text = scene->addText("VC  1: ");
                                                          text->setPos(x, y+240);
                                                          text->setFont(QFont("serif",14));
                                                          text->setDefaultTextColor(Qt::darkYellow);
                                                          text = scene->addText("VC  2: ");
                                                          text->setPos(x, y+300);
                                                          text->setFont(QFont("serif",14));
                                                          text->setDefaultTextColor(Qt::darkYellow);
                                                          text = scene->addText("VC  3: ");
                                                          text->setPos(x, y+360);
                                                          text->setFont(QFont("serif",14));
                                                          text->setDefaultTextColor(Qt::darkYellow);

                                                          //VC  0
                                                          if(flit_id!=-1)
                                                          {
                                                              if(inputq0[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                                {
                                                                  index=inputq0[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                  k=index;
                                                                  for(;inputq0[m*c+n][index]!=']';index++)
                                                                  {
                                                                      if(k*10+20>680)
                                                                          line=scene->addLine(x+index*10-680+20, y+230,x+index*10+40-680+20,y+230,redd);
                                                                      else
                                                                          line=scene->addLine(x+index*10, y+210,x+index*10+40,y+210,redd);
                                                                  }

                                                              }
                                                          }
                                                            text = scene->addText(inputq0[m*c+n]);
                                                            text->setPos(x+60, y+180);
                                                            text->setFont(QFont("serif",14));
                                                            text->setTextWidth(640);
                                                          //VC  1
                                                            if(flit_id!=-1)
                                                            {
                                                                if(inputq1[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                                  {
                                                                    index=inputq1[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                    k=index;
                                                                    for(;inputq1[m*c+n][index]!=']';index++)
                                                                    {
                                                                        if(k*10+20>680)
                                                                            line=scene->addLine(x+index*10-680+20, y+290,x+index*10+40-680+20,y+290,redd);
                                                                        else
                                                                            line=scene->addLine(x+index*10, y+270,x+index*10+40,y+270,redd);
                                                                    }

                                                                }
                                                            }
                                                            text = scene->addText(inputq1[m*c+n]);
                                                            text->setPos(x+60, y+240);
                                                            text->setFont(QFont("serif",14));
                                                            text->setTextWidth(640);
                                                          //VC  2
                                                            if(flit_id!=-1)
                                                            {
                                                                if(inputq2[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                                  {
                                                                    index=inputq2[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                    k=index;
                                                                    for(;inputq2[m*c+n][index]!=']';index++)
                                                                    {
                                                                        if(k*10+20>680)
                                                                            line=scene->addLine(x+index*10-680+20, y+350,x+index*10+40-680+20,y+350,redd);
                                                                        else
                                                                            line=scene->addLine(x+index*10, y+330,x+index*10+40,y+330,redd);
                                                                    }

                                                                }
                                                            }
                                                            text = scene->addText(inputq2[m*c+n]);
                                                            text->setPos(x+60, y+300);
                                                            text->setFont(QFont("serif",14));
                                                            text->setTextWidth(640);
                                                          //VC  3
                                                            if(flit_id!=-1)
                                                            {
                                                                if(inputq3[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                                  {
                                                                    index=inputq3[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                    k=index;
                                                                    for(;inputq3[m*c+n][index]!=']';index++)
                                                                    {
                                                                        if(k*10+20>680)
                                                                            line=scene->addLine(x+index*10-680+20, y+410,x+index*10+40-680+20,y+410,redd);
                                                                        else
                                                                            line=scene->addLine(x+index*10, y+390,x+index*10+40,y+390,redd);
                                                                    }

                                                                }
                                                            }
                                                            text = scene->addText(inputq3[m*c+n]);
                                                            text->setPos(x+60, y+360);
                                                            text->setFont(QFont("serif",14));
                                                            text->setTextWidth(640);
                                                  //ReceiveFlit
                                                      text = scene->addText("ReceiveFlit:");
                                                      text->setPos(x, y+90);
                                                      text->setFont(QFont("serif",14));
                                                      text->setDefaultTextColor(Qt::darkCyan);
                                                      if(flit_id!=-1)
                                                      {
                                                          if(receiveflit[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                            {
                                                              index=receiveflit[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                              k=index;
                                                              for(;receiveflit[m*c+n][index]!=']';index++)
                                                              {
                                                                  if(k*10+20>680)
                                                                      line=scene->addLine(x+index*10-680+20, y+170,x+index*10+40-680+20,y+170,redd);
                                                                  else
                                                                      line=scene->addLine(x+index*10, y+150,x+index*10+40,y+150,redd);
                                                              }

                                                          }
                                                      }
                                                      text = scene->addText(receiveflit[m*c+n]);
                                                      text->setPos(x, y+120);
                                                      text->setFont(QFont("serif",14));
                                                  //GenFlit
                                                      text = scene->addText("GenFlit:");
                                                      text->setPos(x, y);
                                                      text->setFont(QFont("serif",14));
                                                      text->setDefaultTextColor(Qt::darkCyan);
                                                      if(flit_id!=-1)
                                                      {
                                                          if(genflit[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                            {
                                                              index=genflit[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                              k=index;
                                                              for(;genflit[m*c+n][index]!=']';index++)
                                                              {
                                                                  if(k*10+20>680)
                                                                      line=scene->addLine(x+index*10-680+20, y+80,x+index*10+40-680+20,y+80,redd);
                                                                  else
                                                                      line=scene->addLine(x+index*10, y+60,x+index*10+40,y+60,redd);
                                                              }

                                                          }
                                                      }
                                                      text = scene->addText(genflit[m*c+n]);
                                                      text->setPos(x,y+30);
                                                      text->setFont(QFont("serif",14));
                                                      text->setTextWidth(640);

                                                  x=x+900;
                                                  n++;
                                                  if (n==d-1)
                                                  {
                                                      //ReturnFlit
                                                          text = scene->addText("ReturnFlit:");
                                                          text->setPos(x, y+630);
                                                          text->setFont(QFont("serif",14));
                                                          text->setDefaultTextColor(Qt::darkCyan);
                                                          if(flit_id!=-1)
                                                          {
                                                              if(returnflit[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                                {
                                                                  index=returnflit[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                  k=index;
                                                                  for(;returnflit[m*c+n][index]!=']';index++)
                                                                  {
                                                                      if(k*10+20>680)
                                                                          line=scene->addLine(x+index*10-680+20, y+710,x+index*10+40-680+20,y+710,redd);
                                                                      else
                                                                          line=scene->addLine(x+index*10, y+690,x+index*10+40,y+690,redd);
                                                                  }

                                                              }
                                                          }
                                                          text = scene->addText(returnflit[m*c+n]);
                                                          text->setPos(x, y+660);
                                                          text->setFont(QFont("serif",14));
                                                          text->setDefaultTextColor(Qt::red);
                                                      //SendingFlit
                                                          text = scene->addText("SendingFlit:");
                                                          text->setPos(x, y+540);
                                                          text->setFont(QFont("serif",14));
                                                          text->setDefaultTextColor(Qt::darkCyan);
                                                          if(flit_id!=-1)
                                                          {
                                                              if(sendingflit[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                                {
                                                                  index=sendingflit[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                  k=index;
                                                                  for(;sendingflit[m*c+n][index]!=']';index++)
                                                                  {
                                                                      if(k*10+20>680)
                                                                          line=scene->addLine(x+index*10-680+20, y+620,x+index*10+40-680+20,y+620,redd);
                                                                      else
                                                                          line=scene->addLine(x+index*10, y+600,x+index*10+40,y+600,redd);
                                                                  }

                                                              }
                                                          }
                                                          text = scene->addText(sendingflit[m*c+n]);
                                                          text->setPos(x, y+570);
                                                          text->setFont(QFont("serif",14));
                                                          text->setTextWidth(680);
                                                      //SWUpdate
                                                          text = scene->addText("SWUpdate:");
                                                          text->setPos(x, y+480);
                                                          text->setFont(QFont("serif",14));
                                                          text->setDefaultTextColor(Qt::darkCyan);
                                                          if(flit_id!=-1)
                                                          {
                                                              if(swupdate[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                                {
                                                                  index=swupdate[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                  k=index;
                                                                  for(;swupdate[m*c+n][index]!=']';index++)
                                                                  {
                                                                      if(k*10+20>680)
                                                                          line=scene->addLine(x+index*10-680+20, y+560,x+index*10+40-680+20,y+560,redd);
                                                                      else
                                                                          line=scene->addLine(x+index*10, y+540,x+index*10+40,y+540,redd);
                                                                  }

                                                              }
                                                          }
                                                          text = scene->addText(swupdate[m*c+n]);
                                                          text->setPos(x, y+510);
                                                          text->setFont(QFont("serif",14));
                                                      //VCUpdate
                                                          text = scene->addText("VCUpdate:");
                                                          text->setPos(x, y+420);
                                                          text->setFont(QFont("serif",14));
                                                          text->setDefaultTextColor(Qt::darkCyan);
                                                          text = scene->addText(vcupdate[m*c+n]);
                                                          text->setPos(x, y+450);
                                                          text->setFont(QFont("serif",14));
                                                          //InputQueueing
                                                              text = scene->addText("InputQueueing:");
                                                              text->setPos(x, y+150);
                                                              text->setFont(QFont("serif",14));
                                                              text->setDefaultTextColor(Qt::darkCyan);

                                                              text = scene->addText("VC  0: ");
                                                              text->setPos(x, y+180);
                                                              text->setFont(QFont("serif",14));
                                                              text->setDefaultTextColor(Qt::darkYellow);
                                                              text = scene->addText("VC  1: ");
                                                              text->setPos(x, y+240);
                                                              text->setFont(QFont("serif",14));
                                                              text->setDefaultTextColor(Qt::darkYellow);
                                                              text = scene->addText("VC  2: ");
                                                              text->setPos(x, y+300);
                                                              text->setFont(QFont("serif",14));
                                                              text->setDefaultTextColor(Qt::darkYellow);
                                                              text = scene->addText("VC  3: ");
                                                              text->setPos(x, y+360);
                                                              text->setFont(QFont("serif",14));
                                                              text->setDefaultTextColor(Qt::darkYellow);

                                                              //VC  0
                                                              if(flit_id!=-1)
                                                              {
                                                                  if(inputq0[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                                    {
                                                                      index=inputq0[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                      k=index;
                                                                      for(;inputq0[m*c+n][index]!=']';index++)
                                                                      {
                                                                          if(k*10+20>680)
                                                                              line=scene->addLine(x+index*10-680+20, y+230,x+index*10+40-680+20,y+230,redd);
                                                                          else
                                                                              line=scene->addLine(x+index*10, y+210,x+index*10+40,y+210,redd);
                                                                      }

                                                                  }
                                                              }
                                                                text = scene->addText(inputq0[m*c+n]);
                                                                text->setPos(x+60, y+180);
                                                                text->setFont(QFont("serif",14));
                                                                text->setTextWidth(640);
                                                              //VC  1
                                                                if(flit_id!=-1)
                                                                {
                                                                    if(inputq1[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                                      {
                                                                        index=inputq1[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                        k=index;
                                                                        for(;inputq1[m*c+n][index]!=']';index++)
                                                                        {
                                                                            if(k*10+20>680)
                                                                                line=scene->addLine(x+index*10-680+20, y+290,x+index*10+40-680+20,y+290,redd);
                                                                            else
                                                                                line=scene->addLine(x+index*10, y+270,x+index*10+40,y+270,redd);
                                                                        }

                                                                    }
                                                                }
                                                                text = scene->addText(inputq1[m*c+n]);
                                                                text->setPos(x+60, y+240);
                                                                text->setFont(QFont("serif",14));
                                                                text->setTextWidth(640);
                                                              //VC  2
                                                                if(flit_id!=-1)
                                                                {
                                                                    if(inputq2[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                                      {
                                                                        index=inputq2[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                        k=index;
                                                                        for(;inputq2[m*c+n][index]!=']';index++)
                                                                        {
                                                                            if(k*10+20>680)
                                                                                line=scene->addLine(x+index*10-680+20, y+350,x+index*10+40-680+20,y+350,redd);
                                                                            else
                                                                                line=scene->addLine(x+index*10, y+330,x+index*10+40,y+330,redd);
                                                                        }

                                                                    }
                                                                }
                                                                text = scene->addText(inputq2[m*c+n]);
                                                                text->setPos(x+60, y+300);
                                                                text->setFont(QFont("serif",14));
                                                                text->setTextWidth(640);
                                                              //VC  3
                                                                if(flit_id!=-1)
                                                                {
                                                                    if(inputq3[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                                      {
                                                                        index=inputq3[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                        k=index;
                                                                        for(;inputq3[m*c+n][index]!=']';index++)
                                                                        {
                                                                            if(k*10+20>680)
                                                                                line=scene->addLine(x+index*10-680+20, y+410,x+index*10+40-680+20,y+410,redd);
                                                                            else
                                                                                line=scene->addLine(x+index*10, y+390,x+index*10+40,y+390,redd);
                                                                        }

                                                                    }
                                                                }
                                                                text = scene->addText(inputq3[m*c+n]);
                                                                text->setPos(x+60, y+360);
                                                                text->setFont(QFont("serif",14));
                                                                text->setTextWidth(640);
                                                      //ReceiveFlit
                                                          text = scene->addText("ReceiveFlit:");
                                                          text->setPos(x, y+90);
                                                          text->setFont(QFont("serif",14));
                                                          text->setDefaultTextColor(Qt::darkCyan);
                                                          if(flit_id!=-1)
                                                          {
                                                              if(receiveflit[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                                {
                                                                  index=receiveflit[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                  k=index;
                                                                  for(;receiveflit[m*c+n][index]!=']';index++)
                                                                  {
                                                                      if(k*10+20>680)
                                                                          line=scene->addLine(x+index*10-680+20, y+170,x+index*10+40-680+20,y+170,redd);
                                                                      else
                                                                          line=scene->addLine(x+index*10, y+150,x+index*10+40,y+150,redd);
                                                                  }

                                                              }
                                                          }
                                                          text = scene->addText(receiveflit[m*c+n]);
                                                          text->setPos(x, y+120);
                                                          text->setFont(QFont("serif",14));
                                                      //GenFlit
                                                          text = scene->addText("GenFlit:");
                                                          text->setPos(x, y);
                                                          text->setFont(QFont("serif",14));
                                                          text->setDefaultTextColor(Qt::darkCyan);
                                                          if(flit_id!=-1)
                                                          {
                                                              if(genflit[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                                {
                                                                  index=genflit[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                  k=index;
                                                                  for(;genflit[m*c+n][index]!=']';index++)
                                                                  {
                                                                      if(k*10+20>680)
                                                                          line=scene->addLine(x+index*10-680+20, y+80,x+index*10+40-680+20,y+80,redd);
                                                                      else
                                                                          line=scene->addLine(x+index*10, y+60,x+index*10+40,y+60,redd);
                                                                  }

                                                              }
                                                          }
                                                          text = scene->addText(genflit[m*c+n]);
                                                          text->setPos(x,y+30);
                                                          text->setFont(QFont("serif",14));
                                                          text->setTextWidth(640);
                                                      break;
                                                  }
                                                  else
                                                  {
                                                      continue;
                                                  }

                                              }
                                              y=y+900;
                                              m++;
                                              n=0;
                                              x=0;
                                          }

                            //Printing Time
                             text = scene->addText("Time:");
                             text->setPos(0, y+50);
                             text->setFont(QFont("serif",20));
                             text->setDefaultTextColor(Qt::magenta);
                             text = scene->addText(QString::number(j));
                             text->setPos(90, y+50);
                             text->setFont(QFont("serif",20));
                             text->setDefaultTextColor(Qt::magenta);
                             if(flit_id==-1)
                             {
                                 if(j>=start && j<=end)
                                 {
                                     scene->render(&p);
                                 }
                             }
                             else
                             {
                                 if(flag==0)
                                 {
                                     if(j>=start && j<=end)
                                     {
                                         scene->render(&p);
                                     }
                                 }
                             }
                             if(ui->checkBox->isChecked())
                                 flag=-1;
                             break;
                             //Flush RetFlit
                               for(m=0;m<c;m++)
                               {
                                   for(n=0;n<d;n++)
                                   {
                                       if((returnflit[m*c+n].contains(QString::number(flit_id))) && (returnflit[m*c+n].contains(QString::number(flit_id/5))))
                                            flag=-1;
                                       returnflit[m*c+n].clear();
                                   }
                               }
                         }

                 /*        if(j==cycletime)    //End--------Wrong as only one line of final cycletime runs
                             break;
                    */

                       if(QString::compare(list[i][1],QString::number(j))!=0)    //To next time sequence
                       {
                           //Printing values
                                        x=0;
                                        y=0;
                                        m=0;
                                        n=0;

                                    while(m<c)
                                        {
                                            while(n < d)
                                            {

                                                //ReturnFlit
                                                    text = scene->addText("ReturnFlit:");
                                                    text->setPos(x, y+630);
                                                    text->setFont(QFont("serif",14));
                                                    text->setDefaultTextColor(Qt::darkCyan);
                                                    if(flit_id!=-1)
                                                    {
                                                        if(returnflit[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                          {
                                                            index=returnflit[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                            k=index;
                                                            for(;returnflit[m*c+n][index]!=']';index++)
                                                            {
                                                                if(k*10+20>680)
                                                                    line=scene->addLine(x+index*10-680+20, y+710,x+index*10+40-680+20,y+710,redd);
                                                                else
                                                                    line=scene->addLine(x+index*10, y+690,x+index*10+40,y+690,redd);
                                                            }

                                                        }
                                                    }
                                                    text = scene->addText(returnflit[m*c+n]);
                                                    text->setPos(x, y+660);
                                                    text->setFont(QFont("serif",14));
                                                    text->setDefaultTextColor(Qt::red);
                                                //SendingFlit
                                                    text = scene->addText("SendingFlit:");
                                                    text->setPos(x, y+540);
                                                    text->setFont(QFont("serif",14));
                                                    text->setDefaultTextColor(Qt::darkCyan);
                                                    if(flit_id!=-1)
                                                    {
                                                        if(sendingflit[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                          {
                                                            index=sendingflit[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                            k=index;
                                                            for(;sendingflit[m*c+n][index]!=']';index++)
                                                            {
                                                                if(k*10+20>680)
                                                                    line=scene->addLine(x+index*10-680+20, y+620,x+index*10+40-680+20,y+620,redd);
                                                                else
                                                                    line=scene->addLine(x+index*10, y+600,x+index*10+40,y+600,redd);
                                                            }

                                                        }
                                                    }
                                                    text = scene->addText(sendingflit[m*c+n]);
                                                    text->setPos(x, y+570);
                                                    text->setFont(QFont("serif",14));
                                                    text->setTextWidth(680);
                                                //SWUpdate
                                                    text = scene->addText("SWUpdate:");
                                                    text->setPos(x, y+480);
                                                    text->setFont(QFont("serif",14));
                                                    text->setDefaultTextColor(Qt::darkCyan);
                                                    if(flit_id!=-1)
                                                    {
                                                        if(swupdate[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                          {
                                                            index=swupdate[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                            k=index;
                                                            for(;swupdate[m*c+n][index]!=']';index++)
                                                            {
                                                                if(k*10+20>680)
                                                                    line=scene->addLine(x+index*10-680+20, y+560,x+index*10+40-680+20,y+560,redd);
                                                                else
                                                                    line=scene->addLine(x+index*10, y+540,x+index*10+40,y+540,redd);
                                                            }

                                                        }
                                                    }
                                                    text = scene->addText(swupdate[m*c+n]);
                                                    text->setPos(x, y+510);
                                                    text->setFont(QFont("serif",14));
                                                //VCUpdate
                                                    text = scene->addText("VCUpdate:");
                                                    text->setPos(x, y+420);
                                                    text->setFont(QFont("serif",14));
                                                    text->setDefaultTextColor(Qt::darkCyan);
                                                    text = scene->addText(vcupdate[m*c+n]);
                                                    text->setPos(x, y+450);
                                                    text->setFont(QFont("serif",14));
                                                    //InputQueueing
                                                        text = scene->addText("InputQueueing:");
                                                        text->setPos(x, y+150);
                                                        text->setFont(QFont("serif",14));
                                                        text->setDefaultTextColor(Qt::darkCyan);

                                                        text = scene->addText("VC  0: ");
                                                        text->setPos(x, y+180);
                                                        text->setFont(QFont("serif",14));
                                                        text->setDefaultTextColor(Qt::darkYellow);
                                                        text = scene->addText("VC  1: ");
                                                        text->setPos(x, y+240);
                                                        text->setFont(QFont("serif",14));
                                                        text->setDefaultTextColor(Qt::darkYellow);
                                                        text = scene->addText("VC  2: ");
                                                        text->setPos(x, y+300);
                                                        text->setFont(QFont("serif",14));
                                                        text->setDefaultTextColor(Qt::darkYellow);
                                                        text = scene->addText("VC  3: ");
                                                        text->setPos(x, y+360);
                                                        text->setFont(QFont("serif",14));
                                                        text->setDefaultTextColor(Qt::darkYellow);

                                                        //VC  0
                                                        if(flit_id!=-1)
                                                        {
                                                            if(inputq0[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                              {
                                                                index=inputq0[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                k=index;
                                                                for(;inputq0[m*c+n][index]!=']';index++)
                                                                {
                                                                    if(k*10+20>680)
                                                                        line=scene->addLine(x+index*10-680+20, y+230,x+index*10+40-680+20,y+230,redd);
                                                                    else
                                                                        line=scene->addLine(x+index*10, y+210,x+index*10+40,y+210,redd);
                                                                }

                                                            }
                                                        }
                                                          text = scene->addText(inputq0[m*c+n]);
                                                          text->setPos(x+60, y+180);
                                                          text->setFont(QFont("serif",14));
                                                          text->setTextWidth(640);
                                                        //VC  1
                                                          if(flit_id!=-1)
                                                          {
                                                              if(inputq1[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                                {
                                                                  index=inputq1[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                  k=index;
                                                                  for(;inputq1[m*c+n][index]!=']';index++)
                                                                  {
                                                                      if(k*10+20>680)
                                                                          line=scene->addLine(x+index*10-680+20, y+290,x+index*10+40-680+20,y+290,redd);
                                                                      else
                                                                          line=scene->addLine(x+index*10, y+270,x+index*10+40,y+270,redd);
                                                                  }

                                                              }
                                                          }
                                                          text = scene->addText(inputq1[m*c+n]);
                                                          text->setPos(x+60, y+240);
                                                          text->setFont(QFont("serif",14));
                                                          text->setTextWidth(640);
                                                        //VC  2
                                                          if(flit_id!=-1)
                                                          {
                                                              if(inputq2[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                                {
                                                                  index=inputq2[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                  k=index;
                                                                  for(;inputq2[m*c+n][index]!=']';index++)
                                                                  {
                                                                      if(k*10+20>680)
                                                                          line=scene->addLine(x+index*10-680+20, y+350,x+index*10+40-680+20,y+350,redd);
                                                                      else
                                                                          line=scene->addLine(x+index*10, y+330,x+index*10+40,y+330,redd);
                                                                  }

                                                              }
                                                          }
                                                          text = scene->addText(inputq2[m*c+n]);
                                                          text->setPos(x+60, y+300);
                                                          text->setFont(QFont("serif",14));
                                                          text->setTextWidth(640);
                                                        //VC  3
                                                          if(flit_id!=-1)
                                                          {
                                                              if(inputq3[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                                {
                                                                  index=inputq3[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                  k=index;
                                                                  for(;inputq3[m*c+n][index]!=']';index++)
                                                                  {
                                                                      if(k*10+20>680)
                                                                          line=scene->addLine(x+index*10-680+20, y+410,x+index*10+40-680+20,y+410,redd);
                                                                      else
                                                                          line=scene->addLine(x+index*10, y+390,x+index*10+40,y+390,redd);
                                                                  }

                                                              }
                                                          }
                                                          text = scene->addText(inputq3[m*c+n]);
                                                          text->setPos(x+60, y+360);
                                                          text->setFont(QFont("serif",14));
                                                          text->setTextWidth(640);
                                                //ReceiveFlit
                                                    text = scene->addText("ReceiveFlit:");
                                                    text->setPos(x, y+90);
                                                    text->setFont(QFont("serif",14));
                                                    text->setDefaultTextColor(Qt::darkCyan);
                                                    if(flit_id!=-1)
                                                    {
                                                        if(receiveflit[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                          {
                                                            index=receiveflit[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                            k=index;
                                                            for(;receiveflit[m*c+n][index]!=']';index++)
                                                            {
                                                                if(k*10+20>680)
                                                                    line=scene->addLine(x+index*10-680+20, y+170,x+index*10+40-680+20,y+170,redd);
                                                                else
                                                                    line=scene->addLine(x+index*10, y+150,x+index*10+40,y+150,redd);
                                                            }

                                                        }
                                                    }
                                                    text = scene->addText(receiveflit[m*c+n]);
                                                    text->setPos(x, y+120);
                                                    text->setFont(QFont("serif",14));
                                                //GenFlit
                                                    text = scene->addText("GenFlit:");
                                                    text->setPos(x, y);
                                                    text->setFont(QFont("serif",14));
                                                    text->setDefaultTextColor(Qt::darkCyan);
                                                    if(flit_id!=-1)
                                                    {
                                                        if(genflit[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                          {
                                                            index=genflit[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                            k=index;
                                                            for(;genflit[m*c+n][index]!=']';index++)
                                                            {
                                                                if(k*10+20>680)
                                                                    line=scene->addLine(x+index*10-680+20, y+80,x+index*10+40-680+20,y+80,redd);
                                                                else
                                                                    line=scene->addLine(x+index*10, y+60,x+index*10+40,y+60,redd);
                                                            }

                                                        }
                                                    }
                                                    text = scene->addText(genflit[m*c+n]);
                                                    text->setPos(x,y+30);
                                                    text->setFont(QFont("serif",14));
                                                    text->setTextWidth(640);

                                                x=x+900;
                                                n++;
                                                if (n==d-1)
                                                {

                                                    //ReturnFlit
                                                        text = scene->addText("ReturnFlit:");
                                                        text->setPos(x, y+630);
                                                        text->setFont(QFont("serif",14));
                                                        text->setDefaultTextColor(Qt::darkCyan);
                                                        if(flit_id!=-1)
                                                        {
                                                            if(returnflit[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                              {
                                                                index=returnflit[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                k=index;
                                                                for(;returnflit[m*c+n][index]!=']';index++)
                                                                {
                                                                    if(k*10+20>680)
                                                                        line=scene->addLine(x+index*10-680+20, y+710,x+index*10+40-680+20,y+710,redd);
                                                                    else
                                                                        line=scene->addLine(x+index*10, y+690,x+index*10+40,y+690,redd);
                                                                }

                                                            }
                                                        }
                                                        text = scene->addText(returnflit[m*c+n]);
                                                        text->setPos(x, y+660);
                                                        text->setFont(QFont("serif",14));
                                                        text->setDefaultTextColor(Qt::red);
                                                    //SendingFlit
                                                        text = scene->addText("SendingFlit:");
                                                        text->setPos(x, y+540);
                                                        text->setFont(QFont("serif",14));
                                                        text->setDefaultTextColor(Qt::darkCyan);
                                                        if(flit_id!=-1)
                                                        {
                                                            if(sendingflit[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                              {
                                                                index=sendingflit[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                k=index;
                                                                for(;sendingflit[m*c+n][index]!=']';index++)
                                                                {
                                                                    if(k*10+20>680)
                                                                        line=scene->addLine(x+index*10-680+20, y+620,x+index*10+40-680+20,y+620,redd);
                                                                    else
                                                                        line=scene->addLine(x+index*10, y+600,x+index*10+40,y+600,redd);
                                                                }

                                                            }
                                                        }
                                                        text = scene->addText(sendingflit[m*c+n]);
                                                        text->setPos(x, y+570);
                                                        text->setFont(QFont("serif",14));
                                                        text->setTextWidth(680);
                                                    //SWUpdate
                                                        text = scene->addText("SWUpdate:");
                                                        text->setPos(x, y+480);
                                                        text->setFont(QFont("serif",14));
                                                        text->setDefaultTextColor(Qt::darkCyan);
                                                        if(flit_id!=-1)
                                                        {
                                                            if(swupdate[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                              {
                                                                index=swupdate[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                k=index;
                                                                for(;swupdate[m*c+n][index]!=']';index++)
                                                                {
                                                                    if(k*10+20>680)
                                                                        line=scene->addLine(x+index*10-680+20, y+560,x+index*10+40-680+20,y+560,redd);
                                                                    else
                                                                        line=scene->addLine(x+index*10, y+540,x+index*10+40,y+540,redd);
                                                                }

                                                            }
                                                        }
                                                        text = scene->addText(swupdate[m*c+n]);
                                                        text->setPos(x, y+510);
                                                        text->setFont(QFont("serif",14));
                                                    //VCUpdate
                                                        text = scene->addText("VCUpdate:");
                                                        text->setPos(x, y+420);
                                                        text->setFont(QFont("serif",14));
                                                        text->setDefaultTextColor(Qt::darkCyan);
                                                        text = scene->addText(vcupdate[m*c+n]);
                                                        text->setPos(x, y+450);
                                                        text->setFont(QFont("serif",14));
                                                        //InputQueueing
                                                            text = scene->addText("InputQueueing:");
                                                            text->setPos(x, y+150);
                                                            text->setFont(QFont("serif",14));
                                                            text->setDefaultTextColor(Qt::darkCyan);

                                                            text = scene->addText("VC  0: ");
                                                            text->setPos(x, y+180);
                                                            text->setFont(QFont("serif",14));
                                                            text->setDefaultTextColor(Qt::darkYellow);
                                                            text = scene->addText("VC  1: ");
                                                            text->setPos(x, y+240);
                                                            text->setFont(QFont("serif",14));
                                                            text->setDefaultTextColor(Qt::darkYellow);
                                                            text = scene->addText("VC  2: ");
                                                            text->setPos(x, y+300);
                                                            text->setFont(QFont("serif",14));
                                                            text->setDefaultTextColor(Qt::darkYellow);
                                                            text = scene->addText("VC  3: ");
                                                            text->setPos(x, y+360);
                                                            text->setFont(QFont("serif",14));
                                                            text->setDefaultTextColor(Qt::darkYellow);

                                                            //VC  0
                                                            if(flit_id!=-1)
                                                            {
                                                                if(inputq0[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                                  {
                                                                    index=inputq0[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                    k=index;
                                                                    for(;inputq0[m*c+n][index]!=']';index++)
                                                                    {
                                                                        if(k*10+20>680)
                                                                            line=scene->addLine(x+index*10-680+20, y+230,x+index*10+40-680+20,y+230,redd);
                                                                        else
                                                                            line=scene->addLine(x+index*10, y+210,x+index*10+40,y+210,redd);
                                                                    }

                                                                }
                                                            }
                                                              text = scene->addText(inputq0[m*c+n]);
                                                              text->setPos(x+60, y+180);
                                                              text->setFont(QFont("serif",14));
                                                              text->setTextWidth(640);
                                                            //VC  1
                                                              if(flit_id!=-1)
                                                              {
                                                                  if(inputq1[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                                    {
                                                                      index=inputq1[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                      k=index;
                                                                      for(;inputq1[m*c+n][index]!=']';index++)
                                                                      {
                                                                          if(k*10+20>680)
                                                                              line=scene->addLine(x+index*10-680+20, y+290,x+index*10+40-680+20,y+290,redd);
                                                                          else
                                                                              line=scene->addLine(x+index*10, y+270,x+index*10+40,y+270,redd);
                                                                      }

                                                                  }
                                                              }
                                                              text = scene->addText(inputq1[m*c+n]);
                                                              text->setPos(x+60, y+240);
                                                              text->setFont(QFont("serif",14));
                                                              text->setTextWidth(640);
                                                            //VC  2
                                                              if(flit_id!=-1)
                                                              {
                                                                  if(inputq2[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                                    {
                                                                      index=inputq2[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                      k=index;
                                                                      for(;inputq2[m*c+n][index]!=']';index++)
                                                                      {
                                                                          if(k*10+20>680)
                                                                              line=scene->addLine(x+index*10-680+20, y+350,x+index*10+40-680+20,y+350,redd);
                                                                          else
                                                                              line=scene->addLine(x+index*10, y+330,x+index*10+40,y+330,redd);
                                                                      }

                                                                  }
                                                              }
                                                              text = scene->addText(inputq2[m*c+n]);
                                                              text->setPos(x+60, y+300);
                                                              text->setFont(QFont("serif",14));
                                                              text->setTextWidth(640);
                                                            //VC  3
                                                              if(flit_id!=-1)
                                                              {
                                                                  if(inputq3[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                                    {
                                                                      index=inputq3[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                      k=index;
                                                                      for(;inputq3[m*c+n][index]!=']';index++)
                                                                      {
                                                                          if(k*10+20>680)
                                                                              line=scene->addLine(x+index*10-680+20, y+410,x+index*10+40-680+20,y+410,redd);
                                                                          else
                                                                              line=scene->addLine(x+index*10, y+390,x+index*10+40,y+390,redd);
                                                                      }

                                                                  }
                                                              }
                                                              text = scene->addText(inputq3[m*c+n]);
                                                              text->setPos(x+60, y+360);
                                                              text->setFont(QFont("serif",14));
                                                              text->setTextWidth(640);
                                                    //ReceiveFlit
                                                        text = scene->addText("ReceiveFlit:");
                                                        text->setPos(x, y+90);
                                                        text->setFont(QFont("serif",14));
                                                        text->setDefaultTextColor(Qt::darkCyan);
                                                        if(flit_id!=-1)
                                                        {
                                                            if(receiveflit[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                              {
                                                                index=receiveflit[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                k=index;
                                                                for(;receiveflit[m*c+n][index]!=']';index++)
                                                                {
                                                                    if(k*10+20>680)
                                                                        line=scene->addLine(x+index*10-680+20, y+170,x+index*10+40-680+20,y+170,redd);
                                                                    else
                                                                        line=scene->addLine(x+index*10, y+150,x+index*10+40,y+150,redd);
                                                                }

                                                            }
                                                        }
                                                        text = scene->addText(receiveflit[m*c+n]);
                                                        text->setPos(x, y+120);
                                                        text->setFont(QFont("serif",14));
                                                    //GenFlit
                                                        text = scene->addText("GenFlit:");
                                                        text->setPos(x, y);
                                                        text->setFont(QFont("serif",14));
                                                        text->setDefaultTextColor(Qt::darkCyan);
                                                        if(flit_id!=-1)
                                                        {
                                                            if(genflit[m*c+n].contains("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]"))
                                                              {
                                                                index=genflit[m*c+n].indexOf("["+(QString::number(flit_id))+"]"+"["+(QString::number(flit_id/5))+"]");
                                                                k=index;
                                                                for(;genflit[m*c+n][index]!=']';index++)
                                                                {
                                                                    if(k*10+20>680)
                                                                        line=scene->addLine(x+index*10-680+20, y+80,x+index*10+40-680+20,y+80,redd);
                                                                    else
                                                                        line=scene->addLine(x+index*10, y+60,x+index*10+40,y+60,redd);
                                                                }

                                                            }
                                                        }
                                                        text = scene->addText(genflit[m*c+n]);
                                                        text->setPos(x,y+30);
                                                        text->setFont(QFont("serif",14));
                                                        text->setTextWidth(640);

                                                    break;
                                                }
                                                else
                                                {
                                                    continue;
                                                }

                                            }
                                            y=y+900;
                                            m++;
                                            n=0;
                                            x=0;
                                        }


                          //Printing Time
                          text = scene->addText("Time:");
                          text->setPos(0, y+50);
                          text->setFont(QFont("serif",20));
                          text->setDefaultTextColor(Qt::magenta);
                          text = scene->addText(QString::number(j));
                          text->setPos(90, y+50);
                          text->setFont(QFont("serif",20));
                          text->setDefaultTextColor(Qt::magenta);
                            if(flit_id==-1)
                            {
                                if(j>=start && j<=end)
                                {
                                    scene->render(&p);
                                    if(j<end)
                                        printer.newPage();
                                }
                            }
                            else
                            {
                                if(flag==0)
                                {
                                    if(j>=start && j<=end)
                                    {
                                        scene->render(&p);
                                        if(j<end)
                                            printer.newPage();
                                    }
                                }
                            }
                            if(!ui->checkBox->isChecked())
                                flag=-1;

                            //Flush RetFlit
                            for(m=0;m<c;m++)
                            {
                                    for(n=0;n<d;n++)
                                    {
                                        if((returnflit[m*c+n].contains(QString::number(flit_id))) && (returnflit[m*c+n].contains(QString::number(flit_id/5))))
                                            flag=-1;
                                        returnflit[m*c+n].clear();
                                    }
                            }

                           j++;
                         scene = new QGraphicsScene(this);
                         ui->graphicsView->setScene(scene); //Add "Time:j" on top of scene
                        }


                     }

            }
  /*          else if("Torus"==ui->comboBox->currentText())
            {

                   QString genflit[c*d];
                   QString receiveflit[c*d];
                   QString inputq0[c*d];
                   QString inputq1[c*d];
                   QString inputq2[c*d];
                   QString inputq3[c*d];
                   QString vcupdate[c*d];
                   QString swupdate[c*d];
                   QString sendingflit[c*d];
                   QString returnflit[c*d];


                     for(i=0,j=0;j<=cycletime;)
                     {
             //Ploting and Updating Values
                         x=100;
                         y=100;
                         m=0;
                         n=0;
                     while(m <c)
                         {
                             while(n < d)
                             {
                                 line=scene->addLine(x, y,x+700,y,black);
                                 line=scene->addLine(x, y+700,x+700,y+700,black);

                                 line=scene->addLine(x+700, y+350,x+900,y+350,black);
                                 if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"RetFlit")==0))
                                 {
                                     returnflit[m*c+n].append(list[i][3]);
                                     returnflit[m*c+n].append(",");
                                     if(sendingflit[m*c+n].contains(list[i][3]))
                                         sendingflit[m*c+n].remove((list[i][3])+",");
                                 }
                                 if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"SendingFlit")==0))
                                 {
                                     sendingflit[m*c+n].append(list[i][3]);
                                     sendingflit[m*c+n].append(",");
                                     if(swupdate[m*c+n].contains(list[i][3]))
                                         swupdate[m*c+n].remove((list[i][3])+",");
                                 }
                                 if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"SWUpdate")==0))
                                 {
                                     swupdate[m*c+n].append(list[i][3]);
                                     swupdate[m*c+n].append(",");
                                     if(vcupdate[m*c+n].contains(list[i][3]))
                                         vcupdate[m*c+n].remove((list[i][3])+",");

                                     if(inputq0[m*c+n].contains(list[i][3]))
                                         inputq0[m*c+n].remove((list[i][3])+",");
                                     if(inputq1[m*c+n].contains(list[i][3]))
                                         inputq1[m*c+n].remove((list[i][3])+",");
                                     if(inputq2[m*c+n].contains(list[i][3]))
                                         inputq2[m*c+n].remove((list[i][3])+",");
                                     if(inputq3[m*c+n].contains(list[i][3]))
                                         inputq3[m*c+n].remove((list[i][3])+",");
                                 }
                                 if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"VCUpdate")==0))
                                 {
                                     vcupdate[m*c+n].append(list[i][3]);
                                     vcupdate[m*c+n].append(",");

                                     if(inputq0[m*c+n].contains(list[i][3]))
                                         inputq0[m*c+n].remove((list[i][3])+",");
                                     if(inputq1[m*c+n].contains(list[i][3]))
                                         inputq1[m*c+n].remove((list[i][3])+",");
                                     if(inputq2[m*c+n].contains(list[i][3]))
                                         inputq2[m*c+n].remove((list[i][3])+",");
                                     if(inputq3[m*c+n].contains(list[i][3]))
                                         inputq3[m*c+n].remove((list[i][3])+",");
                                 }
                                 if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"InputQueueing")==0))
                                 {
                                     if(QString::compare(list[i][5],"0")==0)
                                     {
                                         inputq0[m*c+n].append(list[i][3]);
                                         inputq0[m*c+n].append(",");
                                      }
                                     if(QString::compare(list[i][5],"1")==0)
                                     {
                                         inputq1[m*c+n].append(list[i][3]);
                                         inputq1[m*c+n].append(",");
                                     }
                                     if(QString::compare(list[i][5],"2")==0)
                                     {
                                         inputq2[m*c+n].append(list[i][3]);
                                         inputq2[m*c+n].append(",");
                                     }
                                     if(QString::compare(list[i][5],"3")==0)
                                     {
                                         inputq3[m*c+n].append(list[i][3]);
                                         inputq3[m*c+n].append(",");
                                     }
                                     if(receiveflit[m*c+n].contains(list[i][3]))
                                         receiveflit[m*c+n].remove((list[i][3])+",");
                                 }
                                 if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"ReceiveFlit")==0))
                                 {
                                     receiveflit[m*c+n].append(list[i][3]);
                                     receiveflit[m*c+n].append(",");
                                     if(genflit[m*c+n].contains(list[i][3]))
                                         genflit[m*c+n].remove((list[i][3])+",");
                                     for(m1=0;m1<c;m1++)
                                     {
                                         for(n1=0;n1<d;n1++)
                                         {
                                             if(sendingflit[m1*c+n1].contains(list[i][3]))
                                                 sendingflit[m1*c+n1].remove((list[i][3])+",");
                                         }
                                     }
                                 }
                                 if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"GenFlit")==0))
                                 {
                                     genflit[m*c+n].append(list[i][3]);
                                     genflit[m*c+n].append(",");

                                 }




                                 x=x+900;
                                 n++;
                                 if (n==d-1)
                                 {
                                      line=scene->addLine(x, y,x+700,y,black);
                                        line=scene->addLine(x, y+700,x+700,y+700,black);
                                        if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"RetFlit")==0))
                                        {
                                            returnflit[m*c+n].append(list[i][3]);
                                            returnflit[m*c+n].append(",");
                                            if(sendingflit[m*c+n].contains(list[i][3]))
                                                sendingflit[m*c+n].remove((list[i][3])+",");
                                        }
                                        if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"SendingFlit")==0))
                                        {
                                            sendingflit[m*c+n].append(list[i][3]);
                                            sendingflit[m*c+n].append(",");
                                            if(swupdate[m*c+n].contains(list[i][3]))
                                                swupdate[m*c+n].remove((list[i][3])+",");
                                        }
                                        if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"SWUpdate")==0))
                                        {
                                            swupdate[m*c+n].append(list[i][3]);
                                            swupdate[m*c+n].append(",");
                                            if(vcupdate[m*c+n].contains(list[i][3]))
                                                vcupdate[m*c+n].remove((list[i][3])+",");

                                            if(inputq0[m*c+n].contains(list[i][3]))
                                                inputq0[m*c+n].remove((list[i][3])+",");
                                            if(inputq1[m*c+n].contains(list[i][3]))
                                                inputq1[m*c+n].remove((list[i][3])+",");
                                            if(inputq2[m*c+n].contains(list[i][3]))
                                                inputq2[m*c+n].remove((list[i][3])+",");
                                            if(inputq3[m*c+n].contains(list[i][3]))
                                                inputq3[m*c+n].remove((list[i][3])+",");
                                        }
                                        if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"VCUpdate")==0))
                                        {
                                            vcupdate[m*c+n].append(list[i][3]);
                                            vcupdate[m*c+n].append(",");

                                            if(inputq0[m*c+n].contains(list[i][3]))
                                                inputq0[m*c+n].remove((list[i][3])+",");
                                            if(inputq1[m*c+n].contains(list[i][3]))
                                                inputq1[m*c+n].remove((list[i][3])+",");
                                            if(inputq2[m*c+n].contains(list[i][3]))
                                                inputq2[m*c+n].remove((list[i][3])+",");
                                            if(inputq3[m*c+n].contains(list[i][3]))
                                                inputq3[m*c+n].remove((list[i][3])+",");
                                        }
                                        if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"InputQueueing")==0))
                                        {

                                            if(QString::compare(list[i][5],"0")==0)
                                            {
                                                inputq0[m*c+n].append(list[i][3]);
                                                inputq0[m*c+n].append(",");
                                            }
                                            if(QString::compare(list[i][5],"1")==0)
                                            {
                                                inputq1[m*c+n].append(list[i][3]);
                                                inputq1[m*c+n].append(",");
                                            }
                                            if(QString::compare(list[i][5],"2")==0)
                                            {
                                                inputq2[m*c+n].append(list[i][3]);
                                                inputq2[m*c+n].append(",");
                                            }
                                            if(QString::compare(list[i][5],"3")==0)
                                            {
                                                inputq3[m*c+n].append(list[i][3]);
                                                inputq3[m*c+n].append(",");
                                            }
                                            if(receiveflit[m*c+n].contains(list[i][3]))
                                                receiveflit[m*c+n].remove((list[i][3])+",");
                                        }
                                        if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"ReceiveFlit")==0))
                                        {
                                            receiveflit[m*c+n].append(list[i][3]);
                                            receiveflit[m*c+n].append(",");
                                            if(genflit[m*c+n].contains(list[i][3]))
                                                genflit[m*c+n].remove(list[i][3]+",");
                                            for(m1=0;m1<c;m1++)
                                            {
                                                for(n1=0;n1<d;n1++)
                                                {
                                                    if(sendingflit[m1*c+n1].contains(list[i][3]))
                                                        sendingflit[m1*c+n1].remove((list[i][3])+",");
                                                }
                                            }

                                        }
                                        if((QString::compare(list[i][2],QString::number(m*c+n))==0) && (QString::compare(list[i][4],"GenFlit")==0))
                                        {

                                            genflit[m*c+n].append(list[i][3]);
                                            genflit[m*c+n].append(",");

                                        }



                                     break;
                                 }
                                 else
                                 {
                                     continue;
                                 }

                             }
                             line=scene->addLine(0, y+350,100,y+350,black);
                             line=scene->addLine(x+700, y+350,x+900,y+350,black);
                             line=scene->addLine(0, y+350,0,y-50,black);
                             line=scene->addLine(x+900, y+350,x+900,y-50,black);

                             line=scene->addLine(0, y-50,x+900,y-50,black);

                             y=y+900;
                             m++;
                             n=0;
                             x=100;
                         }

                         x=100;
                         y=100;
                         n=0;
                         m=0;
                         while(m<d)
                         {
                             while(n<c)
                             {
                                   line=scene->addLine(x, y,x,y+700,black);
                                    line=scene->addLine(x+700, y,x+700,y+700,black);

                                    line=scene->addLine(x+350, y+700,x+350,y+900,black);


                                 y=y+900;
                                 n++;
                                 if(n==(c-1))
                                 {
                                     line=scene->addLine(x, y,x,y+700,black);
                                     line=scene->addLine(x+700, y,x+700,y+700,black);
                                      break;

                                 }
                                 else
                                 {
                                     continue;
                                 }

                             }
                             line=scene->addLine(x+350, 0,x+350,100,black);
                             line=scene->addLine(x+350, y+700,x+350,y+900,black);
                             line=scene->addLine(x+350, 0,x-60,0,black);
                             line=scene->addLine(x+350, y+900,x-60,y+900,black);

                             line=scene->addLine(x-60, 0,x-60,y+900,black);

                             x=x+900;
                             m++;
                             n=0;
                             y=100;
                         }

             //Constraint Update
                         if(i<count-1)      //Next Line
                            i++;
                         else               //Last Line
                         {
                             //Printing values
                                          x=100;
                                          y=100;
                                          m=0;
                                          n=0;

                                      while(m<c)
                                          {
                                              while(n < d)
                                              {
                                                  //ReturnFlit
                                                      text = scene->addText("ReturnFlit:");
                                                      text->setPos(x, y+320);
                                                      text = scene->addText(returnflit[m*c+n]);
                                                      text->setPos(x, y+340);
                                                  //SendingFlit
                                                      text = scene->addText("SendingFlit:");
                                                      text->setPos(x, y+280);
                                                      text = scene->addText(sendingflit[m*c+n]);
                                                      text->setPos(x, y+300);
                                                  //SWUpdate
                                                      text = scene->addText("SWUpdate:");
                                                      text->setPos(x, y+240);
                                                      text = scene->addText(swupdate[m*c+n]);
                                                      text->setPos(x, y+260);
                                                  //VCUpdate
                                                      text = scene->addText("VCUpdate:");
                                                      text->setPos(x, y+200);
                                                      text = scene->addText(vcupdate[m*c+n]);
                                                      text->setPos(x, y+220);
                                                  //InputQueueing
                                                      text = scene->addText("InputQueueing:");
                                                      text->setPos(x, y+80);

                                                      text = scene->addText("VC  0: ");
                                                      text->setPos(x, y+100);
                                                      text = scene->addText("VC  1: ");
                                                      text->setPos(x, y+120);
                                                      text = scene->addText("VC  2: ");
                                                      text->setPos(x, y+140);
                                                      text = scene->addText("VC  3: ");
                                                      text->setPos(x, y+160);

                                                        //VC  0
                                                          text = scene->addText(inputq0[m*c+n]);
                                                          text->setPos(x+60, y+100);
                                                        //VC  1
                                                          text = scene->addText(inputq1[m*c+n]);
                                                          text->setPos(x+60, y+120);
                                                        //VC  2
                                                          text = scene->addText(inputq2[m*c+n]);
                                                          text->setPos(x+60, y+140);
                                                        //VC  3
                                                          text = scene->addText(inputq3[m*c+n]);
                                                          text->setPos(x+60, y+160);

                                                  //ReceiveFlit
                                                      text = scene->addText("ReceiveFlit:");
                                                      text->setPos(x, y+40);
                                                      text = scene->addText(receiveflit[m*c+n]);
                                                      text->setPos(x, y+60);
                                                  //GenFlit
                                                      text = scene->addText("GenFlit:");
                                                      text->setPos(x, y);
                                                      text = scene->addText(genflit[m*c+n]);
                                                      text->setPos(x,y+20);


                                                  x=x+900;
                                                  n++;
                                                  if (n==d-1)
                                                  {
                                                      //ReturnFlit
                                                          text = scene->addText("ReturnFlit:");
                                                          text->setPos(x, y+320);
                                                          text = scene->addText(returnflit[m*c+n]);
                                                          text->setPos(x, y+340);
                                                      //SendingFlit
                                                          text = scene->addText("SendingFlit:");
                                                          text->setPos(x, y+280);
                                                          text = scene->addText(sendingflit[m*c+n]);
                                                          text->setPos(x, y+300);
                                                      //SWUpdate
                                                          text = scene->addText("SWUpdate:");
                                                          text->setPos(x, y+240);
                                                          text = scene->addText(swupdate[m*c+n]);
                                                          text->setPos(x, y+260);
                                                      //VCUpdate
                                                          text = scene->addText("VCUpdate:");
                                                          text->setPos(x, y+200);
                                                          text = scene->addText(vcupdate[m*c+n]);
                                                          text->setPos(x, y+220);
                                                      //InputQueueing
                                                          text = scene->addText("InputQueueing:");
                                                          text->setPos(x, y+80);

                                                          text = scene->addText("VC  0: ");
                                                          text->setPos(x, y+100);
                                                          text = scene->addText("VC  1: ");
                                                          text->setPos(x, y+120);
                                                          text = scene->addText("VC  2: ");
                                                          text->setPos(x, y+140);
                                                          text = scene->addText("VC  3: ");
                                                          text->setPos(x, y+160);

                                                          //VC  0
                                                            text = scene->addText(inputq0[m*c+n]);
                                                            text->setPos(x+60, y+100);
                                                          //VC  1
                                                            text = scene->addText(inputq1[m*c+n]);
                                                            text->setPos(x+60, y+120);
                                                          //VC  2
                                                            text = scene->addText(inputq2[m*c+n]);
                                                            text->setPos(x+60, y+140);
                                                          //VC  3
                                                            text = scene->addText(inputq3[m*c+n]);
                                                            text->setPos(x+60, y+160);
                                                      //ReceiveFlit
                                                          text = scene->addText("ReceiveFlit:");
                                                          text->setPos(x, y+40);
                                                          text = scene->addText(receiveflit[m*c+n]);
                                                          text->setPos(x, y+60);
                                                      //GenFlit
                                                          text = scene->addText("GenFlit:");
                                                          text->setPos(x, y);
                                                          text = scene->addText(genflit[m*c+n]);
                                                          text->setPos(x,y+20);

                                                      break;
                                                  }
                                                  else
                                                  {
                                                      continue;
                                                  }

                                              }
                                              y=y+900;
                                              m++;
                                              n=0;
                                              x=100;
                                          }


                            //Flush RetFlit
                              for(m=0;m<c;m++)
                              {
                                  for(n=0;n<d;n++)
                                      returnflit[m*c+n].clear();
                              }

                            //Printing Time
                             text = scene->addText("Time:");
                             text->setPos(0, y);
                             text = scene->addText(QString::number(j));
                             text->setPos(40, y);
                             scene->render(&p);

                             break;
                         }

                 if(QString::compare(list[i][1],QString::number(j))!=0)    //To next time sequence
                       {
                           //Printing values
                                        x=100;
                                        y=100;
                                        m=0;
                                        n=0;

                                    while(m<c)
                                        {
                                            while(n < d)
                                            {

                                                //ReturnFlit
                                                    text = scene->addText("ReturnFlit:");
                                                    text->setPos(x, y+320);
                                                    text = scene->addText(returnflit[m*c+n]);
                                                    text->setPos(x, y+340);
                                                //SendingFlit
                                                    text = scene->addText("SendingFlit:");
                                                    text->setPos(x, y+280);
                                                    text = scene->addText(sendingflit[m*c+n]);
                                                    text->setPos(x, y+300);
                                                //SWUpdate
                                                    text = scene->addText("SWUpdate:");
                                                    text->setPos(x, y+240);
                                                    text = scene->addText(swupdate[m*c+n]);
                                                    text->setPos(x, y+260);
                                                //VCUpdate
                                                    text = scene->addText("VCUpdate:");
                                                    text->setPos(x, y+200);
                                                    text = scene->addText(vcupdate[m*c+n]);
                                                    text->setPos(x, y+220);
                                                    //InputQueueing
                                                        text = scene->addText("InputQueueing:");
                                                        text->setPos(x, y+80);

                                                        text = scene->addText("VC  0: ");
                                                        text->setPos(x, y+100);
                                                        text = scene->addText("VC  1: ");
                                                        text->setPos(x, y+120);
                                                        text = scene->addText("VC  2: ");
                                                        text->setPos(x, y+140);
                                                        text = scene->addText("VC  3: ");
                                                        text->setPos(x, y+160);

                                                        //VC  0
                                                          text = scene->addText(inputq0[m*c+n]);
                                                          text->setPos(x+60, y+100);
                                                        //VC  1
                                                          text = scene->addText(inputq1[m*c+n]);
                                                          text->setPos(x+60, y+120);
                                                        //VC  2
                                                          text = scene->addText(inputq2[m*c+n]);
                                                          text->setPos(x+60, y+140);
                                                        //VC  3
                                                          text = scene->addText(inputq3[m*c+n]);
                                                          text->setPos(x+60, y+160);
                                                //ReceiveFlit
                                                    text = scene->addText("ReceiveFlit:");
                                                    text->setPos(x, y+40);
                                                    text = scene->addText(receiveflit[m*c+n]);
                                                    text->setPos(x, y+60);
                                                //GenFlit
                                                    text = scene->addText("GenFlit:");
                                                    text->setPos(x, y);
                                                    text = scene->addText(genflit[m*c+n]);
                                                    text->setPos(x,y+20);

                                                x=x+900;
                                                n++;
                                                if (n==d-1)
                                                {
                                                    //ReturnFlit
                                                        text = scene->addText("ReturnFlit:");
                                                        text->setPos(x, y+320);
                                                        text = scene->addText(returnflit[m*c+n]);
                                                        text->setPos(x, y+340);
                                                    //SendingFlit
                                                        text = scene->addText("SendingFlit:");
                                                        text->setPos(x, y+280);
                                                        text = scene->addText(sendingflit[m*c+n]);
                                                        text->setPos(x, y+300);
                                                    //SWUpdate
                                                        text = scene->addText("SWUpdate:");
                                                        text->setPos(x, y+240);
                                                        text = scene->addText(swupdate[m*c+n]);
                                                        text->setPos(x, y+260);
                                                    //VCUpdate
                                                        text = scene->addText("VCUpdate:");
                                                        text->setPos(x, y+200);
                                                        text = scene->addText(vcupdate[m*c+n]);
                                                        text->setPos(x, y+220);
                                                        //InputQueueing
                                                            text = scene->addText("InputQueueing:");
                                                            text->setPos(x, y+80);

                                                            text = scene->addText("VC  0: ");
                                                            text->setPos(x, y+100);
                                                            text = scene->addText("VC  1: ");
                                                            text->setPos(x, y+120);
                                                            text = scene->addText("VC  2: ");
                                                            text->setPos(x, y+140);
                                                            text = scene->addText("VC  3: ");
                                                            text->setPos(x, y+160);

                                                            //VC  0
                                                              text = scene->addText(inputq0[m*c+n]);
                                                              text->setPos(x+60, y+100);
                                                            //VC  1
                                                              text = scene->addText(inputq1[m*c+n]);
                                                              text->setPos(x+60, y+120);
                                                            //VC  2
                                                              text = scene->addText(inputq2[m*c+n]);
                                                              text->setPos(x+60, y+140);
                                                            //VC  3
                                                              text = scene->addText(inputq3[m*c+n]);
                                                              text->setPos(x+60, y+160);
                                                    //ReceiveFlit
                                                        text = scene->addText("ReceiveFlit:");
                                                        text->setPos(x, y+40);
                                                        text = scene->addText(receiveflit[m*c+n]);
                                                        text->setPos(x, y+60);
                                                    //GenFlit
                                                        text = scene->addText("GenFlit:");
                                                        text->setPos(x, y);
                                                        text = scene->addText(genflit[m*c+n]);
                                                        text->setPos(x,y+20);

                                                    break;
                                                }
                                                else
                                                {
                                                    continue;
                                                }

                                            }
                                            y=y+900;
                                            m++;
                                            n=0;
                                            x=100;
                                        }

                                    //Flush RetFlit
                          for(m=0;m<c;m++)
                          {
                                  for(n=0;n<d;n++)
                                        returnflit[m*c+n].clear();
                          }
                            //Printing Time
                           text = scene->addText("Time:");
                           text->setPos(0, y);
                           text = scene->addText(QString::number(j));
                           text->setPos(40, y);


                           scene->render(&p);
                           printer.newPage();
                           j++;
                         scene = new QGraphicsScene(this);
                         ui->graphicsView->setScene(scene); //Add "Time:j" on top of scene
                        }


                     }

            }
*/


            p.end();

         }

//-----------------------------------------------------------------------------------------------------

         process.start("mv", QStringList() << "print.pdf"<<"Results");
         process.waitForFinished();
                  file.close();
                  return;

}

//Check with Sneha if she wants the returned item gone after displayed or circled red! : Flush Return before every page  //
//Can an entity skip VCUpdate? [ref. [21][4]] : Only header goes through VCUpdate, its tail skips to SwitchUp //
//Remove VC 0 as its only when a flit is just generated- from Torus //
//Problem with removing value from InputQueueing //
//Add VC no. and size as input //
//Take input the cycle number to print just the required time cycles(pages)//
//Increase text size cuz her eyes hurt XD   X
//Draw Arrows to show the flit movement in these cycles   X
//Display cycles on basis of flit movement (take flit id as input) //
//Show Flit Movement among routers through wire//
//Lit it up like a Christmas Tree //
//SetWidth of text and increase size //
//While printing by flit_id, highlight it//----------Really!
//Add 2 options to print Search_by_flit//
//Add all the inputs (see ashwini's work)//
//Arrange GUI//
//Add Default values for GUI//
//Terminal execution of code//
//Seperate RUN func with just log.txt and count_lines//
//Build->Run terminal and execute command "./booksim log.txt(call it mesh-config)" and flush the outputs to a log file//
//Transcend the outputs to a seperate folder, like Results (mkdir -p Results)//
//and something about Sneha1 and Sneha2 XDs//
