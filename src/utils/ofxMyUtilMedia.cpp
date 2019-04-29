#include "ofxMyUtilMedia.h"

#if defined( __WIN32__ ) || defined( _WIN32 )
#define WIN32
#endif

#ifdef WIN32

	#include <winsock2.h>

#else
	#include <sys/types.h>
	#include <semaphore.h>
#endif

using namespace ofxMyUtil;
//--------------------------------------------------------------
// ofxMyUtil Media
//--------------------------------------------------------------
//--------------------------------------------------------------
std::string Media::getIpAddress() {

#ifdef WIN32

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

#else

	//mac or linux
	return std::string();

#endif

}

//--------------------------------------------------------------
void Media::showIpHost() {

#ifdef WIN32

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

#else

#endif


}