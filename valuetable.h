#ifndef VALUETABLE_H
#define VALUETABLE_H

#include <QTableView>
#include <QPointer>

class ModbusClient;
class ValueModel;

class ValueTable : public QTableView
{
    Q_OBJECT
public:
    explicit ValueTable(QWidget *parent = nullptr);

private slots:
    void onRequestFinished(const QPointer<ModbusClient> modbus, int valueAddress, int value);

private:
    ValueModel *model_ = nullptr;
};

#endif // VALUETABLE_H
