#include "devicemodel.h"
#include "device.h"

DeviceModel::DeviceModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

void DeviceModel::addDevice(const Device &device)
{
    const int row = devices_.size();
    beginInsertRows(QModelIndex(), row, row);
    devices_.push_back(device);
    endInsertRows();
}

int DeviceModel::rowCount(const QModelIndex &parent) const
{
    return devices_.size();
}

int DeviceModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant DeviceModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        return devices_[index.row()].address();
    }

    return QVariant();
}
