#ifndef DEVICE_H
#define DEVICE_H

#include <QString>

class Device
{
public:
    explicit Device();

    QString id() const;

    QString name() const;
    void setName(const QString &newName);

    QString ip() const;
    void setIp(const QString &newAddress);

    int port() const;
    void setPort(int newPort);

private:
    QString name_;
    QString ip_;
    int port_ = 502;
};

#endif // DEVICE_H
