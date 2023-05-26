QT = core network

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Auth.cpp \
        Chat.cpp \
        Component.cpp \
        Image.cpp \
        ImageHandler.cpp \
        Manager.cpp \
        MsgData.cpp \
        TestImageConsumer.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Auth.h \
    Chat.h \
    Component.h \
    Image.h \
    ImageHandler.h \
    Manager.h \
    MsgData.h \
    TestImageConsumer.h

DISTFILES += \
    LICENSE \
    README.md
