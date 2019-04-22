#include "heatmap.h"
#include "ui_heatmap.h"

#include "qdebug.h"
#include "qpainter.h"
#include <QDesktopWidget>
#include <QPrinter>
#include <QPrintDialog>
#include <QThread>
#include <QLabel>
#include <QFile>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QPrinter>
#include <QPrintDialog>

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
#include <QMap>




QPainter *mPainter;

//QList<QString> gradientList = {"#00D2E0", "#00E0D6", "#01E1BF", "#01E1A8", "#02E291", "#02E37A", "#03E363", "#04E44C", "#04E535", "#04E535", "#05E51D", "#05E606", "#1DE706", "#35E707", "#4EE807", "#66E908", "#7FE908", "#97EA09", "#B0EB0A", "#C8EB0A", "#E1EC0B", "#EDE00C", "#EDC90C", "#EEB20D", "#EF9B0E", "#F06C0F", "#F15510", "#F13E10", "#F22711", "#F21114"};
//QList<QString> gradientList = {"#07edb4", "#06ecac", "#06eca3", "#06ec9a", "#06ec91", "#06ec88", "#06ec7f", "#06ec76", "#06ec6d", "#05ec64", "#05eb5b", "#05eb52", "#05eb49", "#05eb40", "#05eb37", "#05eb2e", "#05eb25", "#05eb1c", "#04eb13", "#04ea0a", "#07ea04", "#10ea04", "#19ea04", "#21ea04", "#2aea04", "#33ea04", "#3bea04", "#44ea03", "#4de903", "#56e903", "#5ee903", "#67e903", "#70e903", "#79e903", "#81e903", "#8ae903", "#93e902", "#9be802", "#a4e802", "#ade802", "#b6e802", "#bee802", "#c7e802", "#d0e802", "#d9e802", "#e1e801", "#e7e501", "#e7dc01", "#e7d301", "#e7ca01", "#e7c101", "#e7b801", "#e7af01", "#e7a601", "#e79d00", "#e69400", "#e68b00", "#e68200", "#e67900", "#e67000", "#e66700", "#e65e00", "#e65500", "#e64c00", };
QList<QString> gradientList;
QList<QString> gradientListRouterGenerated;
QList<QString> gradientListRouterRetired;
QList<QString> gradientListRouterLinks;

QList<QList<int>> routerLinksDataArray;
QList<QList<int>> routerPacketsDataArray;

QList<QList <QMap <QString, int>>> horizontalLinkValues;
QList<QList <QMap <QString, int>>> verticalLinkValues;
QList<QList <QMap <QString, int>>> routerPacketValues;

QList<double> colorGeneratorValuesRouterGenerated;
QList<double> colorGeneratorValuesRouterRetired;
QList<double> colorGeneratorValuesLinks;

double minValGenerated;
double maxValGenerated;

double minValRetired;
double maxValRetired;

double minValLinks;
double maxValLinks;

int routerRows;
int routerCols;
int totalNumberOfPacketsGenerated = 782;



bool routersGeneratedTraffic = false;
bool routersRetiredTraffic = false;
bool routerLinksTaffic = false;

//int gradientIn

QList<double> minMaxScaleVal;

int screenWidth;


/**************************************************
 *
 * Dimensions of arrows     = 90    -x, 30  -y;
 * Dimensions of routers    = 160   -x, 80  -y;
 * Gap between routers      = 160   -x, 100 -y;
 *
 * ************************************************
 */



int routerWidth = 80;
int routerHeight = 80;
int arrowLength = 65;
int arrowBreadth = 20;
int routerGapsX = 100;
int routerGapsY = 100;






HeatMap::HeatMap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeatMap)
{
    ui->setupUi(this);

    rec = QApplication::desktop()->screenGeometry();
    screenHeight = rec.height();
    screenWidth = rec.width();


    this->resize(screenWidth,screenHeight);
    this->showMaximized();

}

HeatMap::~HeatMap()
{
    delete ui;
}


void HeatMap::submitRouterDataToHeatMapSlot(const QStringList &routerData) {
    routerRows = routerData[0].toInt();
    routerCols = routerData[1].toInt();

    if (routerData[2] == "1") {
        routersGeneratedTraffic = true;
    }
    else {
        routersGeneratedTraffic = false;
    }
    if (routerData[3] == "1") {
        routersRetiredTraffic = true;
    }
    else {
        routersRetiredTraffic = false;
    }
    if (routerData[4] == "1") {
        routerLinksTaffic = true;
    }
    else {
        routerLinksTaffic = false;
    }




    addHeader();
    addTrafficCanvas();
    addSideNav();


}


