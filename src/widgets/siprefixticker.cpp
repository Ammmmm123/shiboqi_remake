// Implementation of SIPrefixTicker
#include "siprefixticker.h"
#include <cmath>

/**
 * @brief 构造函数
 * @param baseUnit 基础单位（例如 "us" 或 "V"）
 */
SIPrefixTicker::SIPrefixTicker(const QString &baseUnit)
    : m_baseUnit(baseUnit)
{
}

/**
 * @brief 生成刻度标签并根据范围选择单位前缀
 */
void SIPrefixTicker::generate(const QCPRange &range, const QLocale &locale, QChar formatChar, int precision,
                              QVector<double> &ticks, QVector<double> *subTicks, QVector<QString> *tickLabels)
{
    QCPAxisTicker::generate(range, locale, formatChar, precision, ticks, subTicks, tickLabels);
    if (!tickLabels) return;

    double span = qAbs(range.upper - range.lower);
    if (m_baseUnit == "us") {
        // 支持 ns/us/ms/s
        if (span <= 1.0) {
            m_lastPrefix = "ns"; m_lastScale = 0.001;
        } else if (span < 10000.0) {
            m_lastPrefix = "us"; m_lastScale = 1.0;
        } else if (span < 10000000.0) {
            m_lastPrefix = "ms"; m_lastScale = 1000.0;
        } else {
            m_lastPrefix = "s"; m_lastScale = 1000000.0;
        }
    } else {
        double maxAbs = 0.0;
        for (double t : ticks) if (qAbs(t) > maxAbs) maxAbs = qAbs(t);
        int exp = 0; if (maxAbs > 0) exp = static_cast<int>(std::floor(std::log10(maxAbs)));

        struct Prefix { int exp; const char* suf; double scale; };
        const Prefix prefixes[] = {
            { -12, "p", 1e-12 }, { -9, "n", 1e-9 }, { -6, "u", 1e-6 }, { -3, "m", 1e-3 },
            { 0, "", 1.0 }, { 3, "k", 1e3 }, { 6, "M", 1e6 }, { 9, "G", 1e9 }, { 12, "T", 1e12 }
        };
        const Prefix *best = &prefixes[4];
        for (const Prefix &p : prefixes) if (exp >= p.exp && exp < p.exp + 3) best = &p;
        m_lastPrefix = QString::fromLatin1(best->suf); m_lastScale = best->scale;
    }

    tickLabels->clear();
    for (double t : ticks) {
        double v = t / m_lastScale;
        QString s = locale.toString(v, 'f', decidePrecision(ticks));
        tickLabels->append(s);
    }
}

QString SIPrefixTicker::lastPrefix() const { return m_lastPrefix; }
double SIPrefixTicker::lastScale() const { return m_lastScale; }

QString SIPrefixTicker::unitLabel() const {
    if (m_lastPrefix.isEmpty()) return m_baseUnit;
    if (m_lastPrefix.endsWith(m_baseUnit) || m_lastPrefix.endsWith('s')) return m_lastPrefix;
    return m_lastPrefix + m_baseUnit;
}

int SIPrefixTicker::decidePrecision(const QVector<double> &ticks) const
{
    if (ticks.size() < 2) return 2;
    double step = 0.0;
    for (int i = 1; i < ticks.size(); ++i) {
        double d = qAbs(ticks[i] - ticks[i-1]); if (d > 0) { step = d; break; }
    }
    if (step <= 0) return 2;
    double s = step / m_lastScale; int prec = 0; while (s < 1.0 && prec < 6) { s *= 10.0; ++prec; }
    return qMin(6, prec);
}
