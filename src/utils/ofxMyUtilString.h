#pragma once
#include <string>

//--------------------------------------------------------------
// ofxMyUtil String
//--------------------------------------------------------------

namespace ofxMyUtil {
	namespace String {

		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";

		std::string adjustFileNo(const unsigned int& currentNo, const unsigned int& digit);
		std::string generateRandomText(const unsigned int &length);
		std::string generateUUID();

		//ImGui用などにJsonなどからデータを読み込む際に使う
		bool loadString2FloatArray(const std::string &str, std::string delimiter, float *pArray);
	}
}