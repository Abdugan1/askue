#ifndef DEVICE_H
#define DEVICE_H

#include <QString>

class Device
{
public:
    explicit Device();

    QString name() const;
    void setName(const QString &newName);

    QString address() const;
    void setAddress(const QString &newAddress);

    int port() const;
    void setPort(int newPort);

private:
    QString name_;
    QString address_;
    int port_ = 502;
};

#endif // DEVICE_H
