#include "sweeprunmethod.h"
#include "ui_sweeprunmethod.h"
#include "mainwindow.h"
#include<QMessageBox>
#include <QDoubleValidator>

SweepRunMethod::SweepRunMethod(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SweepRunMethod)
{
    ui->setupUi(this);

//    ui->trafficPatternDropdown->addItem("neighbor");
//    ui->trafficPatternDropdown->addItem("uniform");
//    ui->trafficPatternDropdown->addItem("tornado");
//    ui->trafficPatternDropdown->addItem("shuffle");
//    ui->trafficPatternDropdown->addItem("transpose");
//    ui->trafficPatternDropdown->addItem("bitcomp");
//    ui->trafficPatternDropdown->addItem("bitrev");

//    ui->routingFunctionDropdown->addItem("dor");
//    ui->routingFunctionDropdown->addItem("xy-yx");
//    ui->routingFunctionDropdown->addItem("adaptive xy-yx");
//    ui->routingFunctionDropdown->addItem("romm");
//    ui->routingFunctionDropdown->addItem("min-adapt");
//    ui->routingFunctionDropdown->addItem("planar adapt");




    ui->injectionRateGroupBox->setStyleSheet("QGroupBox#injectionRateGroupBox { border: 0px;}");
    ui->packetSizeGroupBox->setStyleSheet("QGroupBox#packetSizeGroupBox { border: 0px; }");
    ui->realBenchmarksGroupBox->setStyleSheet("QGroupBox#realBenchmarksGroupBox { border: 0px; }");
    ui->bufferOrganizationGroupBox->setStyleSheet("QGroupBox#bufferOrganizationGroupBox { border: 0px; }");
    ui->routingFunctionGroupBox->setStyleSheet("QGroupBox#routingFunctionGroupBox { border: 0px; }");
    ui->trafficPatternGroupBox->setStyleSheet("QGroupBox#trafficPatternGroupBox { border: 0px; }");


    ui->injectionRateGroupBox->setVisible(0);
    ui->packetSizeGroupBox->setVisible(0);
    ui->realBenchmarksGroupBox->setVisible(0);
    ui->bufferOrganizationGroupBox->setVisible(0);
    ui->routingFunctionGroupBox->setVisible(0);
    ui->trafficPatternGroupBox->setVisible(0);

//    ui->routingFunctionDropdown->setVisible(0);
//    ui->trafficPatternDropdown->setVisible(0);


    // Initiating checkbox indexes
    initRoutingFunctionCheckbox();
    initTrafficPatternCheckbox();


    // Setting validations for Line edits
    QDoubleValidator *doubleVal = new QDoubleValidator( 0.00, 999.00, 5, this );
    ui->injectionRateStart->setValidator(doubleVal);
    ui->injectionRateEnd->setValidator(doubleVal);
    ui->injectionRateIncrement->setValidator(doubleVal);
    ui->packetSizeStart->setValidator(doubleVal);
    ui->packetSizeEnd->setValidator(doubleVal);
    ui->bufferOrganization_noVCs_start->setValidator(doubleVal);
    ui->bufferOrganization_noVCs_end->setValidator(doubleVal);
    ui->bufferOrganization_bufferSize_start->setValidator(doubleVal);
    ui->bufferOrganization_bufferSize_end->setValidator(doubleVal);




}

SweepRunMethod::~SweepRunMethod()
{
    delete ui;
}


void SweepRunMethod::initRoutingFunctionCheckbox() {
    QButtonGroup *routingFunctionGroup =  ui->routingFunctionButtonGroup;
    routingFunctionGroup->setId(ui->routingFunctionCheckbox_1, 0);
    routingFunctionGroup->setId(ui->routingFunctionCheckbox_2, 1);
    routingFunctionGroup->setId(ui->routingFunctionCheckbox_3, 2);
    routingFunctionGroup->setId(ui->routingFunctionCheckbox_4, 3);
    routingFunctionGroup->setId(ui->routingFunctionCheckbox_5, 4);
    routingFunctionGroup->setId(ui->routingFunctionCheckbox_6, 5);
    routingFunctionGroup->setExclusive(false);
}

