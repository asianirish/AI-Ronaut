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

private:
    QString _buffer;
    bool _isComplete;
};

#endif // JSONEXTRACTOR_H
