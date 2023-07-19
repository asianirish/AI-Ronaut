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
