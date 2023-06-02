#include "MainWindow.h"

#include "chat/SessionManager.h"

#include <ModelContext.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("asianirish");
    QCoreApplication::setApplicationName("ai-ronaut");

    qRegisterMetaType<oaic::ModelContext>();

    QObject::connect(&a, &QApplication::aboutToQuit, gSessions, &chat::SessionManager::onQuit);

    MainWindow w;
    w.show();
    return a.exec();
}
