#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      powerOn(false),
      connection(8),
      record(NULL),
      pausedTime(0),
      batteryLevel(15),
      selectCounter(PHASE_OFF),
      criticalLevel(10),
      batteryFlag(true),
      connWaitTime(0)

{

    ui->setupUi(this);
    progressBar = ui->displayBar;
    slider= ui->connectionSlider;
    timeWidget = ui->timeWidget;
    sessionTypeWidget = ui->sessionTypeWidget;
//    ui->batteryLevelBar->setVisible(false);



    connect(ui->powerButton, SIGNAL(released()), this, SLOT(handlePowerButton()));
    connect(ui->powerButton, SIGNAL(pressed()), this, SLOT(handlePowerPressed()));
    connect(ui->upButton, SIGNAL(released()), this, SLOT(handleUpButton()));
    connect(ui->downButton, SIGNAL(released()), this, SLOT(handleDownButton()));
    connect(ui->selectButton, SIGNAL(released()), this, SLOT(handleSelectButton()));
    connect(ui->recordButton, SIGNAL(released()), this, SLOT(handleRecordButton()));
    connect(ui->connectionSlider, SIGNAL(valueChanged(int)),this, SLOT(handleSlider()));

    connect(&secondsTimer, SIGNAL(timeout()), this, SLOT (perSecondUpdate()));
    connect(&sessionTimer, SIGNAL(timeout()), this, SLOT (sessionEnd()));
    connect(&batteryTimer, SIGNAL(timeout()), this, SLOT (criticalBatteryUpdate()));
    secondsTimer.start(1000);
    batteryTimer.start(500);



    init();

}

