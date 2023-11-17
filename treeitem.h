#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>
#include <QList>

class TreeItem
{
public:
    enum Role {
        Type = Qt::UserRole + 1,

        UserRole,
    };

    enum Type {
        Root,
        DeviceItem,
        ValueItem,
    };

    explicit TreeItem(enum Type type, TreeItem *parent = nullptr);
    virtual ~TreeItem();

    int childCount() const;
    virtual int columnCount() const;

    QVariant data(int role) const;

    void addChild(TreeItem *child);
    TreeItem *child(int row);

    TreeItem* parent();

    int row() const;

    enum Type type() const;

protected:
    virtual QVariant dataImp(int column) const;

private:
    QList<TreeItem *> childs_;
    TreeItem *parent_;
    enum Type type_;
};
#endif // TREEITEM_H
