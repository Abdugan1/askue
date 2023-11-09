#include "deviceaddwindow.h"
#include "device.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QIntValidator>

const QRegularExpression ipRegex("^(?:[0-9]{1,3}\\.){3}[0-9]{1,3}$");
const int PortMin = 0;
const int PortMax = 65536;

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
    nameEdit_ = new QLineEdit;
    nameEdit_->setPlaceholderText(tr("Enter name..."));

    nameLabel_ = new QLabel(tr("Device &name"));
    nameLabel_->setBuddy(nameEdit_);

    ipEdit_ = new QLineEdit(DefaultIp);
    ipEdit_->setPlaceholderText(tr("Enter address..."));
    ipEdit_->setValidator(new QRegularExpressionValidator(ipRegex, ipEdit_));

    ipLabel_ = new QLabel("&IP");
    ipLabel_->setBuddy(ipEdit_);

    portEdit_ = new QLineEdit(DefaultPort);
    portEdit_->setPlaceholderText(tr("Enter port..."));
    portEdit_->setValidator(new QIntValidator(PortMin, PortMax, portEdit_));


    portLabel_ = new QLabel(tr("&Port"));
    portLabel_->setBuddy(portEdit_);

    addButton_ = new QPushButton(tr("&Add"));

    auto nameLayout = new QVBoxLayout;
    nameLayout->addWidget(nameLabel_);
    nameLayout->addWidget(nameEdit_);

    auto ipLayout = new QVBoxLayout;
    ipLayout->addWidget(ipLabel_);
    ipLayout->addWidget(ipEdit_);

    auto portLayout = new QVBoxLayout;
    portLayout->addWidget(portLabel_);
    portLayout->addWidget(portEdit_);

    auto addressLayout = new QHBoxLayout;
    addressLayout->addLayout(ipLayout);
    addressLayout->addLayout(portLayout);

    auto editLayout = new QVBoxLayout;
    editLayout->addLayout(nameLayout);
    editLayout->addLayout(addressLayout);

    auto layout = new QVBoxLayout;
    layout->addLayout(editLayout);
    layout->addWidget(addButton_, 0, Qt::AlignRight | Qt::AlignBottom);

    setLayout(layout);
}

void DeviceAddWindow::clear()
{
    nameEdit_->clear();
    ipEdit_->clear();
    portEdit_->setText("");
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

    emit deviceAdded(device);

    close();
}
