#ifndef MODBUSCLIENT_H
#define MODBUSCLIENT_H

#include <QObject>
#include <QModbusDataUnit>

class QModbusClient;
class QModbusReply;

class ModbusClient : public QObject
{
    Q_OBJECT
public:
    enum ConnectionType {
        Tcp,
        Rtu
    };

    explicit ModbusClient(const QString &name, const QString &address, int port = 502);

    bool connectDevice();

    void sendReadRequest(QModbusDataUnit::RegisterType type, int startAddress, int count, int serverAddress = 1);

    QString name() const;
    QString ip()   const;
    int     port() const;

signals:
    void connected();
    void disconnected();

    void readFinished(QModbusReply *reply);

private slots:
    void onStateChanged();
    void onReadFinished();

private:
    QString name_;
    QModbusClient *modbus_ = nullptr;
};

#endif // MODBUSCLIENT_H
