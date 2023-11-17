#ifndef VALUEITEM_H
#define VALUEITEM_H

#include "treeitem.h"
#include "valuerequestoptions.h"

class ValueItem : public TreeItem
{
public:
    enum Role {
        Name =  TreeItem::UserRole + 1,
        Address,
        RequestInterval,

        ColumnCount = 3
    };

    explicit ValueItem(const ValueRequestOptions &valueOptions, TreeItem *parent = nullptr);

    int columnCount() const override;

    QString name() const;
    int address() const;
    int requestInterval() const;

protected:
    QVariant dataImp(int column) const override;

private:
    ValueRequestOptions valueOptions_;
};

#endif // VALUEITEM_H
