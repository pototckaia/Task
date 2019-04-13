#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtCore>
#include <QtCore/qmetatype.h>
#include <QQmlContext>

#include "imageprovider.h"
#include "liveimage.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<LiveImage>("org.qmlplayground.liveimage", 1, 0, "LiveImage");
    ImageProvider provider;
    engine.rootContext()->setContextProperty("LiveImageProvider", &provider);

//    QTimer::singleShot(1000, [&provider](){
//        provider.changeFrame();
//    });

    engine.load(QUrl(QStringLiteral("qrc:/base.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

//    QObject *rootObject = qobject_cast<QObject*>(engine.rootObjects().first());

    return app.exec();
}
