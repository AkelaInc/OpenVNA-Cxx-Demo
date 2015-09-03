/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QFrame *line;
    QVBoxLayout *verticalLayout;
    QGroupBox *sysGroup;
    QFormLayout *formLayout;
    QSpinBox *ip;
    QLabel *label_5;
    QLabel *label_6;
    QSpinBox *port;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *doInitialize;
    QPushButton *runToggle;
    QGroupBox *stimGroup;
    QFormLayout *formLayout_2;
    QDoubleSpinBox *startFreq;
    QLabel *label_2;
    QLabel *label;
    QComboBox *sweepRate;
    QLabel *label_3;
    QDoubleSpinBox *stopFreq;
    QLabel *label_4;
    QSpinBox *points;
    QGroupBox *calGroup;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_10;
    QComboBox *calibrationSetting;
    QPushButton *loadCal;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *clearCal;
    QPushButton *saveCal;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *p1OpenStatus;
    QPushButton *doP1Open;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *p1ShortStatus;
    QPushButton *doP1Short;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *p2OpenStatus;
    QPushButton *doP2Open;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *p2LoadStatus;
    QPushButton *doP2Load;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *p1LoadStatus;
    QPushButton *doP1Load;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *p2ShortStatus;
    QPushButton *doP2Short;
    QHBoxLayout *horizontalLayout_8;
    QCheckBox *thruStatus;
    QPushButton *doThru;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QDoubleSpinBox *openLength;
    QPushButton *applyOpenLength;
    QSpacerItem *verticalSpacer;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(915, 691);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));

        horizontalLayout->addLayout(gridLayout);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        sysGroup = new QGroupBox(centralWidget);
        sysGroup->setObjectName(QStringLiteral("sysGroup"));
        formLayout = new QFormLayout(sysGroup);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        ip = new QSpinBox(sysGroup);
        ip->setObjectName(QStringLiteral("ip"));
        ip->setMinimum(1);
        ip->setMaximum(254);
        ip->setValue(192);

        formLayout->setWidget(0, QFormLayout::FieldRole, ip);

        label_5 = new QLabel(sysGroup);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_5);

        label_6 = new QLabel(sysGroup);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_6);

        port = new QSpinBox(sysGroup);
        port->setObjectName(QStringLiteral("port"));
        port->setMinimum(1024);
        port->setMaximum(65535);

        formLayout->setWidget(1, QFormLayout::FieldRole, port);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        doInitialize = new QPushButton(sysGroup);
        doInitialize->setObjectName(QStringLiteral("doInitialize"));
        doInitialize->setCheckable(true);

        horizontalLayout_11->addWidget(doInitialize);

        runToggle = new QPushButton(sysGroup);
        runToggle->setObjectName(QStringLiteral("runToggle"));
        runToggle->setCheckable(true);

        horizontalLayout_11->addWidget(runToggle);


        formLayout->setLayout(2, QFormLayout::SpanningRole, horizontalLayout_11);


        verticalLayout->addWidget(sysGroup);

        stimGroup = new QGroupBox(centralWidget);
        stimGroup->setObjectName(QStringLiteral("stimGroup"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stimGroup->sizePolicy().hasHeightForWidth());
        stimGroup->setSizePolicy(sizePolicy);
        formLayout_2 = new QFormLayout(stimGroup);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        startFreq = new QDoubleSpinBox(stimGroup);
        startFreq->setObjectName(QStringLiteral("startFreq"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, startFreq);

        label_2 = new QLabel(stimGroup);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_2);

        label = new QLabel(stimGroup);
        label->setObjectName(QStringLiteral("label"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label);

        sweepRate = new QComboBox(stimGroup);
        sweepRate->setObjectName(QStringLiteral("sweepRate"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, sweepRate);

        label_3 = new QLabel(stimGroup);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_3);

        stopFreq = new QDoubleSpinBox(stimGroup);
        stopFreq->setObjectName(QStringLiteral("stopFreq"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, stopFreq);

        label_4 = new QLabel(stimGroup);
        label_4->setObjectName(QStringLiteral("label_4"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_4);

        points = new QSpinBox(stimGroup);
        points->setObjectName(QStringLiteral("points"));
        points->setMinimum(2);
        points->setMaximum(6000);
        points->setValue(251);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, points);


        verticalLayout->addWidget(stimGroup);

        calGroup = new QGroupBox(centralWidget);
        calGroup->setObjectName(QStringLiteral("calGroup"));
        gridLayout_2 = new QGridLayout(calGroup);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        calibrationSetting = new QComboBox(calGroup);
        calibrationSetting->setObjectName(QStringLiteral("calibrationSetting"));

        horizontalLayout_10->addWidget(calibrationSetting);

        loadCal = new QPushButton(calGroup);
        loadCal->setObjectName(QStringLiteral("loadCal"));

        horizontalLayout_10->addWidget(loadCal);


        gridLayout_2->addLayout(horizontalLayout_10, 0, 0, 1, 3);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        clearCal = new QPushButton(calGroup);
        clearCal->setObjectName(QStringLiteral("clearCal"));

        horizontalLayout_9->addWidget(clearCal);

        saveCal = new QPushButton(calGroup);
        saveCal->setObjectName(QStringLiteral("saveCal"));

        horizontalLayout_9->addWidget(saveCal);


        gridLayout_2->addLayout(horizontalLayout_9, 1, 0, 1, 3);

        groupBox = new QGroupBox(calGroup);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        p1OpenStatus = new QCheckBox(groupBox);
        p1OpenStatus->setObjectName(QStringLiteral("p1OpenStatus"));
        p1OpenStatus->setEnabled(false);

        horizontalLayout_2->addWidget(p1OpenStatus);

        doP1Open = new QPushButton(groupBox);
        doP1Open->setObjectName(QStringLiteral("doP1Open"));

        horizontalLayout_2->addWidget(doP1Open);


        gridLayout_3->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        p1ShortStatus = new QCheckBox(groupBox);
        p1ShortStatus->setObjectName(QStringLiteral("p1ShortStatus"));
        p1ShortStatus->setEnabled(false);

        horizontalLayout_7->addWidget(p1ShortStatus);

        doP1Short = new QPushButton(groupBox);
        doP1Short->setObjectName(QStringLiteral("doP1Short"));

        horizontalLayout_7->addWidget(doP1Short);


        gridLayout_3->addLayout(horizontalLayout_7, 1, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        p2OpenStatus = new QCheckBox(groupBox);
        p2OpenStatus->setObjectName(QStringLiteral("p2OpenStatus"));
        p2OpenStatus->setEnabled(false);

        horizontalLayout_6->addWidget(p2OpenStatus);

        doP2Open = new QPushButton(groupBox);
        doP2Open->setObjectName(QStringLiteral("doP2Open"));

        horizontalLayout_6->addWidget(doP2Open);


        gridLayout_3->addLayout(horizontalLayout_6, 0, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        p2LoadStatus = new QCheckBox(groupBox);
        p2LoadStatus->setObjectName(QStringLiteral("p2LoadStatus"));
        p2LoadStatus->setEnabled(false);

        horizontalLayout_4->addWidget(p2LoadStatus);

        doP2Load = new QPushButton(groupBox);
        doP2Load->setObjectName(QStringLiteral("doP2Load"));

        horizontalLayout_4->addWidget(doP2Load);


        gridLayout_3->addLayout(horizontalLayout_4, 2, 1, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        p1LoadStatus = new QCheckBox(groupBox);
        p1LoadStatus->setObjectName(QStringLiteral("p1LoadStatus"));
        p1LoadStatus->setEnabled(false);

        horizontalLayout_5->addWidget(p1LoadStatus);

        doP1Load = new QPushButton(groupBox);
        doP1Load->setObjectName(QStringLiteral("doP1Load"));

        horizontalLayout_5->addWidget(doP1Load);


        gridLayout_3->addLayout(horizontalLayout_5, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        p2ShortStatus = new QCheckBox(groupBox);
        p2ShortStatus->setObjectName(QStringLiteral("p2ShortStatus"));
        p2ShortStatus->setEnabled(false);

        horizontalLayout_3->addWidget(p2ShortStatus);

        doP2Short = new QPushButton(groupBox);
        doP2Short->setObjectName(QStringLiteral("doP2Short"));

        horizontalLayout_3->addWidget(doP2Short);


        gridLayout_3->addLayout(horizontalLayout_3, 1, 1, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        thruStatus = new QCheckBox(groupBox);
        thruStatus->setObjectName(QStringLiteral("thruStatus"));
        thruStatus->setEnabled(false);

        horizontalLayout_8->addWidget(thruStatus);

        doThru = new QPushButton(groupBox);
        doThru->setObjectName(QStringLiteral("doThru"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(doThru->sizePolicy().hasHeightForWidth());
        doThru->setSizePolicy(sizePolicy2);

        horizontalLayout_8->addWidget(doThru);


        gridLayout_3->addLayout(horizontalLayout_8, 3, 0, 1, 2);


        gridLayout_2->addWidget(groupBox, 2, 0, 1, 3);

        groupBox_2 = new QGroupBox(calGroup);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        openLength = new QDoubleSpinBox(groupBox_2);
        openLength->setObjectName(QStringLiteral("openLength"));
        openLength->setMinimum(-1000);
        openLength->setMaximum(1000);
        openLength->setValue(-19.05);

        gridLayout_4->addWidget(openLength, 0, 0, 1, 1);

        applyOpenLength = new QPushButton(groupBox_2);
        applyOpenLength->setObjectName(QStringLiteral("applyOpenLength"));

        gridLayout_4->addWidget(applyOpenLength, 0, 1, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 3, 0, 1, 3);


        verticalLayout->addWidget(calGroup);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(0, 1);
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "AKELA Open VNA", 0));
        sysGroup->setTitle(QApplication::translate("MainWindow", "System", 0));
        ip->setPrefix(QApplication::translate("MainWindow", "192.168.1.", 0));
        label_5->setText(QApplication::translate("MainWindow", "IP Address", 0));
        label_6->setText(QApplication::translate("MainWindow", "IP Port", 0));
        doInitialize->setText(QApplication::translate("MainWindow", "Initialize", 0));
        runToggle->setText(QApplication::translate("MainWindow", "Run", 0));
        stimGroup->setTitle(QApplication::translate("MainWindow", "Stimulus", 0));
        label_2->setText(QApplication::translate("MainWindow", "Start Freq [MHz]", 0));
        label->setText(QApplication::translate("MainWindow", "Sweep Rate [kHz]", 0));
        sweepRate->clear();
        sweepRate->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "45", 0)
         << QApplication::translate("MainWindow", "30", 0)
         << QApplication::translate("MainWindow", "15.3", 0)
         << QApplication::translate("MainWindow", "7", 0)
         << QApplication::translate("MainWindow", "3.5", 0)
         << QApplication::translate("MainWindow", "2", 0)
        );
        label_3->setText(QApplication::translate("MainWindow", "Stop Freq [MHz]", 0));
        label_4->setText(QApplication::translate("MainWindow", "Points", 0));
        calGroup->setTitle(QApplication::translate("MainWindow", "Calibration", 0));
        calibrationSetting->clear();
        calibrationSetting->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Off", 0)
         << QApplication::translate("MainWindow", "Factory", 0)
         << QApplication::translate("MainWindow", "User", 0)
        );
        loadCal->setText(QApplication::translate("MainWindow", "Load...", 0));
        clearCal->setText(QApplication::translate("MainWindow", "Clear", 0));
        saveCal->setText(QApplication::translate("MainWindow", "Save...", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Primary 12-term", 0));
        p1OpenStatus->setText(QString());
        doP1Open->setText(QApplication::translate("MainWindow", "Port 1 Open", 0));
        p1ShortStatus->setText(QString());
        doP1Short->setText(QApplication::translate("MainWindow", "Port 1 Short", 0));
        p2OpenStatus->setText(QString());
        doP2Open->setText(QApplication::translate("MainWindow", "Port 2 Open", 0));
        p2LoadStatus->setText(QString());
        doP2Load->setText(QApplication::translate("MainWindow", "Port 2 Load", 0));
        p1LoadStatus->setText(QString());
        doP1Load->setText(QApplication::translate("MainWindow", "Port 1 Load", 0));
        p2ShortStatus->setText(QString());
        doP2Short->setText(QApplication::translate("MainWindow", "Port 2 Short", 0));
        thruStatus->setText(QString());
        doThru->setText(QApplication::translate("MainWindow", "Thru", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Offset Open Compensation", 0));
        openLength->setSuffix(QApplication::translate("MainWindow", " mm", 0));
        applyOpenLength->setText(QApplication::translate("MainWindow", "Apply", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
