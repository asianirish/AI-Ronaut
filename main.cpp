/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#include "MainWindow.h"

#include "chat/SessionManager.h"

#include "plg/Info.h"

#include "util/Copyright.h"

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

    if (!query.exec("PRAGMA foreign_keys = ON")) {
        qDebug() << "error setting PRAGMA foreign_keys:" << query.lastError().text();
        return false;
    }


    if (!query.exec("CREATE TABLE IF NOT EXISTS characters ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "name VARCHAR(64) NOT NULL UNIQUE, "
                    "message TEXT NOT NULL, "
                    "useNameInMessage BOOLEAN DEFAULT 1"
                    ")")) {
        qDebug() << "error creating characters:" << query.lastError().text();
        return false;
    }

    {
        if (!query.exec("SELECT COUNT(*) FROM characters")) {
            qDebug() << "error checking characters count:" << query.lastError().text();
            return false;
        }

        int rowCount = 0;
        if (query.next()) {
            rowCount = query.value(0).toInt();
        }

        if (rowCount == 0) {
            if (!query.exec("INSERT INTO characters ('name', 'message') "
                            "VALUES('Margaret Bigley', "
                            "'exceptional mathematics professor renowned for your ability "
                            "to articulate complex material in a comprehensible and engaging manner')")) {
                qDebug() << "error creating a character:" << query.lastError().text();
                return false;
            }
        }
    }

    if (!query.exec("CREATE TABLE IF NOT EXISTS sessions ("
                    "uuid VARCHAR(38) PRIMARY KEY, "
                    "character_id INTEGER, "
                    "name TEXT NOT NULL, "
                    "created DATETIME, "
                    "accessed DATETIME, "
                    "FOREIGN KEY (character_id) REFERENCES characters (id) ON DELETE SET NULL"
                    ")")) {
        qDebug() << "error creating sessions:" << query.lastError().text();
        return false;
    }

    if (!query.exec("CREATE TABLE IF NOT EXISTS messages ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "session_uuid VARCHAR(38) NOT NULL, "
                    "order_num INTEGER NOT NULL, "
                    "role TEXT CHECK (role IN ('system', 'assistant', 'user')) NOT NULL, " // ENUM type for SQLite (use ENUM for other SQL engines)
                    "content TEXT NOT NULL, "
                    "FOREIGN KEY (session_uuid) REFERENCES sessions (uuid) ON DELETE CASCADE, "
                    "UNIQUE (session_uuid, order_num)"
                    ")")) {
        qDebug() << "error creating messages:" << query.lastError().text();
        return false;
    }

    if (!query.exec("CREATE TABLE IF NOT EXISTS plugins ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "file VARCHAR(64) NOT NULL UNIQUE, "
                    "name VARCHAR(64), "
                    "desc TEXT, "
                    "author TEXT NOT NULL, "
                    "version VARCHAR(16), "
                    "hash BLOB"
                    ")")) {
        qDebug() << "error creating plugins:" << query.lastError().text();
        return false;
    }

    qDebug() << "db success";

    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "VERSION:" << VERSION;

    QCoreApplication::setOrganizationName("asianirish");
    QCoreApplication::setApplicationName("ai-ronaut");

    qRegisterMetaType<oaic::ModelContext>();
    qRegisterMetaType<plg::Info>();

    QObject::connect(&a, &QApplication::aboutToQuit, gSessions, &chat::SessionManager::onQuit);

    if (!maybeCreateDb()) {
        return -1;
    }

    MainWindow w;
    w.showMaximized();
    int result = a.exec();

    QSqlDatabase db = QSqlDatabase::database();

    qDebug() << "DATABASE:" << db.databaseName() << "is closing...";

    db.close();

    return result;
}
