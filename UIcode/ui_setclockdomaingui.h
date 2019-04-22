/********************************************************************************
** Form generated from reading UI file 'setclockdomaingui.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETCLOCKDOMAINGUI_H
#define UI_SETCLOCKDOMAINGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetClockDomainGUI
{
public:
    QWidget *clockDomainsWidget;
    QFrame *routersFrame;
    QPushButton *submit;

    void setupUi(QWidget *SetClockDomainGUI)
    {
        if (SetClockDomainGUI->objectName().isEmpty())
            SetClockDomainGUI->setObjectName(QStringLiteral("SetClockDomainGUI"));
        SetClockDomainGUI->resize(1221, 477);
        clockDomainsWidget = new QWidget(SetClockDomainGUI);
        clockDomainsWidget->setObjectName(QStringLiteral("clockDomainsWidget"));
        clockDomainsWidget->setGeometry(QRect(770, 80, 291, 301));
        routersFrame = new QFrame(SetClockDomainGUI);
        routersFrame->setObjectName(QStringLiteral("routersFrame"));
        routersFrame->setGeometry(QRect(60, 80, 631, 301));
        routersFrame->setFrameShape(QFrame::StyledPanel);
        routersFrame->setFrameShadow(QFrame::Raised);
        submit = new QPushButton(SetClockDomainGUI);
        submit->setObjectName(QStringLiteral("submit"));
        submit->setGeometry(QRect(1028, 390, 101, 41));

        retranslateUi(SetClockDomainGUI);

        QMetaObject::connectSlotsByName(SetClockDomainGUI);
    } // setupUi

    void retranslateUi(QWidget *SetClockDomainGUI)
    {
        SetClockDomainGUI->setWindowTitle(QApplication::translate("SetClockDomainGUI", "Form", Q_NULLPTR));
        submit->setText(QApplication::translate("SetClockDomainGUI", "Submit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SetClockDomainGUI: public Ui_SetClockDomainGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETCLOCKDOMAINGUI_H
