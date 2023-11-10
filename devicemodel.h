#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QPointer>

#include <memory>

#include "device.h"
#include "modbusclient.h"

class TreeItem;
using TreeItemPtr = std::shared_ptr<TreeItem>;

class TreeItem
{
public:
    explicit TreeItem(const QVector<QVariant> &data, TreeItemPtr parent = nullptr);
    virtual ~TreeItem();

    void appendChild(TreeItemPtr child);

    TreeItemPtr child(int row);
    int childCound() const;
    int columnCount();

    QVariant data(int column) const;
    int row() const;
    TreeItemPtr parentItem() const;

private:
    QVector<TreeItemPtr> childItems_;
    QVector<QVariant> data_;
    TreeItemPtr parentItem_;
};

class DeviceModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit DeviceModel(QObject *parent = nullptr) : QAbstractItemModel(parent)
    {
        rootItem = new DeviceItem("Root");
    }

    ~DeviceModel()
    {
        delete rootItem;
    }

    // Методы QAbstractItemModel
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Дополнительные методы для работы с моделью
    void addDevice(const QString &deviceName);
    void addTag(const QModelIndex &deviceIndex, const QString &tagName);

private:
    class DeviceItem
    {
    public:
        explicit DeviceItem(const QString &name, DeviceItem *parentItem = nullptr) : itemName(name), parentItem(parentItem) {}

        ~DeviceItem()
        {
            qDeleteAll(childItems);
        }

        void appendChild(DeviceItem *child)
        {
            childItems.append(child);
        }

        DeviceItem *child(int row)
        {
            return childItems.value(row);
        }

        int childCount() const
        {
            return childItems.count();
        }

        int row() const
        {
            if (parentItem)
                return parentItem->childItems.indexOf(const_cast<DeviceItem *>(this));
            return 0;
        }

        QString name() const
        {
            return itemName;
        }

    private:
        QList<DeviceItem *> childItems;
        QString itemName;
        DeviceItem *parentItem;

        friend class DeviceModel;
    };

    DeviceItem *rootItem;
};

#endif // DEVICEMODEL_H
