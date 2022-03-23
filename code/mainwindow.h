#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QProgressBar>
#include <QSlider>
#include <QtGlobal>
#include <QDateTime>
#include <QtCore>
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
    void customDuration();
    void setButtonState();

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
    QElapsedTimer time;     // rm
    QTimer timer;           // rm
    QTimer secondsTimer;
    QTimer sessionTimer;
    // might need a timer for powerButton as well - current one seems to be bugging on repeating clicks fast
    bool powerOn;
    int connection;
    float batteryLevel;       // display is ceil(), drain per sec is 0.2 at intensity 1, max 0.2*8 = 1.6 drain per sec for intensity 8
    int selectCounter;        // determines whether progress bar shows connection or intensity
    // selectCounter == 1 -- on selection state
    // selectCounter == 2 -- on session running state (this should be connection test state)
    // selectCounter == 3 -- (should be session running state)
    quint64 pressedTime;
    void init();

private slots:
    // slots handling the input
    void handlePowerButton();
    void handlePowerPressed();
    void handleUpButton();
    void handleDownButton();
    void handleSelectButton();
    void handleRecordButton();
    void handleSlider();
    void updateTimeLabel();
    void perSecondUpdate();
    void sessionEnd();
};
#endif // MAINWINDOW_H
