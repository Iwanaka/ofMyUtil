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
//7:�ʏ� 8:�D�F 9:�� 10:�� 11:���F 12:�� 13:�� 14:���F 15:��
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
	
	// ���[�J���}�V���̃z�X�g�����擾����
	gethostname(szBuf, (int)sizeof(szBuf));
	printf("HOST Name : %s\n", szBuf);

	// �z�X�g�����擾
	lpHost = gethostbyname(szBuf);
	// IP�A�h���X���擾
	for (i = 0; lpHost->h_addr_list[i]; i++) {

		memcpy(&inaddr, lpHost->h_addr_list[i], 4);
		
		strcpy(szIP, inet_ntoa(inaddr));
		
	}

	return string(szIP);

}

//--------------------------------------------------------------
int myUtil::getIpHost() {

	int i;
	HOSTENT *lpHost; 			//  �z�X�g�����i�[����\����
	IN_ADDR inaddr; 				// IP�A�h���X���i�[����\����
	char szBuf[256], szIP[16]; // �z�X�g��/IP�A�h���X���i�[����z��

							   // ���[�J���}�V���̃z�X�g�����擾����
	gethostname(szBuf, (int)sizeof(szBuf));
	printf("HOST Name : %s\n", szBuf);

	// �z�X�g�����擾
	lpHost = gethostbyname(szBuf);
	// IP�A�h���X���擾
	for (i = 0; lpHost->h_addr_list[i]; i++) {
		memcpy(&inaddr, lpHost->h_addr_list[i], 4);
		strcpy(szIP, inet_ntoa(inaddr));
		printf("IP Adress : %s\n", szIP);
	}

	return 0;

}