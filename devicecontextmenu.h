#ifndef DEVICECONTEXTMENU_H
#define DEVICECONTEXTMENU_H


#include <QMenu>
#include <QModelIndex>

class DeviceContextMenu : public QMenu
{
    Q_OBJECT
public:
    explicit DeviceContextMenu(QWidget *parent = nullptr);

    void popup(const QPoint &pos, const QModelIndex &index);

signals:
    void addValueTriggered(const QModelIndex &toAddIndex);
    void deleteTriggered(const QModelIndex &deleteIndex);

private:
    QModelIndex index_;

    QAction *addValueAction_ = nullptr;
    QAction *deleteAction_ = nullptr;
};

#endif // DEVICECONTEXTMENU_H
