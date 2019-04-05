#include "ofxMyUtilMedia.h"
#include <winsock2.h>

using namespace ofxMyUtil;
//--------------------------------------------------------------
// ofxMyUtil Media
//--------------------------------------------------------------
//--------------------------------------------------------------
std::string Media::getIpAddress() {

	int i;
	HOSTENT *lpHost;
	IN_ADDR inaddr;
	char szBuf[256], szIP[16];

	gethostname(szBuf, (int)sizeof(szBuf));
	//printf("HOST Name : %s\n", szBuf);

	lpHost = gethostbyname(szBuf);

	for (i = 0; lpHost->h_addr_list[i]; i++) {

		memcpy(&inaddr, lpHost->h_addr_list[i], 4);

		strcpy(szIP, inet_ntoa(inaddr));

	}

	return std::string(szIP);

}

//--------------------------------------------------------------
int Media::getIpHost() {

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