#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlQuery>

class Device;
class Value;

class SqlQuery : public QSqlQuery
{
public:
    explicit SqlQuery(const QString &query = "");
};

class Database : public QObject
{
    Q_OBJECT
public:
    static Database &instance();

    QList<Value> values(const QString &name);

public slots:
    void addDevice(const Device &device);
    void addValue(const Device &device, const Value &value);

private:
    explicit Database();
    void createDatabase(const QString &name);

    void createTables();

private:
    QSqlDatabase database_;

    friend class SqlQuery;
};

inline Database &database()
{
    return Database::instance();
}

#endif // DATABASE_H