void MainWindow::init() {
    ui->batteryLevelBar->setValue(batteryLevel);
//    ui->batteryLevelBar->setVisible(false);
    ui->recordButton->setEnabled(false);
    ui->powerButton->setText(powerOn? "Off" : "On");
    ui->timeSpinBox->setVisible(false);

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
    sessionList << "Delta" << "Theta" << "Alpha" << "Beta";
    sessionTypeWidget->addItems(sessionList);

    // do we need a list of previous dummy records?
    Session *s1 = new Session("Delta", 5);
    Session *s2 = new Session("Beta", 8);
    recordList.append(new Record(45, 5, s1));
    recordList.append(new Record());    // can handle null sessions as well
    recordList.append(new Record(20, 2, s2));
    recordList.append(new Record());

    for(Record *r : recordList) {
        ui->historyWidget->addItem(r->getRecordString());
    }

    // set button state
    setUIState();
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

void MainWindow::setUIState(){
    ui->upButton->setEnabled(powerOn);
    ui->downButton->setEnabled(powerOn);
    ui->selectButton->setEnabled(powerOn);
    ui->timeWidget->setEnabled(powerOn);
    ui->sessionTypeWidget->setEnabled(powerOn);
    ui->powerButton->setText(powerOn? "Off" : "On");
    ui->batteryLevelBar->setVisible(powerOn);
    ui->timerLabel->setVisible(powerOn);
    ui->timeElapsedLabel->setVisible(powerOn);
    if(powerOn && selectCounter == PHASE_SELECT) {
        updateTimeLabel();
    }


    timeWidget->setCurrentRow(0);
    sessionTypeWidget->setCurrentRow(0);

    slider->setEnabled(powerOn);
    slider->setValue(0);
    progressBar->setValue(1);
    handleSlider();
    if(!powerOn) {
        ui->historyWidget->clear();
    }
    else {
        for(Record *r : recordList) {
            ui->historyWidget->addItem(r->getRecordString());
        }
    }
}
void MainWindow::handlePowerPressed(){
    pressedTime = QDateTime::currentSecsSinceEpoch();
}

//pass batteryflag arg
// change highlighted color instead of set visible.
void MainWindow::criticalBatteryUpdate(){
    QString red = "QProgressBar { selection-background-color: red; background-color: rgb(255, 255, 255);color: }";
    QString yellow = "QProgressBar { selection-background-color: yellow; background-color: rgb(255, 255, 255);color:black }";
    QString green = "QProgressBar { selection-background-color: green; background-color: rgb(255, 255, 255); }";
    if(batteryLevel<=criticalLevel && powerOn){
        batteryFlag = !batteryFlag;
        ui->batteryLevelBar->setVisible(batteryFlag);
    }
    if(batteryLevel<=10){
        ui->batteryLevelBar->setStyleSheet(red);
    }
    else if(batteryLevel>30){
        ui->batteryLevelBar->setStyleSheet(green);
    }
    else if(batteryLevel>10 && batteryLevel<=30){
        ui->batteryLevelBar->setStyleSheet(yellow);
    }


}



void MainWindow::handlePowerButton() {
    quint64 releasedTime = QDateTime::currentSecsSinceEpoch();

    if((releasedTime-pressedTime)>1){
        // if battery is too low to start device
        if(!powerOn && batteryLevel == 0) {
            return;
        }
        powerOn = !powerOn;
        setUIState();
        selectCounter = powerOn? PHASE_SELECT : PHASE_OFF;
        if(powerOn) {
            record = new Record();
        }
        else {
            sessionEnd();
            char flag = 0;
            for(Record *r : recordList) {
                if(r == record) {
                    flag = 1;
                    break;
                }
            }
            if (!flag) {
                delete record;
            }
            record = NULL;
        }
    }
    // select time duration
    else if(powerOn && selectCounter == PHASE_SELECT){
        int newIndex = timeWidget->currentRow() + 1;

        if (newIndex >= timeWidget->count()) {
            newIndex = 0;
        }

        timeWidget->setCurrentRow(newIndex);
        if(timeWidget->currentRow() == 2) {
            ui->timeSpinBox->setVisible(true);
        }
        else {
            ui->timeSpinBox->setVisible(false);
        }
    }

    qInfo("Power button pressed");
}

void MainWindow::handleUpButton() {
    // session type
    if(selectCounter == PHASE_SELECT){
        int newIndex = sessionTypeWidget->currentRow() - 1;

        if (newIndex < 0) {
            newIndex = sessionTypeWidget->count() - 1;
        }

        sessionTypeWidget->setCurrentRow(newIndex);
    }

    // intensity
    else if (selectCounter >= PHASE_RUN){
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
    // session type
    if(selectCounter == PHASE_SELECT){
        int newIndex = sessionTypeWidget->currentRow() + 1;

        if (newIndex >= sessionTypeWidget->count()) {
            newIndex = 0;
        }
        sessionTypeWidget->setCurrentRow(newIndex);
    }

    // intensity
    else if(selectCounter >= PHASE_RUN){
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

void MainWindow::updateTimeLabel(){
     int s = sessionTimer.remainingTime() / 1000;  // counts down
//    int s = (sessionTimer.interval() - sessionTimer.remainingTime()) / 1000;     // counts up
    QString timeString = QString::number(s/60) + ((s%60 < 10) ? + ":0" + QString::number(s%60) : + ":" + QString::number(s%60));
    ui->timeElapsedLabel->setText(timeString);
}

void MainWindow::handleSelectButton() {
    ui->recordButton->setEnabled(false);

    if(batteryLevel>criticalLevel){
        if(selectCounter == PHASE_SELECT || selectCounter == PHASE_CONN) {
            selectCounter++;
            handleSlider();
        }
//        if (selectCounter == PHASE_CONN) {
//            connStartTime = QDateTime::currentSecsSinceEpoch();
//        }
        if (selectCounter == PHASE_RUN) {
            connWaitTime = 0;
            int timeToSet = durationList[timeWidget->currentRow()];
        //    timeToSet = timeToSet? timeToSet : 60*60;       // 60*60 is an arbitrary max value
            if(timeWidget->currentRow() == 2) {
                timeToSet = ui->timeSpinBox->value();
            }
            sessionTimer.start((timeToSet) * 1000);
            updateTimeLabel();

            QString sessionName = sessionList[sessionTypeWidget->currentRow()];
            Session *s = new Session(sessionName);
            record->setSession(s);

            record->setDuration(durationList[timeWidget->currentRow()]);
            if(timeWidget->currentRow() == 2) {
                record->setDuration(ui->timeSpinBox->value());
            }

            progressBar->setValue(record->getIntensity()+1);
        }
    }

    qInfo("Select button pressed");
}

void MainWindow::handleRecordButton(){
    // add record to recordList
    // update record widget
    recordList.append(record);
    ui->historyWidget->clear();
    for(Record *r : recordList) {
        ui->historyWidget->addItem(r->getRecordString());
    }
    record = new Record();
    ui->recordButton->setEnabled(false);
}

void MainWindow::handleSlider(){
//    qDebug() << "slider value: " << slider->value() << "phase: " << selectCounter;

    if(selectCounter == PHASE_RUN && slider->value()==2 && pausedTime == 0) {
        // disconnect it
        // pause timer
        selectCounter = PHASE_CONN;
        pausedTime = sessionTimer.remainingTime();
        qDebug() << "pausedTime:" << pausedTime;
        sessionTimer.stop();
    }
//    if(selectCounter == PHASE_CONN && slider->value()!=2 && pausedTime > 0) {
//        connStartTime = QDateTime::currentSecsSinceEpoch();
//    }
//    else if(selectCounter == PHASE_CONN && slider->value()!=2 && pausedTime > 0) {
//        selectCounter = PHASE_RUN;
//        sessionTimer.start(pausedTime+1);
//        qDebug() << "resumed pausedTime:" << pausedTime;
//        pausedTime = 0;
//    }

}

void MainWindow::updateLEDs() {
    QString style = "";
    int progressBarVal = 1;
    switch(slider->value()) {
        case 0:
            ui->selectButton->setEnabled(powerOn);
            style = "QLabel { background-color: green; color: white; }";
            progressBarVal = 3;
            break;
        case 1:
            ui->selectButton->setEnabled(powerOn);
            style = "QLabel { background-color: yellow; color: black; }";
            progressBarVal = 6;
            break;
        case 2:
            ui->selectButton->setEnabled(false);
            style = "QLabel { background-color: red; color: white; }";
            progressBarVal = 8;
            break;

    }
    // off or not connection
    if(!powerOn || selectCounter != PHASE_CONN) {
        style = "QLabel { background-color: transparent; color: black; }";
    }
    // on and connection
    else if (powerOn && selectCounter == PHASE_CONN) {
        progressBar->setValue(progressBarVal);
    }
    ui->leftLightLabel->setStyleSheet(style);
    ui->rightLightLabel->setStyleSheet(style);
}

void MainWindow::perSecondUpdate() {
    qDebug() << "slider value: " << slider->value() << "phase: " << selectCounter;
    // if session is on:
    // update battery level
    // update session timer
    updateLEDs();
    if (selectCounter == PHASE_CONN && slider->value() != 2) {
        connWaitTime++;
        qDebug() << "connWaitTime:" << connWaitTime;
        if (connWaitTime >= 5) {
            if(pausedTime > 0) {
                selectCounter = PHASE_RUN;
                sessionTimer.start(pausedTime+1);
                qDebug() << "resumed pausedTime:" << pausedTime;
                pausedTime = 0;
                progressBar->setValue(record->getIntensity() + 1);
            }
            else {
                handleSelectButton();
            }
        }
    }
    if(selectCounter >= PHASE_RUN && slider->value() <= 1) {
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
    if(powerOn && selectCounter == PHASE_END){
        qDebug() << "line 408";
        record->decrementIntensity();
        progressBar->setValue(progressBar->value() - 1);
        if(progressBar->value() == 1) {
            selectCounter = PHASE_SELECT;
        }
    }
}

// called when sessionTimer runs out
// can also be called when device powers off mid session
void MainWindow::sessionEnd() {
//    for(int i=progressBar->maximum(); i>=1;i--){
//        record->decrementIntensity();
//        progressBar->setValue(i);
//        usleep(1000);
//    }

    sessionTimer.stop();
    qDebug() << "line 427";
    progressBar->setValue(progressBar->maximum());
    usleep(1000);
    selectCounter = PHASE_END;
    if(batteryLevel>criticalLevel) {
        ui->recordButton->setEnabled(true);
    }

    // perform soft off
    // change selectCounter
    // if !powerOn -- move clearing record information from handlePowerButton to here
    // give option to add session to record
}

