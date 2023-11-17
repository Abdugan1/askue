#include "database.h"
#include "device.h"
#include "value.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

SqlQuery::SqlQuery(const QString &query)
    : QSqlQuery(query, database().database_)
{

}

Database &Database::instance()
{
    static Database self;
    return self;
}

QList<Value> Database::values(const QString &name)
{
    QSqlQuery query;
    if (!query.exec("SELECT * FROM datas")) {
        qWarning() << "Could not select datas." << query.lastError().text();
        return {};
    }

    QList<Value> values;
    while (query.next()) {
        Value value;
        value.setDateTime(query.value("date").toDateTime());
        value.setAddress(query.value("value_address").toInt());
        value.setValue(query.value("value").toInt());

        values.append(value);
    }

    return values;
}

void Database::addDevice(const Device &device)
{
    QSqlQuery query;

    query.prepare("INSERT INTO devices(id, name) VALUES(:id, :name)");
    query.bindValue(":id", device.id());
    query.bindValue(":name", device.name());

    if (!query.exec()) {
        qWarning() << "Couldn't add device. device_id:" << device.id() << "name:" << device.name() << query.lastError().text();
    }
}

void Database::addValue(const Device &device, const Value &value)
{
    QSqlQuery query;

    query.prepare("INSERT INTO consumption(device_id, timestamp, value) VALUES(:device_id, :timestamp, :value)");
    query.bindValue(":device_id", device.id());
    query.bindValue(":timestamp", value.dateTime());
    query.bindValue(":value", value.value());

    if (!query.exec()) {
        qWarning() << "Couldn't data value. device_id:" << device.id() << "date:" << value.dateTime()
                   << "value address:" << value.address() << "value:" << value.value()
                   << "error:" << query.lastError().text();
    }
}

Database::Database()
    : QObject()
{
    database_ = QSqlDatabase::addDatabase("QSQLITE");
    createDatabase("askue");
}

void Database::createDatabase(const QString &name)
{
    database_.setDatabaseName(name);

    if (!database_.open()) {
        qWarning() << "Could not open database." << database_.lastError().text();
        return;
    }

    createTables();
}

void Database::createTables()
{
    QSqlQuery enableForeignKeys{"PRAGMA foreign_keys = ON;"};

    if (!enableForeignKeys.exec()) {
        qCritical() << "Couldn't enable keys!" << enableForeignKeys.lastError().text();
        return;
    }

    const QList<QString> queries{
        "CREATE TABLE IF NOT EXISTS devices ("
        "   id TEXT PRIMARY KEY,"
        "   name TEXT NOT NULL"
        ");",
        "CREATE TABLE IF NOT EXISTS consumption ("
        "   id INTEGER PRIMARY KEY,"
        "   device_id TEXT NOT NULL,"
        "   timestamp DATETIME NOT NULL,"
        "   value INTEGER NOT NULL,"
        "FOREIGN KEY (device_id) REFERENCES devices(id) ON DELETE CASCADE ON UPDATE CASCADE"
        ");"
    };

    for (const auto& queryStr : queries) {
        QSqlQuery query(queryStr);
        if (!query.exec()) {
            qCritical() << "Could not create database!" << query.lastError().text();
            return;
        }
    }
}