void SweepRunMethod::initTrafficPatternCheckbox() {
    QButtonGroup *trafficPatternGroup =  ui->trafficPatternButtonGroup;
    trafficPatternGroup->setId(ui->trafficPatternCheckbox_1, 0);
    trafficPatternGroup->setId(ui->trafficPatternCheckbox_2, 1);
    trafficPatternGroup->setId(ui->trafficPatternCheckbox_3, 2);
    trafficPatternGroup->setId(ui->trafficPatternCheckbox_4, 3);
    trafficPatternGroup->setId(ui->trafficPatternCheckbox_5, 4);
    trafficPatternGroup->setId(ui->trafficPatternCheckbox_6, 5);
    trafficPatternGroup->setId(ui->trafficPatternCheckbox_7, 6);
    trafficPatternGroup->setExclusive(false);
}

QString SweepRunMethod::compileCheckedRoutingFunctionOptions() {

    QString mCompiledData;

    QList<QCheckBox*> checkboxes;
    checkboxes.append(ui->routingFunctionCheckbox_1);
    checkboxes.append(ui->routingFunctionCheckbox_2);
    checkboxes.append(ui->routingFunctionCheckbox_3);
    checkboxes.append(ui->routingFunctionCheckbox_4);
    checkboxes.append(ui->routingFunctionCheckbox_5);
    checkboxes.append(ui->routingFunctionCheckbox_6);

    QButtonGroup *routingFunctionGroup =  ui->routingFunctionButtonGroup;

    for (int i=0; i<6; i++) {
        if (checkboxes[i]->isChecked()) {
            if (mCompiledData != "") {
                mCompiledData += ",";
            }
            mCompiledData += QString::number(routingFunctionGroup->id(checkboxes[i]));
        }
    }

    return mCompiledData;
}


QString SweepRunMethod::compileCheckedTrafficPatternOptions() {

    QString mCompiledData;

    QList<QCheckBox*> checkboxes;
    checkboxes.append(ui->trafficPatternCheckbox_1);
    checkboxes.append(ui->trafficPatternCheckbox_2);
    checkboxes.append(ui->trafficPatternCheckbox_3);
    checkboxes.append(ui->trafficPatternCheckbox_4);
    checkboxes.append(ui->trafficPatternCheckbox_5);
    checkboxes.append(ui->trafficPatternCheckbox_6);
    checkboxes.append(ui->trafficPatternCheckbox_7);

    QButtonGroup *trafficPatternGroup =  ui->trafficPatternButtonGroup;

    for (int i=0; i<7; i++) {
        if (checkboxes[i]->isChecked()) {
            if (mCompiledData != "") {
                mCompiledData += ",";
            }
            mCompiledData += QString::number(trafficPatternGroup->id(checkboxes[i]));
        }
    }

    return mCompiledData;
}

