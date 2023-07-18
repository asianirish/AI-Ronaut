#include "JsonExtractor.h"

JsonExtractor::JsonExtractor() : _isComplete(true)
{

}

QStringList JsonExtractor::parse(const QString &input, bool &isComplete)
{
    _buffer += input;
    isComplete = true;

    QStringList potentialJsons = extractJSON(_buffer);
    QStringList parsedJsons;

    for (auto const& potentialJson : potentialJsons) {
        QJsonParseError parseError;
        QJsonDocument::fromJson(potentialJson.toUtf8(), &parseError);

        if (parseError.error == QJsonParseError::NoError) {
            parsedJsons.append(potentialJson);
        }
        else {
            isComplete = false;
            break;
        }
    }

    if (isComplete) {
        _buffer.clear();
    }

    return parsedJsons;
}

QStringList JsonExtractor::extractJSON(const QString &input)
{
    QStringList jsons;
    int start = 0;
    int end = 0;
    int brackets = 0;
    bool in_json = false;
    bool in_string = false;
    for (int i = 0; i < input.size(); ++i) {
        QChar current = input[i];

        if (current == '"' && (i == 0 || input[i - 1] != '\\')) {
            in_string = !in_string;
        }

        if (!in_string) {
            if (current == '{') {
                if (!in_json) {
                    start = i;
                    in_json = true;
                }
                brackets++;
            } else if (current == '}') {
                brackets--;
                if (brackets == 0 && in_json) {
                    end = i;
                    in_json = false;
                    jsons.push_back(input.mid(start, end - start + 1));
                }
            }
        }
    }
    return jsons;
}

