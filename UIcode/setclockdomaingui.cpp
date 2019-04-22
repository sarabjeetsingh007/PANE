#include "setclockdomaingui.h"
#include "ui_setclockdomaingui.h"
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
#include <QFileDialog>
#include <QLabel>
#include <QWidget>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QLineEdit>








SetClockDomainGUI::SetClockDomainGUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetClockDomainGUI)
{
    ui->setupUi(this);


    rec = widget.availableGeometry(widget.primaryScreen());

    this->setWindowState(Qt::WindowMaximized);





//    qDebug() << "App path : " << qApp->applicationDirPath();
}

SetClockDomainGUI::~SetClockDomainGUI()
{
    delete ui;
}



void SetClockDomainGUI::submitClockDomainDataToGUISlot(const QStringList &clockDomainData){
    qDebug() << "--------------------------------- SetClockDomainGUI -------------------------------------";
    qDebug() << clockDomainData;

    rows = clockDomainData[0].toInt();
    cols = clockDomainData[1].toInt();

    qDebug() << "Rows: " << rows;
    qDebug() << "Cols: " << cols;

    generatedClockDomains = clockDomainData[2].toInt();


    clockDomainsClientValueArray.clear();
    assignedRoutersPerClockDomainArray.clear();

    int k=3;
    for(int i=0; i<generatedClockDomains; i++) {
        QList<QString> mTempArray;
        clockDomainsClientValueArray.append(mTempArray);
        for(int j=0; j<4; j++) {
            clockDomainsClientValueArray[i].append(clockDomainData[k]);
            k++;
            qDebug() << "Clock Domain " << i << " client " << j << " :" << clockDomainsClientValueArray[i][j];
        }
    }

    for(int i=0; i<generatedClockDomains; i++) {
        assignedRoutersPerClockDomainArray.append(clockDomainData[k]);
        k++;
        qDebug() << "Assigned routers for Clock Domain " << i << " :" << assignedRoutersPerClockDomainArray[i];
    }












    createRouterMatrix();
    createClockDomainList();
    this->show();
}




void SetClockDomainGUI::routersButtonGroup(QAbstractButton *mButton )
{

        qDebug() << "Clicked router: ";
        qDebug() << mButton->objectName();
        QString routerName = mButton->objectName();

        ui->routersFrame->setStyleSheet("QWidget#" + routerName + " {border-image: url(selected.png) 0 0 0 0 stretch stretch;}");
}



void SetClockDomainGUI::createRouterMatrix() {


    routerMatrix.clear();
    routerMatrixClockDomain.clear();

    QButtonGroup *routerSelectors;
    routerSelectors = new QButtonGroup(this);

    QFrame *routersFrame = ui->routersFrame;
//    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
//    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    routersFrame->resize(rec.height() - 150, rec.height() - 150);

//    routersFrame->setStyleSheet({""});


    for(int i=0; i<rows; i++) {
        QList<QPushButton*> subRouterList;
        QList<QString> subRouterClockDomainData;
        for (int j=0; j<cols; j++) {
            QPushButton* button = new QPushButton(QString(""), routersFrame);
            subRouterList.append(button);
            button->move(QPoint(20 + 80*j , 20 + 80*i));
            button->setStyleSheet({"border: 0px solid transparent; height:40; width:40; background: #9f9f9f;"});
            button->setObjectName("router_" + QString::number(i) + "_" + QString::number(j));
            routerSelectors->addButton(button);
            subRouterClockDomainData.append("not_assgined");
        }
        routerMatrix.append(subRouterList);
        routerMatrixClockDomain.append(subRouterClockDomainData);
    }


    QString assignedRoutersTemp;
    int colorIndexTemp = 0;
    foreach(assignedRoutersTemp, assignedRoutersPerClockDomainArray) {
        QStringList routerKeyList = assignedRoutersTemp.split(",");
        QString routerKey;
        foreach(routerKey, routerKeyList) {

            int rowKey = routerKey.toInt() / cols;
            int colKey = routerKey.toInt() % cols;
            routerMatrix[rowKey][colKey]->setStyleSheet({"border: 0px solid transparent; height:40; width:40; background: " + selectionColors[colorIndexTemp] + ";"});
            routerMatrixClockDomain[rowKey][colKey] = QString::number(colorIndexTemp);
        }
        colorIndexTemp ++;
    }



    connect(routerSelectors, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(routerOnSelected(QAbstractButton*)));



}

