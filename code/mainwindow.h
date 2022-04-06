#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QProgressBar>
#include <QSlider>
#include <QtGlobal>
#include <QDateTime>
#include <QtCore>
#include <stdlib.h>
#include <unistd.h>
#include "Record.h"

#define PHASE_OFF       0       // when device is off (buttons, displays are disabled)
#define PHASE_SELECT    1       // when device is in selection phase (up/down, power buttons used to toggle selection in widget lists)
#define PHASE_CONN      2       // when device is in connection phase (progress bar displays the connection level)
#define PHASE_RUN       3       // when the session is running (timer is running)
#define PHASE_END       4       // when the session has ended (for soft off)

#define NO_CONN         2
#define OK_CONN         1
#define EXCELLENT_CONN  0

#define MAX_IDLE_TIME   45      // maximum time the device can be left idle before it turns off

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


// This is the header file for MainWindow class
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;                 // ui pointer

    QProgressBar *progressBar;          // ptr to progress bar that displays the connection level, intensity, soft off
    QAbstractSlider *slider;            // ptr to the connection slider
    QListWidget *timeWidget;            // ptr to the widget that displays the time duration list
    QListWidget *sessionTypeWidget;     // ptr to the widget that displays the list of sessions

    QTimer secondsTimer;                // timer that times out every second for updating time label and checking status
    QTimer sessionTimer;                // timer that counts down the time remaining for the session to end
    QTimer batteryTimer;                // timer that helps the battery bar blink at critical level

    Record* record;                     // Record pointer that holds the current session details

    QList<int> durationList;            // list of available times that the user can select from
    QStringList sessionList;            // list of available sessions that the user can select from
    QList<Record*> recordList;          // list of Record pointers for past saved session records (history)

    float criticalLevel;                // critical battery level for the device

    int phase;                          // stores the state of the device
    bool powerOn;                       // boolean that contains the power state of the device (on/off)
    float batteryLevel;                 // current battery level of the device
    bool batteryFlag;                   // boolean that helps the battery blink (whether it should be displayed or not)

    quint64 pressedTime;                // time at which the power button is pressed
    int connWaitTime;                   // how long the connection test runs
    int pausedTime;                     // time left on the timer when session is paused (due to no connection / critical battery)
    int idleTime;                       // time that the device has been idle for

    void init();                        // initializes the device
    void setUIState(bool partial);   // sets the UI state depending on the boolean arg - to update the UI partially or fully
    void updateTimeLabel();             // updates the time tabel with the time remaining in sessionTimer
    void updateLEDs();                  // updates the L/R LEDs and progress bar
    void togglePowerOn();               // switches on/off the device and sets state of UI, phase

private slots:
    // slots handling the input
    void handlePowerButton();           // handler for power button released
    void handlePowerPressed();          // handler for when the power button is pressed
    void handleUpButton();              // handler for the "UP" button
    void handleDownButton();            // handler for the "DOWN" button
    void handleSelectButton();          // handler for the "SELECT" button
    void handleRecordButton();          // handler for the "RECORD SESSION" button
    void handleSlider();                // handler for the connection slider
    void perSecondUpdate();             // handler for the secondsTimer
    void sessionEnd();                  // handler for the sessionTimer
    void criticalBatteryUpdate();       // handler for blinking (when critical) and color of battery bar
};
#endif // MAINWINDOW_H
