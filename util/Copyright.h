/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef COPYRIGHT_H
#define COPYRIGHT_H

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>


class Copyright
{
public:
    QString copyrightInfo("/*\n"
                          "* Copyright (c) 2023, Asianirish, asianirish@gmail.com\n"
                          "* \n"
                          "* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.\n"
                          "* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.\n"
                          "*/\n");
    Copyright();

    static void addCopyright(const QString &path, const QString &copyrightInfo);
    static void addCopyright1(const QString& dirPath, const QString& copyright);


};

#endif // COPYRIGHT_H
