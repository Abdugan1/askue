#ifndef DEVICEADDWINDOW_H
#define DEVICEADDWINDOW_H

#include <QDialog>

class BuddyLineEdit;
class QPushButton;

class Device;
class Value;

class DeviceAddWindow : public QDialog
{
    Q_OBJECT
public:
    explicit DeviceAddWindow(QWidget *parent = nullptr);

signals:
    void deviceAdded(const Device &device, const Value &value);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void setupUi();

    void clear();

private slots:
    void onAddClicked();

private:
    BuddyLineEdit *nameEdit_ = nullptr;
    BuddyLineEdit *ipEdit_ = nullptr;
    BuddyLineEdit *portEdit_ = nullptr;
    BuddyLineEdit *valueAddressEdit_ = nullptr;

    QPushButton *addButton_ = nullptr;
};

#endif // DEVICEADDWINDOW_H
