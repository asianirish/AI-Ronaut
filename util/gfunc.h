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
