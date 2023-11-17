#include "devicemodel.h"
#include "device.h"
#include "valuerequestoptions.h"
#include "deviceitem.h"
#include "valueitem.h"

DeviceModel::DeviceModel(QObject *parent)
    : QAbstractItemModel(parent)
    , rootItem_(new TreeItem(TreeItem::Root))
{

}

void DeviceModel::addDevice(const Device &device)
{
    const int row = rootItem_->childCount();
    beginInsertRows(QModelIndex(), row, row);
    rootItem_->addChild(new DeviceItem(device));
    endInsertRows();
}

void DeviceModel::addValue(const QModelIndex &deviceIndex, const ValueRequestOptions &options)
{
    const int row = rowCount(deviceIndex);
    beginInsertRows(deviceIndex, row, row);
    auto deviceItem = rootItem_->child(deviceIndex.row());
    ValueItem *valueItem = new ValueItem(options);
    deviceItem->addChild(valueItem);
    endInsertRows();
}

QModelIndex DeviceModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid()) {
        parentItem = rootItem_;
    } else {
        parentItem = (static_cast<TreeItem *>(parent.internalPointer()));
    }

    TreeItem *childItem = parentItem->child(row);
    if (childItem) {
        return createIndex(row, column, childItem);
    }
    return QModelIndex();
}

QModelIndex DeviceModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    TreeItem *childItem = (static_cast<TreeItem *>(child.internalPointer()));
    TreeItem *parentItem = childItem->parent();

    if ((parentItem == rootItem_) || (!parentItem))
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int DeviceModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    TreeItem *parentItem;
    if (!parent.isValid()) {
        parentItem = rootItem_;
    } else {
        parentItem = (static_cast<TreeItem *>(parent.internalPointer()));
    }

    return parentItem->childCount();
}

int DeviceModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem *>(parent.internalPointer())->columnCount();

    return rootItem_->columnCount();
}

QVariant DeviceModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeItem *item = (static_cast<TreeItem *>(index.internalPointer()));
    return item->data(role);
}
