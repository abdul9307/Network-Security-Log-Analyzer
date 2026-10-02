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
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QPushButton *loadLogBtn;
    QPushButton *runDetectionBtn;
    QPushButton *configBtn;
    QPushButton *manageWhitelistBtn;
    QPushButton *generateReportsBtn;
    QTableWidget *alertsTable;
    QTextEdit *summaryText;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(900, 600);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        loadLogBtn = new QPushButton(centralwidget);
        loadLogBtn->setObjectName("loadLogBtn");

        verticalLayout->addWidget(loadLogBtn);

        runDetectionBtn = new QPushButton(centralwidget);
        runDetectionBtn->setObjectName("runDetectionBtn");

        verticalLayout->addWidget(runDetectionBtn);

        configBtn = new QPushButton(centralwidget);
        configBtn->setObjectName("configBtn");

        verticalLayout->addWidget(configBtn);

        manageWhitelistBtn = new QPushButton(centralwidget);
        manageWhitelistBtn->setObjectName("manageWhitelistBtn");

        verticalLayout->addWidget(manageWhitelistBtn);

        generateReportsBtn = new QPushButton(centralwidget);
        generateReportsBtn->setObjectName("generateReportsBtn");

        verticalLayout->addWidget(generateReportsBtn);

        alertsTable = new QTableWidget(centralwidget);
        if (alertsTable->columnCount() < 4)
            alertsTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        alertsTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        alertsTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        alertsTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        alertsTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        alertsTable->setObjectName("alertsTable");
        alertsTable->setColumnCount(4);
        alertsTable->setRowCount(0);

        verticalLayout->addWidget(alertsTable);

        summaryText = new QTextEdit(centralwidget);
        summaryText->setObjectName("summaryText");
        summaryText->setReadOnly(true);

        verticalLayout->addWidget(summaryText);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 900, 26));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Logic Analyzer Dashboard", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        loadLogBtn->setText(QCoreApplication::translate("MainWindow", "Load Log File", nullptr));
        runDetectionBtn->setText(QCoreApplication::translate("MainWindow", "Run Detection", nullptr));
        configBtn->setText(QCoreApplication::translate("MainWindow", "Configure Thresholds", nullptr));
        manageWhitelistBtn->setText(QCoreApplication::translate("MainWindow", "Manage Whitelist", nullptr));
        generateReportsBtn->setText(QCoreApplication::translate("MainWindow", "Generate Reports", nullptr));
        QTableWidgetItem *___qtablewidgetitem = alertsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Timestamp", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = alertsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Rule", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = alertsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Source IP", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = alertsTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Severity", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
