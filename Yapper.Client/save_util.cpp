#include "save_util.h"

using namespace Yapper::Client::Utilities;

SaveUtil::SaveUtil() {
	this->isNameSet = false;
	this->name = "Bulya";
	this->documentsPath = ConvertUtil::ConvertString(HelpUtil::getDocumentsDirectory()) + "Yapper\\";
}

SaveUtil::SaveUtil(bool isNameSet, String^ name) {
	this->isNameSet = isNameSet;
	this->name = name;
	this->documentsPath = ConvertUtil::ConvertString(HelpUtil::getDocumentsDirectory()) + "Yapper\\";
}

SaveUtil::~SaveUtil() {

}

Void SaveUtil::SaveData() {
	ByteStream byteStream;

	byteStream.writeBoolean(isNameSet);
	byteStream.writeString(ConvertUtil::ConvertString(name));

	char* decryptedData = byteStream.getByteArray();
	int dataLength = byteStream.getLength();

	char* encryptedData = HelpUtil::xorData(decryptedData, dataLength, ConvertUtil::ConvertString(key));

	string documentsPathStr = ConvertUtil::ConvertString(documentsPath);
	string filePath = documentsPathStr + ConvertUtil::ConvertString(saveFileName);

	if (!std::filesystem::exists(documentsPathStr)) {
		std::filesystem::create_directory(documentsPathStr);
	}

	std::ofstream outFile(filePath);

	outFile.write(encryptedData, dataLength);
	outFile.close();

	delete[] decryptedData;
	delete[] encryptedData;
}

Void SaveUtil::LoadData() {
	string documentsPathStr = ConvertUtil::ConvertString(documentsPath);
	string filePath = documentsPathStr + ConvertUtil::ConvertString(saveFileName);

	std::ifstream inFile(filePath, std::ios::binary); 

	if (!inFile) {
		SaveData();
		return;
	}

	inFile.seekg(0, std::ios::end);
	std::streamsize dataLength = inFile.tellg();
	inFile.seekg(0, std::ios::beg);

	char* encryptedData = new char[dataLength];

	inFile.read(encryptedData, dataLength);

	int dataLengthInt = static_cast<int>(dataLength);

	char* decryptedData = HelpUtil::xorData(encryptedData, dataLengthInt, ConvertUtil::ConvertString(key));

	ByteStream byteStream;
	byteStream.setByteArray(decryptedData, dataLengthInt);

	this->isNameSet = byteStream.readBoolean();
	if (isNameSet) this->name = ConvertUtil::ConvertString(byteStream.readString());

	inFile.close();

	delete[] encryptedData;
	delete[] decryptedData;
}

String^ SaveUtil::getName() {
	return name;
}

void SaveUtil::setName(String^ name) {
	this->name = name;
}

bool SaveUtil::getIsNameSet() {
	return isNameSet;
}

void SaveUtil::setIsNameSet(bool isNameSet) {
	this->isNameSet = isNameSet;
}
