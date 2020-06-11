#include "ofxMyUtilString.h"

#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <locale>
#include <codecvt>

#include "openssl/sha.h"
#include "ofUtils.h"

//--------------------------------------------------------------
// String
//--------------------------------------------------------------

using namespace std;
using namespace ofxMyUtil;

std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> strconverter;

//--------------------------------------------------------------
string String::WString_to_String(std::wstring wstr) {
	return strconverter.to_bytes(wstr);
}
//--------------------------------------------------------------
wstring String::String_to_WString(std::string str) {
	return strconverter.from_bytes(str);
}

//--------------------------------------------------------------
std::string String::ToSha256(std::string str) {

	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, str.c_str(), str.length());
	SHA256_Final(hash, &sha256);

	string output = "";
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		output += ofToHex(hash[i]);
	}
	return output;

}

//--------------------------------------------------------------
string String::AdjustNo(const unsigned int& currentNo, const unsigned int& digit) 
{
	string No = ofToString(currentNo);
	for (int i = No.length(); i < digit; i++) 
	{
		No = "0" + No;
	}
	return No;
}

//--------------------------------------------------------------
string String::GenerateRandomText(const unsigned int &length) {

	auto randchar = []() -> char
	{
		const size_t max_index = (sizeof(Charset) - 1);
		return Charset[rand() % max_index];
	};
	string str(length, 0);
	generate_n(str.begin(), length, randchar);

	return str;
}

//--------------------------------------------------------------
string String::GenerateUUID() 
{
	std::string uuid = std::string(36, ' ');
	int rnd = 0, r = 0;

	uuid[8] = '-', uuid[13] = '-', uuid[18] = '-', uuid[23] = '-';
	uuid[14] = '4';

	for (int i = 0; i < 36; i++) 
	{
		if (i != 8 && i != 13 && i != 18 && i != 14 && i != 23) 
		{
			if (rnd <= 0x02) 
			{
				rnd = 0x2000000 + (std::rand() * 0x1000000) | 0;
			}
			rnd >>= 4;
			uuid[i] = Charset[(i == 19) ? ((rnd & 0xf) & 0x3) | 0x8 : rnd & 0xf];
		}
	}
	return uuid;
}

//--------------------------------------------------------------
bool String::LoadString2FloatArray(const string &str, std::string delimiter, float *pArray) 
{
	vector<string> _temp = ofSplitString(str, delimiter);
	size_t size = _ARRAYSIZE(pArray) + 1;
	if (_temp.size() != size) return 0;
	try
	{
		for (int i = 0; i < size; i++) 
		{
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
