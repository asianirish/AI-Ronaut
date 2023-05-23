#include "gfunc.h"

namespace potato_util
{

const char BASE_36[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char BASE_62[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";


// maximum radix - base36
std::string uint64_t2string(uint64_t value, uint64_t radix) {
    std::string result;
    while (value > 0) {
        int64_t remainder = value % radix;
        value /= radix;
        result.insert(result.begin(), BASE_36[remainder]);
    }
    return result;
}

#ifdef QT_CORE_LIB
QString uint64_t2qstring(uint64_t value, uint64_t radix)
{
    QString result;
    while (value > 0) {
        int64_t remainder = value % radix;
        value /= radix;
        result.prepend(BASE_36[remainder]);
    }
    return result;
}

//max 36+26 = 62
QString uint64_t2qstring_ext(uint64_t value, uint64_t radix)
{
    QString result;
    while (value > 0) {
        int64_t remainder = value % radix;
        value /= radix;
        result.prepend(BASE_62[remainder]);
    }
    return result;
}

bool isNumber(const QVariant &arg)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    auto tp = arg.type();
#else
    auto tp = arg.typeId();
#endif
    if (static_cast<int>(tp) == static_cast<int>(QMetaType::Int) ||
        static_cast<int>(tp) == static_cast<int>(QMetaType::UInt) ||
        static_cast<int>(tp) == static_cast<int>(QMetaType::LongLong) ||
        static_cast<int>(tp) == static_cast<int>(QMetaType::ULongLong) ||
        static_cast<int>(tp) == static_cast<int>(QMetaType::Double) ||
        static_cast<int>(tp) == static_cast<int>(QMetaType::Float) ||
        static_cast<int>(tp) == static_cast<int>(QMetaType::Short) ||
        static_cast<int>(tp) == static_cast<int>(QMetaType::UShort)) {

        return true;
    }

    return false;
}

bool isInteger(const QVariant &arg)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    auto tp = arg.type();
#else
    auto tp = arg.typeId();
#endif
    if (static_cast<int>(tp) == static_cast<int>(QMetaType::Int) ||
        static_cast<int>(tp) == static_cast<int>(QMetaType::UInt) ||
        static_cast<int>(tp) == static_cast<int>(QMetaType::LongLong) ||
        static_cast<int>(tp) == static_cast<int>(QMetaType::ULongLong) ||
        static_cast<int>(tp) == static_cast<int>(QMetaType::Short) ||
        static_cast<int>(tp) == static_cast<int>(QMetaType::UShort)) {

        return true;
    }

    return false;
}

int varToInt(const QVariant &arg)
{
    if (isInteger(arg)) {

        return arg.toInt();

    } /*else*/ { //implied a string type
        QString numStr = arg.toString();
        bool ok;
        return numStr.toInt(&ok, 16);
    }
}

QString phraseToCamelCase(const QString& s, int maxWords)
{
    QStringList parts = s.split(' ', Qt::SkipEmptyParts);
    QStringList camelParts;

    int num = parts.size() > maxWords ? maxWords : parts.size();

    for (int i = 0; i < num; ++i) {
        auto camelPart = parts[i].replace(0, 1, parts[i][0].toUpper());
        camelParts.append(camelPart);
    }

    return camelParts.join("");
}

QString phraseToLowerCamelCase(const QString &s, int maxWords)
{
    QStringList parts = s.split(' ', Qt::SkipEmptyParts);
    QStringList camelParts{parts.at(0)};

    int num = parts.size() > maxWords ? maxWords : parts.size();

    for (int i = 1; i < num; ++i) {
        auto camelPart = parts[i].replace(0, 1, parts[i][0].toUpper());
        camelParts.append(camelPart);
    }

    return camelParts.join("");
}

#endif

double dRand(double dMin, double dMax)
{
    double d = (double)rand() / RAND_MAX;
    return dMin + d * (dMax - dMin);
}

bool iequals(const std::string& a, const std::string& b)
{
    return std::equal(a.begin(), a.end(),
                      b.begin(), b.end(),
                      [](char a, char b) {
                          return tolower(a) == tolower(b);
                      });
}



} // namespace util
