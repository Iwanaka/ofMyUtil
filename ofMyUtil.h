#pragma once
#include "ofMain.h"
#include "ofxJSON.h"
#include "Poco\Base64Decoder.h"
#include "Poco\Base64Encoder.h"
#include <winsock2.h>

namespace myUtil {

	bool checkExitsFile(string path, float _retryTime);
	void bufferToJson(ofBuffer *buf, string savePath, bool seeLog);
	void encodeBase64toJson(string imgPath, string jsonSavePath);
	string adjustFileNo(unsigned int currentNo,unsigned int digit);
	void chengeConsollColor(unsigned short colorID);

	string getIpAddress();
	int getIpHost();

};
