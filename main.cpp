#include "MainWindow.h"

#include "ModelContext.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("asianirish");
    QCoreApplication::setApplicationName("ai-ronaut");

    qRegisterMetaType<ModelContext>();

    MainWindow w;
    w.show();
    return a.exec();
}
