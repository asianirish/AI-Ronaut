#include "PageGeneralChatPage.h"
#include "ui_PageGeneralChatPage.h"

#include "chat/SessionManager.h"

#include <QSettings>


PageGeneralChatPage::PageGeneralChatPage(QWidget *parent) :
    PageWidget(parent),
    ui(new Ui::PageGeneralChatPage)
{
    static int pageNumber = 1;

    ui->setupUi(this);

    _pageContext = new PageContext(pageNumber);
    ui->chatWidget->setPageContext(_pageContext);
    ui->chatSessionWidget->setPageContext(_pageContext);
    ui->systemMessageWidget->setPageContext(_pageContext);
    ui->chatConfigWidget->setPageContext(_pageContext);

    // good place to create a session
    auto currentSessionId = gSessions->createSession(pageNumber);
    _pageContext->setCurrentSessionId(currentSessionId);

    // synchronization with the newly created and empty session is not required

    pageNumber++;

    // connection between widgets
    connect(ui->chatWidget, &ChatWidget::renameSession, ui->chatSessionWidget, &ChatSessionWidget::onRenameSession);

    // TODO: implement & connect ChatSessionWidget signals

    QSettings settings;

    auto modelName = settings.value("model/name").toString();
    _modelCntx.setModelName(modelName);

    // read other model settings
    {
        auto temperature = settings.value("model/temperature").toDouble();
        _modelCntx.setTemperature(temperature);
    }

    {
        auto maxTokens = settings.value("model/maxTokens").toInt();
        _modelCntx.setMaxTokens(maxTokens);
    }

    {
        auto topP = settings.value("model/topP").toDouble();
        _modelCntx.setTopP(topP);
    }

    {
        auto frequencyPenalty = settings.value("model/frequencyPenalty").toDouble();
        _modelCntx.setFrequencyPenalty(frequencyPenalty);
    }

    {
        auto presencePenalty = settings.value("model/presencePenalty").toDouble();
        _modelCntx.setPresencePenalty(presencePenalty);
    }

    ui->chatConfigWidget->setModelCntx(&_modelCntx);
    ui->chatWidget->setModelCntx(&_modelCntx);
}

PageGeneralChatPage::~PageGeneralChatPage()
{
    delete ui;
    delete _pageContext;
}

void PageGeneralChatPage::synchronizeClient(oaic::Manager *client)
{
//    connect(ui->chatWidget, &ChatWidget::sendMessage, client->chat(), &oaic::Chat::onSingleMessageSent);
    connect(ui->chatWidget, &ChatWidget::sendCurrentSessionMessages, this, &PageGeneralChatPage::onUserMessage);

    // TODO: do not connect to to oaic::Chat but call SessionManager functions
    connect(this, &PageGeneralChatPage::sendSessionMessages, client->chat(), &oaic::Chat::onSessionMessagesSent);

    ui->chatWidget->setClient(client);
    ui->chatConfigWidget->synchronizeClient(client);
}

void PageGeneralChatPage::changeCurrentToolPage(int index)
{
    ui->tabWidget->setCurrentIndex(index);
}

void PageGeneralChatPage::onUserMessage(const oaic::ModelContext &modelCntx)
{
    auto currentSessionId = _pageContext->currentSessionId();

    auto character = ui->systemMessageWidget->character();
    gSessions->addCharacter(character, currentSessionId);

    // TODO: move to ChatWidget (?)

    auto messages = gSessions->session(currentSessionId)->msgDataList();
    emit sendSessionMessages(modelCntx, messages);
}

void PageGeneralChatPage::onCurrentSessionChange()
{
//    _currentSessionId = sessionId;
}

