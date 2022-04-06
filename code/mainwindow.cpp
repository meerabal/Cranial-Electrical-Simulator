#include "mainwindow.h"
#include "ui_mainwindow.h"


// This is the MainWindow where most of the functionality is
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      record(NULL),
      criticalLevel(10),
      phase(PHASE_OFF),
      powerOn(false),
      batteryLevel(100),
      batteryFlag(true),
      connWaitTime(0),
      pausedTime(0),
      idleTime(0)
{
    ui->setupUi(this);
    progressBar = ui->displayBar;
    slider = ui->connectionSlider;
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
    connect(&batteryTimer, SIGNAL(timeout()), this, SLOT (criticalBatteryUpdate()));
    secondsTimer.start(1000);
    batteryTimer.start(500);

    init();

}


MainWindow::~MainWindow()
{
    delete ui;
    // record should not delete if it is stored in history
    for(Record *r : recordList) {
        if(r != NULL) {
            delete r;
        }
    }

}


void MainWindow::init() {
    ui->batteryLevelBar->setValue(batteryLevel);
    ui->recordButton->setEnabled(false);
    ui->powerButton->setText(powerOn? "OFF" : "ON");
    ui->timeSpinBox->setVisible(powerOn);

    // populate duration list and widget
    durationList << 20 << 45 << 0;
    for(int time : durationList) {
        QString timeStr = QString::number(time) + " min";
        if(time == 0) {
            timeStr = "User Defined";
        }
        timeWidget->addItem(timeStr);
    }

    // populate session list and widget
    sessionList << "Delta" << "Theta" << "Alpha" << "Beta";
    sessionTypeWidget->addItems(sessionList);

    // populate the history widget
    for(Record *r : recordList) {
        ui->historyWidget->addItem(r->getRecordString());
    }

    setUIState(false);
}


