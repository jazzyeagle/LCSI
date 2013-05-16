#include "sqlmodel.h"


SQLModel::SQLModel(QObject *parent) : QObject(parent) {
    QMessageBox qmb;

    dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("csidb");
    if(dbase.open()) {
        model = new QSqlTableModel(parent, dbase);
        if(dbase.tables(QSql::Tables).isEmpty()) createTable();
        model->setTable("All_Software");
        model->select();

        model->setHeaderData(0, Qt::Horizontal, "Status");
        model->setHeaderData(1, Qt::Horizontal, "Title");
        model->setHeaderData(2, Qt::Horizontal, "Version");
        model->setHeaderData(3, Qt::Horizontal, "Category");
        model->setHeaderData(4, Qt::Horizontal, "Author");
        model->setHeaderData(5, Qt::Horizontal, "Description");
        model->setHeaderData(6, Qt::Horizontal, "Dependencies");
        model->setHeaderData(7, Qt::Horizontal, "Release Date");
        model->setHeaderData(8, Qt::Horizontal, "Source Code Link");
        model->setHeaderData(9, Qt::Horizontal, "Flattr");
        model->setHeaderData(10, Qt::Horizontal, "PayPal");
    } else {
        qmb.setText(dbase.lastError().text());
        qmb.exec();
    }
}

void SQLModel::createTable() {
    QSqlRecord record, record2;

    dbase.exec("CREATE TABLE All_Software (Status Integer, Title Text, CurrVersion Text, Category Text, Author Text, Description Text, Dependencies Text, VerRelease Real, SrcCode Text, FlattrID Text, PayPal Text);");
    dbase.exec("CREATE TABLE Installed (Title Integer, InstVersion Text, Dependent Text, FOREIGN KEY (Title) REFERENCES All_Software(Title)");

    model->setTable("All_Software");
    record.append(QSqlField(tr("Status"), QVariant::Int));
    record.append(QSqlField(tr("Category"), QVariant::String));
    record.append(QSqlField(tr("Title"), QVariant::String));
    record.append(QSqlField(tr("CurrVersion"), QVariant::String));
    record.append(QSqlField(tr("Author"), QVariant::String));
    record.append(QSqlField(tr("Description"), QVariant::String));
    record.append(QSqlField(tr("Dependencies"), QVariant::String));
    record.append(QSqlField(tr("SrcCode"), QVariant::String));
    record.append(QSqlField(tr("FlattrID"), QVariant::String));
    record.append(QSqlField(tr("PayPal"), QVariant::String));

    record.setValue("Status", 0);
    record.setValue("Category", "Audio Systems");
    record.setValue("Title", "Cadence");
    record.setValue("CurrVersion", "0.1.2");
    record.setValue("Author", "falktx");
    record.setValue("Description", "Does Cool Audio System Stuff");
    record.setValue("Dependencies", "qt5, alsa, jack");
    record.setValue("SrcCode", "http://sourceforge.net/projects/kxstudio/files/Releases/cadence/Cadence-0.8-beta2-linux64.tar.xz/download");
    record.setValue("FlattrID", "1098067");
    record.setValue("PayPal", "N/A");
    model->insertRecord(0, record);

    record.setValue("Status", 0);
    record.setValue("Category", "Synthesizers");
    record.setValue("Title", "QSynth");
    record.setValue("CurrVersion", "0.3.7");
    record.setValue("Author", "rncbc");
    record.setValue("Description", "Front-End to FluidSynth");
    record.setValue("Dependencies", "qt5, jack");
    record.setValue("SrcCode", "http://downloads.sourceforge.net/qsynth/qsynth-0.3.7.tar.gz");
    record.setValue("FlattrID", "59775");
    record.setValue("PayPal", "N/A");
    model->insertRecord(1, record);
    model->submitAll();
}

QSqlTableModel* SQLModel::getModel() { return model; }

/*      Table 1 (Maintained remotely, synced when program opened / user requested
 *  Primary Key
 *  Status  (Indicator identifying installed, installed but not up to date, not installed, other?) - Identified based on results from Table 2
 *  Category
 *  Software Title
 *  Current Version
 *  Version Release Date
 *  Author
 *  Description
 *  Dependency(ies)
 *  Link to Source Code
 *  Flattr Button
 *  PayPal Donate Button
 */


/*      Table 2
 *  Software Title (foreign key?)
 *  Installed Version
 *  Other software installed, if any, that is dependent upon this software
 */
