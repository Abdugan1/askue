#include "deviceaddwindow.h"
#include "device.h"
#include "buddylineedit.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QIntValidator>

const QRegularExpression ipRegex("^(?:[0-9]{1,3}\\.){3}[0-9]{1,3}$");
const QRegularExpression nameRegex("\\w+");
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
    nameEdit_ = new BuddyLineEdit(tr("Device &name"), tr("Enter name..."));
    nameEdit_->setText("local");
    nameEdit_->setValidator(new QRegularExpressionValidator(nameRegex, nameEdit_));

    ipEdit_ = new BuddyLineEdit(tr("&IP"), tr("Example 127.0.0.1"));
    ipEdit_->setText("127.0.0.1");
    ipEdit_->setValidator(new QRegularExpressionValidator(ipRegex, ipEdit_));

    portEdit_ = new BuddyLineEdit(tr("&Port"), tr("Example 50200"));
    portEdit_->setText("50200");
    portEdit_->setValidator(new QIntValidator(PortMin, PortMax, portEdit_));

    addButton_ = new QPushButton(tr("&Add"));

    auto addressLayout = new QHBoxLayout;
    addressLayout->addWidget(ipEdit_);
    addressLayout->addWidget(portEdit_);

    auto editLayout = new QVBoxLayout;
    editLayout->addWidget(nameEdit_);
    editLayout->addLayout(addressLayout);

    auto layout = new QVBoxLayout;
    layout->addLayout(editLayout);
    layout->addWidget(addButton_, 0, Qt::AlignRight | Qt::AlignBottom);

    setLayout(layout);
}

void DeviceAddWindow::clear()
{
//    nameEdit_->clear();
//    ipEdit_->clear();
//    portEdit_->clear();
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
    device.setIp(ipEdit_->text());
    device.setPort(portEdit_->text().toInt());

    emit deviceAdded(device);

    close();
}
