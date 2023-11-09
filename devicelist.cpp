#include "devicelist.h"
#include "devicemodel.h"
#include "device.h"
#include "modbusmanager.h"

#include <QPushButton>
#include <QBoxLayout>

DeviceList::DeviceList(QWidget *parent)
    : QListView(parent)
    , model_(new DeviceModel(this))
{
    setModel(model_);

    setupUi();

    connect(addDeviceButton_, &QPushButton::clicked, this, &DeviceList::addDeviceButtonClicked);
}

void DeviceList::addDevice(const Device &device)
{
    model_->addDevice(device);
    modbusManager().addModbus(device.name(), device.address(), device.port());
}

void DeviceList::setupUi()
{
    addDeviceButton_ = new QPushButton("&Add Device");

    auto layout = new QVBoxLayout;
    layout->addWidget(addDeviceButton_, 0, Qt::AlignRight | Qt::AlignBottom);

    setLayout(layout);
}
