#ifndef JSONMODEL_H
#define JSONMODEL_H

#include <QDebug>
#include <QFile>
#include <QAbstractTableModel>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

enum repoEnum {
	package = Qt::UserRole,
	category,
	description,
	developer,
	website,
	email,
	screenshot,
	icon,
	flattr,
	paypal,
	aptget,
	yum,
	pacaur,
	hidden
};

struct JSONFilteredModel {
	bool isFiltered;
	QString filterType;
	QString filterValue;
	QJsonArray model;
};

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
		void sort(QString sortType);
		QStringList getCategories();
		QStringList getTypes();
		QHash<int, QByteArray> roleNames() const;

	signals:

	public slots:
		void filterChanged(QString type, QString value);

	private:
		void loadHashes();
		
		QJsonDocument doc;
		QJsonArray categories, project;
		QFile file;
		QHash<int, QString> keys, repokeys;
		JSONFilteredModel model;
};

#endif // JSONMODEL_H
