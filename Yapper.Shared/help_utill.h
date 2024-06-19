#pragma once
#include <string>
#include <filesystem>

using std::string;
using std::wstring;

namespace Yapper::Shared::Utilities {
	class HelpUtil {
	public:
		static string getCurrentDirectory();
		static string getDocumentsDirectory();
		static char* xorData(const char* input, int length, const string& key);
	};
}