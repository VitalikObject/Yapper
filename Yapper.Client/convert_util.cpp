#include "convert_util.h"

using namespace Yapper::Client::Utilities;

String^ ConvertUtil::ConvertString(const string& value) {
    return msclr::interop::marshal_as<String^>(value);
}

string ConvertUtil::ConvertString(String^ value) {
    return msclr::interop::marshal_as<string>(value);
}