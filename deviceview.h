#ifndef DEVICEVIEW_H
#define DEVICEVIEW_H

#include <QTreeView>

//#include "modbusclient.h"

class QPushButton;

class DeviceModel;
class DeviceDelegate;

class Device;
class ValueRequestOptions;

class DeviceContextMenu;
class DeviceAddWindow;
class ValueAddWindow;

class DeviceView : public QTreeView
{
    Q_OBJECT
public:
    explicit DeviceView(QWidget *parent = nullptr);

signals:
    void currentChanged(const QString &currentName);


public slots:
    void addDevice(const Device &device);
    void addValue(const QModelIndex &deviceIndex, const ValueRequestOptions &options);
    void onContextMenuRequested(const QPoint &pos);

private:
    void setupUi();

private:
    DeviceModel *model_ = nullptr;
    DeviceDelegate *delegate_ = nullptr;

    QPushButton *addDeviceButton_ = nullptr;

    DeviceContextMenu *deviceContextMenu_ = nullptr;
    DeviceAddWindow *deviceAddWindow_ = nullptr;
    ValueAddWindow *valueAddWindow_ = nullptr;
};

#endif // DEVICEVIEW_H
