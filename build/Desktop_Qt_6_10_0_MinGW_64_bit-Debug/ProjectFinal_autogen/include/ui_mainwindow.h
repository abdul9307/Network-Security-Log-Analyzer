/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *buttonLayout;
    QPushButton *btnLoadLog;
    QPushButton *btnRunDetection;
    QPushButton *btnConfigureThresholds;
    QPushButton *btnManageWhitelist;
    QPushButton *btnGenerateReports;
    QPushButton *btnQuit;
    QTextEdit *txtAlerts;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        btnLoadLog = new QPushButton(centralwidget);
        btnLoadLog->setObjectName("btnLoadLog");

        buttonLayout->addWidget(btnLoadLog);

        btnRunDetection = new QPushButton(centralwidget);
        btnRunDetection->setObjectName("btnRunDetection");

        buttonLayout->addWidget(btnRunDetection);

        btnConfigureThresholds = new QPushButton(centralwidget);
        btnConfigureThresholds->setObjectName("btnConfigureThresholds");

        buttonLayout->addWidget(btnConfigureThresholds);

        btnManageWhitelist = new QPushButton(centralwidget);
        btnManageWhitelist->setObjectName("btnManageWhitelist");

        buttonLayout->addWidget(btnManageWhitelist);

        btnGenerateReports = new QPushButton(centralwidget);
        btnGenerateReports->setObjectName("btnGenerateReports");

        buttonLayout->addWidget(btnGenerateReports);

        btnQuit = new QPushButton(centralwidget);
        btnQuit->setObjectName("btnQuit");

        buttonLayout->addWidget(btnQuit);


        verticalLayout->addLayout(buttonLayout);

        txtAlerts = new QTextEdit(centralwidget);
        txtAlerts->setObjectName("txtAlerts");
        txtAlerts->setReadOnly(true);

        verticalLayout->addWidget(txtAlerts);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Logic Analyzer", nullptr));
        btnLoadLog->setText(QCoreApplication::translate("MainWindow", "Load Log", nullptr));
        btnRunDetection->setText(QCoreApplication::translate("MainWindow", "Run Detection", nullptr));
        btnConfigureThresholds->setText(QCoreApplication::translate("MainWindow", "Configure Thresholds", nullptr));
        btnManageWhitelist->setText(QCoreApplication::translate("MainWindow", "Manage Whitelist", nullptr));
        btnGenerateReports->setText(QCoreApplication::translate("MainWindow", "Generate Reports", nullptr));
        btnQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
