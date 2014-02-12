#include "jsonmodel.h"

JSONModel::JSONModel(QObject *parent) : QAbstractTableModel(parent) {
	QJsonObject projectlist;
	fprintf(stderr, "JSONMOdel instantiated\n");

	file.setFileName("local.json");
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		fprintf(stderr, "Error opening %s: %d: %s\n", file.fileName().toLatin1().data(), file.error(), file.errorString().toLatin1().data());
	}

	if(file.isOpen() && file.isReadable()) {
		QByteArray bytearray = file.readAll();
		doc = QJsonDocument::fromJson(bytearray);

		if(doc.isNull()) { fprintf(stderr, "doc is NULL"); }
		else if(doc.isEmpty()) { fprintf(stderr, "doc is empty"); }
		else {
			loadHashes();
			projectlist = doc.object();
			
			if(projectlist.value("filetype").toString() == "Repository") {
				fprintf(stderr, "Repository loading...\n");
				keys = repokeys; // Eventually, more hashes will be available based on the file being opened.
				categories = projectlist.value("categories").toArray();
				project = projectlist.value("projects").toArray();
			}
		}

	} else {
		fprintf(stderr, "Unreadable file: %s\n", file.fileName().toLatin1().data());
	}
	fprintf(stderr, "# of JSONModel Items: %d\n", this->rowCount());
	file.close();
}

JSONModel::~JSONModel() {
	QJsonObject projectlist;
	projectlist.insert("projects", QJsonValue(project));
	doc.setObject(projectlist);
	file.remove();
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	if(file.isOpen() && file.isWritable())
		file.write(doc.toJson());
	else { fprintf(stderr, "Unable to save local.json"); }
	file.close();
}

void JSONModel::loadHashes() {
	repokeys[program] = "Program";
	repokeys[category] = "Category";
	repokeys[description] = "Description";
	repokeys[developer] = "Developer";
	repokeys[website] = "Website";
	repokeys[email] = "E-Mail";
	repokeys[screenshot] = "Screenshot";
	repokeys[icon] = "Icon";
	repokeys[flattr] = "Flattr";
	repokeys[paypal] = "Paypal";
	repokeys[aptget] = "apt-get";
	repokeys[yum] = "yum";
	repokeys[pacaur] = "pacaur";
	repokeys[hidden] = "hidden";
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

QHash<int, QByteArray> JSONModel::roleNames() const {
	QHash<int, QByteArray> roles;

	roles[program] = "program";
	roles[category] = "category";
	roles[description] = "description";
	roles[developer] = "developer";
	roles[website] = "website";
	roles[email] = "email";
	roles[screenshot] = "screenshot";
	roles[icon] = "icon";
	roles[flattr] = "flattr";
	roles[paypal] = "paypal";
	roles[aptget] = "aptget";
	roles[yum] = "yum";
	roles[pacaur] = "pacaur";
	roles[hidden] = "hidden";

	roles[Qt::DisplayRole] = "display";
	roles[Qt::DecorationRole] = "decoration";
	roles[Qt::EditRole] = "edit";
	roles[Qt::ToolTipRole] = "tooltip";
	roles[Qt::WhatsThisRole] = "whatsthis";
	roles[Qt::SizeHintRole] = "sizehint";
	roles[Qt::CheckStateRole] = "checkstate";

	return roles;
}

QVariant JSONModel::data(const QModelIndex &index, int role) const {
	QVariant result;

	fprintf(stderr, "Role = %d\n", role);
	QJsonObject obj = project.at(index.row()).toObject();
	if(role>=Qt::UserRole && index.column() < 13) {
		result = obj.value(keys[role]).toString();
	} else if((role>=Qt::UserRole) && index.column()==13) {
		if(obj.value(keys[role]).toBool())
			result = Qt::Checked;
		else
			result = Qt::Unchecked;
	}
	else
		result = QVariant();

	return result;
}


QVariant JSONModel::headerData(int section, Qt::Orientation orientation, int role) const {
	QString result;

	if(role < Qt::UserRole)
		return QVariant();

	if(orientation==Qt::Horizontal) {
		if(section < 13) {
			QJsonObject obj = project.at(section).toObject();
			return keys[role];
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
	QJsonValue temp;
	QJsonObject obj = project.at(index.row()).toObject();

	if(index.isValid() && role>=Qt::UserRole && index.column() < 13) {
		obj.insert(keys[role], QJsonValue::fromVariant(value));
		project.replace(index.row(), QJsonValue(obj));
		emit dataChanged(index, index);
		return true;
	} else if(index.isValid() && role>=Qt::UserRole && index.column() == 13) {
		obj.insert(keys[role], QJsonValue::fromVariant(value.toBool()));
		project.replace(index.row(), QJsonValue(obj));
		emit dataChanged(index, index);
		return true;
	} else {
		return false;
	}
}

QStringList JSONModel::getCategories() {
	QStringList cl;
	QVariantList vl;
	
	vl = categories.toVariantList();
	fprintf(stderr, "# of categories: %d\n", vl.count());
	cl << "All";
	for(int i=0; i < vl.count(); i++) {
		cl << vl.at(i).toString();
		fprintf(stderr, "Category #%d: %s\n", i, cl.at(i).toLatin1().data());
	}
		
	return cl;
}
