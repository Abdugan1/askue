#include "value.h"

Value::Value()
{

}

QDateTime Value::dateTime() const
{
    return dateTime_;
}

void Value::setDateTime(const QDateTime &newDateTime)
{
    dateTime_ = newDateTime;
}

int Value::address() const
{
    return address_;
}

void Value::setAddress(int newAddress)
{
    address_ = newAddress;
}

int Value::value() const
{
    return value_;
}

void Value::setValue(int newValue)
{
    value_ = newValue;
}
