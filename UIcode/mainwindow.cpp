#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configinput.h"
#include "sweeprunmethod.h"
#include "setclockdomains.h"
#include "heatmap.h"

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
#include <QFileDialog>

#define PI 3.14159265


QString fileNames = "../UIcode/Inputs/output_sarabjeet_(copy).txt";
//QString fileNames_exe="/home/sarab/Downloads/booksim2-classes/src/booksim";
//QString fileNames_config="/home/sarab/Desktop/final/code/Results/log";

//  Defining output for booksim2-master/src/examples/BITREV
QString fileOPbuild = "../booksim2-master/src/examples/bitrev";
bool isTopologyMess = true;
bool allowUserToRun = false;
bool defaultClockDomainConfig = true;

//-----------------------------------------------------//


/*********************  Inported data for input configuration *********************/
QStringList inputConfigData;
QString myMessage;
/*********************  Inported data for input configuration ENDS *********************/


/*********************  Inported data for configuring client domains *********************/
int noOfClockDomains;
QList<QList <QString>>  clockDomainsClientValueArray;
QList<QString> assignedRoutersPerClockDomainArray;
/*********************  Inported data for configuring client domains ENDS *********************/


bool canShowHeatMap = false;

using namespace std;
QString b[7];
int c;
int d;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->topology->addItem("mesh");
    ui->topology->addItem("torus");
    ui->topology->addItem("ring");
    ui->topology->addItem("bus");
    ui->topology->addItem("anynet");
    ui->topology->addItem("cmesh");
    ui->topology->addItem("dragonfly");
    ui->topology->addItem("fattree");
    ui->topology->addItem("flatfly_onchip");
    ui->topology->addItem("fly");
    ui->topology->addItem("kncube");
    ui->topology->addItem("qtree");
    ui->topology->addItem("tree4");
    ui->topology->setEditable(1);

    ui->singleRun->setChecked(1);


    ui->setClockDomains->setVisible(false);


}

MainWindow::~MainWindow()
{
    delete ui;
}



/************* TEST START **************************/
void MainWindow::on_setIPconfig_clicked()
{
    ConfigInput *mConfigInput = new ConfigInput();
    mConfigInput->show();
    //this->hide();
    mConfigInput->setWindowState(Qt::WindowActive);

}

void MainWindow::setConfigParamLinked(QMap<QString, QString> *configData){
    qDebug() << configData;
}

void MainWindow::mySlot(const QStringList &arg1){
    qDebug() << arg1;
}



void MainWindow::bar1(){
    myMessage = "Ashim";
    qDebug() << "Receveived";
}





/*********************** TEST END ***************************/





void MainWindow::submitIpConfSlot(const QStringList &configData) {
    qDebug() << configData;
    inputConfigData = configData;
}

