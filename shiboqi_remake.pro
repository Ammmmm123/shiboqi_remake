QT       += core gui printsupport network opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    qcustomplot-source/qcustomplot.cpp \
    shiboqi_remake.cpp \
    udp_receive.cpp \
    udp_send.cpp\
    OBW.cpp

HEADERS += \
    qcustomplot-source/qcustomplot.h \
    shiboqi_remake.h \
    udp_receive.h \
    udp_send.h\
    OBW.h

FORMS += \
    shiboqi_remake.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
