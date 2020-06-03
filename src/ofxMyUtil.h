#pragma once
//--------------------------
// classes
#include "ofCircleInfo.h"
#include "ofImGuiUtil.h"
#include "ofScaleable.h"
#include "ofThreadSaveImage.h"


//--------------------------
// utils
#include "ofxMyUtilConsole.h"
#include "ofxMyUtilEvent.h"
#include "ofxMyUtilGL.h"
#include "ofxMyUtilIO.h"
#include "ofxMyUtilMedia.h"
#include "ofxMyUtilString.h"


namespace ofxMyUtil {

	//配列のサイズを確認する
	//#define IWAX_GET_ARRAY_SIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))
	//#define GET_ARRAY_SIZE(a)   (sizeof(a)/sizeof(a[0]))
	//これを使いましょう 機能は一緒
	//_ARRAYSIZE

	//not a number check
	/*template<typename T>
	T isNaNCheck(T val, T defaultVal);
	template<typename T>
	T ofxMyUtil::SP::isNaNCheck(T val, T defaultVal) {
		if (isnan(val)) return defaultVal;
		return val;
	}
	template<>
	float ofxMyUtil::SP::isNaNCheck(float val, float defaultVal) {
		if (isnan(val)) return defaultVal;
		return val;
	}*/

};