void MainWindow::on_build_clicked()
{
    QMessageBox msgBoxEmptyConfigAlert;

    if (inputConfigData.isEmpty() && ui->configFilePath->text().isEmpty()){
        msgBoxEmptyConfigAlert.setText("You haven't set the input configurations!");
        msgBoxEmptyConfigAlert.exec();
        return;
    }

    else if(assignedRoutersPerClockDomainArray.isEmpty() && (!defaultClockDomainConfig)){
        msgBoxEmptyConfigAlert.setText("You haven't set your custom clock domains!");
        msgBoxEmptyConfigAlert.exec();
        return;
    }



//    else if(assignedRoutersPerClockDomainArray.isEmpty()){
//        msgBoxEmptyConfigAlert.setText("You haven't set clock domains!");
//        msgBoxEmptyConfigAlert.exec();
//        return;
//    }



    if (defaultClockDomainConfig) {
        setDefaultClockDomainConfig();
    }



    QProcess process;
    process.start("mkdir", QStringList() << "Results");
    process.waitForFinished();

    QMessageBox msgBox;
    msgBox.setText("Error Opening File, Bah");
    QFile file(fileNames);
    if(!file.open(QIODevice::ReadOnly |  QIODevice::Text)) {
        msgBox.exec();
        return;
    }

//     QFile fileout("Results/log");
    QFile fileout(fileOPbuild);
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


    qDebug()<<"Number of VC's = "<<inputConfigData[2];
    qDebug()<<"VC Buffer Size = "<<inputConfigData[3];




    /**************** Output / Log File  **********************/
    out<<"\n//Topology";
    out<<"\ntopology = "<<ui->topology->currentText()<<";";
    out<<"\nk = "<<ui->numRows->text()<<";";
    out<<"\nn = "<<"2"<<";";
    //out<<"\nno_of_endpts = "<<ui->lineEdit_3->text()<<";";
    out<<"\n\n//Routing";
    out<<"\nrouting_function = "<<inputConfigData[1]<<";";
    out<<"\n\n//Flow Control";
    out<<"\nnum_vcs = "<<inputConfigData[2]<<";";
    out<<"\nvc_buf_size = "<<inputConfigData[3]<<";";

    if(inputConfigData[1] == "1")
       out<<"\nwait_for_tail_credit = 1;";
    else
       out<<"\nwait_for_tail_credit = 0;";


    out<<"\n\n//Router Architecture";

    out<<"\nvc_allocator = "<<inputConfigData[5]<<";";
    out<<"\nsw_allocator = "<<inputConfigData[6]<<";";   //alloc_iters missing
    out<<"\n\ncredit_delay = "<<inputConfigData[8]<<";";
    out<<"\nrouting_delay = "<<inputConfigData[9]<<";";
    out<<"\nvc_alloc_delay = "<<inputConfigData[10]<<";";
    out<<"\nsw_alloc_delay = "<<inputConfigData[11]<<";";
    out<<"\n\ninput_speedup = "<<inputConfigData[12]<<";";
    out<<"\noutput_speedup = "<<inputConfigData[13]<<";";
    out<<"\ninternal_speedup = "<<inputConfigData[14]<<";";

    if(inputConfigData[15] == "1")
       out<<"\n\nvc_busy_when_full = 1;";   //Not in the manual
    else
       out<<"\n\nvc_busy_when_full = 0;";

    //out<<"\n\n//Traffic";
    //out<<"\ntraffic = "<<ui->lineEdit_19->text()<<";";
    out<<"\npacket_size = "<<inputConfigData[17]<<";";
    out<<"\n\n//Simulation";
    out<<"\nsim_type = "<<inputConfigData[16]<<";";

    if(inputConfigData[18] == "1")
    {
        out<<"\n\n//Simulation Data";                   //Not in the manual
        out<<"\ntraffic = "<<inputConfigData[19]<<";"<<"\t//Synthetic";
    }
    else if(inputConfigData[20] == "1")
    {
        out<<"\n\n//Simulation Data";                   //Not in the manual
        out<<"\ntraffic = \""<<inputConfigData[21]<<"\""<<";<<\t//Real";
    }

    if(inputConfigData[22] == "1")
       out<<"\n\n//Power Calculation"<<"\n//Path to the Tech file:\""<<inputConfigData[23] <<"\"";  //Not in the manual

    out<<"\n\nmax_samples = "<<inputConfigData[24]<<";";
    out<<"\n\ninjection_rate = "<<inputConfigData[25]<<";";
    out<<"\n\n//Explicit Data";
    out<<"\n//total_time = "<<cycletime<<";";
    out<<"\n//total_no_of_flits = "<<flitnum<<";\n";









    /*********************************************  Events for setting clock domain configurations ********************************************************************************************************************************************************************************************************/
    //     Input data will in the format of: filename.py number_of_clock_domains 'assigned_routers for clock domain 1' 'assigned_routers for clock domain 2' .................. clock_domain_1_client_index_0 clock_domain_1_client_index_1 ...............clock_domain_lastOne_client_index_4
    //     Eg. : python client_generate.py 3 '1,2,3,4' '5,6,7' '8,9,10' 1 2 3 4 5 6 7 8 9 10 11 12

    QString inputArguments;
    inputArguments = " " + QString::number(noOfClockDomains) + " "  ;

    for (int i=0; i<noOfClockDomains; i++) {
        inputArguments +=  "'" + assignedRoutersPerClockDomainArray[i] + "' ";
    }

    for (int i=0; i<noOfClockDomains; i++) {
        for(int j=0; j<4; j++) {
            inputArguments += clockDomainsClientValueArray[i][j] + " ";
        }
    }

    process.start("gnome-terminal -x sh -c \"(cd ../SideScripts/Pane/ ; python client_generate.py" + inputArguments + ";)\"");
    process.waitForFinished();


    /*********************************************  Events for setting clock domain configurations ENDS ***************************************************************************************************************************************************************************************************/












    /************** ADDING EDIT OPTIONS TO PANE AND BOOKSIM ******************/
    QString routerRow = ui->numRows->text();
    QString routerCol = ui->numCols->text();
    int numOfRouters = routerRow.toInt() * routerCol.toInt();
    QString numOfRoutersStr = QString::number(numOfRouters);

    /***************** ../booksim2-master/ *********************/
    QProcess::execute ("sed -i \"/#define numRouters / c #define numRouters " + numOfRoutersStr + "\" ../booksim2-master/src/main.cpp");
    QProcess::execute ("sed -i \"/#define numRouters / c #define numRouters " + numOfRoutersStr + "\" ../booksim2-master/src/routers/iq_router.cpp");
    QProcess::execute ("sed -i \"/#define numRouters / c #define numRouters " + numOfRoutersStr + "\" ../booksim2-master/src/routers/socket_lib.cpp");
//    QProcess::execute ("sed -i \"/_int_map\\\[\\\'max_samples\\\'\\\] = / c \\ \\ _int_map\\\[\\\'max_samples\\\'\\\] = "+ QString::number(inputConfigData[24].toInt()/10) + ";  //1000;   // maximum number of sample periods in a simulation //Sneha\" ../booksim2-master/src/booksim_config.cpp");
//    sed -i "/_int_map\[\"max_samples\"\] = / c \ \ _int_map\[\"max_samples\"\] = 600;  //1000;   // maximum number of sample periods in a simulation //Sneha" ./booksim_config.cpp
    QProcess::execute ("sed -i \"/int maxSamples = / c \\ \\ int maxSamples = " + inputConfigData[24] + ";  \" ../booksim2-master/src/booksim_config.cpp");
    QProcess::execute ("sed -i \"/int samplePeriod = / c \\ \\ int samplePeriod = " + inputConfigData[26] + ";  \" ../booksim2-master/src/booksim_config.cpp");





    /****************** ../PANE/ ******************/
    QProcess::execute ("sed -i \"/#define numRouters / c #define numRouters " + numOfRoutersStr + "\" ../PANE/client.cc");
    QProcess::execute ("sed -i \"/#define numRouters / c #define numRouters " + numOfRoutersStr + "\" ../PANE/controller.cc");
    QProcess::execute ("sed -i \"/#define numRouters / c #define numRouters " + numOfRoutersStr + "\" ../PANE/socket_lib.cc");
    QProcess::execute ("sed -i \"/int numRouters = / c \\\t\\\tint numRouters = " + numOfRoutersStr + ";\" ../PANE/controller.ned");
    QProcess::execute ("sed -i \"/int setNumRouters = / c \\\t\\\tint setNumRouters = " + numOfRoutersStr + ";\" ../PANE/network.ned");




    int mTopology = ui->topology->currentIndex();
    qDebug() <<mTopology <<"debug";

    switch(mTopology){
       case 0  :
            QProcess::execute ("sed -i \"/maxH=/ c maxH=" + routerRow + "\" ../SideScripts/Pane/ned_files/network_ned_connections_mesh.py");
            QProcess::execute ("sed -i \"/maxV=/ c maxV=" + routerCol + "\" ../SideScripts/Pane/ned_files/network_ned_connections_mesh.py");
            process.start("gnome-terminal -x sh -c \"(cd ../SideScripts/Pane/ned_files/ ; python network_ned_connections_mesh.py;)\"");
            process.waitForFinished();
            break; //optional
       case 1 :
            QProcess::execute ("sed -i \"/maxH=/ c maxH=" + routerRow + "\" ../SideScripts/Pane/ned_files/network_ned_connections_torus.py");
            QProcess::execute ("sed -i \"/maxV=/ c maxV=" + routerCol + "\" ..//SideScripts/Pane/ned_files/network_ned_connections_torus.py");
            process.start("gnome-terminal -x sh -c \"(cd ../SideScripts/Pane/ned_files/ ; python network_ned_connections_torus.py;)\"");
            process.waitForFinished();
            break; //optional

    }

    // Changing PANE/socket_lib.cc
    QProcess::execute ("sed -i \"/numRouters = / c numRouters = " + numOfRoutersStr + "\" ../SideScripts/Pane/socket_gen.py");
    process.start("gnome-terminal -x sh -c \"(cd ../SideScripts/Pane/ ; python socket_gen.py;)\"");
    process.waitForFinished();

    // Changing booksim/src/routers/socket_lib.cpp
    QProcess::execute ("sed -i \"/numRouters = / c numRouters = " + numOfRoutersStr + "\" ../SideScripts/Booksim/routers/socket_gen.py");
    process.start("gnome-terminal -x sh -c \"(cd ../SideScripts/Booksim/routers/ ; python socket_gen.py;)\"");
    process.waitForFinished();






    allowUserToRun = true;   // Restricts users from running project without building

    msgBox.setText("Build Successful!");
    msgBox.exec();
}

