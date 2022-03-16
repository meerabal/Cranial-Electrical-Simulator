#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      powerOn(false),
      connection(8),
      batteryLevel(96)
{
    ui->setupUi(this);
    ui->powerButton->setText(powerOn? "Off" : "On");
    ui->displayBar->setValue(connection);
    ui->batteryLevelBar->setValue(batteryLevel);
    connect(ui->powerButton, SIGNAL(released()), this, SLOT(handlePowerButton()));
    connect(ui->upButton, SIGNAL(released()), this, SLOT(handleUpButton()));
    connect(ui->downButton, SIGNAL(released()), this, SLOT(handleDownButton()));
    connect(ui->selectButton, SIGNAL(released()), this, SLOT(handleSelectButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handlePowerButton() {
    powerOn = !powerOn;
    ui->powerButton->setText(powerOn? "Off" : "On");
    qInfo("Power button pressed");
}

void MainWindow::handleUpButton() {
    qInfo("Up button pressed");
}

void MainWindow::handleDownButton() {
    qInfo("Down button pressed");
}

void MainWindow::handleSelectButton() {
    qInfo("Select button pressed");
}
