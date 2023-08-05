/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef OAIC_MODELCONTEXT_H
#define OAIC_MODELCONTEXT_H

#include <QString>
#include <QMetaType>

namespace oaic {

class ModelContext
{
public:
    static const double DEFAULT_TEMPERATURE;
    static const int DEFAULT_MAX_TOKENS;
    static const double DEFAULT_TOP_P;
    static const double DEFAULT_FREQUENCY_PENALTY;
    static const double DEFAULT_PRESENCE_PENALTY;

    static const QString DEFAULT_MODEL;

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

    void setDefault();

private:
    QString _modelName;
    double _temperature;
    int _maxTokens;
    double _topP;
    double _frequencyPenalty;
    double _presencePenalty;
};

} // namespace

Q_DECLARE_METATYPE(oaic::ModelContext)

#endif // OAIC_MODELCONTEXT_H