void MainWindow::on_run_clicked()
{
    QProcess mProcess;

    QMessageBox msgBox;
    msgBox.setText("First build the project!");
    if (!allowUserToRun) {
        msgBox.exec();
        return;
    }


    if (ui->singleRun->isChecked()) {

//        process.start("gnome-terminal -x sh -c \"(make -C ../PANE/; make sock -C ../PANE/; sleep 10; cd ../booksim2-master/src/;   ./run.sh > dump; cd ../../PANE/; ./PANE -u Cmdenv -f omnetpp.ini;)\"");
//        process.waitForFinished(-1);
//        mProcess.start("gnome-terminal -x sh -c \"(make -C ../PANE/; make sock -C ../PANE/; gnome-terminal -x sh -c \\\"(sleep 2; cd ../booksim2-master/src/;   ./run.sh;)\\\"; cd ../PANE/; ./PANE -u Cmdenv -f omnetpp.ini;)\"");
//        process.waitForFinished(-1);

        mProcess.start("gnome-terminal -x sh -c \"(cd  ../PANE/; ./run_new_my.sh;)\"");

//        while (true) {
//            qDebug() << QString::number(mProcess.waitForFinished());
//            if (mProcess.waitForFinished()) {
//                QProcess::execute("gnome-terminal -x sh -c \"(sleep 2; cd ../booksim2-master/src/;   ./run.sh;)\"");
//                QProcess::execute("gnome-terminal -x sh -c \"(cd ../PANE/; ./PANE -u Cmdenv -f omnetpp.ini;)\"");
//                break;
//            }

//        }
//        for (int i = 0; i < 30000 ; i++) {
//            qDebug() << QString::number(mProcess.waitForFinished());

//        }

//        process.start("gnome-terminal -x sh -c \"(sleep 2; cd ../booksim2-master/src/;   ./run.sh > dump;)\"");
//        process.waitForFinished();
//        process.start("gnome-terminal -x sh -c \"(cd ../PANE/; ./PANE -u Cmdenv -f omnetpp.ini;)\"");

//        process.waitForFinished();

        msgBox.setText("Running in progress...");
        msgBox.exec();

        canShowHeatMap = true;

    }
    else {
        SweepRunMethod *mSweepRunMethod = new SweepRunMethod();
        this->hide();
        mSweepRunMethod->show();
    }
}

