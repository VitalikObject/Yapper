#include "message_handler_base.h"

using namespace Yapper::Shared::Handler;

MessageHandlerBase::MessageHandlerBase() {

}

void MessageHandlerBase::registerHandler(int messageType, HandlerFunc handler) {
    handlers[messageType] = handler;
}

bool MessageHandlerBase::handleMessage(PiranhaMessage* message) {
    int messageType = message->getMessageType();
    auto it = handlers.find(messageType);
    if (it != handlers.end()) {
        it->second(message);
        return true;
    }
    return false;
}