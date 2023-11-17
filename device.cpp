#include "device.h"

Device::Device()
{

}

QString Device::id() const
{
    return ip_ + ":" + QString::number(port_);
}

QString Device::name() const
{
    return name_;
}

void Device::setName(const QString &newName)
{
    name_ = newName;
}

QString Device::ip() const
{
    return ip_;
}

void Device::setIp(const QString &newAddress)
{
    ip_ = newAddress;
}

int Device::port() const
{
    return port_;
}

void Device::setPort(int newPort)
{
    port_ = newPort;
}
