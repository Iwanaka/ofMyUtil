#pragma once
#include "AbsCommunicationManager.h"
#include "ofxNetwork.h"
#include "ofUtils.h"

//égÇ§Ç»äÎåØ Ç»ÇÒÇ©è„éËÇ≠ìÆÇ©Ç»Ç¢éûÇ™ëΩÇ¢
namespace ofxMyUtil {

	class TcpClientManager : public AbsCommunicationManager
	{
	public:

		TcpClientManager() {}
		~TcpClientManager() { stop(); }

		//--------------------------------------------------------------
		void setup(std::shared_ptr<ofxTCPClient> tcp) {
			this->tcp = tcp;
		}

		//--------------------------------------------------------------
		void start(std::string ip, int port, std::string delimiter = "\n", bool autoRedirect = false) {
			
			if (!nullCheck()) return;

			if (isThreadRunning()) {
				mLogGui.addText("[Warning] : You tryed start thread but thread has already running.");
				return;
			}

			this->ip = ip;
			this->port = port;
			this->autoRedirect = autoRedirect;
			this->delimiter = delimiter;

			startThread();
		}

		//--------------------------------------------------------------
		void stop() {
			if (isThreadRunning()) {
				stopThread();
				waitForThread();
			}

			if (!nullCheck()) return;
			if (tcp->isConnected()) tcp->close();
		}

		//--------------------------------------------------------------
		void sendMsg(std::string msg) {
			
			if (!nullCheck()) return;
			if (tcp->isConnected()) {
				mLogGui.addText("[Send] : " + msg);
				tcp->send(msg);
			}
			else {
				mLogGui.addText("[Warning] : You tryed to send messages but now is not connecting to server.");
			}
		}

		//--------------------------------------------------------------
		void addProcessInThreadedFunction() override {

			try
			{
				if (tcp->isConnected()) {

					//string str = tcp.receive();
					//string str = tcp.receiveRaw();
					//char rBuf[4];
					//int res = tcp.receiveRawBytes(rBuf, 4);
					//int res = tcp.peekReceiveRawBytes(rBuf, 4);

					std::string str = tcp->receive();
					if (0 < str.length()) {
						mLogGui.addText("[Recieve] " + str);
						ofNotifyEvent(onReceiveNewMsg, str, this);
					}
				}
				else {

					deltaTime = ofGetElapsedTimeMillis() - connectTime;
					if (deltaTime > retryTime && autoRedirect) {

						mLogGui.addText("[Notice] : try connect to server...");

						ofxTCPSettings settings(ip, port);
						settings.messageDelimiter = delimiter;
						tcp->setup(settings);

						if (tcp->isConnected()) {
							mLogGui.addText("[Notice] : Success connect to server.");
							ofNotifyEvent(onConnectResult, true, this);
						}
						else {
							mLogGui.addText("[ERROR] : Failed connect to server.");
							ofNotifyEvent(onConnectResult, false, this);
						}

						connectTime = ofGetElapsedTimeMillis();
					}
				}
			}
			catch (const std::exception&)
			{
				mLogGui.addText("[ERROR] : Happend unknown error");
			}
		}

		//--------------------------------------------------------------
		ofEvent<const std::string> onReceiveNewMsg;
		ofEvent<const bool> onConnectResult;

	private:

		//--------------------------------------------------------------
		bool nullCheck() {

			if (tcp == nullptr) {
				mLogGui.addText("[Warning] : You tryed start thread but tcp class is null");
				return 0;
			}
			else {
				return 1;
			}

		}

		//--------------------------------------------------------------
		void addPropertyImGui() override {

			if (ImGui::CollapsingHeader("Settings Data")) {
				ImGui::Text("Tcp server ip : %s, port : %i", ip.c_str(), port);
				if (nullCheck()) ImGui::Text("Tcp server isConnect : %s", std::string(tcp->isConnected() ? "connected" : "not connected").c_str());
				ImGui::Checkbox("Tcp connect auto redirect", &autoRedirect);
				ImGui::InputInt("retry Time", &retryTime, 100, 100000);
			}

		}

		std::shared_ptr<ofxTCPClient> tcp;
		std::string ip = "127.0.0.1";
		int port = 8080;
		std::string delimiter = "\n";
		bool autoRedirect = false;
		uint64_t deltaTime = 0, connectTime = 0;
		int retryTime = 5000;

	};
}