void MainWindow::on_browseConfigFile_clicked()
{
    QString configFileName;
    configFileName = QFileDialog::getOpenFileName(this, tr("Open Configuration File"));
    ui->configFilePath->setText(configFileName);
}

void MainWindow::on_setClockDomains_clicked()
{
    SetClockDomains *mSetClockDomains = new SetClockDomains();

    QStringList routerMatrixData;
    routerMatrixData.append(ui->numRows->text());
    routerMatrixData.append(ui->numCols->text());

    connect(this, SIGNAL(submitRouterMatrixConfigSignal(QStringList)), mSetClockDomains, SLOT(submitRouterMatrixConfigSlot(QStringList)));
    emit this->submitRouterMatrixConfigSignal(routerMatrixData);

    mSetClockDomains->show();
}


void MainWindow::submitClockDomainDataSlot(const QStringList &clockDomainData) {
    clockDomainsClientValueArray.clear();
    assignedRoutersPerClockDomainArray.clear();

    qDebug() << clockDomainData;
    noOfClockDomains = clockDomainData[0].toInt();
    qDebug() << "No of Clock Domains: "<< noOfClockDomains;

    int k=1;
    for(int i=0; i<noOfClockDomains; i++) {
        QList<QString> mTempArray;
        clockDomainsClientValueArray.append(mTempArray);
        for(int j=0; j<4; j++) {
            clockDomainsClientValueArray[i].append(clockDomainData[k]);
            k++;
            qDebug() << "Clock Domain " << i << " client " << j << " :" << clockDomainsClientValueArray[i][j];
        }
    }

    for(int i=0; i<noOfClockDomains; i++) {
        assignedRoutersPerClockDomainArray.append(clockDomainData[k]);
        k++;
        qDebug() << "Assigned routers for Clock Domain " << i << " :" << assignedRoutersPerClockDomainArray[i];
    }



}

