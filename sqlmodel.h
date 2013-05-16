#ifndef SQLMODEL_H
#define SQLMODEL_H

//#include <QSql>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlField>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

class SQLModel : public QObject {
    Q_OBJECT

    public:
        explicit SQLModel(QObject *parent = 0);
        QSqlTableModel* getModel();

    signals:

    public slots:

    private:
        QSqlDatabase dbase;
        QSqlTableModel* model;
        void createTable();
};

#endif // SQLMODEL_H