void HeatMap::addHeader() {

    header = new QGraphicsScene();   // Инициализируем графическую сцену

    QGraphicsView *mGraphicViewHeader;
    mGraphicViewHeader = ui->header;
    mGraphicViewHeader->setScene(header);  // Устанавливаем графическую сцену в graphicsView
    mGraphicViewHeader->setRenderHint(QPainter::Antialiasing);    // Устанавливаем сглаживание
    mGraphicViewHeader->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по вертикали
    mGraphicViewHeader->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по горизонтали



//    QTransform transform = this->transform();

//    int sideNavHeight = 250;
//    mGraphicViewHeader->move(QPoint(-5, screenHeight - sideNavHeight));
    mGraphicViewHeader->resize(screenWidth - 250, mGraphicViewHeader->height());
//    ui->print->setFixedWidth(screenWidth - 250);
    ui->print->move(QPoint((screenWidth - 250)/2 - 10, 20));
    ui->print->setStyleSheet("QPushButton {border:none; background:#01E1A8; color: #fff; cursor:pointer;} QPushButton:hover:!pressed {background:transparent; border: 1px solid #01E1A8; color: #01E1A8;}");


}

void HeatMap::addSideNav() {

    sidenav = new QGraphicsScene();   // Инициализируем графическую сцену

    QGraphicsView *mGraphicViewSideNav;
    mGraphicViewSideNav = ui->sidenav;
    mGraphicViewSideNav->setScene(sidenav);  // Устанавливаем графическую сцену в graphicsView
    mGraphicViewSideNav->setRenderHint(QPainter::Antialiasing);    // Устанавливаем сглаживание
    mGraphicViewSideNav->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по вертикали
    mGraphicViewSideNav->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по горизонтали



//    QTransform transform = this->transform();

//    int mGraphicViewContainer = screenHeight - mGraphicViewHeader->y();
    int sideNavWidth = 250;
    mGraphicViewSideNav->move(QPoint(screenWidth - sideNavWidth, -5));
    mGraphicViewSideNav->resize(sideNavWidth, screenHeight+10);
    ui->scale->setFixedWidth(sideNavWidth);
    ui->scale->move(QPoint(mGraphicViewSideNav->x(), 20));

//    sidenav->setSceneRect(-250,-30,500,35); // Устанавливаем область графической сцены

    sidenav->addLine(-600,0,600,0,QPen(Qt::transparent));   // Добавляем горизонтальную линию через центр
    sidenav->addLine(0,-250,0,250,QPen(Qt::transparent));   // Добавляем вертикальную линию через центр



    QList<QString> gradientList = {"#06b830", "#09b62f", "#0cb42e", "#0fb22e", "#12b12d", "#15af2d", "#18ad2c", "#1bac2b", "#1eaa2b", "#22a82a", "#25a62a", "#28a529", "#2ba328", "#2ea128", "#31a027", "#349e27", "#379c26", "#3a9a25", "#3e9925", "#419724", "#449524", "#479423", "#4a9222", "#4d9022", "#508e21", "#538d21", "#568b20", "#5a891f", "#5d881f", "#60861e", "#63841e", "#66821d", "#69811c", "#6c7f1c", "#6f7d1b", "#727c1b", "#767a1a", "#797819", "#7c7619", "#7f7518", "#827318", "#857117", "#887016", "#8b6e16", "#8e6c15", "#926a15", "#956914", "#986713", "#9b6513", "#9e6412", "#a16212", "#a46011", "#a75e10", "#aa5d10", "#ae5b0f", "#b1590f", "#b4580e", "#b7560d", "#ba540d", "#bd520c", "#c0510c", "#c34f0b", "#c64d0a", "#ca4c0a", "#cd4a09", "#d04809", "#d34608", "#d64507", "#d94307", "#dc4106", "#df4006", "#e23e05", "#e63c04", "#e93a04", "#ec3903", "#ef3703", "#f23502", "#f53401", "#f83201", "#fb3000", "#ff2f00"};

    int sizeofgradientlist = gradientList.size();

    int scaleHeight = screenHeight*0.7;
    int scaleOffsetY = -scaleHeight*0.5;
    int scaleblockheight = scaleHeight/20.0;
    int gradientIncrementIndex = sizeofgradientlist/20.0;


    double valueMultiplier = totalNumberOfPacketsGenerated/100.0;
    int scaleOffsetInc = 30;

    if (routersGeneratedTraffic) {
        for (int i=0; i<20; i++) {
            QPolygon polygon;   // Using Polygon class, to draw the triangle
            polygon << QPoint(0, 0) << QPoint(40, 0) << QPoint(40, scaleblockheight) << QPoint(0,scaleblockheight);
            polygon.translate(QPoint(scaleOffsetInc, scaleOffsetY + scaleblockheight*i));

            QString colorHexCode = gradientList[gradientIncrementIndex*i];
            sidenav->addPolygon(polygon, QColor(colorHexCode), QColor(colorHexCode));

        }
        addScaleValues(scaleOffsetInc, 0, QString::number(minMaxScaleVal[0]*valueMultiplier), QString::number(minMaxScaleVal[1]*valueMultiplier), "G\ne\nn\ne\nr\na\nt\ne\nd\n \nP\na\nc\nk\ne\nt\ns");

        scaleOffsetInc += 60;
    }


    if (routersRetiredTraffic) {
        for (int i=0; i<20; i++) {
            QPolygon polygon;   // Using Polygon class, to draw the triangle
            polygon << QPoint(0, 0) << QPoint(40, 0) << QPoint(40, scaleblockheight) << QPoint(0,scaleblockheight);
            polygon.translate(QPoint(scaleOffsetInc, scaleOffsetY + scaleblockheight*i));

            QString colorHexCode = gradientList[gradientIncrementIndex*i];
            sidenav->addPolygon(polygon, QColor(colorHexCode), QColor(colorHexCode));

        }
        addScaleValues(scaleOffsetInc, 0, QString::number(minMaxScaleVal[2]*valueMultiplier), QString::number(minMaxScaleVal[3]*valueMultiplier), "R\ne\nt\ni\nr\ne\nd\n \nP\na\nc\nk\ne\nt\ns");

        scaleOffsetInc += 60;
    }


    if(routerLinksTaffic) {
        for (int i=0; i<20; i++) {
            QPolygon polygon;   // Using Polygon class, to draw the triangle
            polygon << QPoint(0, 0) << QPoint(40, 0) << QPoint(40, scaleblockheight) << QPoint(0,scaleblockheight);
            polygon.translate(QPoint(scaleOffsetInc, scaleOffsetY + scaleblockheight*i));

            QString colorHexCode = gradientList[gradientIncrementIndex*i];
            sidenav->addPolygon(polygon, QColor(colorHexCode), QColor(colorHexCode));

        }
        addScaleValues(scaleOffsetInc, 0, QString::number(minMaxScaleVal[4]*valueMultiplier), QString::number(minMaxScaleVal[5]*valueMultiplier), "L\ni\nn\nk\ns");
    }







}


