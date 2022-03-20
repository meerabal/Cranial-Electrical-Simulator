#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      powerOn(false),
      connection(8),
      batteryLevel(96),
      selectCounter(0),
      session(new Record())

{


    ui->setupUi(this);
    ui->powerButton->setText(powerOn? "Off" : "On");

    ///ui->displayBar->setValue(connection);
    ui->batteryLevelBar->setValue(batteryLevel);
    connect(ui->powerButton, SIGNAL(released()), this, SLOT(handlePowerButton()));
    connect(ui->powerButton, SIGNAL(pressed()), this, SLOT(handlePowerPressed()));
    connect(ui->upButton, SIGNAL(released()), this, SLOT(handleUpButton()));
    connect(ui->downButton, SIGNAL(released()), this, SLOT(handleDownButton()));
    connect(ui->selectButton, SIGNAL(released()), this, SLOT(handleSelectButton()));
    connect(ui->connectionSlider, SIGNAL(sliderReleased()),this, SLOT(handleSlider()));

    connect(&timer, SIGNAL(timeout()), this, SLOT (updateTimeLabel()));


    progressBar = ui->displayBar;

    slider= ui->connectionSlider;

    setButtonState();


    //Qlist widget's addItems takes only QStringList, i dont think it takes Qvector.
    timeWidget = ui->timeWidget;
    timeWidget->addItems(durationList);
    timeWidget->setCurrentRow(0);

    sessionTypeWidget = ui->sessionTypeWidget;
    sessionTypeWidget->addItems(sessionList);
    sessionTypeWidget->setCurrentRow(0);




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setButtonState(){
    ui->upButton->setEnabled(powerOn);
    ui->downButton->setEnabled(powerOn);
    ui->selectButton->setEnabled(powerOn);

    slider->setEnabled(powerOn);
    slider->setValue(0);

}
void MainWindow::handlePowerPressed(){
    pressedTime = QDateTime::currentSecsSinceEpoch();
}

void MainWindow::handlePowerButton() {
    quint64 releasedTime = QDateTime::currentSecsSinceEpoch();
    if((releasedTime-pressedTime)>1){
        powerOn = !powerOn;
        ui->powerButton->setText(powerOn? "Off" : "On");
        setButtonState();
        selectCounter = powerOn? 1 : 0;
        timeWidget->setCurrentRow(0);
        //timeWidget->setEnabled(powerOn);
        //timeWidget->setSelectionMode(QAbstractItemView::NoSelection);
       // sess
    }
    else if(powerOn){
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


    }

    qInfo("Down button pressed");
}

//need to increment selectCounter
void MainWindow::updateTimeLabel(){

    int s = time.elapsed()/1000;
    //int m = (s/60) % 60;
    //s = s % 60;
    QString timeString =QString::number(s/60) + ((s%60 < 10) ? + ":0" + QString::number(s%60) : + ":" + QString::number(s%60));

   // ui->timeElapsedLabel->setText((QDateTime::fromTime_t(s).toUTC().toString("hh:mm:ss")));
    //ui->timeElapsedLabel->setText(QString("Time elapsed %01:%02").arg(m).arg(s));
    ui->timeElapsedLabel->setText(timeString);


}
void MainWindow::handleSelectButton() {

    selectCounter++;
    timer.start(1000);
    time.start();
    updateTimeLabel();

    if(selectCounter>=2 && timeWidget->currentRow()==2){
        customDuration();
    }
    qInfo("Select button pressed");


}



void MainWindow::customDuration(){




}

void MainWindow:: handleSlider(){

}




