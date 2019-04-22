/********************************************************************************
** Form generated from reading UI file 'sweeprunmethod.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SWEEPRUNMETHOD_H
#define UI_SWEEPRUNMETHOD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SweepRunMethod
{
public:
    QLabel *label_6;
    QFrame *line;
    QFrame *line_2;
    QToolButton *runCurrentMethod;
    QCheckBox *InjectionRate;
    QCheckBox *packetSize;
    QCheckBox *realBenchmarks;
    QCheckBox *trafficPattern;
    QCheckBox *routingFunction;
    QCheckBox *bufferOrganization;
    QGroupBox *injectionRateGroupBox;
    QLineEdit *injectionRateIncrement;
    QFrame *injectionRate_line1;
    QFrame *injectionRate_line2;
    QLineEdit *injectionRateStart;
    QLineEdit *injectionRateEnd;
    QGroupBox *packetSizeGroupBox;
    QLineEdit *packetSizeEnd;
    QLineEdit *packetSizeStart;
    QFrame *packetSize_line;
    QGroupBox *realBenchmarksGroupBox;
    QToolButton *realBenchmarksAddNewPath;
    QToolButton *realBenchmarksBrowse_1;
    QLineEdit *realBenchmarksPath_1;
    QGroupBox *bufferOrganizationGroupBox;
    QLabel *label_2;
    QFrame *bufferOrganization_line1;
    QLabel *label;
    QLineEdit *bufferOrganization_noVCs_start;
    QLineEdit *bufferOrganization_noVCs_end;
    QFrame *bufferOrganization_line2;
    QLineEdit *bufferOrganization_bufferSize_end;
    QLineEdit *bufferOrganization_bufferSize_start;
    QToolButton *back;
    QGroupBox *trafficPatternGroupBox;
    QCheckBox *trafficPatternCheckbox_7;
    QCheckBox *trafficPatternCheckbox_5;
    QCheckBox *trafficPatternCheckbox_4;
    QCheckBox *trafficPatternCheckbox_1;
    QCheckBox *trafficPatternCheckbox_3;
    QCheckBox *trafficPatternCheckbox_2;
    QCheckBox *trafficPatternCheckbox_6;
    QGroupBox *routingFunctionGroupBox;
    QCheckBox *routingFunctionCheckbox_3;
    QCheckBox *routingFunctionCheckbox_6;
    QCheckBox *routingFunctionCheckbox_5;
    QCheckBox *routingFunctionCheckbox_1;
    QCheckBox *routingFunctionCheckbox_2;
    QCheckBox *routingFunctionCheckbox_4;
    QButtonGroup *routingFunctionButtonGroup;
    QButtonGroup *trafficPatternButtonGroup;

    void setupUi(QWidget *SweepRunMethod)
    {
        if (SweepRunMethod->objectName().isEmpty())
            SweepRunMethod->setObjectName(QStringLiteral("SweepRunMethod"));
        SweepRunMethod->resize(856, 579);
        label_6 = new QLabel(SweepRunMethod);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(270, 20, 351, 51));
        line = new QFrame(SweepRunMethod);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(50, 70, 771, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(SweepRunMethod);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(50, 460, 771, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        runCurrentMethod = new QToolButton(SweepRunMethod);
        runCurrentMethod->setObjectName(QStringLiteral("runCurrentMethod"));
        runCurrentMethod->setGeometry(QRect(710, 490, 111, 31));
        InjectionRate = new QCheckBox(SweepRunMethod);
        InjectionRate->setObjectName(QStringLiteral("InjectionRate"));
        InjectionRate->setGeometry(QRect(70, 120, 162, 22));
        packetSize = new QCheckBox(SweepRunMethod);
        packetSize->setObjectName(QStringLiteral("packetSize"));
        packetSize->setGeometry(QRect(70, 230, 162, 22));
        realBenchmarks = new QCheckBox(SweepRunMethod);
        realBenchmarks->setObjectName(QStringLiteral("realBenchmarks"));
        realBenchmarks->setGeometry(QRect(70, 330, 162, 22));
        trafficPattern = new QCheckBox(SweepRunMethod);
        trafficPattern->setObjectName(QStringLiteral("trafficPattern"));
        trafficPattern->setGeometry(QRect(380, 120, 162, 22));
        routingFunction = new QCheckBox(SweepRunMethod);
        routingFunction->setObjectName(QStringLiteral("routingFunction"));
        routingFunction->setGeometry(QRect(380, 230, 162, 22));
        bufferOrganization = new QCheckBox(SweepRunMethod);
        bufferOrganization->setObjectName(QStringLiteral("bufferOrganization"));
        bufferOrganization->setGeometry(QRect(380, 330, 162, 22));
        injectionRateGroupBox = new QGroupBox(SweepRunMethod);
        injectionRateGroupBox->setObjectName(QStringLiteral("injectionRateGroupBox"));
        injectionRateGroupBox->setGeometry(QRect(90, 140, 251, 61));
        QFont font;
        font.setKerning(false);
        font.setStyleStrategy(QFont::PreferDefault);
        injectionRateGroupBox->setFont(font);
        injectionRateGroupBox->setAcceptDrops(false);
        injectionRateIncrement = new QLineEdit(injectionRateGroupBox);
        injectionRateIncrement->setObjectName(QStringLiteral("injectionRateIncrement"));
        injectionRateIncrement->setGeometry(QRect(160, 30, 81, 21));
        injectionRateIncrement->setMaximumSize(QSize(100, 16777215));
        QFont font1;
        font1.setPointSize(9);
        injectionRateIncrement->setFont(font1);
        injectionRateIncrement->setAlignment(Qt::AlignCenter);
        injectionRate_line1 = new QFrame(injectionRateGroupBox);
        injectionRate_line1->setObjectName(QStringLiteral("injectionRate_line1"));
        injectionRate_line1->setGeometry(QRect(70, 30, 21, 20));
        injectionRate_line1->setFrameShadow(QFrame::Plain);
        injectionRate_line1->setFrameShape(QFrame::HLine);
        injectionRate_line2 = new QFrame(injectionRateGroupBox);
        injectionRate_line2->setObjectName(QStringLiteral("injectionRate_line2"));
        injectionRate_line2->setGeometry(QRect(140, 20, 20, 41));
        injectionRate_line2->setFrameShape(QFrame::VLine);
        injectionRate_line2->setFrameShadow(QFrame::Sunken);
        injectionRateStart = new QLineEdit(injectionRateGroupBox);
        injectionRateStart->setObjectName(QStringLiteral("injectionRateStart"));
        injectionRateStart->setEnabled(true);
        injectionRateStart->setGeometry(QRect(20, 30, 41, 21));
        injectionRateStart->setMaximumSize(QSize(100, 16777215));
        injectionRateStart->setFont(font1);
        injectionRateStart->setAlignment(Qt::AlignCenter);
        injectionRateEnd = new QLineEdit(injectionRateGroupBox);
        injectionRateEnd->setObjectName(QStringLiteral("injectionRateEnd"));
        injectionRateEnd->setGeometry(QRect(100, 30, 41, 21));
        injectionRateEnd->setMaximumSize(QSize(100, 16777215));
        injectionRateEnd->setFont(font1);
        injectionRateEnd->setAlignment(Qt::AlignCenter);
        packetSizeGroupBox = new QGroupBox(SweepRunMethod);
        packetSizeGroupBox->setObjectName(QStringLiteral("packetSizeGroupBox"));
        packetSizeGroupBox->setGeometry(QRect(90, 250, 251, 61));
        packetSizeGroupBox->setFont(font);
        packetSizeGroupBox->setAcceptDrops(false);
        packetSizeEnd = new QLineEdit(packetSizeGroupBox);
        packetSizeEnd->setObjectName(QStringLiteral("packetSizeEnd"));
        packetSizeEnd->setGeometry(QRect(100, 30, 41, 21));
        packetSizeEnd->setMaximumSize(QSize(100, 16777215));
        packetSizeEnd->setFont(font1);
        packetSizeEnd->setAlignment(Qt::AlignCenter);
        packetSizeStart = new QLineEdit(packetSizeGroupBox);
        packetSizeStart->setObjectName(QStringLiteral("packetSizeStart"));
        packetSizeStart->setGeometry(QRect(20, 30, 41, 21));
        packetSizeStart->setMaximumSize(QSize(100, 16777215));
        packetSizeStart->setFont(font1);
        packetSizeStart->setAlignment(Qt::AlignCenter);
        packetSize_line = new QFrame(packetSizeGroupBox);
        packetSize_line->setObjectName(QStringLiteral("packetSize_line"));
        packetSize_line->setGeometry(QRect(70, 30, 21, 20));
        packetSize_line->setFrameShadow(QFrame::Plain);
        packetSize_line->setFrameShape(QFrame::HLine);
        realBenchmarksGroupBox = new QGroupBox(SweepRunMethod);
        realBenchmarksGroupBox->setObjectName(QStringLiteral("realBenchmarksGroupBox"));
        realBenchmarksGroupBox->setGeometry(QRect(90, 350, 251, 81));
        realBenchmarksGroupBox->setFont(font);
        realBenchmarksGroupBox->setAcceptDrops(false);
        realBenchmarksAddNewPath = new QToolButton(realBenchmarksGroupBox);
        realBenchmarksAddNewPath->setObjectName(QStringLiteral("realBenchmarksAddNewPath"));
        realBenchmarksAddNewPath->setGeometry(QRect(170, 50, 71, 21));
        QFont font2;
        font2.setPointSize(10);
        realBenchmarksAddNewPath->setFont(font2);
        realBenchmarksBrowse_1 = new QToolButton(realBenchmarksGroupBox);
        realBenchmarksBrowse_1->setObjectName(QStringLiteral("realBenchmarksBrowse_1"));
        realBenchmarksBrowse_1->setGeometry(QRect(170, 20, 71, 21));
        realBenchmarksBrowse_1->setFont(font2);
        realBenchmarksPath_1 = new QLineEdit(realBenchmarksGroupBox);
        realBenchmarksPath_1->setObjectName(QStringLiteral("realBenchmarksPath_1"));
        realBenchmarksPath_1->setGeometry(QRect(20, 20, 141, 21));
        realBenchmarksPath_1->setMaximumSize(QSize(6000, 16777215));
        realBenchmarksPath_1->setFont(font1);
        realBenchmarksPath_1->setAlignment(Qt::AlignCenter);
        bufferOrganizationGroupBox = new QGroupBox(SweepRunMethod);
        bufferOrganizationGroupBox->setObjectName(QStringLiteral("bufferOrganizationGroupBox"));
        bufferOrganizationGroupBox->setGeometry(QRect(400, 350, 251, 81));
        bufferOrganizationGroupBox->setFont(font);
        bufferOrganizationGroupBox->setAcceptDrops(false);
        label_2 = new QLabel(bufferOrganizationGroupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 50, 71, 21));
        label_2->setFont(font2);
        bufferOrganization_line1 = new QFrame(bufferOrganizationGroupBox);
        bufferOrganization_line1->setObjectName(QStringLiteral("bufferOrganization_line1"));
        bufferOrganization_line1->setGeometry(QRect(160, 20, 21, 20));
        bufferOrganization_line1->setFrameShadow(QFrame::Plain);
        bufferOrganization_line1->setFrameShape(QFrame::HLine);
        label = new QLabel(bufferOrganizationGroupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 20, 71, 21));
        label->setFont(font2);
        bufferOrganization_noVCs_start = new QLineEdit(bufferOrganizationGroupBox);
        bufferOrganization_noVCs_start->setObjectName(QStringLiteral("bufferOrganization_noVCs_start"));
        bufferOrganization_noVCs_start->setGeometry(QRect(110, 20, 41, 21));
        bufferOrganization_noVCs_start->setMaximumSize(QSize(100, 16777215));
        bufferOrganization_noVCs_start->setFont(font1);
        bufferOrganization_noVCs_start->setAlignment(Qt::AlignCenter);
        bufferOrganization_noVCs_end = new QLineEdit(bufferOrganizationGroupBox);
        bufferOrganization_noVCs_end->setObjectName(QStringLiteral("bufferOrganization_noVCs_end"));
        bufferOrganization_noVCs_end->setGeometry(QRect(190, 20, 41, 21));
        bufferOrganization_noVCs_end->setMaximumSize(QSize(100, 16777215));
        bufferOrganization_noVCs_end->setFont(font1);
        bufferOrganization_noVCs_end->setAlignment(Qt::AlignCenter);
        bufferOrganization_line2 = new QFrame(bufferOrganizationGroupBox);
        bufferOrganization_line2->setObjectName(QStringLiteral("bufferOrganization_line2"));
        bufferOrganization_line2->setGeometry(QRect(160, 50, 21, 20));
        bufferOrganization_line2->setFrameShadow(QFrame::Plain);
        bufferOrganization_line2->setFrameShape(QFrame::HLine);
        bufferOrganization_bufferSize_end = new QLineEdit(bufferOrganizationGroupBox);
        bufferOrganization_bufferSize_end->setObjectName(QStringLiteral("bufferOrganization_bufferSize_end"));
        bufferOrganization_bufferSize_end->setGeometry(QRect(190, 50, 41, 21));
        bufferOrganization_bufferSize_end->setMaximumSize(QSize(100, 16777215));
        bufferOrganization_bufferSize_end->setFont(font1);
        bufferOrganization_bufferSize_end->setAlignment(Qt::AlignCenter);
        bufferOrganization_bufferSize_start = new QLineEdit(bufferOrganizationGroupBox);
        bufferOrganization_bufferSize_start->setObjectName(QStringLiteral("bufferOrganization_bufferSize_start"));
        bufferOrganization_bufferSize_start->setGeometry(QRect(110, 50, 41, 21));
        bufferOrganization_bufferSize_start->setMaximumSize(QSize(100, 16777215));
        bufferOrganization_bufferSize_start->setFont(font1);
        bufferOrganization_bufferSize_start->setAlignment(Qt::AlignCenter);
        back = new QToolButton(SweepRunMethod);
        back->setObjectName(QStringLiteral("back"));
        back->setGeometry(QRect(570, 490, 111, 31));
        trafficPatternGroupBox = new QGroupBox(SweepRunMethod);
        trafficPatternGroupBox->setObjectName(QStringLiteral("trafficPatternGroupBox"));
        trafficPatternGroupBox->setGeometry(QRect(400, 130, 421, 80));
        trafficPatternCheckbox_7 = new QCheckBox(trafficPatternGroupBox);
        trafficPatternButtonGroup = new QButtonGroup(SweepRunMethod);
        trafficPatternButtonGroup->setObjectName(QStringLiteral("trafficPatternButtonGroup"));
        trafficPatternButtonGroup->addButton(trafficPatternCheckbox_7);
        trafficPatternCheckbox_7->setObjectName(QStringLiteral("trafficPatternCheckbox_7"));
        trafficPatternCheckbox_7->setGeometry(QRect(220, 50, 91, 22));
        trafficPatternCheckbox_5 = new QCheckBox(trafficPatternGroupBox);
        trafficPatternButtonGroup->addButton(trafficPatternCheckbox_5);
        trafficPatternCheckbox_5->setObjectName(QStringLiteral("trafficPatternCheckbox_5"));
        trafficPatternCheckbox_5->setGeometry(QRect(10, 50, 91, 22));
        trafficPatternCheckbox_4 = new QCheckBox(trafficPatternGroupBox);
        trafficPatternCheckbox_4->setObjectName(QStringLiteral("trafficPatternCheckbox_4"));
        trafficPatternCheckbox_4->setGeometry(QRect(330, 20, 91, 22));
        trafficPatternCheckbox_1 = new QCheckBox(trafficPatternGroupBox);
        trafficPatternButtonGroup->addButton(trafficPatternCheckbox_1);
        trafficPatternCheckbox_1->setObjectName(QStringLiteral("trafficPatternCheckbox_1"));
        trafficPatternCheckbox_1->setGeometry(QRect(10, 20, 91, 22));
        trafficPatternCheckbox_3 = new QCheckBox(trafficPatternGroupBox);
        trafficPatternButtonGroup->addButton(trafficPatternCheckbox_3);
        trafficPatternCheckbox_3->setObjectName(QStringLiteral("trafficPatternCheckbox_3"));
        trafficPatternCheckbox_3->setGeometry(QRect(220, 20, 91, 22));
        trafficPatternCheckbox_2 = new QCheckBox(trafficPatternGroupBox);
        trafficPatternButtonGroup->addButton(trafficPatternCheckbox_2);
        trafficPatternCheckbox_2->setObjectName(QStringLiteral("trafficPatternCheckbox_2"));
        trafficPatternCheckbox_2->setGeometry(QRect(110, 20, 91, 22));
        trafficPatternCheckbox_6 = new QCheckBox(trafficPatternGroupBox);
        trafficPatternButtonGroup->addButton(trafficPatternCheckbox_6);
        trafficPatternCheckbox_6->setObjectName(QStringLiteral("trafficPatternCheckbox_6"));
        trafficPatternCheckbox_6->setGeometry(QRect(110, 50, 91, 22));
        routingFunctionGroupBox = new QGroupBox(SweepRunMethod);
        routingFunctionGroupBox->setObjectName(QStringLiteral("routingFunctionGroupBox"));
        routingFunctionGroupBox->setGeometry(QRect(400, 240, 421, 80));
        routingFunctionCheckbox_3 = new QCheckBox(routingFunctionGroupBox);
        routingFunctionButtonGroup = new QButtonGroup(SweepRunMethod);
        routingFunctionButtonGroup->setObjectName(QStringLiteral("routingFunctionButtonGroup"));
        routingFunctionButtonGroup->addButton(routingFunctionCheckbox_3);
        routingFunctionCheckbox_3->setObjectName(QStringLiteral("routingFunctionCheckbox_3"));
        routingFunctionCheckbox_3->setGeometry(QRect(220, 20, 141, 22));
        routingFunctionCheckbox_6 = new QCheckBox(routingFunctionGroupBox);
        routingFunctionButtonGroup->addButton(routingFunctionCheckbox_6);
        routingFunctionCheckbox_6->setObjectName(QStringLiteral("routingFunctionCheckbox_6"));
        routingFunctionCheckbox_6->setGeometry(QRect(220, 50, 131, 22));
        routingFunctionCheckbox_5 = new QCheckBox(routingFunctionGroupBox);
        routingFunctionButtonGroup->addButton(routingFunctionCheckbox_5);
        routingFunctionCheckbox_5->setObjectName(QStringLiteral("routingFunctionCheckbox_5"));
        routingFunctionCheckbox_5->setGeometry(QRect(110, 50, 91, 22));
        routingFunctionCheckbox_1 = new QCheckBox(routingFunctionGroupBox);
        routingFunctionButtonGroup->addButton(routingFunctionCheckbox_1);
        routingFunctionCheckbox_1->setObjectName(QStringLiteral("routingFunctionCheckbox_1"));
        routingFunctionCheckbox_1->setGeometry(QRect(10, 20, 91, 22));
        routingFunctionCheckbox_2 = new QCheckBox(routingFunctionGroupBox);
        routingFunctionButtonGroup->addButton(routingFunctionCheckbox_2);
        routingFunctionCheckbox_2->setObjectName(QStringLiteral("routingFunctionCheckbox_2"));
        routingFunctionCheckbox_2->setGeometry(QRect(110, 20, 91, 22));
        routingFunctionCheckbox_4 = new QCheckBox(routingFunctionGroupBox);
        routingFunctionButtonGroup->addButton(routingFunctionCheckbox_4);
        routingFunctionCheckbox_4->setObjectName(QStringLiteral("routingFunctionCheckbox_4"));
        routingFunctionCheckbox_4->setGeometry(QRect(10, 50, 91, 22));

        retranslateUi(SweepRunMethod);

        QMetaObject::connectSlotsByName(SweepRunMethod);
    } // setupUi

    void retranslateUi(QWidget *SweepRunMethod)
    {
        SweepRunMethod->setWindowTitle(QApplication::translate("SweepRunMethod", "Form", Q_NULLPTR));
        label_6->setText(QApplication::translate("SweepRunMethod", "<html><head/><body><p align=\"center\"><span style=\" font-size:20pt; color:#901c1c;\">Select Runing Method</span></p></body></html>", Q_NULLPTR));
        runCurrentMethod->setText(QApplication::translate("SweepRunMethod", "Run", Q_NULLPTR));
        InjectionRate->setText(QApplication::translate("SweepRunMethod", "Injection Rate", Q_NULLPTR));
        packetSize->setText(QApplication::translate("SweepRunMethod", "Packet Size", Q_NULLPTR));
        realBenchmarks->setText(QApplication::translate("SweepRunMethod", "Real Benchmarks", Q_NULLPTR));
        trafficPattern->setText(QApplication::translate("SweepRunMethod", "Traffic Pattern", Q_NULLPTR));
        routingFunction->setText(QApplication::translate("SweepRunMethod", "Routing Function", Q_NULLPTR));
        bufferOrganization->setText(QApplication::translate("SweepRunMethod", "Buffer Organization", Q_NULLPTR));
        injectionRateGroupBox->setTitle(QString());
        injectionRateIncrement->setText(QString());
        injectionRateIncrement->setPlaceholderText(QApplication::translate("SweepRunMethod", "Increment", Q_NULLPTR));
        injectionRateStart->setText(QString());
        injectionRateStart->setPlaceholderText(QApplication::translate("SweepRunMethod", "Start", Q_NULLPTR));
        injectionRateEnd->setText(QString());
        injectionRateEnd->setPlaceholderText(QApplication::translate("SweepRunMethod", "End", Q_NULLPTR));
        packetSizeGroupBox->setTitle(QString());
        packetSizeEnd->setText(QString());
        packetSizeEnd->setPlaceholderText(QApplication::translate("SweepRunMethod", "End", Q_NULLPTR));
        packetSizeStart->setText(QString());
        packetSizeStart->setPlaceholderText(QApplication::translate("SweepRunMethod", "Start", Q_NULLPTR));
        realBenchmarksGroupBox->setTitle(QString());
        realBenchmarksAddNewPath->setText(QApplication::translate("SweepRunMethod", "Add", Q_NULLPTR));
        realBenchmarksBrowse_1->setText(QApplication::translate("SweepRunMethod", "Browse", Q_NULLPTR));
        realBenchmarksPath_1->setText(QString());
        realBenchmarksPath_1->setPlaceholderText(QApplication::translate("SweepRunMethod", "path to file", Q_NULLPTR));
        bufferOrganizationGroupBox->setTitle(QString());
        label_2->setText(QApplication::translate("SweepRunMethod", "Buffer size :", Q_NULLPTR));
        label->setText(QApplication::translate("SweepRunMethod", "No. of VC's :", Q_NULLPTR));
        bufferOrganization_noVCs_start->setText(QString());
        bufferOrganization_noVCs_start->setPlaceholderText(QApplication::translate("SweepRunMethod", "Start", Q_NULLPTR));
        bufferOrganization_noVCs_end->setText(QString());
        bufferOrganization_noVCs_end->setPlaceholderText(QApplication::translate("SweepRunMethod", "End", Q_NULLPTR));
        bufferOrganization_bufferSize_end->setText(QString());
        bufferOrganization_bufferSize_end->setPlaceholderText(QApplication::translate("SweepRunMethod", "End", Q_NULLPTR));
        bufferOrganization_bufferSize_start->setText(QString());
        bufferOrganization_bufferSize_start->setPlaceholderText(QApplication::translate("SweepRunMethod", "Start", Q_NULLPTR));
        back->setText(QApplication::translate("SweepRunMethod", "Back", Q_NULLPTR));
        trafficPatternGroupBox->setTitle(QString());
        trafficPatternCheckbox_7->setText(QApplication::translate("SweepRunMethod", "bitrev", Q_NULLPTR));
        trafficPatternCheckbox_5->setText(QApplication::translate("SweepRunMethod", "transpose", Q_NULLPTR));
        trafficPatternCheckbox_4->setText(QApplication::translate("SweepRunMethod", "shuffle", Q_NULLPTR));
        trafficPatternCheckbox_1->setText(QApplication::translate("SweepRunMethod", "Neighbor", Q_NULLPTR));
        trafficPatternCheckbox_3->setText(QApplication::translate("SweepRunMethod", "tornado", Q_NULLPTR));
        trafficPatternCheckbox_2->setText(QApplication::translate("SweepRunMethod", "uniform", Q_NULLPTR));
        trafficPatternCheckbox_6->setText(QApplication::translate("SweepRunMethod", "bitcomp", Q_NULLPTR));
        routingFunctionGroupBox->setTitle(QString());
        routingFunctionCheckbox_3->setText(QApplication::translate("SweepRunMethod", "adaptive xy-yx", Q_NULLPTR));
        routingFunctionCheckbox_6->setText(QApplication::translate("SweepRunMethod", "planar adapt", Q_NULLPTR));
        routingFunctionCheckbox_5->setText(QApplication::translate("SweepRunMethod", "min-adapt", Q_NULLPTR));
        routingFunctionCheckbox_1->setText(QApplication::translate("SweepRunMethod", "dor", Q_NULLPTR));
        routingFunctionCheckbox_2->setText(QApplication::translate("SweepRunMethod", "xy-yx", Q_NULLPTR));
        routingFunctionCheckbox_4->setText(QApplication::translate("SweepRunMethod", "romm", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SweepRunMethod: public Ui_SweepRunMethod {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SWEEPRUNMETHOD_H
