/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef GFUNC_H
#define GFUNC_H

#include <string>
#include <cstdint>

#ifdef QT_CORE_LIB
#include <QString>
#include <QVariant>
#endif

namespace potato_util
{

#ifdef QT_CORE_LIB
QString uint64_t2qstring(uint64_t value, uint64_t radix);

QString uint64_t2qstring_ext(uint64_t value, uint64_t radix = 62);

bool isNumber(const QVariant &arg);

bool isInteger(const QVariant &arg);

int varToInt(const QVariant &arg);

QString phraseToCamelCase(const QString& str, int maxWords, int fromIndex = 0);
QString phraseToLowerCamelCase(const QString& s, int maxWords);

#endif

// maximum radix - base36
std::string uint64_t2string(uint64_t value, uint64_t radix);

double dRand(double dMin, double dMax);

bool iequals(const std::string& a, const std::string& b);

} // namespace potato_util

#endif // GFUNC_H
