#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "mygraphcuts.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<MyGraphCuts>("org.qter.MyGraphCutsing", 1, 0, "MyGraphCuts");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
