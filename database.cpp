#include "database.h"
#include "value.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Database &Database::instance()
{
    static Database self;
    return self;
}

void Database::addValue(const QString &name, const Value &value)
{
    database_.setDatabaseName(name);

    if (!database_.open()) {
        qWarning() << "Cold not open database. Name:" << name << "date:" << value.dateTime()
                   << "value address:" << value.address() << "value:" << value.value();
        return;
    }

    createTables();

    QSqlQuery query(database_);
    query.prepare("INSERT INTO datas(date, value_address, value) VALUES(:date, :value_address, :value)");
    query.bindValue(":date", value.dateTime());
    query.bindValue(":value_address", value.address());
    query.bindValue(":value", value.value());

    if (!query.exec()) {
        qWarning() << "Cold not write data. Name:" << name << "date:" << value.dateTime()
                   << "value address:" << value.address() << "value:" << value.value()
                   << "error:" << query.lastError().text();
    }

    database_.close();
}

Database::Database()
    : QObject()
{
    database_ = QSqlDatabase::addDatabase("QSQLITE");
}

void Database::createTables()
{
    QSqlQuery query("CREATE TABLE IF NOT EXISTS datas ("
                    "   id INTEGER PRIMARY KEY,"
                    "   date DATETIME NOT NULL,"
                    "   value_address INTEGER NOT NULL,"
                    "   value INTEGER NOT NULL"
                    ")");

    if (query.exec()) {
        qCritical() << "Could not create database!" << query.lastError().text();
    }
}
