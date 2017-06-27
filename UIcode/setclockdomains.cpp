#include "setclockdomains.h"
#include "ui_setclockdomains.h"
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
#include <QtWidgets>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QStackedLayout>



//QRect rec = QApplication::desktop()->screenGeometry();
//int heightSys = rec.height();
//int widthSys = rec.width();

//QVBoxLayout *Vlayout = new QVBoxLayout();
bool firstTime=true;


QList<QList <QLineEdit*>>  clockDomainsArray;
QList<QLineEdit*> assignedRoutersArray;
int generatedClockDomains;




SetClockDomains::SetClockDomains(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetClockDomains)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);



    ui->clear->setVisible(0);
    ui->submit->setVisible(0);
    ui->separator->setVisible(0);

    ui->noOfClockDomains->setValidator( new QIntValidator(0, 999, this) );


//    ui->header->setFixedWidth(this->width());

/*
    QWidget *controlsRestrictorWidget = ui->mWidget;
    controlsRestrictorWidget->setLayout(Vlayout);
    Vlayout->setSpacing(10);
*/



}

SetClockDomains::~SetClockDomains()
{
    delete ui;
}

void SetClockDomains::on_generate_clicked()
{


    generatedClockDomains = (ui->noOfClockDomains->text()).toInt();


    QWidget *controlsRestrictorWidget = ui->mWidget;






    QVBoxLayout *Vlayout = new QVBoxLayout();

    if (!firstTime) {

//        qDeleteAll(Vlayout->findChildren<QHBoxLayout *>());
//        qDeleteAll(controlsRestrictorWidget->findChildren<QVBoxLayout *>());
//        qDeleteAll(controlsRestrictorWidget->findChildren<QVBoxLayout *>());
    }







    controlsRestrictorWidget->setMinimumHeight(45 + generatedClockDomains*45);
    Vlayout->setSpacing(10);

    controlsRestrictorWidget->setLayout(Vlayout);





    QList<QHBoxLayout*> mHBoxLayoutArray;

    for(int i=0; i<generatedClockDomains; i++) {

        QList<QLineEdit*> mNextArray;
        clockDomainsArray.append(mNextArray);
        mHBoxLayoutArray.append(new QHBoxLayout());
        mHBoxLayoutArray[i]->setObjectName("clock_domain_" + QString::number(i));

        // Adding Clock Domain # label
        mHBoxLayoutArray[i]->addWidget(new QLabel("Clock domain #" + QString::number(i)));

        for(int j=0; j<4; j++) {

            QLineEdit *clockDomainClient = new QLineEdit();
            clockDomainClient->setPlaceholderText("Client " + QString::number(j));
            clockDomainClient->setAccessibleName("clock_domain_" + QString::number(i) +  "_client_" + QString::number(j));
            clockDomainClient->setObjectName("clock_domain_" + QString::number(i) +  "_client_" + QString::number(j));
            clockDomainClient->setValidator( new QIntValidator(1, 9, this));
            clockDomainsArray[i].append(clockDomainClient);
            mHBoxLayoutArray[i]->addWidget(clockDomainsArray[i][j]);

        }

        /*********** Adding Vertical line  *****************/
        QWidget *verticalLineWidget = new QWidget;
        verticalLineWidget->setFixedWidth(2);
        verticalLineWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        verticalLineWidget->setStyleSheet(QString("background-color: #c0c0c0;"));
        mHBoxLayoutArray[i]->addWidget(verticalLineWidget);
        /*********** Adding Vertical line end *****************/


        /*********** Adding Assigned routers # label  *****************/
        mHBoxLayoutArray[i]->addWidget(new QLabel("Clock domain #" + QString::number(i)));
         /*********** Adding Assigned routers # label Ends *****************/


        /*********** Adding Assigned routers # input textbox  *****************/
        QLineEdit *assignedRouters = new QLineEdit();
        assignedRouters->setPlaceholderText("# separated by commas");
        assignedRouters->setObjectName("assigned_routers_client_" + QString::number(i));
        assignedRoutersArray.append(assignedRouters);
        mHBoxLayoutArray[i]->addWidget(assignedRoutersArray[i]);
        /*********** Adding Assigned routers # input textbox ends *****************/



        //Adding Horizontal layout to vertical layout
        Vlayout->addLayout(mHBoxLayoutArray[i]);

        qDebug() << "Object Name: " <<mHBoxLayoutArray[i]->objectName();

    }





    firstTime = false;
    ui->generate->setEnabled(0);


    QPushButton *mSubmit = ui->submit;
    //mSubmit->pos().x();
    mSubmit->move(mSubmit->pos().x(), mSubmit->pos().y() + generatedClockDomains*45);

    QWidget *mSeparatorHorizontal = ui->separator;
    mSeparatorHorizontal->move(mSeparatorHorizontal->pos().x(), mSeparatorHorizontal->pos().y() + generatedClockDomains*45);

    ui->submit->setVisible(1);
    ui->separator->setVisible(1);
    ui->info_message->setVisible(0);
}








void SetClockDomains::on_clear_clicked()
{
    QWidget *controlsRestrictorWidget = ui->mWidget;
    controlsRestrictorWidget->layout()->deleteLater();
//        qDeleteAll(Vlayout->findChildren<QHBoxLayout *>());
//        qDeleteAll(controlsRestrictorWidget->findChildren<QVBoxLayout *>());
       qDeleteAll(controlsRestrictorWidget->findChildren<QVBoxLayout *>());

//        QList<QVBoxLayout *> lay = controlsRestrictorWidget->findChildren<QVBoxLayout *>();
//        foreach(QVBoxLayout * layout, lay)
//        {
//            delete layout;
//        }
//        controlsRestrictorWidget->hide();
//        this->update();
//        firstTime = true;

//        return;
//        QVBoxLayout *Vlayout = new QVBoxLayout();

       //        QList<QVBoxLayout *> lay = controlsRestrictorWidget->findChildren<QVBoxLayout *>();
       //        foreach(QVBoxLayout * layout, lay)
       //        {
       //            delete layout;
       //        }
       //        controlsRestrictorWidget->
       //        this->update();
       //        delete controlsRestrictorWidget;
       //        QWidget *controlsRestrictorWidget = new QWidget();
}

void SetClockDomains::on_submit_clicked()
{

    qDebug() << clockDomainsArray[0][0]->text() <<"Yo";

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
        QString assignedRouterStr;
        if (isRangeFormat(assignedRoutersArray[i]->text())) {
            assignedRouterStr = getListElementsFromRange(assignedRoutersArray[i]->text());
        }
        else {
            assignedRouterStr = assignedRoutersArray[i]->text();
        }
        clockDomainData << assignedRouterStr;
    }





    MainWindow *mMainWindow = new MainWindow;
    connect(this, SIGNAL(submitClockDomainSignal(QStringList)), mMainWindow, SLOT(submitClockDomainDataSlot(QStringList)));
    emit this->submitClockDomainSignal(clockDomainData);

    this->hide();
}

bool SetClockDomains::isRangeFormat(QString mString) {
    QList<QString> splittedList = mString.split('-');

    if (splittedList.size() > 1) {
        return true;
    }
    else {
        return false;
    }
}

QString SetClockDomains::getListElementsFromRange(QString mString) {
    QString mRange;
    QList<QString> splittedList = mString.split("-");

    int start = splittedList[0].toInt();
    int end = splittedList[1].toInt();

    for (int i = start; i < end + 1; i++) {
        if (!mRange.isEmpty()) {
            mRange += ",";
        }
        mRange +=QString::number(i);
    }

    return mRange;

}
