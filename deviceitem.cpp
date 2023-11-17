#include "deviceitem.h"

DeviceItem::DeviceItem(const Device &device, TreeItem *parent)
    : TreeItem(TreeItem::DeviceItem, parent)
    , device_(device)
{
}

int DeviceItem::columnCount() const
{
    return ColumnCount;
}

QString DeviceItem::id() const
{
    return device_.id();
}

QString DeviceItem::name() const
{
    return device_.name();
}

QString DeviceItem::ip() const
{
    return device_.ip();
}

int DeviceItem::port() const
{
    return device_.port();
}

QVariant DeviceItem::dataImp(int role) const
{
    switch (role) {
    case Role::Id:
        return id();
        break;
    case Role::Name:
        return name();
        break;
    case Role::Ip:
        return ip();
        break;
    case Role::Port:
        return port();
        break;
    default:
        break;
    }
    return QVariant();
}
