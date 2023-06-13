#include "MainWindow.h"

#include "chat/SessionManager.h"

#include <ModelContext.h>

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

bool maybeCreateDb() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("ai-ronaut.db");

    if (!db.open()) {
        qDebug() << "error opening: " << db.lastError().text();
        return false;
    }

    QSqlQuery query;

    if (!query.exec("CREATE TABLE IF NOT EXISTS roles ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "name TEXT NOT NULL UNIQUE, "
                    "message TEXT NOT NULL"
                    ")")) {
        qDebug() << "error creating roles:" << query.lastError().text();
        return false;
    }

    if (!query.exec("SELECT COUNT(*) FROM roles")) {
        qDebug() << "error checking roles count:" << query.lastError().text();
        return false;
    }

    int rowCount = 0;
    if (query.next()) {
        rowCount = query.value(0).toInt();
    }

    if (rowCount == 0) {
        if (!query.exec("INSERT INTO roles ('name', 'message') "
                        "VALUES('Margaret Bigley', "
                        "'exceptional mathematics professor renowned for your ability "
                        "to articulate complex material in a comprehensible and engaging manner')")) {
            qDebug() << "error creating a role:" << query.lastError().text();
            return false;
        }
    }

    qDebug() << "db success";

    // TODO: where to close?
//    db.close();
    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("asianirish");
    QCoreApplication::setApplicationName("ai-ronaut");

    qRegisterMetaType<oaic::ModelContext>();

    QObject::connect(&a, &QApplication::aboutToQuit, gSessions, &chat::SessionManager::onQuit);

    if (!maybeCreateDb()) {
        return -1;
    }

    MainWindow w;
    w.show();
    return a.exec();
}