void HeatMap::addScaleValues(int labelOffsetX, int labelOffsetY, QString minVal, QString maxVal, QString scaleName) {
    int scaleHeight = screenWidth*0.7;
    int scaleOffsetY = -scaleHeight*0.5;

    QLabel *scaleMinLabel = (new QLabel(minVal));
    sidenav->addWidget(scaleMinLabel);
    scaleMinLabel->setStyleSheet("QLabel {background: transparent; color: #fff}");
    scaleMinLabel->move(QPoint(labelOffsetX + 15, scaleOffsetY/2 -13));

    QLabel *scaleMaxLabel = (new QLabel(maxVal));
    sidenav->addWidget(scaleMaxLabel);
    scaleMaxLabel->setStyleSheet("QLabel {background: transparent; color: #fff}");
    scaleMaxLabel->move(QPoint(labelOffsetX + 15, -scaleOffsetY/2 - 13));

    QLabel *scaleNameLabel = (new QLabel(scaleName));
    sidenav->addWidget(scaleNameLabel);
    scaleNameLabel->setStyleSheet("QLabel {background: transparent; color: #fff}");
    scaleNameLabel->move(QPoint(labelOffsetX + 15, scaleOffsetY + scaleHeight/2 - 140));

//    qDebug() << minMaxScaleVal;
//        qDebug() <<temp;
}


int routerDataPosX;
int routerDataPosY;
void HeatMap::addTrafficCanvas() {
    trafficCanvas = new QGraphicsScene();   // Инициализируем графическую сцену

    QGraphicsView *mGraphicViewTrafficCanvas;
    mGraphicViewTrafficCanvas = ui->trafficCanvas;
//    ui->graphicsView->width() = width;
    mGraphicViewTrafficCanvas->setScene(trafficCanvas);  // Устанавливаем графическую сцену в graphicsView
    mGraphicViewTrafficCanvas->setRenderHint(QPainter::Antialiasing);    // Устанавливаем сглаживание
    mGraphicViewTrafficCanvas->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn); // Отключаем скроллбар по вертикали
    mGraphicViewTrafficCanvas->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn); // Отключаем скроллбар по горизонтали

//    mGraphicViewHeader->resize(screenWidth, mGraphicViewHeader->height());

//    trafficCanvas->setSceneRect(-250,-25,1000,1000); // Устанавливаем область графической сцены

    int mGraphicViewContainer = screenHeight - mGraphicViewTrafficCanvas->y();
    mGraphicViewTrafficCanvas->resize(screenWidth, mGraphicViewContainer);


    routerDataPosX = -((screenWidth/2));
    routerDataPosY = -(mGraphicViewContainer/2  - 100 );
