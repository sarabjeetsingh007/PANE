/********************************************************************************
** Form generated from reading UI file 'heatmap.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HEATMAP_H
#define UI_HEATMAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HeatMap
{
public:
    QGraphicsView *trafficCanvas;
    QGraphicsView *header;
    QLabel *scale;
    QPushButton *print;
    QGraphicsView *sidenav;

    void setupUi(QWidget *HeatMap)
    {
        if (HeatMap->objectName().isEmpty())
            HeatMap->setObjectName(QStringLiteral("HeatMap"));
        HeatMap->resize(1322, 472);
        trafficCanvas = new QGraphicsView(HeatMap);
        trafficCanvas->setObjectName(QStringLiteral("trafficCanvas"));
        trafficCanvas->setGeometry(QRect(0, 60, 770, 411));
        header = new QGraphicsView(HeatMap);
        header->setObjectName(QStringLiteral("header"));
        header->setGeometry(QRect(0, 0, 771, 61));
        scale = new QLabel(HeatMap);
        scale->setObjectName(QStringLiteral("scale"));
        scale->setGeometry(QRect(890, 20, 81, 31));
        QFont font;
        font.setPointSize(15);
        font.setItalic(false);
        font.setUnderline(false);
        font.setStrikeOut(false);
        scale->setFont(font);
        scale->setAlignment(Qt::AlignCenter);
        scale->setWordWrap(false);
        print = new QPushButton(HeatMap);
        print->setObjectName(QStringLiteral("print"));
        print->setGeometry(QRect(310, 10, 89, 25));
        sidenav = new QGraphicsView(HeatMap);
        sidenav->setObjectName(QStringLiteral("sidenav"));
        sidenav->setGeometry(QRect(770, 0, 551, 471));

        retranslateUi(HeatMap);

        QMetaObject::connectSlotsByName(HeatMap);
    } // setupUi

    void retranslateUi(QWidget *HeatMap)
    {
        HeatMap->setWindowTitle(QApplication::translate("HeatMap", "Form", Q_NULLPTR));
        scale->setText(QApplication::translate("HeatMap", "<html><head/><body><p>Scale</p></body></html>", Q_NULLPTR));
        print->setText(QApplication::translate("HeatMap", "Print PDF", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class HeatMap: public Ui_HeatMap {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HEATMAP_H
