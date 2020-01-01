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

		//ImGui�p�Ȃǂ�Json�Ȃǂ���f�[�^��ǂݍ��ލۂɎg��
		bool loadString2FloatArray(const std::string &str, std::string delimiter, float *pArray);
	}
}