//    routerDataPosX = 0;
//    routerDataPosY = 10;
    trafficCanvas->addLine(-600,0,1000,0,QPen(Qt::transparent));   // Добавляем горизонтальную линию через центр
    trafficCanvas->addLine(0,-300,0,800,QPen(Qt::transparent));   // Добавляем вертикальную линию через центр



//    mGraphicViewTrafficCanvas->move(routerCanvasPositionX, routerCanvasPositionY);

    getRouterStats();

//    mPainter = painter;
//    mPainter->setPen(Qt::transparent);

    minValGenerated = findMinMax(colorGeneratorValuesRouterGenerated)[0];
    maxValGenerated = findMinMax(colorGeneratorValuesRouterGenerated)[1];
    gradientListRouterGenerated = setColorGradientSamples(colorGeneratorValuesRouterGenerated);
    minMaxScaleVal.append(minValGenerated);
    minMaxScaleVal.append(maxValGenerated);

    minValRetired = findMinMax(colorGeneratorValuesRouterRetired)[0];
    maxValRetired = findMinMax(colorGeneratorValuesRouterRetired)[1];
    gradientListRouterRetired = setColorGradientSamples(colorGeneratorValuesRouterRetired);
    minMaxScaleVal.append(minValRetired);
    minMaxScaleVal.append(maxValRetired);

    minValLinks = findMinMax(colorGeneratorValuesLinks)[0];
    maxValLinks = findMinMax(colorGeneratorValuesLinks)[1];
    gradientListRouterLinks = setColorGradientSamples(colorGeneratorValuesLinks);
    minMaxScaleVal.append(minValLinks);
    minMaxScaleVal.append(maxValLinks);

    qDebug() << minMaxScaleVal;

    paintRouterMatrix(routerRows,routerCols, routerPacketValues);
    paintHorizontalSignalPathMatrix(routerRows,routerCols - 1, horizontalLinkValues);
    paintVerticalSignalPathMatrix(routerRows - 1, routerCols, verticalLinkValues);
}



void HeatMap::routerLinksDataArrayInit() {

    QList<int> tempLinks;
    for (int i=0; i<routerRows; i++) {
        for (int j=0; j<routerCols; j++) {

            if(i > 0) {
                tempLinks.clear();
                tempLinks.append(j + routerRows*i);
                tempLinks.append(j + routerRows*(i-1));
                tempLinks.append(0);
                routerLinksDataArray.append(tempLinks);
            }

            if( j%routerRows != 0 ) {
                tempLinks.clear();
                tempLinks.append(j + routerRows*i);
                tempLinks.append(j + routerRows*i - 1);
                tempLinks.append(0);
                routerLinksDataArray.append(tempLinks);
            }

            if((j+1)%routerRows != 0 && j <routerCols-1) {
                tempLinks.clear();
                tempLinks.append(j + routerRows*i);
                tempLinks.append(j + routerRows*i + 1);
                tempLinks.append(0);
                routerLinksDataArray.append(tempLinks);
            }

            if(i < routerRows && i<routerRows-1) {
                tempLinks.clear();
                tempLinks.append(j + routerRows*i);
                tempLinks.append(j + routerRows*(i+1));
                tempLinks.append(0);
                routerLinksDataArray.append(tempLinks);
            }
        }
    }

//    qDebug() << routerLinksDataArray;
}



void HeatMap::getRouterStats() {
    routerLinksDataArray.clear();
    routerPacketsDataArray.clear();


    routerLinksDataArrayInit();

//    colorGeneratorValues.clear();

    QFile file("../PANE/dump/singleRunStats");
//    QFile file("../RouterLinkStats");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);


    while(!in.atEnd()) {
        QString line = in.readLine();

        QStringList temp_links;
        QStringList temp_routers;

        temp_links = line.split("Router:[");
        temp_routers = line.split("Router[");





//        QList<int> tempRouterLinks;
        QList<int> tempRouterPackets;

        if (temp_links.size() > 1) {
            QList<int> tempLinks;
            temp_links = temp_links[1].split("]\t->\t[");


//            tempRouterLinks.append((temp_links[0]).toInt());
            tempLinks.append((temp_links[0]).toInt());

            temp_links = temp_links[1].split("] = ");
//            tempRouterLinks.append(temp_links[0].toInt());
            tempLinks.append(temp_links[0].toInt());

//            tempRouterLinks.append(temp_links[1].toInt());
            tempLinks.append(0);

            routerLinksDataArray[routerLinksDataArray.indexOf(tempLinks)][2] = temp_links[1].toInt();
//            routerLinksDataArray.append(tempRouterLinks);
        }

        if (temp_routers.size() > 1) {
            if (temp_routers[1].split("# Generated\t\t# Retired").size() <2) {

                temp_routers = temp_routers[1].split("]\t\t\t");
                tempRouterPackets.append((temp_routers[0]).toInt());
                temp_routers = temp_routers[1].split("\t\t\t");
                tempRouterPackets.append(temp_routers[0].toInt());
                tempRouterPackets.append(temp_routers[1].toInt());
                routerPacketsDataArray.append(tempRouterPackets);
            }
        }

//        model->appendRow(fields);

    }


    file.close();

//    qDebug() << routerLinksDataArray;
    qSort(routerLinksDataArray);
    // Sorting the defined array
//    qDebug() << routerLinksDataArray;

    createRouterPacketsData(routerPacketsDataArray);
    createHorizontalLinkData(routerLinksDataArray);
    createVerticalLinkData(routerLinksDataArray);

}




