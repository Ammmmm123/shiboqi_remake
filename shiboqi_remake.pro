QT += core gui printsupport network opengl serialport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# 启用 QCustomPlot 的 OpenGL 支持（在编译时定义）
DEFINES += QCUSTOMPLOT_USE_OPENGL


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += qcustomplot-source

SOURCES += \
    UART_receive.cpp \
    main.cpp \
    qcustomplot-source/qcustomplot.cpp \
    shiboqi_remake.cpp \
    siprefixticker.cpp \
    udp_receive.cpp \
    udp_send.cpp \
    data_processor.cpp \
    spectrum_analyzer.cpp \
    waveform_sender_thread.cpp

HEADERS += \
    UART_receive.h \
    qcustomplot-source/qcustomplot.h \
    shiboqi_remake.h \
    siprefixticker.h \
    udp_receive.h \
    udp_send.h \
    data_processor.h \
    spectrum_analyzer.h \
    waveform_sender_thread.h

FORMS += \
    shiboqi_remake.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -lopengl32 #开启opengl关键操作





