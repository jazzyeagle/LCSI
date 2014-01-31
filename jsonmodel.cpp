#include "jsonmodel.h"
#include <QMessageBox>

JSONModel::JSONModel(QObject *parent) : QAbstractTableModel(parent) {
	QMessageBox qmb;
	QJsonObject projectlist;

	keys << "program" << "category" << "description" << "developer" << "website" << "e-mail" << "screenshot" << "icon" << "flattr" << "paypal" << "apt-get" << "yum" << "pacaur" << "hidden";

	file.setFileName("local.json");
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qmb.setText(QString("Error opening %1: %2: %3").arg(file.fileName()).arg(file.error()).arg(file.errorString()));
		qmb.exec();
	}

	if(file.isOpen() && file.isReadable()) {
		QByteArray bytearray = file.readAll();
		doc = QJsonDocument::fromJson(bytearray);

		if(doc.isNull()) { qmb.setText("doc is NULL"); qmb.exec(); }
		else if(doc.isEmpty()) { qmb.setText("doc is empty"); qmb.exec(); }
		else {
			projectlist = doc.object();
			project = projectlist.value("projects").toArray();
		}

	} else {
		qmb.setText(QString("Unreadable file: %1").arg(file.fileName())); qmb.exec();
	}
	file.close();
}


int JSONModel::rowCount(const QModelIndex &parent) const {
	Q_UNUSED(parent)
	return project.count();
}


int JSONModel::columnCount(const QModelIndex &parent) const {
	Q_UNUSED(parent)
	QJsonObject obj = project.at(0).toObject();
	return obj.count();
}


QVariant JSONModel::data(const QModelIndex &index, int role) const {
	QVariant result;

	QJsonObject obj = project.at(index.row()).toObject();
	if((role==Qt::DisplayRole or role==Qt::EditRole) && index.column() < 13) {
		result = obj.value(keys.at(index.column())).toString();
	} else if((role==Qt::CheckStateRole || Qt::EditRole) && index.column()==13)
		result = obj.value(keys.at(index.column())).toBool();
	else
		result = QVariant();

	return result;
}


QVariant JSONModel::headerData(int section, Qt::Orientation orientation, int role) const {
	QMessageBox qmb;
	QString result;

	if(role !=Qt::DisplayRole)
		return QVariant();

	if(orientation==Qt::Horizontal) {
		if(section < 13) {
			QJsonObject obj = project.at(section).toObject();
			return keys.at(section);
		}
		else
			return QVariant();
	} else {
		return section+1;
	}
}

Qt::ItemFlags JSONModel::flags(const QModelIndex &index) const {
	if(!index.isValid())
		return Qt::ItemIsEnabled;

	if(index.column()==13) { // If we're dealing with the Boolean value
		return QAbstractTableModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsUserCheckable;
	}
	else {
		return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
	}
}


bool JSONModel::setData(const QModelIndex &index, const QVariant &value, int role) {
	QJsonObject obj = project.at(index.row()).toObject();

	if(index.isValid() && role==Qt::EditRole && index.column() < 13) {
		obj.value(keys.at(index.column())) = value.toString();
		emit dataChanged(index, index);
		return true;
	} else if(index.isValid() && index.column()==13 && (role==Qt::CheckStateRole || Qt::EditRole)) {
		obj.value("hidden") = value.toBool();
		emit dataChanged(index, index);
		return true;
	} else {
		return false;
	}
}
