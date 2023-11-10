#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QSqlDatabase>

class Value;

class Database : public QObject
{
    Q_OBJECT
public:
    static Database &instance();

public slots:
    void addValue(const QString &name, const Value &value);

private:
    explicit Database();

    void createTables();

private:
    QSqlDatabase database_;
};

inline Database &database()
{
    return Database::instance();
}

#endif // DATABASE_H