void HeatMap::createRouterPacketsData(QList<QList<int>> packetsData) {
    routerPacketValues.clear();
    QList<int> subLinkData;
    QList <QMap <QString, int>> tempRow;
    int i=0;
    foreach (subLinkData, packetsData) {
        i++;
        QMap <QString, int> tempCol;
        tempCol["generated"] = subLinkData[1];
        tempCol["retired"] = subLinkData[2];

        colorGeneratorValuesRouterGenerated.append(double(subLinkData[1]*100.0/totalNumberOfPacketsGenerated));
        colorGeneratorValuesRouterRetired.append(double(subLinkData[2]*100.0/totalNumberOfPacketsGenerated));

        tempRow.append(tempCol);


        if (i%(routerCols) == 0) {
            i=0;
            routerPacketValues.append(tempRow);
//            qDebug() << tempRow;
            tempRow.clear();
        }
    }


}

void HeatMap::createHorizontalLinkData(QList<QList<int>> linkData) {
    horizontalLinkValues.clear();
    QList<int> subLinkData;
    QList <QMap <QString, int>> tempRow;
    int i=0;
    int j=0;
    foreach (subLinkData, linkData) {
        if (abs(subLinkData[0] - subLinkData[1]) == 1) {

            i++;



            colorGeneratorValuesLinks.append(double(subLinkData[2]*100.0/totalNumberOfPacketsGenerated));

            QMap <QString, int> tempCol;
            if (subLinkData[0] < subLinkData[1]) {
                tempCol["right"] = subLinkData[2];
//                qDebug() << subLinkData[0] << "->" << subLinkData[1] << " = " << subLinkData[2];
                tempRow.append(tempCol);
            }
            else {
//                tempCol["left"] = subLinkData[2];
//                qDebug() << subLinkData[1] << "<-" << subLinkData[0] << " = " << subLinkData[2];
                tempRow[j]["left"] = subLinkData[2];
                j++;

            }


            if (i%(routerCols*2 - 2) == 0) {
                i=0;
                j=0;
                horizontalLinkValues.append(tempRow);
//                qDebug() << tempRow;
                tempRow.clear();
            }


//            qDebug() << subLinkData;
        }

    }


//    qDebug() << horizontalLinkValues;
}




void HeatMap::createVerticalLinkData(QList<QList<int>> linkData) {
    verticalLinkValues.clear();
    QList<int> subLinkData;
    QList <QMap <QString, int>> tempData;

    foreach (subLinkData, linkData) {
        if (abs(subLinkData[0] - subLinkData[1]) == routerCols) {


            colorGeneratorValuesLinks.append(double(subLinkData[2]*100.0/totalNumberOfPacketsGenerated));

            QMap <QString, int> tempCol;
            if (subLinkData[0] < subLinkData[1]) {
                tempCol["down"] = subLinkData[2];
//                qDebug() << subLinkData[0] << "\\/" << subLinkData[1] << " = " << subLinkData[2];
                tempData.append(tempCol);
            }
            else {
//                tempCol["up"] = subLinkData[2];
//                qDebug() << subLinkData[1] << "/\\" << subLinkData[0] << " = " << subLinkData[2];
                tempData[subLinkData[1]]["up"] = subLinkData[2];
            }


        }

    }

//    qDebug() << tempData << "\n\n";

    int k=0;
    for (int i=0; i<routerRows-1; i++) {
        QList <QMap <QString, int>> tempRow;
        for (int j=0; j<routerCols; j++) {
            tempRow.append(tempData[k]);
            k++;
        }
        verticalLinkValues.append(tempRow);
    }

//    qDebug() << verticalLinkValues;
}


QList<double> HeatMap::findMinMax(QList<double> colorGeneratorValues) {
    QList<double> tempMinMaxList;
    double min = colorGeneratorValues[0];
    double max = colorGeneratorValues[0];
    double sample;
    foreach (sample, colorGeneratorValues) {
        if (min > sample) {
            min = sample;
        }

        if (max < sample) {
            max = sample;
        }
    }

    tempMinMaxList.append(min);
    tempMinMaxList.append(max);
    return tempMinMaxList;
}



