#include "jsonmodel.h"
#include <QMessageBox>

JSONModel::JSONModel(QObject *parent) : QAbstractTableModel(parent) {
	QMessageBox qmb;
	QJsonObject projectlist;

	file.setFileName("local.json");
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qmb.setText(QString("Error opening %1: %2: %3").arg(file.fileName()).arg(file.error()).arg(file.errorString()));
		qmb.exec();
	}

	if(file.isOpen() && file.isReadable()) {
		QByteArray bytearray = file.readAll();
		//qmb.setText(bytearray); qmb.exec();
		doc = QJsonDocument::fromJson(bytearray);

		if(doc.isNull()) { qmb.setText("doc is NULL"); qmb.exec(); }
		else if(doc.isEmpty()) { qmb.setText("doc is empty"); qmb.exec(); }
		else {
			projectlist = doc.object();
			//qmb.setText(QString("Total number of Object entries: %1").arg(projectlist.count()));
			//qmb.exec();
			project = projectlist.value("projects").toArray();

/*			qmb.setText(QString("Total number of Array entries: %1").arg(project.count()));
			qmb.exec(); */

/*			for(int i=0; i<project.count(); i++) {
				QJsonValue temp2 = project.at(i);
				if(temp2.isObject()) {
					QJsonObject temp = temp2.toObject();
					for(int j=0; j<temp.count(); j++) {
						qmb.setText(QString("Key: %1, Value: %2, j = %3").arg(temp.keys().at(j)).arg(temp.value(temp.keys().at(j)).toString()).arg(j));
						qmb.exec();
					}
					//qmb.setText(QString("%1 entries in Object #%2").arg(temp.count()).arg(i));
					//qmb.setText(QString("%1 %2 %3").arg(temp.valueAt(0).toString()).arg(temp.valueAt(3).toString()).arg(temp.valueAt(4).toString()));
					//qmb.exec();
				} else { qmb.setText("Array Value is not an object"); qmb.exec(); }
			} */
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
//	QMessageBox qmb; qmb.setText(QString("# Columns: %1").arg(obj.count())); qmb.exec();
	return obj.count();
}


QVariant JSONModel::data(const QModelIndex &index, int role) const {
	QVariant result;

	QJsonObject obj = project.at(index.row()).toObject();
	if((role==Qt::DisplayRole or role==Qt::EditRole) && index.column() < 13) {
		switch(index.column()) {
			case 0:
				result = obj.value("program").toString();
				break;
			case 1:
				result = obj.value("category").toString();
				break;
			case 2:
				result = obj.value("description").toString();
				break;
			case 3:
				result = obj.value("developer").toString();
				break;
			case 4:
				result = obj.value("website").toString();
				break;
			case 5:
				result = obj.value("e-mail").toString();
				break;
			case 6:
				result = obj.value("screenshot").toString();
				break;
			case 7:
				result = obj.value("icon").toString();
				break;
			case 8:
				result = obj.value("flattr").toString();
				break;
			case 9:
				result = obj.value("paypal").toString();
				break;
			case 10:
				result = obj.value("apt-get").toString();
				break;
			case 11:
				result = obj.value("yum").toString();
				break;
			case 12:
				result = obj.value("pacaur").toString();
				break;
			default:
				result = QVariant();
				break;
		}
	} else if((role==Qt::CheckStateRole || Qt::EditRole) && index.column()==13)
		result = obj.value("hidden").toBool();
	else
		result = QVariant();

	//QMessageBox qmb; qmb.setText(result.toString()); qmb.exec();
	return result;
	//return obj.keys().at(.value(index.model()->headerData(index.column(), Qt::Horizontal).toString());
}


QVariant JSONModel::headerData(int section, Qt::Orientation orientation, int role) const {
	QMessageBox qmb;
	QString result;

	if(role !=Qt::DisplayRole)
		return QVariant();

	if(orientation==Qt::Horizontal) {
		QJsonObject obj = project.at(section).toObject();
		switch(section) {
			case 0:
				result = "Program";
				break;
			case 1:
				result = "Category";
				break;
			case 2:
				result = "Description";
				break;
			case 3:
				result = "Developer";
				break;
			case 4:
				result = "Website";
				break;
			case 5:
				result = "E-Mail";
				break;
			case 6:
				result = "Screenshot";
				break;
			case 7:
				result = "Icon";
				break;
			case 8:
				result = "Flattr";
				break;
			case 9:
				result = "PayPal";
				break;
			case 10:
				result = "Apt-Get";
				break;
			case 11:
				result = "Yum";
				break;
			case 12:
				result = "PacAUR";
				break;
			case 13:
				result = "Hidden";
				break;
			default:
				result = QString();
				break;
		}

		return result;
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

	if(index.isValid() && role==Qt::EditRole) {
		switch(index.column()) {
			case 0:
				obj.value("program") = value.toString();
				break;
			case 1:
				obj.value("category") = value.toString();
				break;
			case 2:
				obj.value("description") = value.toString();
				break;
			case 3:
				obj.value("developer") = value.toString();
				break;
			case 4:
				obj.value("website") = value.toString();
				break;
			case 5:
				obj.value("e-mail") = value.toString();
				break;
			case 6:
				obj.value("screenshot") = value.toString();
				break;
			case 7:
				obj.value("icon") = value.toString();
				break;
			case 8:
				obj.value("flattr") = value.toString();
				break;
			case 9:
				obj.value("paypal") = value.toString();
				break;
			case 10:
				obj.value("apt-get") = value.toString();
				break;
			case 11:
				obj.value("yum") = value.toString();
				break;
			case 12:
				obj.value("pacaur") = value.toString();
				break;
			default:
				break;
		}
		emit dataChanged(index, index);
		return true;
	} else if(index.isValid() && index.column()==13 && role==Qt::CheckStateRole) {
		obj.value("hidden") = value.toBool();
		emit dataChanged(index, index);
		return true;
	} else {
		return false;
	}
}
