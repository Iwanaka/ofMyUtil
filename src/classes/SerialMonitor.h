#pragma once
#include "AbsCommunicationManager.h"
#include "ofSerial.h"
#include "ofUtils.h"

namespace ofxMyUtil {

	class SerialMonitor : public AbsCommunicationManager
	{
	public:

		SerialMonitor() {}
		~SerialMonitor() { stop(); }

		//--------------------------------------------------------------
		void setup(std::shared_ptr<ofSerial> serial) {
			this->serial = serial;
			deviceInfos = serial->getDeviceList();
		}

		//--------------------------------------------------------------
		void start(std::string COM, int baudrate, bool autoRedirect = false) {

			if (!nullCheck()) return;

			if (isThreadRunning()) {
				_log.addText("[Warning] : You tryed start thread but thread has already running.");
				return;
			}

			this->com = COM;
			this->baudRate = baudrate;
			this->autoRedirect = autoRedirect;

			serial->setup(com, baudRate);
			startThread();
		}

		//--------------------------------------------------------------
		void stop() {
			if (isThreadRunning()) {
				stopThread();
				waitForThread();
			}
			if (!nullCheck()) return;
			if (serial->isInitialized()) serial->close();
		}

		//--------------------------------------------------------------
		void sendMsg(std::string msg) {

			if (!nullCheck()) return;
			if (serial->isInitialized()) {

				_log.addText("[Send] : " + msg);
				//serial->writeBytes(msg.c_str(), msg.length());

				unsigned char* writeBytes = (unsigned char*)msg.c_str();

				if (serial->available()) serial->flush();

				//Waring
				for (int i = 0; i < msg.size(); i++) {
					Sleep(50);
					if (!serial->writeByte(char(msg[i]))) {
						serial->close();
						break;
					}
				}

			}
			else {
				_log.addText("[Warning] : You tryed to send mmessages but now is not connecting to COM port.");
			}
		}

		//--------------------------------------------------------------
		void addProcessInThreadedFunction() override {

			try
			{

				if (serial->isInitialized()) {

					if (int size = serial->available()) {

						//ofBuffer buf;
						//serial->readBytes(buf, size);
						//_log.addText(buf.getText());
						
						std::string buf;
						for (int i = 0; i < size; i++) {
							buf += ofToString(char(serial->readByte()));
						}
						_log.addText("$ : " + buf);

						serial->flush(true, false);
					}

					//read responce	
					//bool available = false;
					//string buf = "";
					//while (serial->available())
					//{
					//	//wait for buffer, like a drain function
					//	if (!available) {
					//		sleep(100);
					//		available = true;
					//	}
					//	char byte = serial->readByte();
					//	buf += ofUTF8ToString(byte);
					//}

					//if (available) {
					//	std::vector<std::string> msgs = ofSplitString(buf, "\r");
					//	for each (auto m in msgs)
					//	{
					//		_log.addText(m);
					//	}
					//}

				}
				else {

					deltaTime = ofGetElapsedTimeMillis() - connectTime;

					if (deltaTime > retryTime && autoRedirect) {

						_log.addText("[Notice] : try connect to com port...");

						serial->setup(com, baudRate);

						if (serial->isInitialized()) {
							_log.addText("[Notice] : Success connect to " + com + ".");
							ofNotifyEvent(onConnectResult, true, this);
						}
						else {
							_log.addText("[ERROR] : Failed connect to " + com + ".");
							ofNotifyEvent(onConnectResult, false, this);
						}

						connectTime = ofGetElapsedTimeMillis();
					}
				}
			}
			catch (const std::exception&)
			{
				_log.addText("[ERROR] : Happend unknown error");
			}
		}

		//--------------------------------------------------------------
		ofEvent<const std::string> onReceiveNewMsg;
		ofEvent<const bool> onConnectResult;

	private:

		//--------------------------------------------------------------
		bool nullCheck() {

			if (serial == nullptr) {
				_log.addText("[Warning] : You tryed start thread but serial class is null");
				return 0;
			}
			else {
				return 1;
			}

		}

		//--------------------------------------------------------------
		void addPropertyImGui() override {
			ImGui::Text("Serial %s : %i", com.c_str(), baudRate);
			if (nullCheck()) ImGui::Text("Serial port isConnect : %s", std::string(serial->isInitialized() ? "connected" : "not connected").c_str());
			if (ImGui::Button("Serial Flush") && nullCheck()) serial->flush();
			if (ImGui::Button("update device info") && nullCheck()) deviceInfos = serial->getDeviceList();
			if (ImGui::Button("disconnect")) serial->close();
			if (ImGui::TreeNode("COM list")) {
				for (int i = 0; i < deviceInfos.size(); i++) {
					ImGui::Text("  id : %i", deviceInfos[i].getDeviceID());
					ImGui::Text("name : %s", deviceInfos[i].getDeviceName().c_str());
					ImGui::Text("path : %s", deviceInfos[i].getDevicePath().c_str());
					ImGui::Text("==============================");
				}
				ImGui::TreePop();
			}
			ImGui::Checkbox("Serial port connect auto redirect", &autoRedirect);
			ImGui::InputInt("retry Time", &retryTime, 100, 100000);
		}

		std::shared_ptr<ofSerial> serial;
		std::vector<ofSerialDeviceInfo> deviceInfos;
		std::string com = "COM1";
		int baudRate = 9600;
		bool autoRedirect = true;
		uint64_t deltaTime = 0, connectTime = 0;
		int retryTime = 5000;

	};
}