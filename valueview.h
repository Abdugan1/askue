#ifndef VALUEVIEW_H
#define VALUEVIEW_H

#include <QTableView>
#include <QPointer>

class ModbusClient;
class ValueModel;

class Value;

class ValueView : public QTableView
{
    Q_OBJECT
public:
    explicit ValueView(QWidget *parent = nullptr);

public slots:
    void selectCurrent(const QString &name);

private slots:
    void onRequestFinished(const QPointer<ModbusClient> modbus, const Value &value);

private:
    ValueModel *model_ = nullptr;
};

#endif // VALUEVIEW_H
