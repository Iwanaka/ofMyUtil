#include "ofxMyUtilString.h"
#include <algorithm>
#include "ofUtils.h"

//--------------------------------------------------------------
// String
//--------------------------------------------------------------

using namespace ofxMyUtil;
//--------------------------------------------------------------
std::string String::adjustFileNo(const unsigned int& currentNo, const unsigned int& digit) {

	std::string No = ofToString(currentNo);

	for (int i = No.length(); i < digit; i++) {
		No = "0" + No;
	}

	return No;
}

//--------------------------------------------------------------
std::string String::generateRandomText(const unsigned int &length) {

	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);

		return charset[rand() % max_index];

	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);

	return str;

}