QList<QString> HeatMap::setColorGradientSamples(QList<double> colorGeneratorValues) {
    QList<QString> tempGradientList;
//    gradientList.clear();



//    qDebug() << colorGeneratorValues.size();
//    qDebug() << min << max;


    int theColorBegin = 0x06b830;
    int theColorEnd = 0xff2f00;

    int theNumSteps = colorGeneratorValues.size();
    if (theNumSteps>255){
        theNumSteps = 255;
    }


    theColorBegin = ((theColorBegin >= 0x000000) && (theColorBegin <= 0xffffff)) ? theColorBegin : 0x000000;
    theColorEnd = ((theColorEnd >= 0x000000) && (theColorEnd <= 0xffffff)) ? theColorEnd : 0xffffff;
    theNumSteps = ((theNumSteps > 0) && (theNumSteps < 256)) ? theNumSteps : 16;




    int theR0 = (theColorBegin & 0xff0000) >> 16;
    int theG0 = (theColorBegin & 0x00ff00) >> 8;
    int theB0 = (theColorBegin & 0x0000ff) >> 0;

    int theR1 = (theColorEnd & 0xff0000) >> 16;
    int theG1 = (theColorEnd & 0x00ff00) >> 8;
    int theB1 = (theColorEnd & 0x0000ff) >> 0;

    // return the interpolated value between pBegin and pEnd


    for (int i = 0; i <= theNumSteps; i++) {
        int theR = colorInterpolate(theR0, theR1, i, theNumSteps);
        int theG = colorInterpolate(theG0, theG1, i, theNumSteps);
        int theB = colorInterpolate(theB0, theB1, i, theNumSteps);

        int theVal = (((theR << 8) | theG) << 8) | theB;

        QString hexadecimal;
        hexadecimal.setNum(theVal,16);
        for(int j=hexadecimal.size(); j<6 ; j++){
            hexadecimal =  "0" + hexadecimal;
        }
        hexadecimal = "#" + hexadecimal;
        tempGradientList.append(hexadecimal);

    }

//    qDebug() << gradientList;
    return tempGradientList;

}

int HeatMap::colorInterpolate(int pBegin, int pEnd, int pStep,int pMax) {
    if (pBegin < pEnd) {
      return ((pEnd - pBegin) * (pStep * 1.0 / pMax)) + pBegin;
    }
    else {
      return ((pBegin - pEnd) * (1 - (pStep * 1.0 / pMax))) + pEnd;
    }
}


int HeatMap::getPreferredColor(int data, double min, double max, QList<double> colorGeneratorValues){
    int theNumSteps = colorGeneratorValues.size();
    if (theNumSteps>255){
        theNumSteps = 255;
    }
    double data_calc = double(data*100.0/totalNumberOfPacketsGenerated);
//    double sampling = double((max - min)*100.0/theNumSteps);
//    qDebug() << int((data_calc - min)*theNumSteps*1.0/(max - min));
    return ((data_calc - min)*theNumSteps*1.0/(max - min));
}







void HeatMap::paintRouterMatrix(int rows, int cols, QList<QList <QMap <QString, int>>> packetInfoMatrix) {
    int offsetX = routerDataPosX;
    int offsetY = routerDataPosY;

    QPoint offsets;

    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            offsets = QPoint(offsetX, offsetY);
            paintRouter(offsets, packetInfoMatrix[i][j]);
            offsetX += 180;
        }

        offsetX = routerDataPosX;
        offsetY += 180;
    }
}



void HeatMap::paintHorizontalSignalPathMatrix(int rows, int cols, QList<QList <QMap <QString, int>>> trafficMatrix) {
    int offsetX = routerWidth + (routerGapsX - arrowLength)/2 + routerDataPosX;
    int offsetY = (routerHeight - 2*arrowBreadth)/2 + routerDataPosY;

    QPoint offsets;

    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            offsets = QPoint(offsetX, offsetY);
            paintHorizontalSignalPath(offsets, trafficMatrix[i][j]);
            offsetX += 180;
        }

        offsetX = routerWidth + (routerGapsX - arrowLength)/2 + routerDataPosX;
        offsetY += 180;
    }
}

void HeatMap::paintVerticalSignalPathMatrix(int rows, int cols, QList<QList <QMap <QString, int>>> trafficMatrix) {
    int offsetX = (routerWidth - 2*arrowBreadth)/2 + routerDataPosX;
    int offsetY = routerHeight + (routerGapsY-arrowLength)/2 + routerDataPosY;

    QPoint offsets;

    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            offsets = QPoint(offsetX, offsetY);
            paintVerticalSignalPath(offsets, trafficMatrix[i][j]);
            offsetX += 180;
        }

        offsetX = (routerWidth - 2*arrowBreadth)/2 + routerDataPosX;
        offsetY += 180;
    }
}


