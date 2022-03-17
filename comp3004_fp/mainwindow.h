#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QProgressBar>
#include <QSlider>
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
    Record* session;
    QStringList durationList;
    QStringList sessionList;
    //QVector<int> durationList;
    QVector<int> intensityList;
    QVector<Record*> recordList;
    QProgressBar *progressBar;
    QSlider *slider;
    QListWidget *timeWidget;
    QListWidget *sessionTypeWidget;
    bool powerOn;
    int connection;
    float batteryLevel;       // display is ceil(), drain per sec is 0.2 at intensity 1, max 0.2*8 = 1.6 drain per sec for intensity 8
    int selectCounter;

private slots:
    // slots handling the input
    void handlePowerButton();
    void handleUpButton();
    void handleDownButton();
    void handleSelectButton();
    void handleSlider();
};
#endif // MAINWINDOW_H
