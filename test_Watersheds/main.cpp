#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "mywatersheds.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<MyWatersheds>("org.qter.MyWatershedsing", 1, 0, "MyWatersheds");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
