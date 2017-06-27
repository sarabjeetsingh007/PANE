#ifndef SWEEPRUNMETHOD_H
#define SWEEPRUNMETHOD_H

#include <QWidget>

namespace Ui {
class SweepRunMethod;
}

class SweepRunMethod : public QWidget
{
    Q_OBJECT

public:
    explicit SweepRunMethod(QWidget *parent = 0);
    ~SweepRunMethod();

private slots:
    void on_runCurrentMethod_clicked();

    void on_InjectionRate_toggled(bool checked);

    void on_packetSize_toggled(bool checked);

    void on_realBenchmarks_toggled(bool checked);

    void on_bufferOrganization_toggled(bool checked);

    void on_routingFunction_toggled(bool checked);

    void on_trafficPattern_toggled(bool checked);

    bool checkValidationOnRuntime();

    void on_back_clicked();

    void initRoutingFunctionCheckbox();

    void initTrafficPatternCheckbox();

    QString compileCheckedRoutingFunctionOptions();

    QString compileCheckedTrafficPatternOptions();

private:
    Ui::SweepRunMethod *ui;
};

#endif // SWEEPRUNMETHOD_H
