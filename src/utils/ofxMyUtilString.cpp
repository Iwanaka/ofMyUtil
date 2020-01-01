#include "ofxMyUtilString.h"
#include <algorithm>
#include <cstdlib>
#include "ofUtils.h"

//--------------------------------------------------------------
// String
//--------------------------------------------------------------

using namespace std;
using namespace ofxMyUtil;
//--------------------------------------------------------------
string String::adjustFileNo(const unsigned int& currentNo, const unsigned int& digit) {

	string No = ofToString(currentNo);

	for (int i = No.length(); i < digit; i++) {
		No = "0" + No;
	}

	return No;
}

//--------------------------------------------------------------
string String::generateRandomText(const unsigned int &length) {

	auto randchar = []() -> char
	{
		const size_t max_index = (sizeof(charset) - 1);

		return charset[rand() % max_index];

	};
	string str(length, 0);
	generate_n(str.begin(), length, randchar);

	return str;

}

//--------------------------------------------------------------
string String::generateUUID() {

	std::string uuid = std::string(36, ' ');
	int rnd = 0, r = 0;

	uuid[8] = '-', uuid[13] = '-', uuid[18] = '-', uuid[23] = '-';
	uuid[14] = '4';

	for (int i = 0; i < 36; i++) {
		if (i != 8 && i != 13 && i != 18 && i != 14 && i != 23) {
			if (rnd <= 0x02) {
				rnd = 0x2000000 + (std::rand() * 0x1000000) | 0;
			}
			rnd >>= 4;
			uuid[i] = charset[(i == 19) ? ((rnd & 0xf) & 0x3) | 0x8 : rnd & 0xf];
		}
	}

	return uuid;

}

//--------------------------------------------------------------
bool String::loadString2FloatArray(const string &str, std::string delimiter, float *pArray) {

	vector<string> _temp = ofSplitString(str, delimiter);
	size_t size = _ARRAYSIZE(pArray) + 1;
	if (_temp.size() != size) return 0;

	try
	{
		for (int i = 0; i < size; i++) {
			pArray[i] = ofToFloat(_temp[i]);
		}
		return 1;
	}
	catch (const std::exception&)
	{
		return 0;
	}
	return 1;

}