void SweepRunMethod::on_runCurrentMethod_clicked()
{
//    QButtonGroup *runningMethod =  ui->runningMethod;
//    runningMethod->setId(ui->injectionRateRun, 0);
//    runningMethod->setId(ui->packetSizeRun, 1);
//    runningMethod->setId(ui->realBenchmarksRun, 2);
//    runningMethod->setId(ui->routingFunctionsRun, 3);
//    runningMethod->setId(ui->trafficPatternRun, 4);
//    runningMethod->setId(ui->bufferOrganizationRun, 5);


//    int runningMethodIndex = runningMethod->checkedId();
//    QProcess mProcess;

//    switch (runningMethodIndex) {
//        case 0:
//            mProcess.start("gnome-terminal -x sh -c \"(cd  ../PANE/Scripts/make_dir/; ./run_injectionrate.sh;)\"");
//            qDebug() << "Injection Rate run";
//            break;
//        case 1:
//            mProcess.start("gnome-terminal -x sh -c \"(cd  ../PANE/Scripts/make_dir/; ./run_packetsize.sh;)\"");
//            qDebug() << "Packet Size  run";
//            break;
//        case 2:
//            mProcess.start("gnome-terminal -x sh -c \"(cd  ../PANE/Scripts/make_dir/; ./run_real_benchmarks.sh;)\"");
//            qDebug() << "Real Benchmark run";
//            break;
//        case 3:
//            mProcess.start("gnome-terminal -x sh -c \"(cd  ../PANE/Scripts/make_dir/; ./run_routingfunc.sh;)\"");
//            qDebug() << "Routing Function run";
//            break;
//        case 4:
//            mProcess.start("gnome-terminal -x sh -c \"(cd  ../PANE/Scripts/make_dir/; ./run_trafficpattern.sh;)\"");
//            qDebug() << "Traffic Pattern run";
//            break;
//        case 5:
//            mProcess.start("gnome-terminal -x sh -c \"(cd  ../PANE/Scripts/make_dir/; ./run_bufferorganization.sh;)\"");
//            qDebug() << "Buffer Organization run";
//            break;
//    }

//    mProcess.waitForFinished();
//    qDebug() <<runningMethodIndex;

    // Executing commands


    QString routingFunctionData = compileCheckedRoutingFunctionOptions();
    QString trafficPatternData = compileCheckedTrafficPatternOptions();


    QMessageBox msgRunSuccessAlert;

    if (checkValidationOnRuntime()) {
        msgRunSuccessAlert.setText("Cannot leave empty fields");
        msgRunSuccessAlert.exec();
        return;
    }


    QProcess mProcess;

    if (ui->InjectionRate->isChecked()) {
        QString injectionRateSTart = ui->injectionRateStart->text();
        QString injectionRateEnd = ui->injectionRateEnd->text();
        QString injectionRateIncrement = ui->injectionRateIncrement->text();
        QProcess::execute ("sed -i \"/injectionRate = / c injectionRate = [" + injectionRateSTart+ ", " + injectionRateEnd + ", " + injectionRateIncrement + "]\" ../PANE/Scripts/running_fxn_generator.py");
        qDebug() << "Injection rate checked";
    }
    else {
        QProcess::execute ("sed -i \"/injectionRate = / c injectionRate = []\" ../PANE/Scripts/running_fxn_generator.py");

    }


    if (ui->packetSize->isChecked()) {
        QString packetSizeStart = ui->packetSizeStart->text();
        QString packetSizeEnd = ui->packetSizeEnd->text();
        QProcess::execute ("sed -i \"/packetSize = / c packetSize = [" + packetSizeStart+ ", " + packetSizeEnd + ", 1]\" ../PANE/Scripts/running_fxn_generator.py");
        qDebug()<< "Packet size selected";
    }
    else {
        QProcess::execute ("sed -i \"/packetSize = / c packetSize = []\" ../PANE/Scripts/running_fxn_generator.py");

    }


    if (ui->realBenchmarks->isChecked()) {
        qDebug()<< "real Benchmarks selected";
    }



    if (ui->routingFunction->isChecked()) {
        QProcess::execute ("sed -i \"/routingFunctionData = / c routingFunctionData = '" + routingFunctionData + "'\" ../PANE/Scripts/running_fxn_generator.py");
        qDebug()<< "routing Function selected";
    }
    else {
        QProcess::execute ("sed -i \"/routingFunctionData = / c routingFunctionData = ''\" ../PANE/Scripts/running_fxn_generator.py");
    }


    if (ui->trafficPattern->isChecked()) {
        QProcess::execute ("sed -i \"/trafficPatternData = / c trafficPatternData = '" + trafficPatternData + "'\" ../PANE/Scripts/running_fxn_generator.py");
        qDebug()<< "traffic Pattern selected";
    }
    else {
        QProcess::execute ("sed -i \"/trafficPatternData = / c trafficPatternData = ''\" ../PANE/Scripts/running_fxn_generator.py");
    }


    if (ui->bufferOrganization->isChecked()) {
        QString noVCsStart = ui->bufferOrganization_noVCs_start->text();
        QString noVCsEnd = ui->bufferOrganization_noVCs_end->text();
        QString bufferSizeStart = ui->bufferOrganization_bufferSize_start->text();
        QString bufferSizeEnd = ui->bufferOrganization_bufferSize_end->text();
        QProcess::execute ("sed -i \"/bufferOrganization_VCs = / c bufferOrganization_VCs = [" + noVCsStart+ ", " + noVCsEnd + ", 1]\" ../PANE/Scripts/running_fxn_generator.py");
        QProcess::execute ("sed -i \"/bufferOrganization_bufferSize = / c bufferOrganization_bufferSize = [" + bufferSizeStart+ ", " + bufferSizeEnd + ", 1]\" ../PANE/Scripts/running_fxn_generator.py");

        qDebug()<< "buffer Organization selected";
    }
    else {
        QProcess::execute ("sed -i \"/bufferOrganization_VCs = / c bufferOrganization_VCs = []\" ../PANE/Scripts/running_fxn_generator.py");
        QProcess::execute ("sed -i \"/bufferOrganization_bufferSize = / c bufferOrganization_bufferSize = []\" ../PANE/Scripts/running_fxn_generator.py");
    }




    mProcess.start("gnome-terminal -x sh -c \"(cd ../PANE/Scripts/ ; python running_fxn_generator.py;)\"");
    mProcess.waitForFinished();


    msgRunSuccessAlert.setText("Run Successful!");
    msgRunSuccessAlert.exec();



}

