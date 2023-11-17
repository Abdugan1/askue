#ifndef MODBUSMANAGER_H
#define MODBUSMANAGER_H

#include <QObject>
#include <QVector>
#include <QPointer>
#include <QTimer>

#include "modbusclient.h"
#include "modbusintervalrequester.h"

class Device;
class Value;

class ModbusManager : public QObject
{
    Q_OBJECT
public:
    static ModbusManager &instance();

    void addModbus(const Device &device, const Value &toRequest, int requestInterval = 2 * 1000);

signals:
    void readFinished(const QPointer<ModbusClient> modbus, const Value &value);

private slots:
    void onRequestResult(int value);

private:
    explicit ModbusManager();

private:
    QVector<QPointer<ModbusIntervalRequester>> modbusIntervalRequesters_;
};

inline ModbusManager &modbusManager()
{
    return ModbusManager::instance();
}

#endif // MODBUSMANAGER_H
