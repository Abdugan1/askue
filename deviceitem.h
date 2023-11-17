#ifndef DEVICEITEM_H
#define DEVICEITEM_H

#include "treeitem.h"
#include "device.h"

class DeviceItem : public TreeItem
{
public:
    enum Role {
        Id = TreeItem::UserRole + 1,
        Name,
        Ip,
        Port,

        ColumnCount = 4
    };

    explicit DeviceItem(const Device &device, TreeItem *parent = nullptr);

    int columnCount() const override;

    QString id() const;
    QString name() const;
    QString ip() const;
    int port() const;

protected:
    QVariant dataImp(int column) const override;

private:
    Device device_;
};

#endif // DEVICEITEM_H
