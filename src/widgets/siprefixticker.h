#ifndef SIPREFIXTICKER_H
#define SIPREFIXTICKER_H

#include "qcustomplot.h"
#include <QString>

/**
 * @brief SIPrefixTicker
 *
 * QCPAxisTicker 的扩展，用于：
 * - 避免科学计数法，使用固定小数格式显示刻度值
 * - 根据坐标范围自动选择 SI 前缀（对时间轴支持 ns/us/ms/s）
 */
class SIPrefixTicker : public QCPAxisTicker
{
public:
    /**
     * @brief 构造函数
     * @param baseUnit 基础单位字符串（例如 "us" 或 "V"）
     */
    explicit SIPrefixTicker(const QString &baseUnit);

    /**
     * @brief 根据范围生成刻度与刻度文本
     * @param range 轴范围
     * @param locale 本地化设置，用于数字格式化
     * @param formatChar 未使用（由基类提供）
     * @param precision 未使用（由基类提供）
     * @param ticks 输出刻度位置
     * @param subTicks 可选的子刻度
     * @param tickLabels 输出刻度文本（覆盖基类行为）
     */
    void generate(const QCPRange &range, const QLocale &locale, QChar formatChar, int precision,
                  QVector<double> &ticks, QVector<double> *subTicks, QVector<QString> *tickLabels) override;

    QString lastPrefix() const;
    double lastScale() const;
    QString unitLabel() const;

private:
    QString m_baseUnit;
    QString m_lastPrefix;
    double m_lastScale = 1.0;

    int decidePrecision(const QVector<double> &ticks) const;
};

#endif // SIPREFIXTICKER_H
