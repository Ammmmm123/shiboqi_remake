#include "shiboqi_remake.h"
#include "src/data_processing/data_processor.h"  // 引入 WaveformAnalysisResult 定义
#include "src/analysis/spectrum_analyzer.h"      // 引入 SpectrumAnalysisResult 定义

#include <QApplication>
#include <QIcon>
#include <QTextCodec>
#include <QMetaType>
#include <QVector>

int main(int argc, char *argv[])
{
    // ========== 注册元类型（跨线程信号槽必须） ==========
    // 注册 QVector<double> 类型，使其可以在跨线程信号槽中传递
    qRegisterMetaType<QVector<double>>("QVector<double>");
    qRegisterMetaType<QVector<double>>("const QVector<double>&");
    
    // 注册 WaveformAnalysisResult 类型，使分析结果可以跨线程传递
    qRegisterMetaType<WaveformAnalysisResult>("WaveformAnalysisResult");
    qRegisterMetaType<WaveformAnalysisResult>("const WaveformAnalysisResult&");
    
    // 注册 SpectrumAnalysisResult 类型，使频谱分析结果可以跨线程传递
    qRegisterMetaType<SpectrumAnalysisResult>("SpectrumAnalysisResult");
    qRegisterMetaType<SpectrumAnalysisResult>("const SpectrumAnalysisResult&");
    
    // 设置控制台输出编码为 UTF-8（解决 qDebug 中文乱码）
#ifdef Q_OS_WIN
    system("chcp 65001 > nul");  // Windows: 设置控制台为 UTF-8
#endif
    
    QApplication a(argc, argv);
    
    // 设置应用程序名称
    a.setApplicationName("FPGA多功能调试仪");
    a.setApplicationDisplayName("FPGA多功能调试仪");
    
    // 设置应用程序图标
    a.setWindowIcon(QIcon(":/tubiao.ico"));
    
    shiboqi_remake w;
    w.setWindowTitle("FPGA多功能调试仪");
    w.show();
    return a.exec();
}
