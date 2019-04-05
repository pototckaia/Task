#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtCore>
#include <QtCore/qmetatype.h>
#include <QQmlContext>

#include "controller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<DataObject>("org.qmlplayground.dataObject", 0, 1, "DataObject");
    engine.load(QUrl(QStringLiteral("qrc:/base.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QObject *rootObject = qobject_cast<QObject*>(engine.rootObjects().first());

    return app.exec();
}
