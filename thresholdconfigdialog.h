#ifndef THRESHOLDCONFIGDIALOG_H
#define THRESHOLDCONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class ThresholdConfigDialog;
}

class ThresholdConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ThresholdConfigDialog(QWidget *parent = nullptr);
    ~ThresholdConfigDialog();

    int getBruteForceThreshold() const;
    int getBruteForceWindow() const;
    int getDoSThreshold() const;
    int getDoSWindow() const;
    int getPortScanPorts() const;
    int getPortScanWindow() const;

    void setDefaults(int bruteT, int bruteW, int dosT, int dosW, int portP, int portW);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ThresholdConfigDialog *ui;

    int bruteForceThreshold;
    int bruteForceWindow;
    int dosThreshold;
    int dosWindow;
    int portScanPorts;
    int portScanWindow;
};

#endif // THRESHOLDCONFIGDIALOG_H