void MainWindow::on_clockDomainConfig_manual_toggled(bool checked)
{
    if (checked) {
        ui->setClockDomains->setVisible(true);
        defaultClockDomainConfig = false;
    }
    else {
        ui->setClockDomains->setVisible(false);
        defaultClockDomainConfig = true;
    }
}


void MainWindow::setDefaultClockDomainConfig() {
    QString routerRow = ui->numRows->text();
    QString routerCol = ui->numCols->text();
    int numOfRouters = routerRow.toInt() * routerCol.toInt();

    QList<QString> defaultClockDomainData;

    // Adding no of clock domains
    defaultClockDomainData.append("1");

    // Adding no of clock domain client value
    for (int i=0; i<4; i++) {
        defaultClockDomainData.append(QString::number(1));
    }

    QString routersAssigned;

    for (int i=0; i<numOfRouters; i++) {
        if (!routersAssigned.isEmpty()) {
            routersAssigned += ",";
        }
        routersAssigned += QString::number(i);
    }

    defaultClockDomainData.append(routersAssigned);

    qDebug() << defaultClockDomainData ;
    submitClockDomainDataSlot(defaultClockDomainData);

}


void MainWindow::on_viewHeatMap_clicked()
{
    QMessageBox mDialogBox;
    if (!canShowHeatMap){
        mDialogBox.setText("First run the project!");
        mDialogBox.exec();
        return;
    }



    QString viewRouterPacketsGeneratedTraffic = QString::number(ui->heatMap_routerPacketsGenerated->isChecked());
    QString viewRouterPacketsRetiredTraffic = QString::number(ui->heatMap_routerPacketsRetired->isChecked());
    QString viewRouterLinksTraffic = QString::number(ui->heatMap_routerLinks->isChecked());

    if (!(ui->heatMap_routerPacketsGenerated->isChecked() || ui->heatMap_routerLinks->isChecked() || ui->heatMap_routerPacketsRetired->isChecked())) {
        mDialogBox.setText("Select atleast one traffic type!");
        mDialogBox.exec();
        return;
    }



    QStringList routerData;

    /*************  configData index mentioned on  ********************************/
    /*************  the right side for retriving   ********************************/
    /*************  data from signal-slot connection ******************************/

    routerData << ui->numRows->text();
    routerData << ui->numCols->text();

    routerData << viewRouterPacketsGeneratedTraffic;
    routerData << viewRouterPacketsRetiredTraffic;
    routerData << viewRouterLinksTraffic;

    HeatMap *mHeatMap = new HeatMap();
    connect(this, SIGNAL(submitRouterDataToHeatMapSignal(QStringList)), mHeatMap, SLOT(submitRouterDataToHeatMapSlot(QStringList)));
    emit this->submitRouterDataToHeatMapSignal(routerData);
    mHeatMap->show();
}
