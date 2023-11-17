#include "modbusmanager.h"
#include "database.h"
#include "value.h"

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

void ModbusManager::addModbus(const Device &device, const Value &toRequest, int requestInterval)
{
    QPointer<ModbusClient> modbus(new ModbusClient(device));

    QPointer<ModbusIntervalRequester> requester(new ModbusIntervalRequester(modbus));
    requester->setRequestIntervalMs(requestInterval);
    requester->setValueAddress(toRequest.address());

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

    Value val;
    val.setAddress(valueAddress);
    val.setValue(value);
    val.setDateTime(QDateTime::currentDateTime());

    emit readFinished(modbus, val);
}
