#ifndef ASSISTANTROLE_H
#define ASSISTANTROLE_H

#include <QString>

namespace chat {

class AssistantRole
{
public:
    AssistantRole();

    QString name() const;
    void setName(const QString &newName);

    QString message() const;
    void setMessage(const QString &newMessage);

private:
    QString _name;
    QString _message;
};

} // namespace chat


#endif // ASSISTANTROLE_H
