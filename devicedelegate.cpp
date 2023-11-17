#include "devicedelegate.h"
#include "deviceitem.h"
#include "valueitem.h"

#include <QPainter>
#include <QDebug>

DeviceDelegate::DeviceDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void DeviceDelegate::paint(QPainter *painter,
                           const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{
    const int type = index.data(TreeItem::Type).toInt();

    switch (type) {
    case TreeItem::DeviceItem:
        paintDeviceItem(painter, option, index);
        break;
    case TreeItem::ValueItem:
        paintValueItem(painter, option, index);
        break;
    default:
        break;
    }
}

void DeviceDelegate::paintDeviceItem(QPainter *painter,
                                     const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const
{
    painter->save();

    painter->drawText(option.rect, index.data(DeviceItem::Name).toString());

    painter->restore();
}

void DeviceDelegate::paintValueItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    painter->drawText(option.rect, index.data(ValueItem::Name).toString());

    painter->restore();
}
