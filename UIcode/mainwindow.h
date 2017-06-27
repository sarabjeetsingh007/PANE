#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtCore>
#include<QtGui>
#include<QGraphicsScene>
#include<QGraphicsEllipseItem>
#include<QGraphicsLineItem>
#include<QPainter>
#include<qpalette.h>
#include<QPrinter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:
//    void on_print_clicked();
//    void on_build_clicked();
//    void on_run_clicked();
//    void on_browse_clicked();
//    void on_browse_exe_clicked();
//    void create_exe_command();
//    void on_browse_config_clicked();
//    void on_radioButton_clicked();
//    void on_radioButton_2_clicked();
//    void on_checkBox_4_clicked();

//    void on_comboBox_currentIndexChanged(const QString &arg1);

//    void on_lineEdit_textChanged(const QString &arg1);


    void on_setIPconfig_clicked();


//    void on_pushButton_clicked();

    void on_build_clicked();

    void on_run_clicked();

    void on_browseConfigFile_clicked();

    void on_setClockDomains_clicked();

    void on_clockDomainConfig_manual_toggled(bool checked);

    void setDefaultClockDomainConfig();

public slots:
    void setConfigParamLinked(QMap<QString, QString> *configData);
    void bar1();
//    void mySlot(QString);
    void mySlot(const QStringList &arg1);

    void submitIpConfSlot(const QStringList &configData);

    void submitClockDomainDataSlot(const QStringList &clockDomainData);

signals:


private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsLineItem *line;
};

#endif // MAINWINDOW_H
