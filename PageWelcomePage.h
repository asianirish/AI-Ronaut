#ifndef PAGEWELCOMEPAGE_H
#define PAGEWELCOMEPAGE_H

#include "PageWidget.h"

#include "plg/Info.h"


namespace Ui {
class PageWelcomePage;
}

class PageWelcomePage : public PageWidget
{
    Q_OBJECT

public:
    static const QString IMAGE_ACTION;
    static const QString CHAT_ACTION;
    static const QString PLOT_ACTION;

    static const QString NETWORK_CONFIG_ACTION;
    static const QString DONATE_ACTION;
    static const QString ABOUT_ACTION;

    static const QString PLUGINS_ACTION;


    explicit PageWelcomePage(QWidget *parent = nullptr);
    ~PageWelcomePage();

private slots:
    void on_browseKeyButton_clicked();

    void on_openActivityButton_clicked();

    void on_activityComboBox_currentIndexChanged(int index);

signals:

    void openImageAction();
    void openChatAction();
    void openDonateAction();
    void openAboutAction();
    void openPlotAction();
//    void openNetworkConfigAction();

    void openPluginAction(const QString &filePath, const plg::Info &plgInfo);

protected:
    void synchronizeClient(oaic::Manager *_client) override;

private:
    Ui::PageWelcomePage *ui;

private:
    void displaySuccess();
    void displayError();
    void displayWait();

    void openAction(const QString &actionData);

    void onKeySuccess();

};

#endif // PAGEWELCOMEPAGE_H
