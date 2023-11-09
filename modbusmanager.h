#ifndef MODBUSMANAGER_H
#define MODBUSMANAGER_H

#include <QObject>
#include <QVector>
#include <QPointer>
#include <QTimer>

#include "modbusclient.h"
#include "modbusintervalrequester.h"

class ModbusManager : public QObject
{
    Q_OBJECT
public:
    static ModbusManager &instance();

    void addModbus(const QString &name, const QString &address, int port = 502, int requestInterval = 2 * 1000);

signals:
    void readFinished(const QPointer<ModbusClient> modbus, int valueAddress, int value);

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
