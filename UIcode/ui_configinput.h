/********************************************************************************
** Form generated from reading UI file 'configinput.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGINPUT_H
#define UI_CONFIGINPUT_H

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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigInput
{
public:
    QFrame *line;
    QLabel *label_21;
    QFrame *line_2;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_19;
    QLabel *label_33;
    QLabel *label_30;
    QLabel *label_18;
    QComboBox *arbiters;
    QCheckBox *powerCalculation;
    QRadioButton *simulationData_Real;
    QLabel *label_6;
    QLineEdit *switchAllocatorDelay;
    QRadioButton *simulationData_Synthetic;
    QComboBox *switchAllocator;
    QLineEdit *VCallocatorDelay;
    QLabel *label_23;
    QCheckBox *waitForTailCredit;
    QCheckBox *VCbusyWhenFull;
    QComboBox *simulationType;
    QLabel *label_31;
    QLabel *label_17;
    QLabel *label_32;
    QLabel *label_20;
    QLineEdit *packetSize;
    QLabel *label_16;
    QLineEdit *routingDelay;
    QLabel *label_26;
    QComboBox *VCallocator;
    QLineEdit *VCbufferSize;
    QLineEdit *simulationData_Real_PathToTraces;
    QLineEdit *outputSpeedUp;
    QLineEdit *endPoints;
    QLabel *label_27;
    QLabel *label_22;
    QLineEdit *powerCalculation_PathToTechFile;
    QLineEdit *noVCs;
    QLabel *label_24;
    QLineEdit *injectionRate;
    QComboBox *simulationData_SyntheticDropdown;
    QLabel *label_29;
    QLabel *label_8;
    QLineEdit *inputSpeedUp;
    QLineEdit *routingFxn;
    QLineEdit *maxSamples;
    QLineEdit *internalSpeedUp;
    QLineEdit *creditDelay;
    QLabel *label_28;
    QLabel *label_15;
    QPushButton *submitIPconfig;
    QLabel *label_34;
    QLineEdit *samplePeriod;

    void setupUi(QWidget *ConfigInput)
    {
        if (ConfigInput->objectName().isEmpty())
            ConfigInput->setObjectName(QStringLiteral("ConfigInput"));
        ConfigInput->resize(1012, 808);
        line = new QFrame(ConfigInput);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(310, 100, 16, 531));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        label_21 = new QLabel(ConfigInput);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(50, 540, 154, 27));
        line_2 = new QFrame(ConfigInput);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(710, 110, 16, 541));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(ConfigInput);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(50, 119, 114, 31));
        label_7 = new QLabel(ConfigInput);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(50, 200, 114, 20));
        label_19 = new QLabel(ConfigInput);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(50, 480, 97, 27));
        label_33 = new QLabel(ConfigInput);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setGeometry(QRect(360, 530, 151, 27));
        label_30 = new QLabel(ConfigInput);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(50, 410, 111, 27));
        label_18 = new QLabel(ConfigInput);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(48, 450, 85, 27));
        arbiters = new QComboBox(ConfigInput);
        arbiters->setObjectName(QStringLiteral("arbiters"));
        arbiters->setGeometry(QRect(170, 410, 121, 27));
        powerCalculation = new QCheckBox(ConfigInput);
        powerCalculation->setObjectName(QStringLiteral("powerCalculation"));
        powerCalculation->setGeometry(QRect(340, 510, 171, 22));
        simulationData_Real = new QRadioButton(ConfigInput);
        simulationData_Real->setObjectName(QStringLiteral("simulationData_Real"));
        simulationData_Real->setGeometry(QRect(360, 450, 117, 22));
        label_6 = new QLabel(ConfigInput);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(380, 30, 241, 31));
        switchAllocatorDelay = new QLineEdit(ConfigInput);
        switchAllocatorDelay->setObjectName(QStringLiteral("switchAllocatorDelay"));
        switchAllocatorDelay->setGeometry(QRect(220, 540, 71, 27));
        simulationData_Synthetic = new QRadioButton(ConfigInput);
        simulationData_Synthetic->setObjectName(QStringLiteral("simulationData_Synthetic"));
        simulationData_Synthetic->setGeometry(QRect(360, 380, 117, 22));
        simulationData_Synthetic->setChecked(true);
        switchAllocator = new QComboBox(ConfigInput);
        switchAllocator->setObjectName(QStringLiteral("switchAllocator"));
        switchAllocator->setGeometry(QRect(170, 370, 121, 27));
        VCallocatorDelay = new QLineEdit(ConfigInput);
        VCallocatorDelay->setObjectName(QStringLiteral("VCallocatorDelay"));
        VCallocatorDelay->setGeometry(QRect(220, 510, 71, 27));
        label_23 = new QLabel(ConfigInput);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(340, 140, 121, 27));
        waitForTailCredit = new QCheckBox(ConfigInput);
        waitForTailCredit->setObjectName(QStringLiteral("waitForTailCredit"));
        waitForTailCredit->setGeometry(QRect(50, 270, 158, 22));
        VCbusyWhenFull = new QCheckBox(ConfigInput);
        VCbusyWhenFull->setObjectName(QStringLiteral("VCbusyWhenFull"));
        VCbusyWhenFull->setGeometry(QRect(340, 210, 162, 22));
        simulationType = new QComboBox(ConfigInput);
        simulationType->setObjectName(QStringLiteral("simulationType"));
        simulationType->setGeometry(QRect(530, 250, 121, 27));
        label_31 = new QLabel(ConfigInput);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(340, 350, 181, 27));
        label_17 = new QLabel(ConfigInput);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(45, 370, 111, 27));
        label_32 = new QLabel(ConfigInput);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setGeometry(QRect(390, 470, 131, 27));
        label_20 = new QLabel(ConfigInput);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(50, 510, 128, 27));
        packetSize = new QLineEdit(ConfigInput);
        packetSize->setObjectName(QStringLiteral("packetSize"));
        packetSize->setGeometry(QRect(530, 290, 124, 27));
        label_16 = new QLabel(ConfigInput);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(45, 330, 111, 27));
        routingDelay = new QLineEdit(ConfigInput);
        routingDelay->setObjectName(QStringLiteral("routingDelay"));
        routingDelay->setGeometry(QRect(150, 480, 141, 27));
        label_26 = new QLabel(ConfigInput);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(340, 300, 76, 27));
        VCallocator = new QComboBox(ConfigInput);
        VCallocator->setObjectName(QStringLiteral("VCallocator"));
        VCallocator->setGeometry(QRect(170, 330, 121, 27));
        VCbufferSize = new QLineEdit(ConfigInput);
        VCbufferSize->setObjectName(QStringLiteral("VCbufferSize"));
        VCbufferSize->setGeometry(QRect(180, 230, 41, 21));
        simulationData_Real_PathToTraces = new QLineEdit(ConfigInput);
        simulationData_Real_PathToTraces->setObjectName(QStringLiteral("simulationData_Real_PathToTraces"));
        simulationData_Real_PathToTraces->setGeometry(QRect(530, 470, 181, 27));
        outputSpeedUp = new QLineEdit(ConfigInput);
        outputSpeedUp->setObjectName(QStringLiteral("outputSpeedUp"));
        outputSpeedUp->setGeometry(QRect(530, 140, 146, 27));
        endPoints = new QLineEdit(ConfigInput);
        endPoints->setObjectName(QStringLiteral("endPoints"));
        endPoints->setGeometry(QRect(180, 120, 51, 31));
        label_27 = new QLabel(ConfigInput);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(340, 250, 121, 27));
        label_22 = new QLabel(ConfigInput);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(340, 110, 121, 27));
        powerCalculation_PathToTechFile = new QLineEdit(ConfigInput);
        powerCalculation_PathToTechFile->setObjectName(QStringLiteral("powerCalculation_PathToTechFile"));
        powerCalculation_PathToTechFile->setGeometry(QRect(530, 530, 181, 27));
        noVCs = new QLineEdit(ConfigInput);
        noVCs->setObjectName(QStringLiteral("noVCs"));
        noVCs->setGeometry(QRect(180, 200, 41, 21));
        label_24 = new QLabel(ConfigInput);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(340, 170, 121, 27));
        injectionRate = new QLineEdit(ConfigInput);
        injectionRate->setObjectName(QStringLiteral("injectionRate"));
        injectionRate->setGeometry(QRect(530, 670, 51, 27));
        simulationData_SyntheticDropdown = new QComboBox(ConfigInput);
        simulationData_SyntheticDropdown->setObjectName(QStringLiteral("simulationData_SyntheticDropdown"));
        simulationData_SyntheticDropdown->setGeometry(QRect(390, 410, 111, 27));
        label_29 = new QLabel(ConfigInput);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(340, 670, 101, 27));
        label_8 = new QLabel(ConfigInput);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(50, 230, 114, 20));
        inputSpeedUp = new QLineEdit(ConfigInput);
        inputSpeedUp->setObjectName(QStringLiteral("inputSpeedUp"));
        inputSpeedUp->setGeometry(QRect(530, 110, 146, 27));
        routingFxn = new QLineEdit(ConfigInput);
        routingFxn->setObjectName(QStringLiteral("routingFxn"));
        routingFxn->setGeometry(QRect(180, 160, 111, 27));
        maxSamples = new QLineEdit(ConfigInput);
        maxSamples->setObjectName(QStringLiteral("maxSamples"));
        maxSamples->setGeometry(QRect(530, 630, 124, 27));
        internalSpeedUp = new QLineEdit(ConfigInput);
        internalSpeedUp->setObjectName(QStringLiteral("internalSpeedUp"));
        internalSpeedUp->setGeometry(QRect(530, 170, 146, 27));
        creditDelay = new QLineEdit(ConfigInput);
        creditDelay->setObjectName(QStringLiteral("creditDelay"));
        creditDelay->setGeometry(QRect(150, 450, 141, 27));
        label_28 = new QLabel(ConfigInput);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(340, 630, 101, 27));
        label_15 = new QLabel(ConfigInput);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(50, 160, 121, 27));
        submitIPconfig = new QPushButton(ConfigInput);
        submitIPconfig->setObjectName(QStringLiteral("submitIPconfig"));
        submitIPconfig->setGeometry(QRect(820, 370, 101, 31));
        label_34 = new QLabel(ConfigInput);
        label_34->setObjectName(QStringLiteral("label_34"));
        label_34->setGeometry(QRect(340, 590, 111, 27));
        samplePeriod = new QLineEdit(ConfigInput);
        samplePeriod->setObjectName(QStringLiteral("samplePeriod"));
        samplePeriod->setGeometry(QRect(530, 590, 124, 27));

        retranslateUi(ConfigInput);

        QMetaObject::connectSlotsByName(ConfigInput);
    } // setupUi

    void retranslateUi(QWidget *ConfigInput)
    {
        ConfigInput->setWindowTitle(QApplication::translate("ConfigInput", "Form", Q_NULLPTR));
        label_21->setText(QApplication::translate("ConfigInput", "Switch Allocator Delay", Q_NULLPTR));
        label_5->setText(QApplication::translate("ConfigInput", "No. of endpoints", Q_NULLPTR));
        label_7->setText(QApplication::translate("ConfigInput", "Number of VC's", Q_NULLPTR));
        label_19->setText(QApplication::translate("ConfigInput", "Routing Delay", Q_NULLPTR));
        label_33->setText(QApplication::translate("ConfigInput", "Path to the Tech File:", Q_NULLPTR));
        label_30->setText(QApplication::translate("ConfigInput", "Arbiters", Q_NULLPTR));
        label_18->setText(QApplication::translate("ConfigInput", "Credit Delay", Q_NULLPTR));
        arbiters->clear();
        arbiters->insertItems(0, QStringList()
         << QApplication::translate("ConfigInput", "matrix_arb", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "prio_arb", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "roundrobin_arb", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "tree_arb", Q_NULLPTR)
        );
        powerCalculation->setText(QApplication::translate("ConfigInput", "Power Calculation", Q_NULLPTR));
        simulationData_Real->setText(QApplication::translate("ConfigInput", "Real", Q_NULLPTR));
        label_6->setText(QApplication::translate("ConfigInput", "<html><head/><body><p align=\"center\"><span style=\" font-size:20pt; text-decoration: underline; color:#901c1c;\">Input Configuration</span></p></body></html>", Q_NULLPTR));
        switchAllocatorDelay->setText(QApplication::translate("ConfigInput", "1", Q_NULLPTR));
        simulationData_Synthetic->setText(QApplication::translate("ConfigInput", "Synthetic", Q_NULLPTR));
        switchAllocator->clear();
        switchAllocator->insertItems(0, QStringList()
         << QApplication::translate("ConfigInput", "islip", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "loa", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "maxsize", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "pim", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "selalloc", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "separable", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "separable_input_first", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "seperable_output_first", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "wavefront", Q_NULLPTR)
        );
        VCallocatorDelay->setText(QApplication::translate("ConfigInput", "1", Q_NULLPTR));
        label_23->setText(QApplication::translate("ConfigInput", "Output_Speedup", Q_NULLPTR));
        waitForTailCredit->setText(QApplication::translate("ConfigInput", "Wait for Tail Credit", Q_NULLPTR));
        VCbusyWhenFull->setText(QApplication::translate("ConfigInput", "VC busy when full", Q_NULLPTR));
        simulationType->clear();
        simulationType->insertItems(0, QStringList()
         << QApplication::translate("ConfigInput", "throughput", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "latency", Q_NULLPTR)
        );
        label_31->setText(QApplication::translate("ConfigInput", "Simulation Data (Traffic) :", Q_NULLPTR));
        label_17->setText(QApplication::translate("ConfigInput", "Switch Allocator", Q_NULLPTR));
        label_32->setText(QApplication::translate("ConfigInput", "Path to the Traces:", Q_NULLPTR));
        label_20->setText(QApplication::translate("ConfigInput", "VC Allocator Delay", Q_NULLPTR));
        packetSize->setText(QApplication::translate("ConfigInput", "1", Q_NULLPTR));
        label_16->setText(QApplication::translate("ConfigInput", "VC Allocator", Q_NULLPTR));
        routingDelay->setText(QApplication::translate("ConfigInput", "1", Q_NULLPTR));
        label_26->setText(QApplication::translate("ConfigInput", "Packet Size", Q_NULLPTR));
        VCallocator->clear();
        VCallocator->insertItems(0, QStringList()
         << QApplication::translate("ConfigInput", "islip", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "loa", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "maxsize", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "pim", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "selalloc", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "separable", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "separable_input_first", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "seperable_output_first", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "wavefront", Q_NULLPTR)
        );
        VCbufferSize->setText(QApplication::translate("ConfigInput", "4", Q_NULLPTR));
        simulationData_Real_PathToTraces->setText(QString());
        outputSpeedUp->setText(QApplication::translate("ConfigInput", "1", Q_NULLPTR));
        endPoints->setText(QApplication::translate("ConfigInput", "invalid", Q_NULLPTR));
        label_27->setText(QApplication::translate("ConfigInput", "Simulation Type", Q_NULLPTR));
        label_22->setText(QApplication::translate("ConfigInput", "Input_Speedup", Q_NULLPTR));
        powerCalculation_PathToTechFile->setText(QString());
        noVCs->setText(QApplication::translate("ConfigInput", "4", Q_NULLPTR));
        label_24->setText(QApplication::translate("ConfigInput", "Internal_Speedup", Q_NULLPTR));
        injectionRate->setText(QApplication::translate("ConfigInput", "0.05", Q_NULLPTR));
        simulationData_SyntheticDropdown->clear();
        simulationData_SyntheticDropdown->insertItems(0, QStringList()
         << QApplication::translate("ConfigInput", "uniform", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "neighbor", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "tornado", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "transpose", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "shuffle", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "bitcomp", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "bitrev", Q_NULLPTR)
         << QApplication::translate("ConfigInput", "hotspot", Q_NULLPTR)
        );
        label_29->setText(QApplication::translate("ConfigInput", "Injection Rate", Q_NULLPTR));
        label_8->setText(QApplication::translate("ConfigInput", "VC Buffer Size", Q_NULLPTR));
        inputSpeedUp->setText(QApplication::translate("ConfigInput", "1", Q_NULLPTR));
        routingFxn->setText(QApplication::translate("ConfigInput", "dor", Q_NULLPTR));
        maxSamples->setText(QApplication::translate("ConfigInput", "10", Q_NULLPTR));
        internalSpeedUp->setText(QApplication::translate("ConfigInput", "1.0", Q_NULLPTR));
        creditDelay->setText(QApplication::translate("ConfigInput", "2", Q_NULLPTR));
        label_28->setText(QApplication::translate("ConfigInput", "Max Samples", Q_NULLPTR));
        label_15->setText(QApplication::translate("ConfigInput", "Routing Function", Q_NULLPTR));
        submitIPconfig->setText(QApplication::translate("ConfigInput", "Done !", Q_NULLPTR));
        label_34->setText(QApplication::translate("ConfigInput", "Sample Period", Q_NULLPTR));
        samplePeriod->setText(QApplication::translate("ConfigInput", "100", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ConfigInput: public Ui_ConfigInput {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGINPUT_H
