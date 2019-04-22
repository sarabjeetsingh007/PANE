/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QPushButton *print;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QComboBox *comboBox;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_8;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_10;
    QLabel *label_11;
    QLabel *label_12;
    QLineEdit *lineEdit_11;
    QCheckBox *checkBox;
    QLabel *label_6;
    QLabel *label_13;
    QLabel *label_14;
    QLineEdit *lineEdit_4;
    QLabel *label_15;
    QCheckBox *checkBox_2;
    QLabel *label_16;
    QComboBox *comboBox_4;
    QLabel *label_17;
    QLabel *label_18;
    QLineEdit *lineEdit_12;
    QLineEdit *lineEdit_13;
    QLabel *label_19;
    QLineEdit *lineEdit_14;
    QLabel *label_20;
    QLineEdit *lineEdit_15;
    QLabel *label_21;
    QFrame *line;
    QFrame *line_2;
    QLineEdit *lineEdit_16;
    QLabel *label_22;
    QLabel *label_23;
    QLineEdit *lineEdit_17;
    QLabel *label_24;
    QLineEdit *lineEdit_18;
    QCheckBox *checkBox_3;
    QLabel *label_26;
    QLineEdit *lineEdit_20;
    QLabel *label_27;
    QLineEdit *lineEdit_22;
    QLabel *label_28;
    QLineEdit *lineEdit_23;
    QLabel *label_29;
    QComboBox *comboBox_5;
    QComboBox *comboBox_2;
    QLabel *label_30;
    QComboBox *comboBox_3;
    QLabel *label_31;
    QRadioButton *radioButton;
    QComboBox *comboBox_6;
    QLineEdit *lineEdit_21;
    QLabel *label_32;
    QCheckBox *checkBox_4;
    QLineEdit *lineEdit_24;
    QLabel *label_33;
    QRadioButton *radioButton_2;
    QPushButton *build;
    QPushButton *run;
    QPushButton *browse;
    QLineEdit *lineEdit_browse;
    QPushButton *browse_exe;
    QLineEdit *lineEdit_browse_2;
    QPushButton *browse_config;
    QLineEdit *lineEdit_browse_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(938, 743);
        MainWindow->setTabShape(QTabWidget::Triangular);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(730, 480, 191, 151));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(160, 170, 41, 31));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(160, 200, 41, 31));
        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(160, 230, 51, 31));
        print = new QPushButton(centralWidget);
        print->setObjectName(QString::fromUtf8("print"));
        print->setGeometry(QRect(810, 380, 111, 41));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 170, 111, 16));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 200, 131, 21));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(30, 240, 114, 20));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(130, 110, 121, 31));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 300, 114, 20));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 330, 114, 20));
        lineEdit_5 = new QLineEdit(centralWidget);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(160, 300, 41, 31));
        lineEdit_8 = new QLineEdit(centralWidget);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));
        lineEdit_8->setGeometry(QRect(160, 330, 41, 31));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(720, 180, 161, 20));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(780, 200, 111, 20));
        lineEdit_9 = new QLineEdit(centralWidget);
        lineEdit_9->setObjectName(QString::fromUtf8("lineEdit_9"));
        lineEdit_9->setGeometry(QRect(780, 230, 41, 31));
        lineEdit_10 = new QLineEdit(centralWidget);
        lineEdit_10->setObjectName(QString::fromUtf8("lineEdit_10"));
        lineEdit_10->setGeometry(QRect(850, 230, 41, 31));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(830, 230, 41, 20));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(720, 280, 161, 20));
        lineEdit_11 = new QLineEdit(centralWidget);
        lineEdit_11->setObjectName(QString::fromUtf8("lineEdit_11"));
        lineEdit_11->setGeometry(QRect(840, 280, 41, 31));
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(750, 320, 151, 21));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(170, 20, 241, 51));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(790, 450, 71, 31));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(30, 110, 91, 16));
        lineEdit_4 = new QLineEdit(centralWidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(160, 270, 111, 27));
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(30, 270, 121, 27));
        checkBox_2 = new QCheckBox(centralWidget);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(70, 370, 158, 22));
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(25, 410, 111, 27));
        comboBox_4 = new QComboBox(centralWidget);
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
        comboBox_4->setGeometry(QRect(150, 410, 121, 27));
        label_17 = new QLabel(centralWidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(25, 450, 111, 27));
        label_18 = new QLabel(centralWidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(28, 530, 85, 27));
        lineEdit_12 = new QLineEdit(centralWidget);
        lineEdit_12->setObjectName(QString::fromUtf8("lineEdit_12"));
        lineEdit_12->setGeometry(QRect(130, 530, 141, 27));
        lineEdit_13 = new QLineEdit(centralWidget);
        lineEdit_13->setObjectName(QString::fromUtf8("lineEdit_13"));
        lineEdit_13->setGeometry(QRect(130, 560, 141, 27));
        label_19 = new QLabel(centralWidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(30, 560, 97, 27));
        lineEdit_14 = new QLineEdit(centralWidget);
        lineEdit_14->setObjectName(QString::fromUtf8("lineEdit_14"));
        lineEdit_14->setGeometry(QRect(200, 590, 71, 27));
        label_20 = new QLabel(centralWidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(30, 590, 128, 27));
        lineEdit_15 = new QLineEdit(centralWidget);
        lineEdit_15->setObjectName(QString::fromUtf8("lineEdit_15"));
        lineEdit_15->setGeometry(QRect(200, 620, 71, 27));
        label_21 = new QLabel(centralWidget);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(30, 620, 154, 27));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(290, 160, 16, 491));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(690, 150, 16, 491));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        lineEdit_16 = new QLineEdit(centralWidget);
        lineEdit_16->setObjectName(QString::fromUtf8("lineEdit_16"));
        lineEdit_16->setGeometry(QRect(480, 150, 146, 27));
        label_22 = new QLabel(centralWidget);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(320, 150, 121, 27));
        label_23 = new QLabel(centralWidget);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(320, 180, 121, 27));
        lineEdit_17 = new QLineEdit(centralWidget);
        lineEdit_17->setObjectName(QString::fromUtf8("lineEdit_17"));
        lineEdit_17->setGeometry(QRect(480, 180, 146, 27));
        label_24 = new QLabel(centralWidget);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(320, 210, 121, 27));
        lineEdit_18 = new QLineEdit(centralWidget);
        lineEdit_18->setObjectName(QString::fromUtf8("lineEdit_18"));
        lineEdit_18->setGeometry(QRect(480, 210, 146, 27));
        checkBox_3 = new QCheckBox(centralWidget);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setGeometry(QRect(350, 250, 162, 22));
        label_26 = new QLabel(centralWidget);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(325, 340, 76, 27));
        lineEdit_20 = new QLineEdit(centralWidget);
        lineEdit_20->setObjectName(QString::fromUtf8("lineEdit_20"));
        lineEdit_20->setGeometry(QRect(430, 340, 124, 27));
        label_27 = new QLabel(centralWidget);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(320, 280, 121, 27));
        lineEdit_22 = new QLineEdit(centralWidget);
        lineEdit_22->setObjectName(QString::fromUtf8("lineEdit_22"));
        lineEdit_22->setGeometry(QRect(450, 610, 124, 27));
        label_28 = new QLabel(centralWidget);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(330, 610, 101, 27));
        lineEdit_23 = new QLineEdit(centralWidget);
        lineEdit_23->setObjectName(QString::fromUtf8("lineEdit_23"));
        lineEdit_23->setGeometry(QRect(450, 650, 51, 27));
        label_29 = new QLabel(centralWidget);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(330, 650, 101, 27));
        comboBox_5 = new QComboBox(centralWidget);
        comboBox_5->setObjectName(QString::fromUtf8("comboBox_5"));
        comboBox_5->setGeometry(QRect(150, 450, 121, 27));
        comboBox_2 = new QComboBox(centralWidget);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(440, 280, 121, 27));
        label_30 = new QLabel(centralWidget);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(30, 490, 111, 27));
        comboBox_3 = new QComboBox(centralWidget);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(150, 490, 121, 27));
        label_31 = new QLabel(centralWidget);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setGeometry(QRect(310, 390, 181, 27));
        radioButton = new QRadioButton(centralWidget);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(radioButton);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(340, 420, 117, 22));
        radioButton->setChecked(true);
        comboBox_6 = new QComboBox(centralWidget);
        comboBox_6->setObjectName(QString::fromUtf8("comboBox_6"));
        comboBox_6->setGeometry(QRect(470, 450, 111, 27));
        lineEdit_21 = new QLineEdit(centralWidget);
        lineEdit_21->setObjectName(QString::fromUtf8("lineEdit_21"));
        lineEdit_21->setGeometry(QRect(510, 500, 181, 27));
        label_32 = new QLabel(centralWidget);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setGeometry(QRect(370, 500, 131, 27));
        checkBox_4 = new QCheckBox(centralWidget);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setGeometry(QRect(310, 550, 171, 22));
        lineEdit_24 = new QLineEdit(centralWidget);
        lineEdit_24->setObjectName(QString::fromUtf8("lineEdit_24"));
        lineEdit_24->setGeometry(QRect(510, 570, 181, 27));
        label_33 = new QLabel(centralWidget);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setGeometry(QRect(350, 570, 151, 27));
        radioButton_2 = new QRadioButton(centralWidget);
        buttonGroup->addButton(radioButton_2);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(340, 480, 117, 22));
        build = new QPushButton(centralWidget);
        build->setObjectName(QString::fromUtf8("build"));
        build->setGeometry(QRect(700, 380, 101, 41));
        run = new QPushButton(centralWidget);
        run->setObjectName(QString::fromUtf8("run"));
        run->setGeometry(QRect(700, 340, 101, 41));
        browse = new QPushButton(centralWidget);
        browse->setObjectName(QString::fromUtf8("browse"));
        browse->setGeometry(QRect(440, 10, 171, 31));
        lineEdit_browse = new QLineEdit(centralWidget);
        lineEdit_browse->setObjectName(QString::fromUtf8("lineEdit_browse"));
        lineEdit_browse->setGeometry(QRect(630, 10, 301, 31));
        browse_exe = new QPushButton(centralWidget);
        browse_exe->setObjectName(QString::fromUtf8("browse_exe"));
        browse_exe->setGeometry(QRect(440, 50, 171, 31));
        lineEdit_browse_2 = new QLineEdit(centralWidget);
        lineEdit_browse_2->setObjectName(QString::fromUtf8("lineEdit_browse_2"));
        lineEdit_browse_2->setGeometry(QRect(630, 50, 301, 31));
        browse_config = new QPushButton(centralWidget);
        browse_config->setObjectName(QString::fromUtf8("browse_config"));
        browse_config->setGeometry(QRect(440, 90, 171, 31));
        lineEdit_browse_3 = new QLineEdit(centralWidget);
        lineEdit_browse_3->setObjectName(QString::fromUtf8("lineEdit_browse_3"));
        lineEdit_browse_3->setGeometry(QRect(630, 90, 301, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 938, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        lineEdit->setText(QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8));
        lineEdit_2->setText(QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8));
        lineEdit_3->setText(QApplication::translate("MainWindow", "invalid", 0, QApplication::UnicodeUTF8));
        print->setText(QApplication::translate("MainWindow", "Print Pdf!", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Nodes per row", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Nodes per column", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "No. of endpoints", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Number of VC's", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "VC Buffer Size", 0, QApplication::UnicodeUTF8));
        lineEdit_5->setText(QApplication::translate("MainWindow", "4", 0, QApplication::UnicodeUTF8));
        lineEdit_8->setText(QApplication::translate("MainWindow", "4", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Cycle to be printed", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "(default- ALL)", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:20pt;\">-</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "<html><head/><body><p>Search by Flit_id:</p></body></html>", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("MainWindow", "Detailed Print", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:20pt; text-decoration: underline; color:#901c1c;\">Interface</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; text-decoration: underline; color:#bb255e;\">Preview</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">TOPOLOGY:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        lineEdit_4->setText(QApplication::translate("MainWindow", "dor", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindow", "Routing Function", 0, QApplication::UnicodeUTF8));
        checkBox_2->setText(QApplication::translate("MainWindow", "Wait for Tail Credit", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("MainWindow", "VC Allocator", 0, QApplication::UnicodeUTF8));
        comboBox_4->clear();
        comboBox_4->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "islip", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "loa", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "maxsize", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "pim", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "selalloc", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "separable", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "separable_input_first", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "seperable_output_first", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "wavefront", 0, QApplication::UnicodeUTF8)
        );
        label_17->setText(QApplication::translate("MainWindow", "Switch Allocator", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("MainWindow", "Credit Delay", 0, QApplication::UnicodeUTF8));
        lineEdit_12->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
        lineEdit_13->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("MainWindow", "Routing Delay", 0, QApplication::UnicodeUTF8));
        lineEdit_14->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("MainWindow", "VC Allocator Delay", 0, QApplication::UnicodeUTF8));
        lineEdit_15->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("MainWindow", "Switch Allocator Delay", 0, QApplication::UnicodeUTF8));
        lineEdit_16->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("MainWindow", "Input_Speedup", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("MainWindow", "Output_Speedup", 0, QApplication::UnicodeUTF8));
        lineEdit_17->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("MainWindow", "Internal_Speedup", 0, QApplication::UnicodeUTF8));
        lineEdit_18->setText(QApplication::translate("MainWindow", "1.0", 0, QApplication::UnicodeUTF8));
        checkBox_3->setText(QApplication::translate("MainWindow", "VC busy when full", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("MainWindow", "Packet Size", 0, QApplication::UnicodeUTF8));
        lineEdit_20->setText(QApplication::translate("MainWindow", "5", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("MainWindow", "Simulation Type", 0, QApplication::UnicodeUTF8));
        lineEdit_22->setText(QApplication::translate("MainWindow", "1000000", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("MainWindow", "Max Samples", 0, QApplication::UnicodeUTF8));
        lineEdit_23->setText(QApplication::translate("MainWindow", "0.5", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("MainWindow", "Injection Rate", 0, QApplication::UnicodeUTF8));
        comboBox_5->clear();
        comboBox_5->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "islip", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "loa", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "maxsize", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "pim", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "selalloc", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "separable", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "separable_input_first", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "seperable_output_first", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "wavefront", 0, QApplication::UnicodeUTF8)
        );
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "throughput", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "latency", 0, QApplication::UnicodeUTF8)
        );
        label_30->setText(QApplication::translate("MainWindow", "Arbiters", 0, QApplication::UnicodeUTF8));
        comboBox_3->clear();
        comboBox_3->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "matrix_arb", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "prio_arb", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "roundrobin_arb", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "tree_arb", 0, QApplication::UnicodeUTF8)
        );
        label_31->setText(QApplication::translate("MainWindow", "Simulation Data (Traffic) :", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("MainWindow", "Synthetic", 0, QApplication::UnicodeUTF8));
        comboBox_6->clear();
        comboBox_6->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "tornado", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "bitcomp", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "transpose", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "bitrev", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "shuffle", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "uniform", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "diagonal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "assymetric", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "taper64", 0, QApplication::UnicodeUTF8)
        );
        lineEdit_21->setText(QString());
        label_32->setText(QApplication::translate("MainWindow", "Path to the Traces:", 0, QApplication::UnicodeUTF8));
        checkBox_4->setText(QApplication::translate("MainWindow", "Power Calculation", 0, QApplication::UnicodeUTF8));
        lineEdit_24->setText(QString());
        label_33->setText(QApplication::translate("MainWindow", "Path to the Tech File:", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("MainWindow", "Real", 0, QApplication::UnicodeUTF8));
        build->setText(QApplication::translate("MainWindow", "Build", 0, QApplication::UnicodeUTF8));
        run->setText(QApplication::translate("MainWindow", "./booksim", 0, QApplication::UnicodeUTF8));
        browse->setText(QApplication::translate("MainWindow", "Browse input file", 0, QApplication::UnicodeUTF8));
        lineEdit_browse->setText(QApplication::translate("MainWindow", "Inputs/output_sarabjeet_(copy).txt", 0, QApplication::UnicodeUTF8));
        browse_exe->setText(QApplication::translate("MainWindow", "Browse executable file", 0, QApplication::UnicodeUTF8));
        lineEdit_browse_2->setText(QApplication::translate("MainWindow", "/home/sarab/Downloads/booksim2-classes/src/booksim", 0, QApplication::UnicodeUTF8));
        browse_config->setText(QApplication::translate("MainWindow", "Browse config file", 0, QApplication::UnicodeUTF8));
        lineEdit_browse_3->setText(QApplication::translate("MainWindow", "/home/sarab/Desktop/final/code/Results/log", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
