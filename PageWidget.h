#ifndef PAGEWIDGET_H
#define PAGEWIDGET_H


namespace oaic {
class Manager;
}

#include <QWidget>

class PageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PageWidget(QWidget *parent = nullptr);

    oaic::Manager *client() const;
    void initClient(); // TODO: use NetworkContext * as an arg

signals:

protected:
    virtual void synchronizeClient(oaic::Manager *_client) = 0;

private:
    oaic::Manager *_client;
};

#endif // PAGEWIDGET_H