void SetClockDomainGUI::createClockDomainList() {
    QWidget *clockDomainsWidget = ui->clockDomainsWidget;


    QVBoxLayout *Vlayout = new QVBoxLayout();

//    generatedClockDomains = 3;   // Manual mode off

    clockDomainsWidget->setMinimumHeight(45 + generatedClockDomains*45);
    clockDomainsWidget->resize(rec.height() - 150, clockDomainsWidget->height());
    Vlayout->setSpacing(10);



    QPushButton *mSubmit = ui->submit;
    mSubmit->move(mSubmit->pos().x(), mSubmit->pos().y() + generatedClockDomains*45);
    mSubmit->setStyleSheet("QPushButton {border:none; background:#01E1A8; color: #fff; cursor:pointer;} QPushButton:hover:!pressed {background:transparent; border: 1px solid #01E1A8; color: #01E1A8;}");



    clockDomainsWidget->setLayout(Vlayout);




    QButtonGroup *clockDomainSelectors;
    clockDomainSelectors = new QButtonGroup(this);


    QList<QHBoxLayout*> mHBoxLayoutArray;

    for(int i=0; i<generatedClockDomains; i++) {

        QList<QLineEdit*> mNextArray;
        clockDomainsArray.append(mNextArray);
        mHBoxLayoutArray.append(new QHBoxLayout());
        mHBoxLayoutArray[i]->setObjectName("clock_domain_" + QString::number(i));

        // Adding Clock Domain selection button
        QPushButton* button = new QPushButton("Clock domain #" + QString::number(i));
        button->setObjectName(QString::number(i));
        button->setStyleSheet({"border:none; height:40; color: #fff; padding: 0 20px; background:" + selectionColors[i] + ";"});
        clockDomainSelectionButton.append(button);

        clockDomainSelectors->addButton(button);

        mHBoxLayoutArray[i]->addWidget(button);

        for(int j=0; j<4; j++) {

            QLineEdit *clockDomainClient = new QLineEdit();
            clockDomainClient->setPlaceholderText("Client " + QString::number(j));
            clockDomainClient->setAccessibleName("clock_domain_" + QString::number(i) +  "_client_" + QString::number(j));
            clockDomainClient->setObjectName("clock_domain_" + QString::number(i) +  "_client_" + QString::number(j));
            clockDomainClient->setValidator( new QIntValidator(1, 9, this));

            clockDomainClient->setText(QString(clockDomainsClientValueArray[i][j]));

            clockDomainsArray[i].append(clockDomainClient);
            mHBoxLayoutArray[i]->addWidget(clockDomainsArray[i][j]);

        }


        //Adding Horizontal layout to vertical layout
        Vlayout->addLayout(mHBoxLayoutArray[i]);

        qDebug() << "Object Name: " <<mHBoxLayoutArray[i]->objectName();

    }

    connect(clockDomainSelectors, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(clockDomainOnSelected(QAbstractButton*)));
}

void SetClockDomainGUI::clockDomainOnSelected(QAbstractButton *mButton )
{

    qDebug() << "Clicked router: ";
    qDebug() << mButton->objectName();
    int clockDomainIndex = mButton->objectName().toInt();

    QPushButton* tempPushButton;
    foreach(tempPushButton, clockDomainSelectionButton) {
        tempPushButton->setStyleSheet("QPushButton {border: 0px solid transparent; height:40; color: #fff; padding: 0 20px; background:" + selectionColors[tempPushButton->objectName().toInt()] + ";}");
    }

    clockDomainSelectionButton[clockDomainIndex]->setStyleSheet("QWidget#" + QString::number(clockDomainIndex) + "{border: 2px solid black; height:40; color: #fff; padding: 0 20px; background:" + selectionColors[clockDomainIndex] + ";}");


    selectedClockDomainColor = selectionColors[clockDomainIndex];

    isClockDomainSelected =true;
    slectedClockdomainIndex = QString::number(clockDomainIndex);
}

void SetClockDomainGUI::routerOnSelected(QAbstractButton *mButton ) {
    QMessageBox mMessageBox;
    if (!isClockDomainSelected) {
        mMessageBox.setText("Please select a clock domain first!");
        mMessageBox.exec();
        return;
    }

    QList<QPushButton*> tempRow;
    foreach(tempRow, routerMatrix) {
        QPushButton* tempPushButton;
        foreach (tempPushButton, tempRow) {
            QColor currentColor = tempPushButton->palette().color(QWidget::backgroundRole());
            tempPushButton->setStyleSheet("QPushButton {border: 0px solid transparent; height:40; color: #fff; padding: 0 20px; background: " + currentColor.name() + ";}");
        }
    }
    mButton->setStyleSheet("QWidget {border: 2px solid black; height:40; color: #fff; padding: 0 20px; background:" + selectedClockDomainColor + ";}");

    QStringList clickedButtonOjectName = mButton->objectName().split("_");
    routerMatrixClockDomain[clickedButtonOjectName[1].toInt()][clickedButtonOjectName[2].toInt()] = slectedClockdomainIndex;

    qDebug() << routerMatrixClockDomain;
}








void SetClockDomainGUI::on_submit_clicked()
{
    QMessageBox mMessageBox;

    QStringList assignedRouterStrList;
    for(int i=0; i<generatedClockDomains; i++){
        assignedRouterStrList.append("");
    }

    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {
            if (routerMatrixClockDomain[i][j] == "not_assgined") {
                mMessageBox.setText("Please assign clock domains to all routers!");
                mMessageBox.exec();
                return;
            }

            if (!assignedRouterStrList[routerMatrixClockDomain[i][j].toInt()].isEmpty()) {
                assignedRouterStrList[routerMatrixClockDomain[i][j].toInt()] += ",";
            }
            assignedRouterStrList[routerMatrixClockDomain[i][j].toInt()] += QString::number(j + cols*i);
        }
    }



    QStringList clockDomainData;

    /*************  configData index mentioned on  ********************************/
    /*************  the right side for retriving   ********************************/
    /*************  data from signal-slot connection ******************************/

    clockDomainData << QString::number(generatedClockDomains);

    // Trasnfering generatedClockDomains clients data
    for(int i=0; i<generatedClockDomains; i++){
        for (int j=0;j<4;j++) {
            clockDomainData << clockDomainsArray[i][j]->text();
        }
    }

    // Transferring generated Clock Domain's assigned routers
    for(int i=0; i<generatedClockDomains; i++){
        clockDomainData << assignedRouterStrList[i];
    }


    qDebug() << "--------------------------- Submitting Clock Domain Data to Main Window----------------------------";
    qDebug() << assignedRouterStrList;


    MainWindow *mMainWindow = new MainWindow;
    connect(this, SIGNAL(submitClockDomainSignal(QStringList)), mMainWindow, SLOT(submitClockDomainDataSlot(QStringList)));
    emit this->submitClockDomainSignal(clockDomainData);

    this->hide();

}
