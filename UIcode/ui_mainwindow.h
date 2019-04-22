/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label_6;
    QLabel *label_14;
    QComboBox *topology;
    QLabel *label_4;
    QLabel *label_3;
    QLineEdit *numCols;
    QLineEdit *numRows;
    QRadioButton *singleRun;
    QRadioButton *sweepRun;
    QLabel *label_5;
    QPushButton *setIPconfig;
    QPushButton *build;
    QFrame *line;
    QFrame *line_2;
    QPushButton *run;
    QLabel *label_15;
    QPushButton *browseConfigFile;
    QLineEdit *configFilePath;
    QPushButton *setClockDomains;
    QRadioButton *clockDomainConfig_default;
    QRadioButton *clockDomainConfig_manual;
    QLabel *label_7;
    QPushButton *viewHeatMap;
    QCheckBox *heatMap_routerPacketsGenerated;
    QCheckBox *heatMap_routerLinks;
    QCheckBox *heatMap_routerPacketsRetired;
    QFrame *line_3;
    QMenuBar *menuBar;
    QMenu *menuNetwork_Define;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QButtonGroup *runParametersButtonGroup;
    QButtonGroup *clockDomainRadioButtonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(744, 586);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(200, 20, 241, 51));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(50, 100, 91, 31));
        topology = new QComboBox(centralWidget);
        topology->setObjectName(QStringLiteral("topology"));
        topology->setGeometry(QRect(170, 100, 121, 31));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(390, 160, 131, 21));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(50, 160, 111, 16));
        numCols = new QLineEdit(centralWidget);
        numCols->setObjectName(QStringLiteral("numCols"));
        numCols->setGeometry(QRect(530, 160, 41, 21));
        numRows = new QLineEdit(centralWidget);
        numRows->setObjectName(QStringLiteral("numRows"));
        numRows->setGeometry(QRect(170, 160, 41, 21));
        singleRun = new QRadioButton(centralWidget);
        runParametersButtonGroup = new QButtonGroup(MainWindow);
        runParametersButtonGroup->setObjectName(QStringLiteral("runParametersButtonGroup"));
        runParametersButtonGroup->addButton(singleRun);
        singleRun->setObjectName(QStringLiteral("singleRun"));
        singleRun->setGeometry(QRect(80, 400, 112, 23));
        sweepRun = new QRadioButton(centralWidget);
        runParametersButtonGroup->addButton(sweepRun);
        sweepRun->setObjectName(QStringLiteral("sweepRun"));
        sweepRun->setGeometry(QRect(230, 400, 112, 23));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(50, 370, 111, 16));
        setIPconfig = new QPushButton(centralWidget);
        setIPconfig->setObjectName(QStringLiteral("setIPconfig"));
        setIPconfig->setGeometry(QRect(50, 210, 151, 31));
        build = new QPushButton(centralWidget);
        build->setObjectName(QStringLiteral("build"));
        build->setGeometry(QRect(610, 430, 121, 31));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(50, 70, 521, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(50, 450, 521, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        run = new QPushButton(centralWidget);
        run->setObjectName(QStringLiteral("run"));
        run->setGeometry(QRect(610, 480, 121, 31));
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(210, 210, 61, 31));
        browseConfigFile = new QPushButton(centralWidget);
        browseConfigFile->setObjectName(QStringLiteral("browseConfigFile"));
        browseConfigFile->setGeometry(QRect(280, 210, 161, 31));
        configFilePath = new QLineEdit(centralWidget);
        configFilePath->setObjectName(QStringLiteral("configFilePath"));
        configFilePath->setGeometry(QRect(450, 210, 121, 31));
        setClockDomains = new QPushButton(centralWidget);
        setClockDomains->setObjectName(QStringLiteral("setClockDomains"));
        setClockDomains->setGeometry(QRect(240, 330, 151, 31));
        clockDomainConfig_default = new QRadioButton(centralWidget);
        clockDomainRadioButtonGroup = new QButtonGroup(MainWindow);
        clockDomainRadioButtonGroup->setObjectName(QStringLiteral("clockDomainRadioButtonGroup"));
        clockDomainRadioButtonGroup->addButton(clockDomainConfig_default);
        clockDomainConfig_default->setObjectName(QStringLiteral("clockDomainConfig_default"));
        clockDomainConfig_default->setGeometry(QRect(80, 300, 112, 23));
        clockDomainConfig_default->setChecked(true);
        clockDomainConfig_manual = new QRadioButton(centralWidget);
        clockDomainRadioButtonGroup->addButton(clockDomainConfig_manual);
        clockDomainConfig_manual->setObjectName(QStringLiteral("clockDomainConfig_manual"));
        clockDomainConfig_manual->setGeometry(QRect(220, 300, 121, 23));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(50, 276, 171, 20));
        viewHeatMap = new QPushButton(centralWidget);
        viewHeatMap->setObjectName(QStringLiteral("viewHeatMap"));
        viewHeatMap->setGeometry(QRect(450, 490, 121, 31));
        heatMap_routerPacketsGenerated = new QCheckBox(centralWidget);
        heatMap_routerPacketsGenerated->setObjectName(QStringLiteral("heatMap_routerPacketsGenerated"));
        heatMap_routerPacketsGenerated->setGeometry(QRect(60, 490, 111, 31));
        heatMap_routerPacketsGenerated->setChecked(true);
        heatMap_routerLinks = new QCheckBox(centralWidget);
        heatMap_routerLinks->setObjectName(QStringLiteral("heatMap_routerLinks"));
        heatMap_routerLinks->setGeometry(QRect(320, 490, 111, 31));
        heatMap_routerLinks->setChecked(true);
        heatMap_routerPacketsRetired = new QCheckBox(centralWidget);
        heatMap_routerPacketsRetired->setObjectName(QStringLiteral("heatMap_routerPacketsRetired"));
        heatMap_routerPacketsRetired->setGeometry(QRect(200, 490, 91, 31));
        heatMap_routerPacketsRetired->setChecked(true);
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(570, 100, 41, 421));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 744, 22));
        menuNetwork_Define = new QMenu(menuBar);
        menuNetwork_Define->setObjectName(QStringLiteral("menuNetwork_Define"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuNetwork_Define->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:20pt; color:#901c1c;\">PANE</span></p></body></html>", Q_NULLPTR));
        label_14->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">TOPOLOGY:</span></p></body></html>", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Nodes per column:", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Nodes per row:", Q_NULLPTR));
        numCols->setText(QApplication::translate("MainWindow", "4", Q_NULLPTR));
        numRows->setText(QApplication::translate("MainWindow", "4", Q_NULLPTR));
        singleRun->setText(QApplication::translate("MainWindow", "Single Run", Q_NULLPTR));
        sweepRun->setText(QApplication::translate("MainWindow", "Sweep Run", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Run parameters:", Q_NULLPTR));
        setIPconfig->setText(QApplication::translate("MainWindow", "Set Input Config", Q_NULLPTR));
        build->setText(QApplication::translate("MainWindow", "Build", Q_NULLPTR));
        run->setText(QApplication::translate("MainWindow", "Run", Q_NULLPTR));
        label_15->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt;\">- OR -</span></p></body></html>", Q_NULLPTR));
        browseConfigFile->setText(QApplication::translate("MainWindow", "Manual Input Config:", Q_NULLPTR));
        configFilePath->setText(QString());
        setClockDomains->setText(QApplication::translate("MainWindow", "Set Clock Domains", Q_NULLPTR));
        clockDomainConfig_default->setText(QApplication::translate("MainWindow", "Default", Q_NULLPTR));
        clockDomainConfig_manual->setText(QApplication::translate("MainWindow", "Set Manually", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Clock Domain Config:", Q_NULLPTR));
        viewHeatMap->setText(QApplication::translate("MainWindow", "View Heat Map", Q_NULLPTR));
        heatMap_routerPacketsGenerated->setText(QApplication::translate("MainWindow", "Generated", Q_NULLPTR));
        heatMap_routerLinks->setText(QApplication::translate("MainWindow", "Router Links", Q_NULLPTR));
        heatMap_routerPacketsRetired->setText(QApplication::translate("MainWindow", "Retired", Q_NULLPTR));
        menuNetwork_Define->setTitle(QApplication::translate("MainWindow", "Network Define", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
