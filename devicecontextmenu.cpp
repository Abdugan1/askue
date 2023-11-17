#include "devicecontextmenu.h"

#include <QAction>

DeviceContextMenu::DeviceContextMenu(QWidget *parent)
    : QMenu(parent)
    , addValueAction_(new QAction(tr("&Add value..."), this))
    , deleteAction_(new QAction(tr("&Delete"), this))
{
    addAction(addValueAction_);
    addAction(deleteAction_);

    connect(addValueAction_, &QAction::triggered, this, [this]() {
        emit addValueTriggered(index_);
    });

    connect(deleteAction_, &QAction::triggered, this, [this]() {
        emit addValueTriggered(index_);
    });
}

void DeviceContextMenu::popup(const QPoint &pos, const QModelIndex &index)
{
    index_ = index;
    QMenu::popup(pos);
}
