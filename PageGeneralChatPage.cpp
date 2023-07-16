#include "PageGeneralChatPage.h"
#include "ui_PageGeneralChatPage.h"

#include "chat/SessionManager.h"


PageGeneralChatPage::PageGeneralChatPage(QWidget *parent) :
    PageWidget(parent),
    ui(new Ui::PageGeneralChatPage)
{
    static int pageNumber = 1;

    ui->setupUi(this);

    // good place to create a session
    auto currentSessionId = gSessions->createSession(pageNumber); // TODO: emits a signal when _pageContex doesn't exist
    _pageContext = new PageContext(pageNumber, currentSessionId);
    pageNumber++;

    ui->chatWidget->setPageContext(_pageContext);
    ui->chatSessionWidget->setPageContext(_pageContext);
    ui->systemMessageWidget->setPageContext(_pageContext);
    ui->chatConfigWidget->setPageContext(_pageContext);

    // TODO: connect with PageContext
    // change current session in chatSessionWidget
    connect(ui->chatSessionWidget, &ChatSessionWidget::currentSessionChanged, ui->chatWidget, &ChatWidget::onCurrentSessionChange);
    connect(ui->chatSessionWidget, &ChatSessionWidget::currentSessionChanged, ui->systemMessageWidget, &SystemMessageWidget::onCurrentSessionChange);
    connect(ui->chatSessionWidget, &ChatSessionWidget::currentSessionChanged, ui->chatConfigWidget, &ChatConfigWidget::onCurrentSessionChange);

    // connection between widgets
    connect(ui->chatWidget, &ChatWidget::renameSession, ui->chatSessionWidget, &ChatSessionWidget::onRenameSession);

    // TODO: implement & connect ChatSessionWidget signals

    // TODO: connect to change _currentSessionId of this

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

