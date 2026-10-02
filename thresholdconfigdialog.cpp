#include "thresholdconfigdialog.h"
#include "ui_thresholdconfigdialog.h"

ThresholdConfigDialog::ThresholdConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThresholdConfigDialog)
{
    ui->setupUi(this);
}

ThresholdConfigDialog::~ThresholdConfigDialog()
{
    delete ui;
}

void ThresholdConfigDialog::setDefaults(int bruteT, int bruteW, int dosT, int dosW, int portP, int portW)
{
    ui->spinBruteThreshold->setValue(bruteT);
    ui->spinBruteWindow->setValue(bruteW);
    ui->spinDoSThreshold->setValue(dosT);
    ui->spinDoSWindow->setValue(dosW);
    ui->spinPortScanPorts->setValue(portP);
    ui->spinPortScanWindow->setValue(portW);
}

int ThresholdConfigDialog::getBruteForceThreshold() const { return ui->spinBruteThreshold->value(); }
int ThresholdConfigDialog::getBruteForceWindow() const { return ui->spinBruteWindow->value(); }
int ThresholdConfigDialog::getDoSThreshold() const { return ui->spinDoSThreshold->value(); }
int ThresholdConfigDialog::getDoSWindow() const { return ui->spinDoSWindow->value(); }
int ThresholdConfigDialog::getPortScanPorts() const { return ui->spinPortScanPorts->value(); }
int ThresholdConfigDialog::getPortScanWindow() const { return ui->spinPortScanWindow->value(); }

void ThresholdConfigDialog::on_buttonBox_accepted()
{
    bruteForceThreshold = getBruteForceThreshold();
    bruteForceWindow = getBruteForceWindow();
    dosThreshold = getDoSThreshold();
    dosWindow = getDoSWindow();
    portScanPorts = getPortScanPorts();
    portScanWindow = getPortScanWindow();
}
