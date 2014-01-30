#ifndef JSONMODEL_H
#define JSONMODEL_H

#include <QFile>
#include <QAbstractTableModel>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

class JSONModel : public QAbstractTableModel {
		Q_OBJECT
	public:
		explicit JSONModel(QObject *parent = 0);
		int rowCount(const QModelIndex &parent = QModelIndex()) const;
		int columnCount(const QModelIndex &parent = QModelIndex()) const;
		QVariant data(const QModelIndex &index, int role) const;
		QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
		Qt::ItemFlags flags(const QModelIndex &index) const;
		bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
		
	signals:
		
	public slots:

	private:
		QJsonDocument doc;
		QJsonArray project;
		QFile file;
		
};

#endif // JSONMODEL_H
