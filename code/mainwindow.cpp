#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      powerOn(false),
      connection(8),
      batteryLevel(15),
      selectCounter(0),
      record(NULL),
      pausedTime(0)

{

    ui->setupUi(this);

    //ui->displayBar->setValue(connection);
    ui->batteryLevelBar->setValue(batteryLevel);
//    QGraphicsScene *scene = new QGraphicsScene(this);
//    ui->graphicsView->setWindowOpacity(0.0);
    //ui->graphicsView->setVisible(true);
    progressBar = ui->displayBar;
    slider= ui->connectionSlider;
    timeWidget = ui->timeWidget;
    sessionTypeWidget = ui->sessionTypeWidget;

    connect(ui->powerButton, SIGNAL(released()), this, SLOT(handlePowerButton()));
    connect(ui->powerButton, SIGNAL(pressed()), this, SLOT(handlePowerPressed()));
    connect(ui->upButton, SIGNAL(released()), this, SLOT(handleUpButton()));
    connect(ui->downButton, SIGNAL(released()), this, SLOT(handleDownButton()));
    connect(ui->selectButton, SIGNAL(released()), this, SLOT(handleSelectButton()));
    connect(ui->recordButton, SIGNAL(released()), this, SLOT(handleRecordButton()));
    connect(ui->connectionSlider, SIGNAL(valueChanged(int)),this, SLOT(handleSlider()));

    connect(&secondsTimer, SIGNAL(timeout()), this, SLOT (perSecondUpdate()));
    connect(&sessionTimer, SIGNAL(timeout()), this, SLOT (sessionEnd()));
    secondsTimer.start(1000);

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

    // do we need a list of previous dummy records?
    Session *s1 = new Session("Delta");
    Record *r1 = new Record(0, 0, s1);
    Record *r2 = new Record();      // can handle null sessions as well
    ui->historyWidget->addItem(r1->getRecordString());
    ui->historyWidget->addItem(r2->getRecordString());

    // set button state
    setButtonState();
}

MainWindow::~MainWindow()
{
    delete ui;
    // record should not delete if it is stored in history
    delete record;
    for(Record *r : recordList) {
        if(r != NULL) {
            delete r;
        }
    }

}

void MainWindow::setButtonState(){
    ui->upButton->setEnabled(powerOn);
    ui->downButton->setEnabled(powerOn);
    ui->selectButton->setEnabled(powerOn);
    ui->timeWidget->setEnabled(powerOn);
    ui->sessionTypeWidget->setEnabled(powerOn);
    ui->powerButton->setText(powerOn? "Off" : "On");
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
    if((releasedTime-pressedTime)>1){
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
        record->incrementIntensity();
        qDebug() << "intensity " << record->getIntensity();
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

        if (newIndex < 1) {
            newIndex = 1;
        }

        progressBar->setValue(newIndex);
        record->decrementIntensity();
        qDebug() << "intensity " << record->getIntensity();

    }

    qInfo("Down button pressed");
}

//need to increment selectCounter
void MainWindow::updateTimeLabel(){
    // int s = sessionTimer.remainingTime() / 1000;  // counts down
    int s = (sessionTimer.interval() - sessionTimer.remainingTime()) / 1000;     // counts up
    QString timeString = QString::number(s/60) + ((s%60 < 10) ? + ":0" + QString::number(s%60) : + ":" + QString::number(s%60));
    ui->timeElapsedLabel->setText(timeString);
}

void MainWindow::handleSelectButton() {


    //if(slider->value()<=1){       // to disable select button if connection is bad
    selectCounter++;
    int timeToSet = durationList[timeWidget->currentRow()];
    timeToSet = timeToSet? timeToSet : 60*60;       // 60*60 is an arbitrary max value
    sessionTimer.start((timeToSet+1) * 1000);
    updateTimeLabel();

    QString sessionName = sessionList[sessionTypeWidget->currentRow()];
    Session *s = new Session(sessionName);
    record->setSession(s);

    record->setDuration(durationList[timeWidget->currentRow()]);

    progressBar->setValue(record->getIntensity());
    qDebug() << "progress bar value on select " << progressBar->value();
    //}

//    if(selectCounter>=2 && timeWidget->currentRow()==2){
//        customDuration();
//    }

    qInfo("Select button pressed");


}

void MainWindow::handleRecordButton(){

}


void MainWindow::customDuration(){

}

void MainWindow::handleSlider(){
    QString str = "sssslider value: ";
    qDebug()<<str<<slider->value();

    if(slider->value()==2){
         ui->selectButton->setEnabled(false);
         ui->leftLightLabel->setStyleSheet("QLabel { background-color: red; color: white; }");
         ui->rightLightLabel->setStyleSheet("QLabel { background-color: red; color: white; }");
    }
    else {
        ui->selectButton->setEnabled(true);
        ui->leftLightLabel->setStyleSheet("QLabel { background-color: transparent; color: black; }");
        ui->rightLightLabel->setStyleSheet("QLabel { background-color: transparent; color: black; }");
    }

    if(slider->value()!=2 && pausedTime > 0){
        sessionTimer.start();
        pausedTime = 0;

    }

}

void MainWindow::perSecondUpdate() {
    // if session is on:
    // update battery level
    // update session timer
    if(selectCounter >= 2 && slider->value()<=1) {
        updateTimeLabel();
        batteryLevel = batteryLevel - (0.1 * (record->getIntensity() + 0.5));
        batteryLevel = batteryLevel < 0? 0 : batteryLevel;
        int displayBattery = ceil(batteryLevel);
        ui->batteryLevelBar->setValue(displayBattery);

        if(batteryLevel == 0) {
            handlePowerButton();    // temporary fix for now
            // should use the sessionEnd function to gracefully end session
        }
    }
    else if(slider->value()==2 && pausedTime == 0){
        // disconnect it
        // pause timer
        pausedTime = sessionTimer.remainingTime();
        sessionTimer.stop();
    }
}

// called when sessionTimer runs out
// can also be called when device powers off mid session
void MainWindow::sessionEnd() {
    sessionTimer.stop();
    selectCounter = 1;
    // perform soft off
    // change selectCounter
    // if !powerOn -- move clearing record information from handlePowerButton to here
    // give option to add session to record
}

