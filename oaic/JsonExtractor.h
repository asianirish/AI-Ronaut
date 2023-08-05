/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef JSONEXTRACTOR_H
#define JSONEXTRACTOR_H

#include <QJsonDocument>
#include <QStringList>



class JsonExtractor
{
public:
    JsonExtractor();

    QStringList parse(const QString& input, bool& isComplete);

private:
    QStringList extractJSON(const QString& input);

     //TODO: does not take into account that "data:" can be a part of chunks
    QStringList extractNotOnlyJSON(const QString& input);

private:
    QString _buffer;
    bool _isComplete;
};

#endif // JSONEXTRACTOR_H
