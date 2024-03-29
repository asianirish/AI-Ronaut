/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#include "./ModelContext.h"

namespace oaic {

const double ModelContext::DEFAULT_TEMPERATURE = 0.70;
const int ModelContext::DEFAULT_MAX_TOKENS = 512;
const double ModelContext::DEFAULT_TOP_P = 1.;

const double ModelContext::DEFAULT_FREQUENCY_PENALTY = 0.;
const double ModelContext::DEFAULT_PRESENCE_PENALTY = 0.;

const QString ModelContext::DEFAULT_MODEL("gpt-4-0613");

ModelContext::ModelContext() :
    _modelName(DEFAULT_MODEL),
    _temperature(DEFAULT_TEMPERATURE),
    _maxTokens(DEFAULT_MAX_TOKENS),
    _topP(DEFAULT_TOP_P),
    _frequencyPenalty(DEFAULT_FREQUENCY_PENALTY),
    _presencePenalty(DEFAULT_PRESENCE_PENALTY)
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

void ModelContext::setDefault()
{
    *this = ModelContext();
}

} // namespace oaic
