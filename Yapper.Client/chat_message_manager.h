#pragma once
using namespace System;
using namespace System::Collections::Generic;

namespace Yapper::Client::Manager {
	ref class ChatMessageManager {
	private:
		static System::Collections::Generic::Queue<String^>^ queue = gcnew System::Collections::Generic::Queue<String^>();
	public:
		static void Enqueue(String^ message);
		static String^ Dequeue();
		static int GetLength();
		static void Clear();
	};
}