void SweepRunMethod::on_InjectionRate_toggled(bool checked)
{
    if (checked){
        ui->injectionRateGroupBox->setVisible(1);
    }
    else {
        ui->injectionRateGroupBox->setVisible(0);
    }

}

void SweepRunMethod::on_packetSize_toggled(bool checked)
{
    if (checked){
        ui->packetSizeGroupBox->setVisible(1);
    }
    else {
        ui->packetSizeGroupBox->setVisible(0);
    }
}

void SweepRunMethod::on_realBenchmarks_toggled(bool checked)
{
    if (checked){
        ui->realBenchmarksGroupBox->setVisible(1);
    }
    else {
        ui->realBenchmarksGroupBox->setVisible(0);
    }
}

void SweepRunMethod::on_bufferOrganization_toggled(bool checked)
{
    if (checked){
        ui->bufferOrganizationGroupBox->setVisible(1);
    }
    else {
        ui->bufferOrganizationGroupBox->setVisible(0);
    }
}

void SweepRunMethod::on_routingFunction_toggled(bool checked)
{
    if (checked){
        ui->routingFunctionGroupBox->setVisible(1);
    }
    else {
        ui->routingFunctionGroupBox->setVisible(0);
    }
}

void SweepRunMethod::on_trafficPattern_toggled(bool checked)
{
    if (checked){
        ui->trafficPatternGroupBox->setVisible(1);
    }
    else {
        ui->trafficPatternGroupBox->setVisible(0);
    }
}

bool SweepRunMethod::checkValidationOnRuntime(){
    if (ui->InjectionRate->isChecked()){
        if (ui->injectionRateStart->text().isEmpty() || ui->injectionRateEnd->text().isEmpty() || ui->injectionRateIncrement->text().isEmpty()) {
            return true;
        }
    }

    if(ui->packetSize->isChecked()){
        if (ui->packetSizeStart->text().isEmpty() || ui->packetSizeEnd->text().isEmpty()) {
            return true;
        }
    }

    if(ui->bufferOrganization->isChecked()){
        if (ui->bufferOrganization_noVCs_start->text().isEmpty() || ui->bufferOrganization_noVCs_end->text().isEmpty() || ui->bufferOrganization_bufferSize_start->text().isEmpty() || ui->bufferOrganization_bufferSize_end->text().isEmpty()) {
            return true;
        }
    }

    return false;
}

void SweepRunMethod::on_back_clicked()
{
    MainWindow *mMainWindow =new MainWindow;
    this->hide();
    mMainWindow->show();
}
