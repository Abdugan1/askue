#include "valuemodel.h"
#include "database.h"

ValueModel::ValueModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

void ValueModel::addValue(const Value &value)
{
    const int row = values_.size();
    beginInsertRows(QModelIndex(), row, row);
    values_.push_back(value);
    endInsertRows();
}

void ValueModel::select(const QString &name)
{
    currentName_ = name;

    const int prevSize = values_.size();

    beginResetModel();
    values_ = database().values(name);
    qDebug() << rowCount(QModelIndex());
    endResetModel();
}

int ValueModel::rowCount(const QModelIndex &parent) const
{
    return values_.size();
}

int ValueModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant ValueModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation != Qt::Horizontal)
        return QAbstractItemModel::headerData(section, orientation, role);

    switch (section) {
    case 0:
        return tr("Date");
        break;
    case 1:
        return tr("Address");
        break;
    case 2:
        return tr("Value");
        break;
    default:
        break;
    }

    return QVariant();
}

QVariant ValueModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    const int row    = index.row();
    const int column = index.column();
    switch (column) {
    case 0:
        return values_[row].dateTime();
        break;
    case 1:
        return values_[row].address();
        break;
    case 2:
        return values_[row].value();
        break;
    default:
        break;
    }

    return QVariant();
}

Qt::ItemFlags ValueModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index);
}

QString ValueModel::currentName() const
{
    return currentName_;
}
