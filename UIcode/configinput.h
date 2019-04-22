#ifndef CONFIGINPUT_H
#define CONFIGINPUT_H

#include <QWidget>
#include <QGraphicsScene>
#include <QMap>

namespace Ui {
class ConfigInput;
}

class ConfigInput : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigInput(QWidget *parent = 0);
    ~ConfigInput();

public:
    Ui::ConfigInput *ui;


signals:
    void foo();
    void mySignal(QStringList);
    void submitIpConfSignal(QStringList);

public slots:


private slots:
//        void on_pushButton_clicked();

        void on_submitIPconfig_clicked();

        void on_simulationData_Synthetic_clicked();

        void on_simulationData_Real_clicked();

        void on_powerCalculation_clicked();

public:
        void method1()
           {
                /* some lines of code executed before this line*/

                 emit foo(); /* This is the firing/raising of the signal 'foo'. */

                /* some lines of code executed after this line*/
           }
};

#endif // CONFIGINPUT_H
