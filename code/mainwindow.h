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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Record* record;
    QList<int> durationList;
    QStringList sessionList;
    QList<Record*> recordList;
    QProgressBar *progressBar;
    QAbstractSlider *slider;
    QListWidget *timeWidget;
    QListWidget *sessionTypeWidget;
    int pausedTime;
    QTimer secondsTimer;
    QTimer sessionTimer;
    QTimer batteryTimer;
    bool batteryFlag;
    bool powerOn;
    int connection;           // unused yet
    float batteryLevel;
    float criticalLevel;
    int selectCounter;        // determines whether progress bar shows connection or intensity
    // selectCounter == 0 -- device is off
    // selectCounter == 1 -- on selection state
    // selectCounter == 2 -- on session running state (this should be connection test state)
    // selectCounter == 3 -- (should be session running state)
    quint64 pressedTime;
    void init();
    void setUIState();
    void updateTimeLabel();

private slots:
    // slots handling the input
    void handlePowerButton();
    void handlePowerPressed();
    void handleUpButton();
    void handleDownButton();
    void handleSelectButton();
    void handleRecordButton();
    void handleSlider();
    void perSecondUpdate();
    void sessionEnd();
    void criticalBatteryUpdate();
};
#endif // MAINWINDOW_H