void HeatMap::paintRouter(QPoint offsets, QMap<QString, int> routerPacketsInfo) {
    paintRouterUpper(offsets, routerPacketsInfo["generated"]);
    paintRouterLower(offsets, routerPacketsInfo["retired"]);
}

void HeatMap::paintHorizontalSignalPath(QPoint offsets, QMap<QString, int> horizontalSignalTraffic) {
    paintHorizontalArrowLeft(offsets, horizontalSignalTraffic["left"]);
    paintHorizontalArrowRight(offsets, horizontalSignalTraffic["right"]);
}

void HeatMap::paintVerticalSignalPath(QPoint offsets, QMap<QString, int> verticalSignalTraffic) {
    paintVerticalArrowUp(offsets, verticalSignalTraffic["up"]);
    paintVerticalArrowDown(offsets, verticalSignalTraffic["down"]);
}

void HeatMap::paintRouterUpper(QPoint offsets, int packetsCount) {

    QPolygon polygon;   // Using Polygon class, to draw the triangle
    // We put the coordinates of points in the polygonal model
    polygon << QPoint(0, 0) << QPoint(80, 0) << QPoint(0,80);
    polygon.translate(offsets);

    QString colorHexCode = "#b9b9b9";
    if (routersGeneratedTraffic) {
        int colorHexIndex = getPreferredColor(packetsCount, minValGenerated, maxValGenerated, colorGeneratorValuesRouterGenerated);
    //    qDebug() << colorGeneratorValuesRouterGenerated;
    //    qDebug() << colorHexIndex;
        colorHexCode = gradientListRouterGenerated[colorHexIndex];
    }

    trafficCanvas->addPolygon(polygon, QColor(colorHexCode), QColor(colorHexCode));
//    mPainter->setBrush(QColor(colorHexCode));     // We set the brush, which will render the object
//    mPainter->drawPolygon(polygon);  // Draw a triangle on a polygonal model


}

void HeatMap::paintRouterLower(QPoint offsets, int packetsCount) {

    QPolygon polygon;   // Using Polygon class, to draw the triangle
    // We put the coordinates of points in the polygonal model
    polygon << QPoint(80,0) << QPoint(80,80) << QPoint(0,80);
    polygon.translate(offsets);

    QString colorHexCode = "#b9b9b9";
    if (routersRetiredTraffic) {
        int colorHexIndex = getPreferredColor(packetsCount, minValRetired, maxValRetired, colorGeneratorValuesRouterRetired);
        //    qDebug() << colorGeneratorValuesRouterRetired;
        //    qDebug() << colorHexIndex;
        colorHexCode = gradientListRouterRetired[colorHexIndex];
    }

    trafficCanvas->addPolygon(polygon, QColor(colorHexCode), QColor(colorHexCode));
//    mPainter->setBrush(QColor(colorHexCode));     // We set the brush, which will render the object
//    mPainter->drawPolygon(polygon);  // Draw a triangle on a polygonal model

}

void HeatMap::paintHorizontalArrowRight(QPoint offsets, int trafficValue) {
    QPolygon polygon;   // Using Polygon class, to draw the triangle
    // We put the coordinates of points in the polygonal model
//    polygon << QPoint(100, -10) << QPoint(170, -10) << QPoint(170,-15) << QPoint(190,0) << QPoint(170,15) << QPoint(170,10) << QPoint(100,10);
    polygon << QPoint(0, 3) << QPoint(50, 3) << QPoint(50,0) << QPoint(65,10) << QPoint(50,20) << QPoint(50,17) << QPoint(0,17);
    polygon.translate(offsets);

    QString colorHexCode = "#b9b9b9";
    if (routerLinksTaffic) {
        int colorHexIndex = getPreferredColor(trafficValue, minValLinks, maxValLinks, colorGeneratorValuesLinks);
        //    qDebug() << colorGeneratorValuesLinks;
        //    qDebug() << colorHexIndex;
        colorHexCode = gradientListRouterLinks[colorHexIndex];
    }

    trafficCanvas->addPolygon(polygon, QColor(colorHexCode), QColor(colorHexCode));
//    mPainter->setBrush(QColor(colorHexCode));     // We set the brush, which will render the object
//    mPainter->drawPolygon(polygon);  // Draw a triangle on a polygonal model
}

