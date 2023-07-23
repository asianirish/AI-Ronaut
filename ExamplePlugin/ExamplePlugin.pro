QT += gui
QT += widgets
QT += network

TEMPLATE = lib
CONFIG += plugin

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += "../"

DESTDIR = "$$PWD/../plg_dest"
OBJECTS_DIR = "$$PWD/../../BuildExamplePlugin"

CONFIG(debug, debug|release) {
MODE = "Debug"
}

CONFIG(release, debug|release) {
MODE = "Release"
}


OBJECTS_DIR = $$OBJECTS_DIR/$${TARGET}_$${QT_VERSION}_$${MODE}

message("OBJECTS_DIR: $$OBJECTS_DIR")


MOC_DIR = $$OBJECTS_DIR/moc
RCC_DIR = $$OBJECTS_DIR/rcc
UI_DIR = $$OBJECTS_DIR/ui


SOURCES += \
    ../PageWidget.cpp \
    ../oaic/Auth.cpp \
    ../oaic/Chat.cpp \
    ../oaic/Component.cpp \
    ../oaic/Image.cpp \
    ../oaic/JsonExtractor.cpp \
    ../oaic/Manager.cpp \
    ../oaic/ModelContext.cpp \
    ../oaic/Models.cpp \
    ../oaic/MsgData.cpp \
    ../oaic/TestChatConsumer.cpp \
    ../oaic/TestImageConsumer.cpp \
    ExamplePluginPageWidget.cpp \
    RootObject.cpp

HEADERS += \
    ../PageWidget.h \
    ../oaic/Auth.h \
    ../oaic/Chat.h \
    ../oaic/Component.h \
    ../oaic/Image.h \
    ../oaic/JsonExtractor.h \
    ../oaic/Manager.h \
    ../oaic/ModelContext.h \
    ../oaic/Models.h \
    ../oaic/MsgData.h \
    ../oaic/TestChatConsumer.h \
    ../oaic/TestImageConsumer.h \
    ../plg_source/IRootObject.h \
    ExamplePluginPageWidget.h \
    RootObject.h

DISTFILES += ExamplePlugin.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    ExamplePluginPageWidget.ui
