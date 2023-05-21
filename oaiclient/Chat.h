#ifndef OAIC_CHAT_H
#define OAIC_CHAT_H

#include "Component.h"

namespace oaic {

class Chat : public Component
{
public:
    explicit Chat(Auth *auth, Manager *parent);

    void sendSimpleChatRequest(const QString &model, const QString &content, bool stream) const;
};

} // namespace oaic

#endif // OAIC_CHAT_H
