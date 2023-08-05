/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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

    auto modelName = settings.value("model/name", _modelCntx.DEFAULT_MODEL).toString();
    _modelCntx.setModelName(modelName);

    // read other model settings
    {
        auto temperature = settings.value("model/temperature", _modelCntx.DEFAULT_TEMPERATURE).toDouble();
        _modelCntx.setTemperature(temperature);
    }

    {
        auto maxTokens = settings.value("model/maxTokens", _modelCntx.DEFAULT_MAX_TOKENS).toInt();
        _modelCntx.setMaxTokens(maxTokens);
    }

    {
        auto topP = settings.value("model/topP", _modelCntx.DEFAULT_TOP_P).toDouble();
        _modelCntx.setTopP(topP);
    }

    {
        auto frequencyPenalty = settings.value("model/frequencyPenalty", _modelCntx.DEFAULT_FREQUENCY_PENALTY).toDouble();
        _modelCntx.setFrequencyPenalty(frequencyPenalty);
    }

    {
        auto presencePenalty = settings.value("model/presencePenalty", _modelCntx.DEFAULT_PRESENCE_PENALTY).toDouble();
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

