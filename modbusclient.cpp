#include "modbusclient.h"

#include <QModbusTcpClient>
#include <QVariant>

ModbusClient::ModbusClient(const QString &name, const QString &address, int port)
    : modbus_(new QModbusTcpClient(this))
    , name_(name)
{
    modbus_->setConnectionParameter(QModbusClient::NetworkAddressParameter, address);
    modbus_->setConnectionParameter(QModbusClient::NetworkPortParameter,    port);

    connect(modbus_, &QModbusClient::stateChanged, this, &ModbusClient::onStateChanged);
}

bool ModbusClient::connectDevice()
{
    return modbus_->connectDevice();
}

void ModbusClient::sendReadRequest(QModbusDataUnit::RegisterType type, int startAddress, int count, int serverAddress)
{
    QModbusDataUnit readUnit(type, startAddress, count);
    auto reply = modbus_->sendReadRequest(readUnit, serverAddress);

    if (!reply)
        return;

    if (!reply->isFinished()) {
        connect(reply, &QModbusReply::finished, this, &ModbusClient::onReadFinished);
    } else {
        delete reply;
    }
}

QString ModbusClient::name() const
{
    return name_;
}

QString ModbusClient::ip() const
{
    return modbus_->connectionParameter(QModbusClient::NetworkAddressParameter).toString();
}

int ModbusClient::port() const
{
    return modbus_->connectionParameter(QModbusClient::NetworkPortParameter).toInt();
}

void ModbusClient::onStateChanged()
{
    switch (modbus_->state()) {
    case QModbusClient::ConnectedState:
        emit connected();
        break;
    case QModbusClient::State::UnconnectedState:
        emit disconnected();
    default:
        break;
    }
}

void ModbusClient::onReadFinished()
{
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    emit readFinished(reply);
}
