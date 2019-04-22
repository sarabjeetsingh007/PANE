#ifndef SETCLOCKDOMAINGUI_H
#define SETCLOCKDOMAINGUI_H

#include <QWidget>
#include <QDesktopWidget>
#include <QPushButton>
#include <QLineEdit>

namespace Ui {
class SetClockDomainGUI;
}

class SetClockDomainGUI : public QWidget
{
    Q_OBJECT

public:
    explicit SetClockDomainGUI(QWidget *parent = 0);
    ~SetClockDomainGUI();

private:
    Ui::SetClockDomainGUI *ui;
    QDesktopWidget widget;
    QRect rec;
    QList<QList <QLineEdit*>>  clockDomainsArray;
    QList <QPushButton*>  clockDomainSelectionButton;
    QList<QLineEdit*> assignedRoutersArray;
    int generatedClockDomains;
    QList<QString> selectionColors = {"#ecc41c", "#03743e", "#14bfb2", "#31ff40", "#fa9300", "#ba0bec", "#aa0000"};

    QString selectedClockDomainColor;
    bool isClockDomainSelected = false;
    QString slectedClockdomainIndex;

    QList<QList<QPushButton*>> routerMatrix;
    QList<QList<QString>> routerMatrixClockDomain;
    int rows;
    int cols;
    QList<QList <QString>>  clockDomainsClientValueArray;
    QList<QString> assignedRoutersPerClockDomainArray;

//    QList<QList <QLineEdit*>>  clockDomainsArraySignal;
//    QList<QLineEdit*> assignedRoutersArraySignal;


private slots:
    void routersButtonGroup(QAbstractButton *mButton);
    void createRouterMatrix();
    void createClockDomainList();
    void clockDomainOnSelected(QAbstractButton *mButton );
    void routerOnSelected(QAbstractButton *mButton ) ;

    void on_submit_clicked();

protected:

public slots:
    void submitClockDomainDataToGUISlot(const QStringList &clockDomainData);

signals:
    void submitClockDomainSignal(QStringList);

};

#endif // SETCLOCKDOMAINGUI_H
