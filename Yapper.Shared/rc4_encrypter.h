#pragma once
#include "stream_encrypter.h"

namespace Yapper::Shared::Cryptography {
	class RC4Encrypter : public StreamEncrypter {
	private:
		unsigned char key[256];
		unsigned char x;
		unsigned char y;
	public:
		RC4Encrypter(const string& baseKey, const string& nonce);
		~RC4Encrypter();
		int decrypt(char* input, char* output, int length);
		int encrypt(char* input, char* output, int length);
	};
}