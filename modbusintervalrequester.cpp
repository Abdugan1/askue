#include "modbusintervalrequester.h"

#include <QModbusReply>
#include <QDebug>

ModbusIntervalRequester::ModbusIntervalRequester(QPointer<ModbusClient> modbus)
    : modbus_(modbus)
{
    requestTimer_.setSingleShot(true);
    setRequestIntervalS(1);

    connect(&requestTimer_, &QTimer::timeout, this, &ModbusIntervalRequester::onTimeout);

    connect(modbus, &ModbusClient::readFinished, this, &ModbusIntervalRequester::onReadFinished);
}

void ModbusIntervalRequester::setRequestIntervalMs(int msec)
{
    requestTimer_.setInterval(msec);
}

void ModbusIntervalRequester::setRequestIntervalS(int sec)
{
    requestTimer_.setInterval(sec * 1000);
}

void ModbusIntervalRequester::startRequest()
{
    requestTimer_.start();
}

QString ModbusIntervalRequester::deviceIp() const
{
    return modbus_->ip();
}

void ModbusIntervalRequester::onTimeout()
{
    modbus_->sendReadRequest(QModbusDataUnit::InputRegisters, valueAddress_, 1);
}

void ModbusIntervalRequester::onReadFinished(QModbusReply *reply)
{
    requestTimer_.start();

    if (reply->error() != QModbusDevice::NoError)
        return;

    const QModbusDataUnit unit = reply->result();
    emit readFinished(unit.value(0));
}

const QPointer<ModbusClient> ModbusIntervalRequester::modbus() const
{
    return modbus_;
}

int ModbusIntervalRequester::valueAddress() const
{
    return valueAddress_;
}

void ModbusIntervalRequester::setValueAddress(int newAddress)
{
    valueAddress_ = newAddress;
}
