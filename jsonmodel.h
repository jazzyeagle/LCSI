#ifndef JSONMODEL_H
#define JSONMODEL_H

#include <QFile>
#include <QAbstractTableModel>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

enum repoEnum {
	program = Qt::UserRole,
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

class JSONModel : public QAbstractTableModel {
		Q_OBJECT

	public:
		explicit JSONModel(QObject *parent = 0);
		~JSONModel();
		int rowCount(const QModelIndex &parent = QModelIndex()) const;
		int columnCount(const QModelIndex &parent = QModelIndex()) const;
		QVariant data(const QModelIndex &index, int role) const;
		QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
		Qt::ItemFlags flags(const QModelIndex &index) const;
		bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
		QStringList getCategories();
		QHash<int, QByteArray> roleNames() const;

	signals:

	public slots:

	private:
		void loadHashes();
		
		QJsonDocument doc;
		QJsonArray categories, project;
		QFile file;
		QHash<int, QString> keys, repokeys;
};

#endif // JSONMODEL_H
