#include "deviceaddwindow.h"
#include "device.h"
#include  "value.h"
#include "buddylineedit.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QIntValidator>

const QRegularExpression ipRegex("^(?:[0-9]{1,3}\\.){3}[0-9]{1,3}$");
const int PortMin = 0;
const int PortMax = 65536;

const int ValueAddressMin = 0;
const int ValueAddressMax = INT_MAX;

const QString DefaultIp   = "89.223.0.230";
const QString DefaultPort = "5678";

DeviceAddWindow::DeviceAddWindow(QWidget *parent)
    : QDialog(parent)
{
    setupUi();

    connect(addButton_, &QPushButton::clicked, this, &DeviceAddWindow::onAddClicked);
}

void DeviceAddWindow::closeEvent(QCloseEvent *event)
{
    QDialog::closeEvent(event);
    clear();
}

void DeviceAddWindow::setupUi()
{
    nameEdit_ = new BuddyLineEdit("The Mura", tr("Device &name"));
    nameEdit_->setPlaceholderText(tr("Enter name..."));

    ipEdit_ = new BuddyLineEdit(DefaultIp, tr("&IP"));
    ipEdit_->setPlaceholderText(tr("Enter address..."));
    ipEdit_->setValidator(new QRegularExpressionValidator(ipRegex, ipEdit_));

    portEdit_ = new BuddyLineEdit(DefaultPort, tr("&Port"));
    portEdit_->setPlaceholderText(tr("Enter port..."));
    portEdit_->setValidator(new QIntValidator(PortMin, PortMax, portEdit_));

    valueAddressEdit_ = new BuddyLineEdit("13312", tr("&Value address"));
    valueAddressEdit_->setPlaceholderText(tr("Enter value address..."));
    valueAddressEdit_->setValidator(new QIntValidator(ValueAddressMin, ValueAddressMax, valueAddressEdit_));


    addButton_ = new QPushButton(tr("&Add"));

    auto addressLayout = new QHBoxLayout;
    addressLayout->addWidget(ipEdit_);
    addressLayout->addWidget(portEdit_);

    auto editLayout = new QVBoxLayout;
    editLayout->addWidget(nameEdit_);
    editLayout->addLayout(addressLayout);
    editLayout->addWidget(valueAddressEdit_);

    auto layout = new QVBoxLayout;
    layout->addLayout(editLayout);
    layout->addWidget(addButton_, 0, Qt::AlignRight | Qt::AlignBottom);

    setLayout(layout);
}

void DeviceAddWindow::clear()
{
    nameEdit_->clear();
    ipEdit_->clear();
    portEdit_->clear();
}

void DeviceAddWindow::onAddClicked()
{
//    const bool acceptableInput = ipEdit_->hasAcceptableInput()
//                                 && portEdit_->hasAcceptableInput()
//                                 && nameEdit_->hasAcceptableInput();

//    if (!acceptableInput) {

//    }

    Device device;
    device.setName(nameEdit_->text());
    device.setAddress(ipEdit_->text());
    device.setPort(portEdit_->text().toInt());

    Value value;
    value.setAddress(valueAddressEdit_->text().toInt());

    emit deviceAdded(device, value);

    close();
}