void MainWindow::setUIState(bool partial){
    if(!partial) {
        ui->upButton->setEnabled(powerOn);
        ui->downButton->setEnabled(powerOn);
        ui->selectButton->setEnabled(powerOn);
        ui->recordButton->setEnabled(false);
        ui->timeWidget->setEnabled(powerOn);
        ui->sessionTypeWidget->setEnabled(powerOn);
        ui->timerLabel->setVisible(powerOn);
        ui->timeElapsedLabel->setVisible(powerOn);
        if(timeWidget->currentRow()==2) {
            ui->timeSpinBox->setVisible(powerOn);
        }
        slider->setEnabled(powerOn);
        slider->setValue(0);
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
    progressBar->setValue(1);
    ui->powerButton->setText(powerOn? "OFF" : "ON");
    ui->batteryLevelBar->setVisible(powerOn);

    if(powerOn && phase == PHASE_SELECT) {
        updateTimeLabel();
    }

    timeWidget->setCurrentRow(0);
    sessionTypeWidget->setCurrentRow(0);

}


void MainWindow::handlePowerPressed(){
    pressedTime = QDateTime::currentSecsSinceEpoch();
}


void MainWindow::handlePowerButton() {
    idleTime = 0;
    quint64 releasedTime = QDateTime::currentSecsSinceEpoch();

    // long press - toggle on/off
    if((releasedTime-pressedTime)>1){
        togglePowerOn();
    }
    // short press - select time duration
    else if(powerOn && phase == PHASE_SELECT){
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

    qDebug() << "Power button released";
}


void MainWindow::togglePowerOn(){
    powerOn = !powerOn;
    phase = powerOn? PHASE_SELECT : PHASE_OFF;

    if(powerOn) {
        sessionTimer.stop();
        // set UI state partially if battery level is critical
        setUIState(batteryLevel<=criticalLevel);
        record = new Record();
    }
    else {
        setUIState(false);
        char flag = 0;
        // if record is saved in recordList, do not delete it
        for(Record *r : recordList) {
            if(r == record) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            delete record;
        }

    }
}


void MainWindow::criticalBatteryUpdate(){
    QString red = "QProgressBar { selection-background-color: red; background-color: rgb(255, 255, 255); }";
    QString yellow = "QProgressBar { selection-background-color: yellow; background-color: rgb(255, 255, 255); }";
    QString green = "QProgressBar { selection-background-color: green; background-color: rgb(255, 255, 255); }";

    // set batteryFlag for blinking
    if(batteryLevel<=criticalLevel && powerOn){
        batteryFlag = !batteryFlag;
        ui->batteryLevelBar->setVisible(batteryFlag);
    }

    // set battery bar color
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


void MainWindow::handleUpButton() {
    idleTime = 0;

    // in selection phase - session type selection
    if(phase == PHASE_SELECT){
        int newIndex = sessionTypeWidget->currentRow() - 1;

        if (newIndex < 0) {
            newIndex = sessionTypeWidget->count() - 1;
        }

        sessionTypeWidget->setCurrentRow(newIndex);
    }

    // increase intensity
    else if (phase >= PHASE_RUN){
        int newIndex = progressBar->value() + 1;

        if (newIndex > progressBar->maximum()) {
            newIndex = 8;
        }

        progressBar->setValue(newIndex);
        record->incrementIntensity();
        qDebug() << "Intensity incremented to" << record->getIntensity();
    }

    qDebug() << "UP button pressed";
}


void MainWindow::handleDownButton() {
    idleTime = 0;

    // in selection phase - session type selection
    if(phase == PHASE_SELECT){
        int newIndex = sessionTypeWidget->currentRow() + 1;

        if (newIndex >= sessionTypeWidget->count()) {
            newIndex = 0;
        }
        sessionTypeWidget->setCurrentRow(newIndex);
    }

    // decrease intensity
    else if(phase >= PHASE_RUN){
        int newIndex = progressBar->value() - 1;

        if (newIndex < 1) {
            newIndex = 1;
        }

        progressBar->setValue(newIndex);
        record->decrementIntensity();
        qDebug() << "Intensity decremented to" << record->getIntensity();
    }

    qDebug() << "DOWN button pressed";
}


void MainWindow::updateTimeLabel(){
    int s = sessionTimer.remainingTime() / 1000;  // counts down
    // format h:mm:ss
    QString timeString = QString::number(s/60) + ((s%60 < 10) ? + ":0" + QString::number(s%60) : + ":" + QString::number(s%60)) + ":00";
    ui->timeElapsedLabel->setText(timeString);
}


void MainWindow::handleSelectButton() {
    idleTime = 0;
    ui->recordButton->setEnabled(false);

    if(batteryLevel>criticalLevel){
        // increment phase if slider has connection
        if(phase == PHASE_SELECT || phase == PHASE_CONN) {
            phase++;
            handleSlider();
        }

        // to run therapy
        if (phase == PHASE_RUN) {
            connWaitTime = 0;
            int timeToSet = durationList[timeWidget->currentRow()];
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

    qDebug() << "SELECT Button pressed";
}

void MainWindow::handleRecordButton(){
    idleTime = 0;

    // add record to recordList and update record widget
    recordList.append(record);
    ui->historyWidget->clear();
    for(Record *r : recordList) {
        ui->historyWidget->addItem(r->getRecordString());
    }
    record = new Record();
    ui->recordButton->setEnabled(false);
}


void MainWindow::handleSlider(){
    idleTime = 0;

    // when no connection in connection phase, connWaitTime should not increment
    if(phase == PHASE_CONN && slider->value() == NO_CONN) {
        connWaitTime = 0;
    }

    // when no connection in session run phase, and not previously paused
    if(phase == PHASE_RUN && slider->value() == NO_CONN && pausedTime == 0) {
        // pause timer and go to connection phase
        phase = PHASE_CONN;
        pausedTime = sessionTimer.remainingTime();
        qDebug() << "pausedTime:" << pausedTime;
        sessionTimer.stop();
    }
    qDebug() << "Connection slider moved to" << ui->connectionSlider->value();
}


void MainWindow::updateLEDs() {
    QString style = "";
    int progressBarVal = 1;
    switch(slider->value()) {
        case EXCELLENT_CONN:
            ui->selectButton->setEnabled(powerOn && batteryLevel>criticalLevel);
            style = "QLabel { background-color: green; color: white; }";
            progressBarVal = 3;
            break;
        case OK_CONN:
            ui->selectButton->setEnabled(powerOn && batteryLevel>criticalLevel);
            style = "QLabel { background-color: yellow; color: black; }";
            progressBarVal = 6;
            break;
        case NO_CONN:
            ui->selectButton->setEnabled(false);
            style = "QLabel { background-color: red; color: white; }";
            progressBarVal = 8;
            break;

    }
    // off or not in connection phase
    if(!powerOn || phase != PHASE_CONN) {
        style = "QLabel { background-color: transparent; color: black; }";
    }
    // on and in connection phase
    else if (powerOn && phase == PHASE_CONN) {
        progressBar->setValue(progressBarVal);
    }
    ui->leftLightLabel->setStyleSheet(style);
    ui->rightLightLabel->setStyleSheet(style);
}


void MainWindow::perSecondUpdate() {
    qDebug() << "phase: " << phase;

    updateLEDs();

    // connection phase, device has connection - start/resume therapy
    if (phase == PHASE_CONN && slider->value() != NO_CONN) {
        connWaitTime++;
        qDebug() << "connWaitTime:" << connWaitTime;
        if (connWaitTime >= 5) {
            if(pausedTime > 0) {
                phase = PHASE_RUN;
                sessionTimer.start(pausedTime+1);
                qDebug() << "resumed pausedTime:" << pausedTime;
                pausedTime = 0;
                connWaitTime = 0;
                progressBar->setValue(record->getIntensity() + 1);
            }
            else {
                handleSelectButton();
            }
        }
    }

    // session run phase, device has connection - drain battery
    if(phase == PHASE_RUN && slider->value() != NO_CONN) {
        updateTimeLabel();
        batteryLevel = batteryLevel - (0.1 * (record->getIntensity() + 0.5));
        batteryLevel = batteryLevel < 0? 0 : batteryLevel;
        int displayBattery = ceil(batteryLevel);
        ui->batteryLevelBar->setValue(displayBattery);

        if(batteryLevel <= criticalLevel) {
            setUIState(true);
            sessionEnd();
        }
    }
    // device is on and in end phase - perform soft off
    else if(powerOn && phase == PHASE_END){
        progressBar->setValue(progressBar->value() - 1);
        updateTimeLabel();
        if(progressBar->value() == 1) {
            phase = PHASE_SELECT;
        }
    }

    // device is on and in selection phase - count idle time
    if(powerOn && phase == PHASE_SELECT){
        idleTime++;
        qDebug() << "idleTime:" << idleTime;
        if(idleTime == MAX_IDLE_TIME){
            togglePowerOn();
        }
    }
 }


// called when sessionTimer runs out
// can also be called when device powers off mid session
void MainWindow::sessionEnd() {
    sessionTimer.stop();
    progressBar->setValue(progressBar->maximum());
    secondsTimer.start(1000);
    phase = PHASE_END;
    idleTime=0;
    if(batteryLevel>criticalLevel) {
        ui->recordButton->setEnabled(true);
    }
}

