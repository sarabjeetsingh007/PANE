#include "configinput.h"
#include "ui_configinput.h"
#include "mainwindow.h"
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
#include <map>

#define PI 3.14159265


ConfigInput::ConfigInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigInput)
{
    ui->setupUi(this);

    //Setting fields
    ui->arbiters->setEditable(1);
    ui->VCallocator->setEditable(1);
    ui->switchAllocator->setEditable(1);
    ui->powerCalculation_PathToTechFile->setDisabled(1);

}

ConfigInput::~ConfigInput()
{
    delete ui;
}




void ConfigInput::on_simulationData_Synthetic_clicked()
{
    ui->simulationData_Real_PathToTraces->setDisabled(1);
    ui->simulationData_SyntheticDropdown->setEnabled(1);
}

void ConfigInput::on_simulationData_Real_clicked()
{
    ui->simulationData_SyntheticDropdown->setDisabled(1);
    ui->simulationData_Real_PathToTraces->setEnabled(1);
}

void ConfigInput::on_powerCalculation_clicked()
{
    if(!ui->powerCalculation->isChecked())
        ui->powerCalculation_PathToTechFile->setDisabled(1);
    else
        ui->powerCalculation_PathToTechFile->setEnabled(1);
}





//void ConfigInput::on_pushButton_clicked()
//{
////    QString configData ="xxxxxxxxxxxxxxxxxxx";
//    QStringList configData;
//    configData << "Arial" << "Helvetica" << "Times" << "Courier";

//    MainWindow *widget = new MainWindow;
////    connect(this, SIGNAL(mySignal(QMap<QString, QString>)), widget, SLOT(setConfigParamLinked(QMap<QString, QString>)));
////    connect(this, SIGNAL(foo()), widget, SLOT(bar1()));
//    connect(this, SIGNAL(mySignal(QStringList)), widget, SLOT(mySlot(QStringList)));
//    emit  this->mySignal(configData);
////    emit  this->mySignal(configData);
//    this->close();

//}



void ConfigInput::on_submitIPconfig_clicked()
{
    QStringList configData;

    /*************  configData index mentioned on  ********************************/
    /*************  the right side for retriving   ********************************/
    /*************  data from signal-slot connection ******************************/

    configData << ui->endPoints->text();                                        // 0
    configData << ui->routingFxn->text();                                       // 1
    configData << ui->noVCs->text();                                            // 2
    configData << ui->VCbufferSize->text();                                     // 3
    configData << QString::number(ui->waitForTailCredit->isChecked());          // 4
    configData << ui->VCallocator->currentText();                               // 5
    configData << ui->switchAllocator->currentText();                           // 6
    configData << ui->arbiters->currentText();                                  // 7
    configData << ui->creditDelay->text();                                      // 8
    configData << ui->routingDelay->text();                                     // 9
    configData << ui->VCallocatorDelay->text();                                 // 10
    configData << ui->switchAllocatorDelay->text();                             // 11
    configData << ui->inputSpeedUp->text();                                     // 12
    configData << ui->outputSpeedUp->text();                                    // 13
    configData << ui->internalSpeedUp->text();                                  // 14
    configData << QString::number(ui->VCbusyWhenFull->isChecked());             // 15
    configData << ui->simulationType->currentText();                            // 16
    configData << ui->packetSize->text();                                       // 17
    configData << QString::number(ui->simulationData_Synthetic->isChecked());   // 18
    configData << ui->simulationData_SyntheticDropdown->currentText();          // 19
    configData << QString::number(ui->simulationData_Real->isChecked());        // 20
    configData << ui->simulationData_Real_PathToTraces->text();                 // 21
    configData << QString::number(ui->powerCalculation->isChecked());           // 22
    configData << ui->powerCalculation_PathToTechFile->text();                  // 23
    configData << ui->maxSamples->text();                                       // 24
    configData << ui->injectionRate->text();                                    // 25
    configData << ui->samplePeriod->text();                                     // 26


    MainWindow *mMainWindow = new MainWindow;
    connect(this, SIGNAL(submitIpConfSignal(QStringList)), mMainWindow, SLOT(submitIpConfSlot(QStringList)));
    emit  this->submitIpConfSignal(configData);
    this->close();

    //mMainWindow->show();
//    mMainWindow->setWindowState(Qt::WindowMaximized);
    mMainWindow->setWindowState(Qt::WindowActive);

}
