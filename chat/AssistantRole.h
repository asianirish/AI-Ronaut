#ifndef ASSISTANTROLE_H
#define ASSISTANTROLE_H

#include <oaic/MsgData.h>

#include <QString>

namespace chat {

class AssistantRole
{
public:
    AssistantRole();

    AssistantRole(const QString &name, const QString &message, bool useNameInMessage = true);

    QString name() const;
    void setName(const QString &newName);

    QString message() const;
    void setMessage(const QString &newMessage);

    bool useNameInMessage() const;
    void setUseNameInMessage(bool newUseNameInMessage);

    QString fullMessage() const;

    oaic::MsgData msgData() const;

private:
    QString _name;
    QString _message;
    bool _useNameInMessage;
};

} // namespace chat


#endif // ASSISTANTROLE_H
