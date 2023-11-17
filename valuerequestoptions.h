#ifndef VALUEREQUESTOPTIONS_H
#define VALUEREQUESTOPTIONS_H

#include <QString>

class ValueRequestOptions
{
public:
    explicit ValueRequestOptions();

    QString deviceId() const;
    void setDeviceId(const QString &newDeviceId);

    QString name() const;
    void setName(const QString &newName);

    int address() const;
    void setAddress(int newAddress);

    int requestIntervalMs() const;
    void setRequestIntervalMs(int newRequestIntervalMs);

private:
    QString deviceId_;
    QString name_;
    int address_ = 0;
    int requestIntervalMs_ = 0;
};

#endif // VALUEREQUESTOPTIONS_H
