#ifndef MODBUSINTERVALREQUESTER_H
#define MODBUSINTERVALREQUESTER_H

#include <QObject>
#include <QTimer>
#include <QPointer>

#include "modbusclient.h"

class ModbusIntervalRequester : public QObject
{
    Q_OBJECT
public:
    explicit ModbusIntervalRequester(QPointer<ModbusClient> modbus);

    void setRequestIntervalMs(int msec);
    void setRequestIntervalS(int sec);

    void startRequest();

    QString deviceIp() const;

    int valueAddress() const;
    void setValueAddress(int newAddress);

    const QPointer<ModbusClient> modbus() const;

signals:
    void readFinished(int value);

private slots:
    void onTimeout();
    void onReadFinished(QModbusReply *reply);

private:
    QPointer<ModbusClient> modbus_;
    int valueAddress_ = 0;
    QTimer requestTimer_;
};

#endif // MODBUSINTERVALREQUESTER_H
