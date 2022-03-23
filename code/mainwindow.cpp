#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      powerOn(false),
      connection(8),
      batteryLevel(96),
      selectCounter(0),
      record(NULL)

{

    ui->setupUi(this);

    //ui->displayBar->setValue(connection);
    ui->batteryLevelBar->setValue(batteryLevel);
    progressBar = ui->displayBar;
    slider= ui->connectionSlider;
    timeWidget = ui->timeWidget;
    sessionTypeWidget = ui->sessionTypeWidget;

    connect(ui->powerButton, SIGNAL(released()), this, SLOT(handlePowerButton()));
    connect(ui->powerButton, SIGNAL(pressed()), this, SLOT(handlePowerPressed()));
    connect(ui->upButton, SIGNAL(released()), this, SLOT(handleUpButton()));
    connect(ui->downButton, SIGNAL(released()), this, SLOT(handleDownButton()));
    connect(ui->selectButton, SIGNAL(released()), this, SLOT(handleSelectButton()));
    connect(ui->connectionSlider, SIGNAL(sliderReleased()),this, SLOT(handleSlider()));

    connect(&timer, SIGNAL(timeout()), this, SLOT (updateTimeLabel()));

    init();

}

void MainWindow::init() {
    ui->powerButton->setText(powerOn? "Off" : "On");

    // populate duration list
    durationList << 20 << 45 << 0;
    for(int time : durationList) {
        QString timeStr = QString::number(time) + " min";
        if(time == 0) {
            timeStr = "User Defined";
        }
        timeWidget->addItem(timeStr);
    }

    // populate session list
    sessionList << "Beta" << "Delta" << "Omega";
    sessionTypeWidget->addItems(sessionList);

    // set button state
    setButtonState();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete record;
}

void MainWindow::setButtonState(){
    ui->upButton->setEnabled(powerOn);
    ui->downButton->setEnabled(powerOn);
    ui->selectButton->setEnabled(powerOn);
    ui->timeWidget->setEnabled(powerOn);
    ui->sessionTypeWidget->setEnabled(powerOn);
    timeWidget->setCurrentRow(0);
    sessionTypeWidget->setCurrentRow(0);

    slider->setEnabled(powerOn);
    slider->setValue(0);
    progressBar->setValue(0);

}
void MainWindow::handlePowerPressed(){
    pressedTime = QDateTime::currentSecsSinceEpoch();
}

void MainWindow::handlePowerButton() {
    quint64 releasedTime = QDateTime::currentSecsSinceEpoch();
    if((releasedTime-pressedTime)>0.5){
        // if battery is too low to start device
        if(!powerOn && batteryLevel == 0) {
            return;
        }
        powerOn = !powerOn;
        setButtonState();
        selectCounter = powerOn? 1 : 0;
        if(powerOn) {
            record = new Record();
        }
        else {
            delete record;
            record = NULL;
        }
        //timeWidget->setEnabled(powerOn);
        //timeWidget->setSelectionMode(QAbstractItemView::NoSelection);
       // sess
    }
    else if(powerOn && selectCounter == 1){
        int newIndex = timeWidget->currentRow() + 1;

        if (newIndex >= timeWidget->count()) {
            newIndex = 0;
        }

        timeWidget->setCurrentRow(newIndex);

    }

    qInfo("Power button pressed");
}

void MainWindow::handleUpButton() {
    //switch slect counter

    if(selectCounter == 1){
        int newIndex = sessionTypeWidget->currentRow() - 1;

        if (newIndex < 0) {
            newIndex = sessionTypeWidget->count() - 1;
        }

        sessionTypeWidget->setCurrentRow(newIndex);
    }



    else if (selectCounter >= 2){
        int newIndex = progressBar->value() + 1;

        if (newIndex > progressBar->maximum()) {
            newIndex = 8;
        }

        progressBar->setValue(newIndex);
        record->setIntensity(newIndex);

    }

    qInfo("Up button pressed");


}

void MainWindow::handleDownButton() {
       //switch slect counter
    if(selectCounter == 1){
        int newIndex = sessionTypeWidget->currentRow() + 1;

        if (newIndex >= sessionTypeWidget->count()) {
            newIndex = 0;
        }

        sessionTypeWidget->setCurrentRow(newIndex);


    }
    else if(selectCounter >= 2){
        int newIndex = progressBar->value() - 1;

        if (newIndex < 0) {
            newIndex = 0;
        }

        progressBar->setValue(newIndex);
        record->setIntensity(newIndex);

    }

    qInfo("Down button pressed");
}

//need to increment selectCounter
void MainWindow::updateTimeLabel(){

    int s = time.elapsed()/1000;
    QString timeString = QString::number(s/60) + ((s%60 < 10) ? + ":0" + QString::number(s%60) : + ":" + QString::number(s%60));

    ui->timeElapsedLabel->setText(timeString);


}
void MainWindow::handleSelectButton() {

    selectCounter++;
    timer.start(1000);
    time.start();
    updateTimeLabel();

    QString sessionName = sessionList[sessionTypeWidget->currentRow()];
    Session *s = new Session(sessionName);
    record->setSession(s);
    record->setDuration(durationList[timeWidget->currentRow()]);

    progressBar->setValue(record->getIntensity());

//    if(selectCounter>=2 && timeWidget->currentRow()==2){
//        customDuration();
//    }

    qInfo("Select button pressed");


}



void MainWindow::customDuration(){




}

void MainWindow:: handleSlider(){

}




