#ifndef DEVICEDELEGATE_H
#define DEVICEDELEGATE_H

#include <QStyledItemDelegate>

class DeviceDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DeviceDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    void paintDeviceItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void paintValueItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // DEVICEDELEGATE_H
