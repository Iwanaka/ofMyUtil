#pragma once
#include <string>

//--------------------------------------------------------------
// ofxMyUtil String
//--------------------------------------------------------------

namespace ofxMyUtil {
	namespace String {

		const char Charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";

		std::string WString_to_String(std::wstring wstr);
		std::wstring String_to_WString(std::string str);
		std::string StringToUtf8(std::string msg);


		std::string ToSha256(std::string str);
		// 0詰め
		std::string AdjustNo(const unsigned int& currentNo, const unsigned int& digit);
		std::string GenerateRandomText(const unsigned int &length);
		std::string GenerateUUID();

		std::string GetTodayStamp();

		// ImGui用などにJsonなどからデータを読み込む際に使う
		bool LoadString2FloatArray(const std::string &str, std::string delimiter, float *pArray);
	}
}