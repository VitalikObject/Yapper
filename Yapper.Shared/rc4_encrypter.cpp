#include "rc4_encrypter.h"

using namespace Yapper::Shared::Cryptography;

RC4Encrypter::RC4Encrypter(const string& baseKey, const string& nonce) : StreamEncrypter() {
	string strKey = baseKey + nonce;

	x = 0;
	y = 0;

	for (int i = 0; i < 256; ++i) {
		key[i] = (unsigned char)i;
	}

	for (int i = 0, j = 0; i < 256; ++i) {
		j = (unsigned char)(j + key[i] + strKey[i % strKey.length()]);

		unsigned char tempSwap = key[i];
		key[i] = key[j];
		key[j] = tempSwap;
	}

	for (int i = 0; i < strKey.length(); ++i) {
		x += 1;
		y += key[x];

		unsigned char tempSwap = key[y];
		key[y] = key[x];
		key[x] = tempSwap;
	}
}

RC4Encrypter::~RC4Encrypter() {

}

int RC4Encrypter::decrypt(char* input, char* output, int length) {
	return encrypt(input, output, length);
}

int RC4Encrypter::encrypt(char* input, char* output, int length) {
	for (int i = 0; i < length; ++i) {
		x += 1;
		y += key[x];

		unsigned char tempSwap = key[y];

		key[y] = key[x];
		key[x] = tempSwap;

		output[i] = (char)(input[i] ^ key[(unsigned char)(key[x] + key[y])]);
	}

	return 0;
}