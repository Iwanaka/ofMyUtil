#pragma once

#include <winsock2.h>
#include "ofMain.h"

//#include "ofxJSON.h"
#include "ofxImGui.h"

using namespace std;

namespace ofxMyUtil {

	//配列のサイズを確認する
	#define IWAX_ARRAY_SIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))

	//--------------------------------------------------------------
	namespace File {

		bool checkExitsFile(const string& path,const float& _retryTime);
		bool createDirectory(const string& path);
		bool createFile(const string& path, const stringstream& Args);
		void bufferToJsonFile(const ofBuffer &buf, string savePath = "res.json", bool pretty = true);
		void bufferToJsonFile(const string &buf, string savePath = "res.json", bool pretty = true);
		bool saveImageAs(const ofFbo &fbo, string savePath, ofImageType type);
		bool saveRandomText(const string &path, const unsigned int &length,const unsigned int &size);

		class ThreadSaveImageQueue : public ofThread {
		public:
			ThreadSaveImageQueue();
			~ThreadSaveImageQueue();
			void run();
			void stop();
			void threadedFunction();
			void addQueue(const ofPixels &pix, const string &savePath);
		private:
			typedef struct {
				string savePath;
				ofPixels pix;
			}QueuePix;
			queue< QueuePix> q;
		};

	}

	//--------------------------------------------------------------
	namespace String {

		std::string adjustFileNo(const unsigned int& currentNo, const unsigned int& digit);
		std::string generateRandomText(const unsigned int &length);

	}


	//--------------------------------------------------------------
	namespace Event {
		bool rectButtonClickDetect(ofRectangle rect, int mouseX, int mouseY);
		bool rectButtonClickDetect(int rect_x, int rect_y, int rect_w, int rect_h, int mouseX, int mouseY);
		bool circleButtonClickDetect(int circle_x, int circle_y, float radius, int mouseX, int mouseY);
	}
	

	//--------------------------------------------------------------
	namespace Console {
		void chengeConsollColor(unsigned short colorID);
		void hideConsole();
	}


	//--------------------------------------------------------------
	namespace IO {
		std::string getIpAddress();
		int getIpHost();
	}


	//--------------------------------------------------------------
	namespace _ImGui {
		
		void BasicInfos();
		void BasicInfos(const std::string &name, ImGuiWindowFlags flags = 0);
		
		void drawFbo(
			const ofFbo &fbo, 
			GLuint &sourceID, 
			string name = "fbo", 
			ImGuiWindowFlags flag = 0);
		void drawImg(
			const ofImage &img, 
			GLuint &sourceID, 
			float scale = 1.0f, 
			string name = "image", 
			ImGuiWindowFlags flag = 0);
		//静的な関数ならこれで呼べるけどtemplateかfunctionでやったほうが良さそう
		void drawImgAsButton(
			const ofImage &img, 
			GLuint &sourceID, 
			void (*fn)(), 
			float scale = 1.0f, 
			string name = "image button", 
			ImGuiWindowFlags flag = 0);
		void drawImgAsButton(
			const ofImage &img,
			GLuint &sourceID,
			function<void()> fn,
			float scale = 1.0f,
			string name = "image button",
			ImGuiWindowFlags flag = 0);



		class ImGuiWindowFlagsSettings {
		public:
			ImGuiWindowFlagsSettings() :
				no_titlebar(false),
				no_border(false),
				no_resize(false),
				no_move(false),
				no_scrollbar(false),
				no_collapse(false),
				no_menu(false),
				flags(0) {}
			~ImGuiWindowFlagsSettings() {}
			void loadSettings(const string &path);
			void saveSettings(const string &path);
			ImGuiWindowFlags getImGuiWindowFlags();
			void ImGui(const string &name);
		
		private:
			ImGuiWindowFlags flags;
			bool no_titlebar, no_border, no_resize, no_move, no_scrollbar, no_collapse, no_menu;
		};


		class ImGuiWindowSetCondSettings {
		public:
			ImGuiWindowSetCondSettings() :
				value((int)ImGuiSetCond_::ImGuiSetCond_Appearing) {};
			~ImGuiWindowSetCondSettings() {};
			void changeState(const ImGuiSetCond_ &state);
			ImGuiSetCond_ getSetCondState();
			void ImGui(const string &name);
		private:
			int value;
		};


	}


	//--------------------------------------------------------------
	namespace GL {

		GLuint loadTextureImage2D(unsigned char * pix, int width, int height);


		class CircleGuide
		{
		public:
			CircleGuide();
			CircleGuide(float px, float py, float radius);
			CircleGuide(const glm::vec2& pos, float radius);
			CircleGuide(const CircleGuide& circle);
			~CircleGuide();

			void set(float px, float py, float radius);
			void set(const glm::vec2 &p, float radius);
			void set(const CircleGuide &circle);

			void setX(float px);
			void setY(float py);
			void setRadius(float radius);

			void setPosition(float px, float py);
			void setPosition(const glm::vec2 &p);

			float getX();
			float getY();
			glm::vec2 getPos();
			float getRadius();


			glm::vec2 p;
			float radius;

		private:

		};

	}


	//--------------------------------------------------------------
	namespace SP {
		bool loadArray2Float(const string &str, float *Array2);
		bool loadArray3Float(const string &str, float *Array3);


		template<typename T>
		T isNaNCheck(T val, T defaultVal);

	}



};
