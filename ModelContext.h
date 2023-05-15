#ifndef MODELCONTEXT_H
#define MODELCONTEXT_H

#include <QString>
#include <QMetaType>

class ModelContext
{
public:
    static const double DEFAULT_TEMPERATURE;
    static const int DEFAULT_MAX_TOKENS;
    static const double DEFAULT_TOP_P;
    ModelContext();

    QString modelName() const;
    void setModelName(const QString &newModelName);

    double temperature() const;
    void setTemperature(double newTemperature);

    int maxTokens() const;
    void setMaxTokens(int newMaxTokens);

    double topP() const;
    void setTopP(double newTopP);

    double frequencyPenalty() const;
    void setFrequencyPenalty(double newFrequencyPenalty);

    double presencePenalty() const;
    void setPresencePenalty(double newPresencePenalty);

private:
    QString _modelName;
    double _temperature;
    int _maxTokens;
    double _topP;
    double _frequencyPenalty;
    double _presencePenalty;
};

Q_DECLARE_METATYPE(ModelContext)

#endif // MODELCONTEXT_H
