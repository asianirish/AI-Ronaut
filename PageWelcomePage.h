/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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
