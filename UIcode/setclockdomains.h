#ifndef SETCLOCKDOMAINS_H
#define SETCLOCKDOMAINS_H

#include <QWidget>

namespace Ui {
class SetClockDomains;
}

class SetClockDomains : public QWidget
{
    Q_OBJECT

public:
    explicit SetClockDomains(QWidget *parent = 0);
    ~SetClockDomains();

private slots:
    void on_generate_clicked();

    void on_clear_clicked();

    void on_submit_clicked();

    bool isRangeFormat(QString mString);

    QString getListElementsFromRange(QString mString);

signals:
    void submitClockDomainSignal(QStringList);


private:
    Ui::SetClockDomains *ui;
};

#endif // SETCLOCKDOMAINS_H
