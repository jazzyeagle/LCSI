// QtQuick 2.0 includes commented out

#include <QGuiApplication>
#include <QtQml>
#include <QStringList>
#include "jsonmodel.h"



int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);
	JSONModel *model = new JSONModel();
	QStringList sl = model->getCategories();
	fprintf(stderr, "# of items: %d\n", model->rowCount());

	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("myModel", model);
	engine.rootContext()->setContextProperty("catModel", sl);
	engine.load(QUrl("main.qml"));

    return app.exec();
}
