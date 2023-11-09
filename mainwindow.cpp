#include "mainwindow.h"
#include "devicelist.h"
#include "deviceaddwindow.h"
#include "valuetable.h"

#include <QBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();

    deviceAddWindow_ = new DeviceAddWindow;

    connect(deviceList_, &DeviceList::addDeviceButtonClicked, deviceAddWindow_, &DeviceAddWindow::show);
    connect(deviceAddWindow_, &DeviceAddWindow::deviceAdded, deviceList_, &DeviceList::addDevice);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUi()
{
    deviceList_ = new DeviceList;
    valueTable_ = new ValueTable;

    auto layout = new QHBoxLayout;
    layout->addWidget(deviceList_);
    layout->addWidget(valueTable_);

    auto widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
}

