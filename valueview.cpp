#include "valueview.h"
#include "modbusmanager.h"
#include "valuemodel.h"
#include "value.h"
#include "database.h"

#include <QDateTime>
#include <QHeaderView>

ValueView::ValueView(QWidget *parent)
    : QTableView(parent)
    , model_(new ValueModel(this))
{
    horizontalHeader()->setVisible(true);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    setModel(model_);
    connect(&modbusManager(), &ModbusManager::readFinished, this, &ValueView::onRequestFinished);
}

void ValueView::selectCurrent(const QString &name)
{
    model_->select(name);
}

void ValueView::onRequestFinished(const QPointer<ModbusClient> modbus, const Value &value)
{
//    database().addValue(modbus->name(), value);
//    if (model_->currentName() == modbus->name())
//        model_->addValue(value);
}
