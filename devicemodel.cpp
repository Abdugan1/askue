#include "devicemodel.h"
#include "device.h"

QModelIndex DeviceModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    DeviceItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<DeviceItem *>(parent.internalPointer());

    DeviceItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

QModelIndex DeviceModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    DeviceItem *childItem = static_cast<DeviceItem *>(child.internalPointer());
    DeviceItem *parentItem = childItem->parentItem;

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int DeviceModel::rowCount(const QModelIndex &parent) const
{
    DeviceItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<DeviceItem *>(parent.internalPointer());

    return parentItem->childCount();
}

int DeviceModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1; // Одна колонка для отображения имени
}

QVariant DeviceModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    DeviceItem *item = static_cast<DeviceItem *>(index.internalPointer());
    return item->name();
}

void DeviceModel::addDevice(const QString &deviceName)
{
    beginInsertRows(QModelIndex(), rootItem->childCount(), rootItem->childCount());
    rootItem->appendChild(new DeviceItem(deviceName, rootItem));
    endInsertRows();
}

void DeviceModel::addTag(const QModelIndex &deviceIndex, const QString &tagName)
{
    if (!deviceIndex.isValid())
        return;

    DeviceItem *deviceItem = static_cast<DeviceItem *>(deviceIndex.internalPointer());
    beginInsertRows(deviceIndex, deviceItem->childCount(), deviceItem->childCount());
    deviceItem->appendChild(new DeviceItem(tagName, deviceItem));
    endInsertRows();
}

TreeItem::TreeItem(const QVector<QVariant> &data, TreeItemPtr parent)
    : data_(data)
    , parentItem_(parent)
{

}

TreeItem::~TreeItem()
{
}

void TreeItem::appendChild(TreeItemPtr child)
{
    childItems_.push_back(child);
}

TreeItemPtr TreeItem::child(int row)
{
    if (row < 0 || row >= childItems_.size())
        return nullptr;
    return childItems_.at(row);
}

int TreeItem::childCound() const
{
    return childItems_.count();
}

int TreeItem::columnCount()
{
    return data_.count();
}

QVariant TreeItem::data(int column) const
{
    if (column < 0 || column >= data_.size())
        return QVariant();
    return data_.at(column);
}

int TreeItem::row() const
{
    if (parentItem_)
        return parentItem_->childItems_.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

TreeItemPtr TreeItem::parentItem() const
{
    return parentItem_;
}
