/********************************************************************************
** Form generated from reading UI file 'setclockdomains.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETCLOCKDOMAINS_H
#define UI_SETCLOCKDOMAINS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetClockDomains
{
public:
    QLabel *header;
    QFrame *line;
    QLineEdit *noOfClockDomains;
    QPushButton *generate;
    QLabel *label_14;
    QFrame *line_2;
    QWidget *mWidget;
    QPushButton *clear;
    QPushButton *submit;
    QFrame *separator;
    QLabel *info_message;
    QPushButton *clockDomainSetGUI;

    void setupUi(QWidget *SetClockDomains)
    {
        if (SetClockDomains->objectName().isEmpty())
            SetClockDomains->setObjectName(QStringLiteral("SetClockDomains"));
        SetClockDomains->resize(1258, 781);
        header = new QLabel(SetClockDomains);
        header->setObjectName(QStringLiteral("header"));
        header->setGeometry(QRect(500, 20, 251, 31));
        line = new QFrame(SetClockDomains);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(40, 60, 1171, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        noOfClockDomains = new QLineEdit(SetClockDomains);
        noOfClockDomains->setObjectName(QStringLiteral("noOfClockDomains"));
        noOfClockDomains->setGeometry(QRect(220, 100, 100, 31));
        noOfClockDomains->setMaximumSize(QSize(100, 16777215));
        generate = new QPushButton(SetClockDomains);
        generate->setObjectName(QStringLiteral("generate"));
        generate->setGeometry(QRect(340, 100, 141, 31));
        label_14 = new QLabel(SetClockDomains);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(50, 100, 181, 31));
        line_2 = new QFrame(SetClockDomains);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(40, 140, 1171, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        mWidget = new QWidget(SetClockDomains);
        mWidget->setObjectName(QStringLiteral("mWidget"));
        mWidget->setGeometry(QRect(40, 170, 1171, 41));
        clear = new QPushButton(SetClockDomains);
        clear->setObjectName(QStringLiteral("clear"));
        clear->setGeometry(QRect(500, 100, 141, 31));
        submit = new QPushButton(SetClockDomains);
        submit->setObjectName(QStringLiteral("submit"));
        submit->setGeometry(QRect(1060, 260, 141, 31));
        separator = new QFrame(SetClockDomains);
        separator->setObjectName(QStringLiteral("separator"));
        separator->setGeometry(QRect(40, 230, 1171, 20));
        separator->setFrameShape(QFrame::HLine);
        separator->setFrameShadow(QFrame::Sunken);
        info_message = new QLabel(SetClockDomains);
        info_message->setObjectName(QStringLiteral("info_message"));
        info_message->setGeometry(QRect(470, 340, 321, 41));
        clockDomainSetGUI = new QPushButton(SetClockDomains);
        clockDomainSetGUI->setObjectName(QStringLiteral("clockDomainSetGUI"));
        clockDomainSetGUI->setGeometry(QRect(660, 100, 191, 31));

        retranslateUi(SetClockDomains);

        QMetaObject::connectSlotsByName(SetClockDomains);
    } // setupUi

    void retranslateUi(QWidget *SetClockDomains)
    {
        SetClockDomains->setWindowTitle(QApplication::translate("SetClockDomains", "Form", Q_NULLPTR));
        header->setText(QApplication::translate("SetClockDomains", "<html><head/><body><p align=\"center\"><span style=\" font-size:20pt; color:#901c1c;\">Set Clock Domains</span></p></body></html>", Q_NULLPTR));
        noOfClockDomains->setText(QString());
        generate->setText(QApplication::translate("SetClockDomains", "Generate", Q_NULLPTR));
        label_14->setText(QApplication::translate("SetClockDomains", "<html><head/><body><p><span style=\" font-size:12pt;\">No . of clock domains:</span></p></body></html>", Q_NULLPTR));
        clear->setText(QApplication::translate("SetClockDomains", "Clear", Q_NULLPTR));
        submit->setText(QApplication::translate("SetClockDomains", "Submit", Q_NULLPTR));
        info_message->setText(QApplication::translate("SetClockDomains", "<html><head/><body><p align=\"center\"><span style=\" font-size:20pt; color:#ef2929;\">Generate Clock Domains</span></p></body></html>", Q_NULLPTR));
        clockDomainSetGUI->setText(QApplication::translate("SetClockDomains", "Switch to GUI mode", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SetClockDomains: public Ui_SetClockDomains {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETCLOCKDOMAINS_H
