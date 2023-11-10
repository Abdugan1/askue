#include "valuetable.h"
#include "modbusmanager.h"
#include "valuemodel.h"
#include "value.h"
#include "database.h"

#include <QDateTime>
#include <QHeaderView>

ValueTable::ValueTable(QWidget *parent)
    : QTableView(parent)
    , model_(new ValueModel(this))
{
    horizontalHeader()->setVisible(true);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    setModel(model_);
    connect(&modbusManager(), &ModbusManager::readFinished, this, &ValueTable::onRequestFinished);
}

void ValueTable::onRequestFinished(const QPointer<ModbusClient> modbus, int valueAddress, int value)
{
    Value newVal;
    newVal.setDateTime(QDateTime::currentDateTime());
    newVal.setAddress(valueAddress);
    newVal.setValue(value);

    database().addValue(modbus->name(), newVal);
    model_->addValue(newVal);
}
