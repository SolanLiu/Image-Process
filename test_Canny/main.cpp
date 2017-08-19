#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "mycanny.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<MyCanny>("org.qter.MyCannying", 1, 0, "MyCanny");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
