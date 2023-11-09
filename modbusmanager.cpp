#include "modbusmanager.h"

#include <QTimer>
#include <QDebug>

ModbusManager::ModbusManager()
{

}

ModbusManager &ModbusManager::instance()
{
    static ModbusManager self;
    return self;
}

void ModbusManager::addModbus(const QString &name, const QString &address, int port, int requestInterval)
{
    QPointer<ModbusClient> modbus(new ModbusClient(name, address, port));

    QPointer<ModbusIntervalRequester> requester(new ModbusIntervalRequester(modbus));
    requester->setRequestIntervalMs(requestInterval);
    requester->setValueAddress(13312);

    modbusIntervalRequesters_.push_back(requester);

    QObject::connect(requester, &ModbusIntervalRequester::readFinished, this, &ModbusManager::onRequestResult);

    QObject::connect(modbus, &ModbusClient::connected, [requester]() {
        qDebug() << "Connected!";
        requester->startRequest();
    });

    QObject::connect(modbus, &ModbusClient::disconnected, [requester]() {
        qDebug() << "Disconnected!";
    });

    modbus->connectDevice();
}

void ModbusManager::onRequestResult(int value)
{
    const auto requester = qobject_cast<ModbusIntervalRequester *>(sender());
    const auto modbus = requester->modbus();

    const QString deviceIp     = modbus->ip();
    const int     valueAddress = requester->valueAddress();

    qDebug() << deviceIp << valueAddress << value;

    emit readFinished(modbus, valueAddress, value);
}
