#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.setStyleSheet("QMainWindow {background: 'Ivory';}");
    //"background-image:url(\"4.jpg\"); background-position: center; "

    w.show();

    return a.exec();
}
