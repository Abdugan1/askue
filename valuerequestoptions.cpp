#include "valuerequestoptions.h"

ValueRequestOptions::ValueRequestOptions()
{

}

QString ValueRequestOptions::name() const
{
    return name_;
}

void ValueRequestOptions::setName(const QString &newName)
{
    name_ = newName;
}

int ValueRequestOptions::address() const
{
    return address_;
}

void ValueRequestOptions::setAddress(int newAddress)
{
    address_ = newAddress;
}

int ValueRequestOptions::requestIntervalMs() const
{
    return requestIntervalMs_;
}

void ValueRequestOptions::setRequestIntervalMs(int newRequestIntervalMs)
{
    requestIntervalMs_ = newRequestIntervalMs;
}

QString ValueRequestOptions::deviceId() const
{
    return deviceId_;
}

void ValueRequestOptions::setDeviceId(const QString &newDeviceId)
{
    deviceId_ = newDeviceId;
}
