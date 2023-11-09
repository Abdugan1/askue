#include "device.h"

Device::Device()
{

}

QString Device::name() const
{
    return name_;
}

void Device::setName(const QString &newName)
{
    name_ = newName;
}

QString Device::address() const
{
    return address_;
}

void Device::setAddress(const QString &newAddress)
{
    address_ = newAddress;
}

int Device::port() const
{
    return port_;
}

void Device::setPort(int newPort)
{
    port_ = newPort;
}
