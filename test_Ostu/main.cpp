#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "myostu.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<MyOstu>("org.qter.MyOstuing", 1, 0, "MyOstu");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
