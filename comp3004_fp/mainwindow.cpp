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
    connect(ui->upButton, SIGNAL(released()), this, SLOT(handleUpButton()));
    connect(ui->downButton, SIGNAL(released()), this, SLOT(handleDownButton()));
    connect(ui->selectButton, SIGNAL(released()), this, SLOT(handleSelectButton()));
    connect(ui->connectionSlider, SIGNAL(sliderReleased()),this, SLOT(handleSlider()));

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

void MainWindow::handlePowerButton() {
    powerOn = !powerOn;
    ui->powerButton->setText(powerOn? "Off" : "On");
    setButtonState();

    selectCounter = powerOn? 1 : 0;




    qInfo("Power button pressed");
}

void MainWindow::handleUpButton() {
    //switch slect counter
    if(selectCounter == 1){
        int newIndex = timeWidget->currentRow() - 1;

        if (newIndex < 0) {
            newIndex = timeWidget->count() - 1;
        }

        timeWidget->setCurrentRow(newIndex);

    }
    else if (selectCounter == 3){
        int newIndex = sessionTypeWidget->currentRow() - 1;

        if (newIndex < 0) {
            newIndex = sessionTypeWidget->count() - 1;
        }

        sessionTypeWidget->setCurrentRow(newIndex);

    }

    else if (selectCounter == 4){
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
        int newIndex = timeWidget->currentRow() + 1;

        if (newIndex >= timeWidget->count()) {
            newIndex = 0;
        }

        timeWidget->setCurrentRow(newIndex);

    }
    else if(selectCounter == 3 ){
        int newIndex = sessionTypeWidget->currentRow() + 1;

        if (newIndex >= sessionTypeWidget->count()) {
            newIndex = 0;
        }

        sessionTypeWidget->setCurrentRow(newIndex);

    }

    else if(selectCounter==4){
        int newIndex = progressBar->value() - 1;

        if (newIndex < 0) {
            newIndex = 0;
        }

        progressBar->setValue(newIndex);


    }

    //add condition for changing time duration for custom

    qInfo("Down button pressed");
}

//need to increment selectCounter
void MainWindow::handleSelectButton() {

    if(selectCounter == 1 && timeWidget->currentRow()!= 2){
        //int currSelection = timeWidget->currentRow();
        //store index and value'
        selectCounter++;
    }
    selectCounter++;`


    qInfo("Select button pressed");

}



void MainWindow::customDuration(){



}

void MainWindow:: handleSlider(){

}




