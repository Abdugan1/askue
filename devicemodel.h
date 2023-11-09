#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QPointer>

#include "device.h"
#include "modbusclient.h"

class DeviceModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit DeviceModel(QObject *parent = nullptr);

    void addDevice(const Device &device);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:
    QVector<Device> devices_;
};

#endif // DEVICEMODEL_H
