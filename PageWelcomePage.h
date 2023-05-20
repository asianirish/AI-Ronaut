#ifndef PAGEWELCOMEPAGE_H
#define PAGEWELCOMEPAGE_H

#include "PageWidget.h"
#include "AppContext.h"


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
    void openNetworkConfigAction();

protected:
    void updateCntx(AppContext *cntx) override;

private:
    Ui::PageWelcomePage *ui;
    AppContext _appContext;


private:
    void displaySuccess();
    void displayError();
    void displayWait();

    void openAction(const QString &actionData);

    bool checkKeyFromEnv();

    void onKeySuccess();



};

#endif // PAGEWELCOMEPAGE_H
