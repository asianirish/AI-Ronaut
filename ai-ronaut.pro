QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += oaic/
INCLUDEPATH += util/

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AIMessageItemWidget.cpp \
    ChatConfigWidget.cpp \
    ChatItemWidget.cpp \
    ChatMessageTextBrowser.cpp \
    ChatSessionItemWidget.cpp \
    ChatSessionWidget.cpp \
    ChatToolWidget.cpp \
    ChatWidget.cpp \
    ErrorMessageItemWidget.cpp \
    NetworkConfiWidget.cpp \
    NetworkContext.cpp \
    PageAboutPage.cpp \
    PageContext.cpp \
    PageDonatePage.cpp \
    PageGeneralChatPage.cpp \
    PageImagePage.cpp \
    PagePlotPage.cpp \
    PageWelcomePage.cpp \
    PageWidget.cpp \
    SystemMessageWidget.cpp \
    UserMessageItemWidget.cpp \
    chat/AssistantMessage.cpp \
    chat/Message.cpp \
    chat/Session.cpp \
    chat/SessionItem.cpp \
    chat/SessionManager.cpp \
    chat/SystemMessage.cpp \
    chat/UserMessage.cpp \
    main.cpp \
    MainWindow.cpp \
    oaic/Auth.cpp \
    oaic/Chat.cpp \
    oaic/Component.cpp \
    oaic/Image.cpp \
    oaic/Manager.cpp \
    oaic/ModelContext.cpp \
    oaic/Models.cpp \
    oaic/MsgData.cpp \
    util/gfunc.cpp

HEADERS += \
    AIMessageItemWidget.h \
    ChatConfigWidget.h \
    ChatItemWidget.h \
    ChatMessageTextBrowser.h \
    ChatSessionItemWidget.h \
    ChatSessionWidget.h \
    ChatToolWidget.h \
    ChatWidget.h \
    ErrorMessageItemWidget.h \
    MainWindow.h \
    NetworkConfiWidget.h \
    NetworkContext.h \
    PageAboutPage.h \
    PageContext.h \
    PageDonatePage.h \
    PageGeneralChatPage.h \
    PageImagePage.h \
    PagePlotPage.h \
    PageWelcomePage.h \
    PageWidget.h \
    SystemMessageWidget.h \
    UserMessageItemWidget.h \
    chat/AssistantMessage.h \
    chat/Message.h \
    chat/Session.h \
    chat/SessionItem.h \
    chat/SessionManager.h \
    chat/SystemMessage.h \
    chat/UserMessage.h \
    oaic/Auth.h \
    oaic/Chat.h \
    oaic/Component.h \
    oaic/Image.h \
    oaic/Manager.h \
    oaic/ModelContext.h \
    oaic/Models.h \
    oaic/MsgData.h \
    util/OrderedMap.h \
    util/gfunc.h

FORMS += \
    AIMessageItemWidget.ui \
    ChatConfigWidget.ui \
    ChatSessionWidget.ui \
    ChatWidget.ui \
    ErrorMessageItemWidget.ui \
    MainWindow.ui \
    NetworkConfiWidget.ui \
    PageAboutPage.ui \
    PageDonatePage.ui \
    PageGeneralChatPage.ui \
    PageImagePage.ui \
    PagePlotPage.ui \
    PageWelcomePage.ui \
    SystemMessageWidget.ui \
    UserMessageItemWidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    LICENSE  \
    README.md \
    TODO \
    oaic/README.md

RESOURCES += \
    air.qrc
