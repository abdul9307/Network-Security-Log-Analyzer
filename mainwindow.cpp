#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logicanalyzer.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnLoadLog, &QPushButton::clicked, this, &MainWindow::onLoadLogClicked);
    connect(ui->btnRunDetection, &QPushButton::clicked, this, &MainWindow::onRunDetectionClicked);
    connect(ui->btnConfigureThresholds, &QPushButton::clicked, this, &MainWindow::onConfigureThresholdsClicked);
    connect(ui->btnManageWhitelist, &QPushButton::clicked, this, &MainWindow::onManageWhitelistClicked);
    connect(ui->btnGenerateReports, &QPushButton::clicked, this, &MainWindow::onGenerateReportsClicked);
    connect(ui->btnQuit, &QPushButton::clicked, this, &MainWindow::onQuitClicked);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onLoadLogClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Log CSV", "", "*.csv");
    if (!fileName.isEmpty())
    {
        logicAnalyzer.loadLogFile(fileName.toStdString());
        ui->txtAlerts->append("Log loaded: " + fileName);
    }
    currentLogFile = fileName;
}

void MainWindow::onRunDetectionClicked()
{
    if (currentLogFile.isEmpty()) {
        ui->txtAlerts->append("No log file loaded.");
        return;
    }

    ui->txtAlerts->clear();

    QString dateStr = QString::fromStdString(logicAnalyzer.extractDate(currentLogFile.toStdString()));

    QDir dir(QDir::currentPath());
    if (!dir.exists("alerts")) dir.mkdir("alerts");

    QString alertFilePath = dir.filePath("alerts/alerts_" + dateStr + ".txt");

    std::ofstream alertFile(alertFilePath.toStdString());
    if (!alertFile.is_open()) {
        ui->txtAlerts->append("Failed to open alerts file: " + alertFilePath);
        return;
    }

    // Run detection
    logicAnalyzer.detectDOS(alertFile, std::cout);
    logicAnalyzer.checkBruteForce(alertFile, std::cout);
    logicAnalyzer.portScanDetect(alertFile, std::cout);

    alertFile.close();

    ui->txtAlerts->append("Detection run complete. Alerts saved to: " + alertFilePath);
}

void MainWindow::onConfigureThresholdsClicked()
{
    bool ok;
    int val;

    val = QInputDialog::getInt(this, "Configure DOS threshold", "Max actions:", logicAnalyzer.dosThreshold, 1, 10000, 1, &ok);
    if (ok) logicAnalyzer.dosThreshold = val;
    val = QInputDialog::getInt(this, "Configure DOS window (seconds)", "Window:", logicAnalyzer.dosWindow, 1, 3600, 1, &ok);
    if (ok) logicAnalyzer.dosWindow = val;

    val = QInputDialog::getInt(this, "Configure Brute-force threshold", "Max fails:", logicAnalyzer.bruteForceThreshold, 1, 100, 1, &ok);
    if (ok) logicAnalyzer.bruteForceThreshold = val;
    val = QInputDialog::getInt(this, "Configure Brute-force window (seconds)", "Window:", logicAnalyzer.bruteForceWindow, 1, 3600, 1, &ok);
    if (ok) logicAnalyzer.bruteForceWindow = val;

    val = QInputDialog::getInt(this, "Configure PortScan ports", "Distinct ports:", logicAnalyzer.portScanPorts, 1, 1000, 1, &ok);
    if (ok) logicAnalyzer.portScanPorts = val;
    val = QInputDialog::getInt(this, "Configure PortScan window (seconds)", "Window:", logicAnalyzer.portScanWindow, 1, 3600, 1, &ok);
    if (ok) logicAnalyzer.portScanWindow = val;

    ui->txtAlerts->append("Thresholds updated.");
}

void MainWindow::onManageWhitelistClicked()
{
    bool ok;
    QString ip = QInputDialog::getText(this, "Add/Remove Whitelist IP", "Enter IP:", QLineEdit::Normal, "", &ok);
    if (ok && !ip.isEmpty())
    {
        if (logicAnalyzer.ipWhitelisted(ip.toStdString()))
        {
            logicAnalyzer.removeWhitelistIP(ip.toStdString());
            ui->txtAlerts->append("Removed from whitelist: " + ip);
        }
        else
        {
            logicAnalyzer.addWhitelistIP(ip.toStdString());
            ui->txtAlerts->append("Added to whitelist: " + ip);
        }
        logicAnalyzer.saveWhitelist("whitelist.txt");
    }
}

void MainWindow::onGenerateReportsClicked()
{
    // Ensure reports folder exists
    QDir dir(QDir::currentPath());
    if (!dir.exists("reports"))
        dir.mkdir("reports");

    // Determine file name based on current date
    QString dateStr = QString::fromStdString(logicAnalyzer.extractDate(currentLogFile.toStdString()));
    QString filePath = dir.filePath(QString("reports/report_%1.csv").arg(dateStr));

    std::ofstream report(filePath.toStdString());
    if (!report.is_open())
    {
        ui->txtAlerts->append("Failed to open file: " + filePath);
        return;
    }

    report << "=== Top Source IPs ===\n";
    report << "SourceIP,EventCount\n";
    // Sort top talkers
    std::vector<std::pair<int, std::string>> sourceStats;
    for (size_t i = 0; i < logicAnalyzer.uniqueIPs.size(); ++i)
        sourceStats.emplace_back(logicAnalyzer.ipActionCount[i], logicAnalyzer.uniqueIPs[i]);

    std::sort(sourceStats.rbegin(), sourceStats.rend()); // descending
    for (size_t i = 0; i < sourceStats.size() && i < 10; ++i)
        report << sourceStats[i].second << "," << sourceStats[i].first << "\n";

    report << "\n=== Top Targets (destIP,port) ===\n";
    report << "DestIP,Port,EventCount\n";

    // Count destIP,port occurrences
    std::map<std::pair<std::string,int>, int> targetCount;
    for (size_t i = 0; i < logicAnalyzer.destIPs.size(); ++i)
        targetCount[{logicAnalyzer.destIPs[i], logicAnalyzer.ports[i]}]++;

    // Sort top targets
    std::vector<std::pair<int, std::pair<std::string,int>>> targetStats;
    for (auto &kv : targetCount)
        targetStats.emplace_back(kv.second, kv.first);

    std::sort(targetStats.rbegin(), targetStats.rend()); // descending
    for (size_t i = 0; i < targetStats.size() && i < 10; ++i)
        report << targetStats[i].second.first << "," << targetStats[i].second.second << "," << targetStats[i].first << "\n";

    report.close();
    ui->txtAlerts->append("Report generated: " + filePath);
}

void MainWindow::onQuitClicked()
{
    close();
}

void MainWindow::addAlertToGui(const QString &msg)
{
    ui->txtAlerts->append(msg);
}

