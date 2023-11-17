#include "mainwindow.h"
#include "deviceview.h"
#include "valueview.h"

#include <QBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();

    connect(deviceList_, &DeviceView::currentChanged, valueTable_, &ValueView::selectCurrent);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUi()
{
    deviceList_ = new DeviceView;
    valueTable_ = new ValueView;

    auto layout = new QHBoxLayout;
    layout->addWidget(deviceList_);
    layout->addWidget(valueTable_);

    auto widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
}