void HeatMap::paintHorizontalArrowLeft(QPoint offsets, int trafficValue) {
    QPolygon polygon;   // Using Polygon class, to draw the triangle
    // We put the coordinates of points in the polygonal model
//    polygon << QPoint(100, 0) << QPoint(120, -15) << QPoint(120,-10) << QPoint(190,-10) << QPoint(190,10) << QPoint(120,10) << QPoint(120,15);
    polygon << QPoint(0, 10) << QPoint(15, 0) << QPoint(15,3) << QPoint(65,3) << QPoint(65,17) << QPoint(15,17) << QPoint(15,20);
    polygon.translate(QPoint(0, 20));
    polygon.translate(offsets);

    QString colorHexCode = "#b9b9b9";
    if (routerLinksTaffic) {
        int colorHexIndex = getPreferredColor(trafficValue, minValLinks, maxValLinks, colorGeneratorValuesLinks);
        //    qDebug() << colorGeneratorValuesLinks;
        //    qDebug() << colorHexIndex;
        colorHexCode = gradientListRouterLinks[colorHexIndex];
    }

    trafficCanvas->addPolygon(polygon, QColor(colorHexCode), QColor(colorHexCode));
//    mPainter->setBrush(QColor(colorHexCode));     // We set the brush, which will render the object
//    mPainter->drawPolygon(polygon);  // Draw a triangle on a polygonal model
}


void HeatMap::paintVerticalArrowUp(QPoint offsets, int trafficValue) {
    QPolygon polygon;   // Using Polygon class, to draw the triangle
    // We put the coordinates of points in the polygonal model
    polygon << QPoint(10, 0) << QPoint(20, 15) << QPoint(17,15) << QPoint(17,65) << QPoint(3,65) << QPoint(3,15) << QPoint(0,15);
    polygon.translate(QPoint(20, 0));
    polygon.translate(offsets);

    QString colorHexCode = "#b9b9b9";
    if (routerLinksTaffic) {
        int colorHexIndex = getPreferredColor(trafficValue, minValLinks, maxValLinks, colorGeneratorValuesLinks);
        //    qDebug() << colorHexIndex;
        colorHexCode = gradientListRouterLinks[colorHexIndex];
    }

    trafficCanvas->addPolygon(polygon, QColor(colorHexCode), QColor(colorHexCode));
//    mPainter->setBrush(QColor(colorHexCode));     // We set the brush, which will render the object
//    mPainter->drawPolygon(polygon);  // Draw a triangle on a polygonal model
}

void HeatMap::paintVerticalArrowDown(QPoint offsets, int trafficValue) {
    QPolygon polygon;   // Using Polygon class, to draw the triangle
    // We put the coordinates of points in the polygonal model
    polygon << QPoint(3, 0) << QPoint(17, 0) << QPoint(17,50) << QPoint(20,50) << QPoint(10,65) << QPoint(0,50) << QPoint(3,50);
    polygon.translate(offsets);

    QString colorHexCode = "#b9b9b9";
    if (routerLinksTaffic) {
        int colorHexIndex = getPreferredColor(trafficValue, minValLinks, maxValLinks, colorGeneratorValuesLinks);
        //    qDebug() << colorHexIndex;
        colorHexCode = gradientListRouterLinks[colorHexIndex];
    }

    trafficCanvas->addPolygon(polygon, QColor(colorHexCode), QColor(colorHexCode));
//    mPainter->setBrush(QColor(colorHexCode));     // We set the brush, which will render the object
//    mPainter->drawPolygon(polygon);  // Draw a triangle on a polygonal model
}







void HeatMap::on_print_clicked()
{
    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    dialog->setWindowTitle(tr("Print Document"));
//    if (editor->textCursor().hasSelection())
//        dialog->addEnabledOption(QAbstractPrintDialog::PrintSelection);
    if (dialog->exec() != QDialog::Accepted)
        return;
    QPainter painter;
    painter.begin(&printer);

    double xscale = printer.pageRect().width()/double(trafficCanvas->width());
    qDebug() << xscale;
    double yscale = printer.pageRect().height()/double(trafficCanvas->height());
    double scale = qMin(xscale, yscale);
    painter.translate(printer.paperRect().x() + printer.pageRect().width()/2,
                       printer.paperRect().y() + printer.pageRect().height()/2);
    painter.scale(scale, scale);
    painter.translate(-width()/2 + 200, -height());

    trafficCanvas->render(&painter);



    xscale = printer.pageRect().width()/double(trafficCanvas->width()/3);
    qDebug() << xscale;
    yscale = printer.pageRect().height()/double(sidenav->height());
    scale = qMin(xscale, yscale);
    painter.translate(printer.paperRect().x() + printer.pageRect().width()/2 + trafficCanvas->width()/3,
                       printer.paperRect().y() + printer.pageRect().height()/2);
    painter.scale(scale, scale);
    painter.translate(-width()/2 + 200, -height()/2);

    sidenav->render(&painter);
}

