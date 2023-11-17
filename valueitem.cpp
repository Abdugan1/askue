#include "valueitem.h"

ValueItem::ValueItem(const ValueRequestOptions &valueOptions, TreeItem *parent)
    : TreeItem(TreeItem::ValueItem, parent)
    , valueOptions_(valueOptions)
{

}

int ValueItem::columnCount() const
{
    return ColumnCount;
}

QString ValueItem::name() const
{
    return valueOptions_.name();
}

int ValueItem::address() const
{
    return valueOptions_.address();
}

int ValueItem::requestInterval() const
{
    return valueOptions_.requestIntervalMs();
}

QVariant ValueItem::dataImp(int role) const
{
    switch (role) {
    case Role::Name:
        return name();
        break;
    case Role::Address:
        return address();
        break;
    case Role::RequestInterval:
        return requestInterval();
        break;
    default:
        break;
    }

    return QVariant();
}
