#pragma once
#include <string>

//--------------------------------------------------------------
// ofxMyUtil String
//--------------------------------------------------------------

namespace ofxMyUtil {
	namespace String {
		std::string adjustFileNo(const unsigned int& currentNo, const unsigned int& digit);
		std::string generateRandomText(const unsigned int &length);
	}
}