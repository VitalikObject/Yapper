#include "help_utill.h"


using namespace Yapper::Shared::Utilities;

string HelpUtil::getCurrentDirectory() {
    std::filesystem::path current_dir = std::filesystem::current_path();

    return current_dir.string();
}

string HelpUtil::getDocumentsDirectory() {
    char* homeDir;
    size_t requiredSize;
    errno_t err = _dupenv_s(&homeDir, &requiredSize, "USERPROFILE");
    if (err != 0 || homeDir == nullptr) {
        return getCurrentDirectory();
    }
    string documentsDir = homeDir;
    free(homeDir);
    return documentsDir + "\\Documents\\";
}

char* HelpUtil::xorData(const char* input, int length, const string& key) {
    char* output = new char[length];
    for (int i = 0; i < length; ++i) {
        output[i] = input[i] ^ key[i % key.length()];
    }

    return output;
}