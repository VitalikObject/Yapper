#include "chat_message_manager.h"

using namespace Yapper::Client::Manager;

void ChatMessageManager::Enqueue(String^ message) {
	queue->Enqueue(message);
}

String^ ChatMessageManager::Dequeue() {
	return queue->Count > 0 ? queue->Dequeue() : "";
}

int ChatMessageManager::GetLength() {
	return queue->Count;
}

void ChatMessageManager::Clear() {
	queue->Clear();
}