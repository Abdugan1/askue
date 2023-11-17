#include "deviceview.h"
#include "devicemodel.h"
#include "devicedelegate.h"
#include "modbusmanager.h"
#include "database.h"
#include "devicecontextmenu.h"
#include "deviceaddwindow.h"
#include "valueaddwindow.h"
#include "device.h"
#include "valuerequestoptions.h"

#include <QPushButton>
#include <QBoxLayout>
#include <QDebug>

DeviceView::DeviceView(QWidget *parent)
    : QTreeView(parent)
    , model_(new DeviceModel(this))
    , delegate_(new DeviceDelegate(this))
    , deviceContextMenu_(new DeviceContextMenu(this))
    , deviceAddWindow_(new DeviceAddWindow(this))
    , valueAddWindow_(new ValueAddWindow(this))
{
    setModel(model_);
    setItemDelegate(delegate_);
    setupUi();

    connect(selectionModel(), &QItemSelectionModel::currentChanged, this, [this](const QModelIndex &current, const QModelIndex &previous) {
        emit currentChanged(current.data(Qt::DisplayRole).toString());
    });

    connect(addDeviceButton_, &QPushButton::clicked, deviceAddWindow_, &DeviceAddWindow::show);
    connect(deviceAddWindow_, &DeviceAddWindow::deviceAdded, this, &DeviceView::addDevice);
    connect(deviceContextMenu_, &DeviceContextMenu::addValueTriggered, valueAddWindow_, [this](const QModelIndex &toAddIndex) {
        valueAddWindow_->setToAddIndex(toAddIndex);
        valueAddWindow_->show();
    });

    connect(valueAddWindow_, &ValueAddWindow::valueAdded, this, &DeviceView::addValue);
}

void DeviceView::addDevice(const Device &device)
{
    database().addDevice(device);
    model_->addDevice(device);
    //    modbusManager().addModbus(device,);
}

void DeviceView::addValue(const QModelIndex &deviceIndex, const ValueRequestOptions &options)
{
    model_->addValue(deviceIndex, options);
}

void DeviceView::onContextMenuRequested(const QPoint &pos)
{
    const QModelIndex indexUnderCusros = indexAt(pos);
    if (!indexUnderCusros.isValid())
        return;

    deviceContextMenu_->popup(viewport()->mapToGlobal(pos), indexUnderCusros);
}

void DeviceView::setupUi()
{
    addDeviceButton_ = new QPushButton("&Add Device");

    auto layout = new QVBoxLayout;
    layout->addWidget(addDeviceButton_, 0, Qt::AlignRight | Qt::AlignBottom);

    setLayout(layout);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QTreeView::customContextMenuRequested, this, &DeviceView::onContextMenuRequested);
}
