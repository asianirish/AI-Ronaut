QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


INCLUDEPATH += third/liboai/include
INCLUDEPATH += third/

LIBS += -lcurl




# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AIMessageItemWidget.cpp \
    AppContext.cpp \
    ChatConfigWidget.cpp \
    ChatItemWidget.cpp \
    ChatSessionWidget.cpp \
    ChatWidget.cpp \
    ErrorMessageItemWidget.cpp \
    ModelContext.cpp \
    NetworkConfiWidget.cpp \
    OpenAIApiHandler.cpp \
    PageAboutPage.cpp \
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
    chat/SessionManager.cpp \
    chat/SystemMessage.cpp \
    chat/UserMessage.cpp \
    main.cpp \
    MainWindow.cpp \
    third/liboai/components/audio.cpp \
    third/liboai/components/chat.cpp \
    third/liboai/components/completions.cpp \
    third/liboai/components/edits.cpp \
    third/liboai/components/embeddings.cpp \
    third/liboai/components/files.cpp \
    third/liboai/components/fine_tunes.cpp \
    third/liboai/components/images.cpp \
    third/liboai/components/models.cpp \
    third/liboai/components/moderations.cpp \
    third/liboai/core/authorization.cpp \
    third/liboai/core/netimpl.cpp \
    third/liboai/core/response.cpp \
    util/gfunc.cpp

HEADERS += \
    AIMessageItemWidget.h \
    AppContext.h \
    ChatConfigWidget.h \
    ChatItemWidget.h \
    ChatSessionWidget.h \
    ChatWidget.h \
    ErrorMessageItemWidget.h \
    MainWindow.h \
    ModelContext.h \
    NetworkConfiWidget.h \
    OpenAIApiHandler.h \
    PageAboutPage.h \
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
    chat/SessionManager.h \
    chat/SystemMessage.h \
    chat/UserMessage.h \
    third/liboai/include/components/audio.h \
    third/liboai/include/components/chat.h \
    third/liboai/include/components/completions.h \
    third/liboai/include/components/edits.h \
    third/liboai/include/components/embeddings.h \
    third/liboai/include/components/files.h \
    third/liboai/include/components/fine_tunes.h \
    third/liboai/include/components/images.h \
    third/liboai/include/components/models.h \
    third/liboai/include/components/moderations.h \
    third/liboai/include/core/authorization.h \
    third/liboai/include/core/exception.h \
    third/liboai/include/core/netimpl.h \
    third/liboai/include/core/network.h \
    third/liboai/include/core/response.h \
    third/liboai/include/liboai.h \
    third/nlohmann/json.hpp \
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
    README.md

RESOURCES += \
    air.qrc
