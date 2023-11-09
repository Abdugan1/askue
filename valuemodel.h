#ifndef VALUEMODEL_H
#define VALUEMODEL_H

#include <QAbstractTableModel>
#include <QVector>

#include "value.h"

class ValueModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ValueModel(QObject *parent = nullptr);

    void addValue(const Value &value);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    QVector<Value> values_;
};

#endif // VALUEMODEL_H
