#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QPointer>

#include <memory>
#include <vector>

class TreeItem;
class ValueRequestOptions;
class Device;

class DeviceModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit DeviceModel(QObject *parent = nullptr);

    void addDevice(const Device &device);
    void addValue(const QModelIndex &deviceIndex, const ValueRequestOptions &options);

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:
    TreeItem *rootItem_ = nullptr;
};


#endif // DEVICEMODEL_H
