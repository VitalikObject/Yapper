#pragma once
#include "string"

using std::string;

namespace Yapper::Shared::Cryptography {
	class StreamEncrypter {
	public:
		~StreamEncrypter();
		virtual int decrypt(char* input, char* output, int length);
		virtual int encrypt(char* input, char* output, int length);
		virtual int getOverheadEncryption();
	};
}