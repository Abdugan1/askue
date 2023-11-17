#include "treeitem.h"

TreeItem::TreeItem(enum Type type, TreeItem *parent)
    : parent_(parent)
    , type_(type)
{

}

TreeItem::~TreeItem()
{

}

int TreeItem::childCount() const
{
    return childs_.size();
}

int TreeItem::columnCount() const
{
    return 1;
}

QVariant TreeItem::data(int role) const
{
    if (role == Role::Type)
        return type_;

    return dataImp(role);
}

void TreeItem::addChild(TreeItem *child)
{
    childs_.push_back(child);
    child->parent_ = this;
}

TreeItem *TreeItem::child(int row)
{
    return childs_[row];
}

TreeItem *TreeItem::parent()
{
    return parent_;
}

int TreeItem::row() const
{
    if (parent_) {
        //        const std::shared_ptr<const TreeItem> self(this);
        return parent_->childs_.indexOf(this);
    }
    return 0;
}

QVariant TreeItem::dataImp(int role) const
{
    qDebug() << "shit";
    return QVariant();
}

enum TreeItem::Type TreeItem::type() const
{
    return type_;
}
