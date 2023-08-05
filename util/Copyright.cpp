/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#include "Copyright.h"

const QStringList fileTypes { "*.h", "*.cpp" };


Copyright::Copyright()
{

}

void Copyright::addCopyright(const QString &path, const QString &copyrightInfo)
{
    QDir dir(path);
    if (!dir.exists()) {
        qWarning("The directory does not exist");
        return;
    }

    dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
//    dir.setNameFilters(QStringList() << "*.cpp" << "*.h"); // <==== TODO: can't find dirs because of this

    for (const QFileInfo &fileInfo : dir.entryInfoList()) {
        if (fileInfo.isDir()) {
            addCopyright(fileInfo.absoluteFilePath(), copyrightInfo);
        } else {

            QStringList list;
            list << "cpp" << "h";
            if (!list.contains(fileInfo.suffix())) {
                continue;
            }

            QFile file(fileInfo.absoluteFilePath());
            if (file.open(QIODevice::ReadOnly)) {
                QString content = file.readAll();
                file.close();

                if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                    QTextStream out(&file);
                    out << copyrightInfo << "\n" << content;
                    file.close();
                }
            }
        }
    }
}

void Copyright::addCopyright1(const QString &dirPath, const QString &copyright)
{
    QDir dir(dirPath);
    if (!dir.exists()) {
        qWarning() << "Directory path not found.";
        return;
    }

    QStringList files;
    for (const auto& fileType : fileTypes) {
        files.append(dir.entryList(QStringList(fileType), QDir::Files));
    }

    for (const auto& file : files) {
        QFile f(dir.absoluteFilePath(file));
        if (!f.open(QFile::ReadWrite | QFile::Text)) {
            qWarning() << "Cannot open file for reading and writing:" << file;
            continue;
        }

        QString content;
        QTextStream in(&f);
        content = in.readAll();
        f.resize(0);
        in << copyright << "\n" << content;
        f.close();
    }
}
