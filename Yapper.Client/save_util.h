#pragma once
#include <fstream>
#include "convert_util.h"
#include "../Yapper.Shared/logic_long.h"
#include "../Yapper.Shared/byte_stream.h"
#include "../Yapper.Shared/help_utill.h"

using namespace System;
using namespace Yapper::Shared::Math;
using namespace Yapper::Shared::Math;
using namespace Yapper::Shared::Utilities;

namespace Yapper::Client::Utilities {
	ref class SaveUtil {
	private:
		bool isNameSet = false;
		String^ name, ^ documentsPath;
		literal String^ key = "ejpruutklghjlsdasvbjwgykwyevyrlowxsmbb";
		literal String^ saveFileName = "save.dat";
	public:
		SaveUtil();
		SaveUtil(bool isNameSet, String^ name);
		~SaveUtil();
		Void SaveData();
		Void LoadData();
		String^ getName();
		void setName(String^ name);
		bool getIsNameSet();
		void setIsNameSet(bool isNameSet);
	};
}