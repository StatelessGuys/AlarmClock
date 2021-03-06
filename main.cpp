#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "alarmmodel.h"
#include "alarmsession.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setOrganizationName("StatelessGuys");
    app.setOrganizationDomain("statelessGuys.com");

    qmlRegisterType<AlarmSession>("Sessions", 1, 0, "AlarmSession");
    qmlRegisterType<AlarmModel>("Models", 1, 0, "AlarmModel");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
