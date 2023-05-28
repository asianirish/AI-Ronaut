#include "./ModelContext.h"

namespace oaic {

const double ModelContext::DEFAULT_TEMPERATURE = 0.70;
const int ModelContext::DEFAULT_MAX_TOKENS = 256;
const double ModelContext::DEFAULT_TOP_P = 1.;
const QString ModelContext::DEFAULT_MODEL("gpt-3.5-turbo");

ModelContext::ModelContext() :
    _modelName(DEFAULT_MODEL),
    _temperature(DEFAULT_TEMPERATURE),
    _maxTokens(DEFAULT_MAX_TOKENS),
    _topP(DEFAULT_TOP_P),
    _frequencyPenalty(0.),
    _presencePenalty(0.)
{

}

QString ModelContext::modelName() const
{
    return _modelName;
}

void ModelContext::setModelName(const QString &newModelName)
{
    _modelName = newModelName;
}

double ModelContext::temperature() const
{
    return _temperature;
}

void ModelContext::setTemperature(double newTemperature)
{
    _temperature = newTemperature;
}

int ModelContext::maxTokens() const
{
    return _maxTokens;
}

void ModelContext::setMaxTokens(int newMaxTokens)
{
    _maxTokens = newMaxTokens;
}

double ModelContext::topP() const
{
    return _topP;
}

void ModelContext::setTopP(double newTopP)
{
    _topP = newTopP;
}

double ModelContext::frequencyPenalty() const
{
    return _frequencyPenalty;
}

void ModelContext::setFrequencyPenalty(double newFrequencyPenalty)
{
    _frequencyPenalty = newFrequencyPenalty;
}

double ModelContext::presencePenalty() const
{
    return _presencePenalty;
}

void ModelContext::setPresencePenalty(double newPresencePenalty)
{
    _presencePenalty = newPresencePenalty;
}

} // namespace oaic
