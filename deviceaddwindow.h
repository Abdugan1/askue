#ifndef DEVICEADDWINDOW_H
#define DEVICEADDWINDOW_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;

class Device;

class DeviceAddWindow : public QDialog
{
    Q_OBJECT
public:
    explicit DeviceAddWindow(QWidget *parent = nullptr);

signals:
    void deviceAdded(const Device &device);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void setupUi();

    void clear();

private slots:
    void onAddClicked();

private:
    QLineEdit *nameEdit_ = nullptr;
    QLabel *nameLabel_ = nullptr;
    QLineEdit *ipEdit_ = nullptr;
    QLabel *ipLabel_ = nullptr;
    QLineEdit *portEdit_ = nullptr;
    QLabel *portLabel_ = nullptr;
    QPushButton *addButton_ = nullptr;
};

#endif // DEVICEADDWINDOW_H
