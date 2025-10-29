QT += core gui printsupport network opengl serialport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# 应用程序名称（使用英文避免编译问题）
TARGET = FPGA_Debugger

# 启用 QCustomPlot 的 OpenGL 支持（在编译时定义）
DEFINES += QCUSTOMPLOT_USE_OPENGL


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# 包含路径
INCLUDEPATH += src/thirdparty/qcustomplot-source \
               src/ui \
               src/network \
               src/data_processing \
               src/analysis \
               src/widgets

SOURCES += \
    main.cpp \
    src/thirdparty/qcustomplot-source/qcustomplot.cpp \
    src/ui/shiboqi_remake.cpp \
    src/network/UART_receive.cpp \
    src/network/udp_receive.cpp \
    src/network/udp_send.cpp \
    src/data_processing/data_processor.cpp \
    src/data_processing/data_processor_thread.cpp \
    src/data_processing/fft_processor.cpp \
    src/data_processing/frequency_detector.cpp \
    src/data_processing/waveform_downsampler.cpp \
    src/analysis/spectrum_analyzer.cpp \
    src/widgets/siprefixticker.cpp \
    src/widgets/waveform_sender_thread.cpp

HEADERS += \
    src/thirdparty/qcustomplot-source/qcustomplot.h \
    src/ui/shiboqi_remake.h \
    src/network/UART_receive.h \
    src/network/udp_receive.h \
    src/network/udp_send.h \
    src/data_processing/data_processor.h \
    src/data_processing/data_processor_thread.h \
    src/data_processing/fft_processor.h \
    src/data_processing/frequency_detector.h \
    src/data_processing/waveform_downsampler.h \
    src/analysis/spectrum_analyzer.h \
    src/widgets/siprefixticker.h \
    src/widgets/waveform_sender_thread.h

FORMS += \
    src/ui/shiboqi_remake.ui

RESOURCES += \
    resources/resources.qrc

# Windows应用程序图标
win32:RC_ICONS = resources/tubiao.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -lopengl32 #开启opengl关键操作





