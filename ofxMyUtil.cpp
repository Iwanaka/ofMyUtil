#include "ofxMyUtil.h"

using namespace std;

//--------------------------------------------------------------
void ofxMyUtil::File::bufferToJsonFile(const ofBuffer &buf,const string &savePath = "result.json",const bool& console = false) {

	ofxJSONElement json;
	json.parse(buf.getText());

	if (console) cout << json << endl;

	if (json.save(savePath)) cout << "save seccess \"" << savePath << "\"" << endl;
	else cout << "save faild \"" << savePath << "\"" << endl;;

}

//--------------------------------------------------------------
bool ofxMyUtil::File::checkExitsFile(const string& path,const float& _retryTime) {

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
string ofxMyUtil::File::adjustFileNo(const unsigned int& currentNo,const unsigned int& digit) {

	string No = ofToString(currentNo);

	for (int i = No.length(); i < digit; i++) {
		No = "0" + No;
	}

	return No;
}

//--------------------------------------------------------------
//7:normal 8:gray 9:blue 10:green 11:aqua 12:red 13:purple 14:yellow 15:white
void ofxMyUtil::console::chengeConsollColor(unsigned short colorID) {

	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, colorID);

}

//--------------------------------------------------------------
string ofxMyUtil::IO::getIpAddress() {

	int i;
	HOSTENT *lpHost;
	IN_ADDR inaddr;
	char szBuf[256], szIP[16];
	
	gethostname(szBuf, (int)sizeof(szBuf));
	printf("HOST Name : %s\n", szBuf);

	lpHost = gethostbyname(szBuf);
	
	for (i = 0; lpHost->h_addr_list[i]; i++) {

		memcpy(&inaddr, lpHost->h_addr_list[i], 4);
		
		strcpy(szIP, inet_ntoa(inaddr));
		
	}

	return string(szIP);

}

//--------------------------------------------------------------
int ofxMyUtil::IO::getIpHost() {

	int i;
	HOSTENT *lpHost;
	IN_ADDR inaddr;
	char szBuf[256], szIP[16];

	gethostname(szBuf, (int)sizeof(szBuf));
	printf("HOST Name : %s\n", szBuf);

	lpHost = gethostbyname(szBuf);

	for (i = 0; lpHost->h_addr_list[i]; i++) {
		memcpy(&inaddr, lpHost->h_addr_list[i], 4);
		strcpy(szIP, inet_ntoa(inaddr));
		printf("IP Adress : %s\n", szIP);
	}

	return 0;

}