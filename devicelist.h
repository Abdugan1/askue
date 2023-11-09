#ifndef DEVICELIST_H
#define DEVICELIST_H

#include <QListView>

//#include "modbusclient.h"

class QPushButton;

class Device;
class DeviceModel;

class DeviceList : public QListView
{
    Q_OBJECT
public:
    explicit DeviceList(QWidget *parent = nullptr);

signals:
    void addDeviceButtonClicked();

public slots:
    void addDevice(const Device &device);

private:
    void setupUi();

private:
    DeviceModel *model_ = nullptr;


    QPushButton *addDeviceButton_ = nullptr;
};

#endif // DEVICELIST_H
