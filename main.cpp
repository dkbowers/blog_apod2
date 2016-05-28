#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <QQmlComponent>
#include <QQuickWindow>
#include <QSurfaceFormat>
#include <QSettings>
#include <QScreen>
#include <QDebug>
#include <QQmlContext>

#include "APODDownloader.h"

int main(int argc, char ** argv)
{
    QCoreApplication::setOrganizationName("David K. Bowers");
    QCoreApplication::setOrganizationDomain("davidkbowers.com");
    QCoreApplication::setApplicationName("APOD BLOG 2");

    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QSettings settings;
    qputenv("QT_LABS_CONTROLS_STYLE", settings.value("style").toByteArray());

    // Register our component type with QML.
    qmlRegisterType<APODDownloader>("com.davidkbowers.APOD_BLOG2", 1, 0, "APODDownloader");

    int rc = 0;

    QQmlApplicationEngine engine;

    QObject::connect(&engine, SIGNAL(quit()), QCoreApplication::instance(), SLOT(quit()));

    const int toolbarHeight = 40;
    const int margin = 5;
    const int textHeight = 20;
    const int pictureHeight = 240;
    const int pictureWidth = 320;

    QRect availGeometry(app.screens().at(0)->availableGeometry());
    QRect contentArea(margin, margin, availGeometry.width() - (margin*2), availGeometry.height() - (toolbarHeight*2) - (margin*2));
    QRect dateArea(contentArea.x(), contentArea.y(), contentArea.width(), textHeight);
    QRect titleArea(contentArea.x(), (dateArea.bottom() + margin), contentArea.width(), textHeight);
    QRect pictureArea((contentArea.width() - pictureWidth)/2, (titleArea.bottom() + margin), pictureWidth, pictureHeight);
    QRect explanationArea(contentArea.x(), (pictureArea.bottom() + margin), contentArea.width(), contentArea.height() - (pictureArea.bottom() + margin + margin));

    engine.rootContext()->setContextProperty("dateArea", dateArea);
    engine.rootContext()->setContextProperty("titleArea", titleArea);
    engine.rootContext()->setContextProperty("pictureArea", pictureArea);
    engine.rootContext()->setContextProperty("explanationArea", explanationArea);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    rc = app.exec();
    return rc;
}
