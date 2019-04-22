#ifndef HEATMAP_H
#define HEATMAP_H

#include <QWidget>
#include <QGraphicsScene>
#include <QMap>

namespace Ui {
class HeatMap;
}

class HeatMap : public QWidget
{
    Q_OBJECT

public:
    explicit HeatMap(QWidget *parent = 0);
    ~HeatMap();

private:
    Ui::HeatMap *ui;
    QGraphicsScene  *header;
    QGraphicsScene  *trafficCanvas;
    QGraphicsScene  *sidenav;
    int     screenWidth;
    int     screenHeight;
    QPainter *mPainter;
    QRect rec;

private slots:
    void addSideNav();
    void addHeader();

//    void on_print_clicked();
    void addScaleValues(int labelOffsetX, int labelOffsetY, QString minVal, QString maxVal, QString scaleName);
    void addTrafficCanvas();
    void getRouterStats();
    void createRouterPacketsData(QList<QList<int>> packetsData);
    void createHorizontalLinkData(QList<QList<int>> linkData);
    void createVerticalLinkData(QList<QList<int>> linkData);

    QList<double> findMinMax(QList<double> colorGeneratorValues);
    QList<QString> setColorGradientSamples(QList<double> colorGeneratorValues);
    int colorInterpolate(int pBegin, int pEnd, int pStep,int pMax);
    int getPreferredColor(int data, double min, double max, QList<double> colorGeneratorValues);

    void paintRouterMatrix(int rows, int cols, QList<QList <QMap <QString, int>>> packetInfoMatrix);
    void paintHorizontalSignalPathMatrix(int rows, int cols, QList<QList <QMap <QString, int>>> trafficMatrix);
    void paintVerticalSignalPathMatrix(int rows, int cols, QList<QList <QMap <QString, int>>> trafficMatrix);
    void paintRouter(QPoint offsets, QMap<QString, int> routerPacketsInfo);
    void paintHorizontalSignalPath(QPoint offsets, QMap<QString, int> horizontalSignalTraffic);
    void paintVerticalSignalPath(QPoint offsets, QMap<QString, int> verticalSignalTraffic);
    void paintRouterUpper(QPoint offsets, int packetsCount);
    void paintRouterLower(QPoint offsets, int packetsCount);
    void paintHorizontalArrowRight(QPoint offsets, int trafficValue);
    void paintHorizontalArrowLeft(QPoint offsets, int trafficValue);
    void paintVerticalArrowUp(QPoint offsets, int trafficValue);
    void paintVerticalArrowDown(QPoint offsets, int trafficValue);


    void on_print_clicked();

    void routerLinksDataArrayInit();

public slots:
    void submitRouterDataToHeatMapSlot(const QStringList &routerData);

};

#endif // HEATMAP_H
