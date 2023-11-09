#ifndef VALUE_H
#define VALUE_H

#include <QDateTime>

class Value
{
public:
    explicit Value();

    QDateTime dateTime() const;
    void setDateTime(const QDateTime &newDateTime);

    int address() const;
    void setAddress(int newAddress);

    int value() const;
    void setValue(int newValue);

private:
    QDateTime dateTime_;
    int address_ = 0;
    int value_   = 0;
};

#endif // VALUE_H
