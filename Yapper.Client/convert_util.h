#pragma once
#include <string>
#include <msclr/marshal_cppstd.h>

using namespace System;
using std::string;

namespace Yapper::Client::Utilities {
    ref class ConvertUtil {
    public:
        static String^ ConvertString(const string& value);
        static string ConvertString(String^ value);
    };
}
