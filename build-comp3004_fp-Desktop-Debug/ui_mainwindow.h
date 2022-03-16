/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *powerButton;
    QPushButton *upButton;
    QPushButton *downButton;
    QPushButton *selectButton;
    QListWidget *historyWidget;
    QProgressBar *displayBar;
    QLabel *leftLightLabel;
    QLabel *rightLightLabel;
    QLabel *label0;
    QLabel *label1;
    QLabel *label2;
    QLabel *label4;
    QLabel *label3;
    QLabel *label5;
    QLabel *label7;
    QLabel *label6;
    QLabel *label8;
    QListWidget *timeWidget;
    QListWidget *sessionTypeWidget;
    QLabel *customTimeLabel;
    QProgressBar *batteryLevelBar;
    QSlider *verticalSlider;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(837, 512);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        powerButton = new QPushButton(centralwidget);
        powerButton->setObjectName(QString::fromUtf8("powerButton"));
        powerButton->setGeometry(QRect(610, 350, 80, 25));
        powerButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	height: 50px;\n"
"	width: 50px;\n"
"	border: 1px solid red;\n"
"}"));
        upButton = new QPushButton(centralwidget);
        upButton->setObjectName(QString::fromUtf8("upButton"));
        upButton->setGeometry(QRect(460, 330, 80, 25));
        downButton = new QPushButton(centralwidget);
        downButton->setObjectName(QString::fromUtf8("downButton"));
        downButton->setGeometry(QRect(460, 370, 80, 25));
        selectButton = new QPushButton(centralwidget);
        selectButton->setObjectName(QString::fromUtf8("selectButton"));
        selectButton->setGeometry(QRect(110, 370, 80, 25));
        historyWidget = new QListWidget(centralwidget);
        new QListWidgetItem(historyWidget);
        new QListWidgetItem(historyWidget);
        historyWidget->setObjectName(QString::fromUtf8("historyWidget"));
        historyWidget->setGeometry(QRect(485, 90, 231, 192));
        displayBar = new QProgressBar(centralwidget);
        displayBar->setObjectName(QString::fromUtf8("displayBar"));
        displayBar->setGeometry(QRect(270, 280, 31, 171));
        displayBar->setLayoutDirection(Qt::LeftToRight);
        displayBar->setMaximum(8);
        displayBar->setValue(7);
        displayBar->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        displayBar->setTextVisible(false);
        displayBar->setOrientation(Qt::Vertical);
        displayBar->setInvertedAppearance(false);
        displayBar->setTextDirection(QProgressBar::BottomToTop);
        leftLightLabel = new QLabel(centralwidget);
        leftLightLabel->setObjectName(QString::fromUtf8("leftLightLabel"));
        leftLightLabel->setGeometry(QRect(560, 40, 54, 17));
        leftLightLabel->setStyleSheet(QString::fromUtf8("QLabel \n"
"{ background-color: red; }"));
        leftLightLabel->setTextFormat(Qt::AutoText);
        leftLightLabel->setScaledContents(false);
        leftLightLabel->setAlignment(Qt::AlignCenter);
        rightLightLabel = new QLabel(centralwidget);
        rightLightLabel->setObjectName(QString::fromUtf8("rightLightLabel"));
        rightLightLabel->setGeometry(QRect(630, 40, 54, 17));
        rightLightLabel->setStyleSheet(QString::fromUtf8(""));
        rightLightLabel->setTextFormat(Qt::AutoText);
        rightLightLabel->setScaledContents(false);
        rightLightLabel->setAlignment(Qt::AlignCenter);
        label0 = new QLabel(centralwidget);
        label0->setObjectName(QString::fromUtf8("label0"));
        label0->setGeometry(QRect(300, 440, 21, 17));
        label0->setStyleSheet(QString::fromUtf8(""));
        label0->setTextFormat(Qt::AutoText);
        label0->setScaledContents(false);
        label0->setAlignment(Qt::AlignCenter);
        label1 = new QLabel(centralwidget);
        label1->setObjectName(QString::fromUtf8("label1"));
        label1->setGeometry(QRect(300, 420, 21, 17));
        label1->setStyleSheet(QString::fromUtf8(""));
        label1->setTextFormat(Qt::AutoText);
        label1->setScaledContents(false);
        label1->setAlignment(Qt::AlignCenter);
        label2 = new QLabel(centralwidget);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setGeometry(QRect(300, 400, 21, 17));
        label2->setStyleSheet(QString::fromUtf8(""));
        label2->setTextFormat(Qt::AutoText);
        label2->setScaledContents(false);
        label2->setAlignment(Qt::AlignCenter);
        label4 = new QLabel(centralwidget);
        label4->setObjectName(QString::fromUtf8("label4"));
        label4->setGeometry(QRect(300, 360, 21, 17));
        label4->setStyleSheet(QString::fromUtf8(""));
        label4->setTextFormat(Qt::AutoText);
        label4->setScaledContents(false);
        label4->setAlignment(Qt::AlignCenter);
        label3 = new QLabel(centralwidget);
        label3->setObjectName(QString::fromUtf8("label3"));
        label3->setGeometry(QRect(300, 380, 21, 17));
        label3->setStyleSheet(QString::fromUtf8(""));
        label3->setTextFormat(Qt::AutoText);
        label3->setScaledContents(false);
        label3->setAlignment(Qt::AlignCenter);
        label5 = new QLabel(centralwidget);
        label5->setObjectName(QString::fromUtf8("label5"));
        label5->setGeometry(QRect(300, 340, 21, 17));
        label5->setStyleSheet(QString::fromUtf8(""));
        label5->setTextFormat(Qt::AutoText);
        label5->setScaledContents(false);
        label5->setAlignment(Qt::AlignCenter);
        label7 = new QLabel(centralwidget);
        label7->setObjectName(QString::fromUtf8("label7"));
        label7->setGeometry(QRect(300, 300, 21, 17));
        label7->setStyleSheet(QString::fromUtf8(""));
        label7->setTextFormat(Qt::AutoText);
        label7->setScaledContents(false);
        label7->setAlignment(Qt::AlignCenter);
        label6 = new QLabel(centralwidget);
        label6->setObjectName(QString::fromUtf8("label6"));
        label6->setGeometry(QRect(300, 320, 21, 17));
        label6->setStyleSheet(QString::fromUtf8(""));
        label6->setTextFormat(Qt::AutoText);
        label6->setScaledContents(false);
        label6->setAlignment(Qt::AlignCenter);
        label8 = new QLabel(centralwidget);
        label8->setObjectName(QString::fromUtf8("label8"));
        label8->setGeometry(QRect(300, 280, 21, 17));
        label8->setStyleSheet(QString::fromUtf8(""));
        label8->setTextFormat(Qt::AutoText);
        label8->setScaledContents(false);
        label8->setAlignment(Qt::AlignCenter);
        timeWidget = new QListWidget(centralwidget);
        new QListWidgetItem(timeWidget);
        new QListWidgetItem(timeWidget);
        new QListWidgetItem(timeWidget);
        timeWidget->setObjectName(QString::fromUtf8("timeWidget"));
        timeWidget->setGeometry(QRect(140, 150, 91, 81));
        sessionTypeWidget = new QListWidget(centralwidget);
        new QListWidgetItem(sessionTypeWidget);
        new QListWidgetItem(sessionTypeWidget);
        new QListWidgetItem(sessionTypeWidget);
        sessionTypeWidget->setObjectName(QString::fromUtf8("sessionTypeWidget"));
        sessionTypeWidget->setGeometry(QRect(250, 150, 91, 81));
        customTimeLabel = new QLabel(centralwidget);
        customTimeLabel->setObjectName(QString::fromUtf8("customTimeLabel"));
        customTimeLabel->setGeometry(QRect(70, 190, 61, 20));
        customTimeLabel->setStyleSheet(QString::fromUtf8(""));
        customTimeLabel->setTextFormat(Qt::AutoText);
        customTimeLabel->setScaledContents(false);
        customTimeLabel->setAlignment(Qt::AlignCenter);
        batteryLevelBar = new QProgressBar(centralwidget);
        batteryLevelBar->setObjectName(QString::fromUtf8("batteryLevelBar"));
        batteryLevelBar->setGeometry(QRect(50, 20, 118, 23));
        batteryLevelBar->setValue(100);
        verticalSlider = new QSlider(centralwidget);
        verticalSlider->setObjectName(QString::fromUtf8("verticalSlider"));
        verticalSlider->setGeometry(QRect(400, 270, 16, 171));
        verticalSlider->setMaximum(2);
        verticalSlider->setSingleStep(1);
        verticalSlider->setValue(2);
        verticalSlider->setTickPosition(QSlider::TicksAbove);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 837, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        powerButton->setText(QApplication::translate("MainWindow", "On", nullptr));
        upButton->setText(QApplication::translate("MainWindow", "Up", nullptr));
        downButton->setText(QApplication::translate("MainWindow", "Down", nullptr));
        selectButton->setText(QApplication::translate("MainWindow", "Select", nullptr));

        const bool __sortingEnabled = historyWidget->isSortingEnabled();
        historyWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = historyWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("MainWindow", "sessionType, duration, intensity", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = historyWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("MainWindow", "sessionType, duration, intensity (2)", nullptr));
        historyWidget->setSortingEnabled(__sortingEnabled);

        leftLightLabel->setText(QApplication::translate("MainWindow", "L", nullptr));
        rightLightLabel->setText(QApplication::translate("MainWindow", "R", nullptr));
        label0->setText(QApplication::translate("MainWindow", "0", nullptr));
        label1->setText(QApplication::translate("MainWindow", "1", nullptr));
        label2->setText(QApplication::translate("MainWindow", "2", nullptr));
        label4->setText(QApplication::translate("MainWindow", "4", nullptr));
        label3->setText(QApplication::translate("MainWindow", "3", nullptr));
        label5->setText(QApplication::translate("MainWindow", "5", nullptr));
        label7->setText(QApplication::translate("MainWindow", "7", nullptr));
        label6->setText(QApplication::translate("MainWindow", "6", nullptr));
        label8->setText(QApplication::translate("MainWindow", "8", nullptr));

        const bool __sortingEnabled1 = timeWidget->isSortingEnabled();
        timeWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem2 = timeWidget->item(0);
        ___qlistwidgetitem2->setText(QApplication::translate("MainWindow", "20min", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = timeWidget->item(1);
        ___qlistwidgetitem3->setText(QApplication::translate("MainWindow", "45min", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = timeWidget->item(2);
        ___qlistwidgetitem4->setText(QApplication::translate("MainWindow", "user defined", nullptr));
        timeWidget->setSortingEnabled(__sortingEnabled1);


        const bool __sortingEnabled2 = sessionTypeWidget->isSortingEnabled();
        sessionTypeWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem5 = sessionTypeWidget->item(0);
        ___qlistwidgetitem5->setText(QApplication::translate("MainWindow", "beta", nullptr));
        QListWidgetItem *___qlistwidgetitem6 = sessionTypeWidget->item(1);
        ___qlistwidgetitem6->setText(QApplication::translate("MainWindow", "delta", nullptr));
        QListWidgetItem *___qlistwidgetitem7 = sessionTypeWidget->item(2);
        ___qlistwidgetitem7->setText(QApplication::translate("MainWindow", "omega", nullptr));
        sessionTypeWidget->setSortingEnabled(__sortingEnabled2);

        customTimeLabel->setText(QApplication::translate("MainWindow", "time = ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
