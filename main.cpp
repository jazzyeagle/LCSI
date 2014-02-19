// QtQuick 2.0 includes commented out

#include <QGuiApplication>
#include <QtQml>
#include <QStringList>
#include "jsonmodel.h"



int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);
	JSONModel *model = new JSONModel();
	QStringList cl = model->getCategories();
	QStringList tl = model->getTypes();
	fprintf(stderr, "# of items: %d\n", model->rowCount());

	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("myModel", model);
	engine.rootContext()->setContextProperty("catModel", cl);
	engine.rootContext()->setContextProperty("typeModel", tl);
	engine.load(QUrl("main.qml"));

    return app.exec();
}
