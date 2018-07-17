#include "ofMyUtil.h"

//--------------------------------------------------------------
void myUtil::encodeBase64toJson(string imgPath, string jsonSavePath) {

	ofImage img(imgPath);
	stringstream ss;
	ofBuffer buf;

	if (!img.isAllocated()) {

		ofLogError() << imgPath << " load faild";
		return;

	}

	ofSaveImage(img.getPixels(), buf, OF_IMAGE_FORMAT_JPEG);
	Poco::Base64Encoder b64enc(ss);
	b64enc << buf;

	ofxJSONElement json;
	json["image"] = ss.str();
	json["selector"] = "ROLL";
	(json.save(jsonSavePath, true) ? ofLog() << jsonSavePath << " save success" : ofLogError() << jsonSavePath << "json save faild");


}

//--------------------------------------------------------------
void myUtil::bufferToJson(ofBuffer *buf, string savePath = "result.json", bool seeLog = false) {

	ofxJSONElement json;
	json.parse(buf->getText());

	if (seeLog)ofLog() << json;
	(json.save(savePath) ? ofLog() << "save seccess \"" << savePath << "\"" : ofLogError() << "save faild \"" << savePath << "\"");

}

//--------------------------------------------------------------
bool myUtil::checkExitsFile(string path, float _retryTime) {

	ofFile file(path);

	float currentTime = ofGetElapsedTimef();
	float retryTime = _retryTime;
	float meusureTime = 0.0;

	while (file.exists() || meusureTime <= retryTime) {

		meusureTime = ofGetElapsedTimef() - currentTime;

		if (file.exists()) return true;
		if (meusureTime >= retryTime) return false;

	}

	return false;

}

//--------------------------------------------------------------
string myUtil::adjustFileNo(unsigned int currentNo, unsigned int digit) {

	string No = ofToString(currentNo);

	int currentDigit = No.length();

	for (int i = currentDigit; i < digit; i++) {
		No = "0" + No;
	}

	return No;
}

//--------------------------------------------------------------
//7:通常 8:灰色 9:青 10:緑 11:水色 12:赤 13:紫 14:黄色 15:白
void myUtil::chengeConsollColor(unsigned short colorID) {

	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, colorID);

}

//--------------------------------------------------------------
string myUtil::getIpAddress() {

	int i;
	HOSTENT *lpHost;
	IN_ADDR inaddr;
	char szBuf[256], szIP[16];
	
	// ローカルマシンのホスト名を取得する
	gethostname(szBuf, (int)sizeof(szBuf));
	printf("HOST Name : %s\n", szBuf);

	// ホスト情報を取得
	lpHost = gethostbyname(szBuf);
	// IPアドレスを取得
	for (i = 0; lpHost->h_addr_list[i]; i++) {

		memcpy(&inaddr, lpHost->h_addr_list[i], 4);
		
		strcpy(szIP, inet_ntoa(inaddr));
		
	}

	return string(szIP);

}

//--------------------------------------------------------------
int myUtil::getIpHost() {

	int i;
	HOSTENT *lpHost; 			//  ホスト情報を格納する構造体
	IN_ADDR inaddr; 				// IPアドレスを格納する構造体
	char szBuf[256], szIP[16]; // ホスト名/IPアドレスを格納する配列

							   // ローカルマシンのホスト名を取得する
	gethostname(szBuf, (int)sizeof(szBuf));
	printf("HOST Name : %s\n", szBuf);

	// ホスト情報を取得
	lpHost = gethostbyname(szBuf);
	// IPアドレスを取得
	for (i = 0; lpHost->h_addr_list[i]; i++) {
		memcpy(&inaddr, lpHost->h_addr_list[i], 4);
		strcpy(szIP, inet_ntoa(inaddr));
		printf("IP Adress : %s\n", szIP);
	}

	return 0;

}