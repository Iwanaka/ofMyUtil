#pragma once
#include "AbsCommunicationManager.h"
#include "ofSerial.h"
#include "ofUtils.h"

namespace ofxMyUtil 
{

	class SerialMonitor : public AbsCommunicationManager
	{
	public:

		SerialMonitor(std::shared_ptr<ofSerial> serial)
		{
			mSerial = serial;
			mDeviceInfos = serial->getDeviceList();
		}
		~SerialMonitor() { Stop(); }

		//--------------------------------------------------------------
		void Start(std::string COM, int baudrate, bool autoRedirect = false) 
		{
			if (mSerial == nullptr) return;

			if (isThreadRunning()) 
			{
				mLogGui.AddText("[Warning] : You tried to start thread but thread has already running.");
				return;
			}

			mCOM = COM;
			mBaudRate = baudrate;
			mAutoRedirect = autoRedirect;

			mSerial->setup(mCOM, mBaudRate);
			startThread();
		}

		//--------------------------------------------------------------
		void Stop() {
			if (isThreadRunning()) 
			{
				stopThread();
				waitForThread();
			}
			if (mSerial == nullptr) return;
			if (mSerial->isInitialized()) mSerial->close();
		}

		//--------------------------------------------------------------
		void SendMsg(std::string msg) 
		{
			if (mSerial == nullptr) return;
			
			if (mSerial->isInitialized()) 
			{
				mLogGui.AddText("[Send] : " + msg);
				//serial->writeBytes(msg.c_str(), msg.length());

				unsigned char* writeBytes = (unsigned char*)msg.c_str();

				if (mSerial->available()) mSerial->flush();

				// Waring
				for (int i = 0; i < msg.size(); i++) 
				{
					if (!mSerial->writeByte(char(msg[i]))) 
					{
						mSerial->close();
						break;
					}
				}
			}
			else 
			{
				mLogGui.AddText("[Warning] : You tried to send messages but now is not connecting to COM port.");
			}
		}

		//--------------------------------------------------------------
		void addProcessInThreadedFunction() override {

			try
			{
				if (mSerial->isInitialized()) 
				{
					if (int size = mSerial->available()) 
					{
						//ofBuffer buf;
						//serial->readBytes(buf, size);
						//_log.addText(buf.getText());
						
						std::string buf;
						for (int i = 0; i < size; i++) 
						{
							buf += ofToString(char(mSerial->readByte()));
						}

						//mLogGui.addText("$ : " + buf);
						mSerial->flush(true, false);
					}
				}
				else 
				{
					mDeltaTime = ofGetElapsedTimeMillis() - mConnectTime;

					if (mDeltaTime > mRetryTime && mAutoRedirect) 
					{
						//_log.addText("[Notice] : Try to connect com port...");
						mSerial->setup(mCOM, mBaudRate);

						if (mSerial->isInitialized()) 
						{
							//_log.addText("[Notice] : Success connect to " + com + ".");
							ofNotifyEvent(onConnectResult, true, this);
						}
						else 
						{
							//_log.addText("[ERROR] : Failed connect to " + com + ".");
							ofNotifyEvent(onConnectResult, false, this);
						}
						mConnectTime = ofGetElapsedTimeMillis();
					}
				}
			}
			catch (const std::exception&)
			{
				//_log.addText("[ERROR] : Unknown error");
			}
		}

		//--------------------------------------------------------------
		ofEvent<const std::string> OnReceiveNewMsg;
		ofEvent<const bool> OnConnectResult;

	private:

		//--------------------------------------------------------------
		void addPropertyImGui() override {

			if (ImGui::CollapsingHeader("Settings Data")) {
				ImGui::Text("COM : %s, Baudrate : %i", mCOM.c_str(), mBaudRate);
				if (mSerial != nullptr) ImGui::Text("isConnected : %s", std::string(mSerial->isInitialized() ? "Connected" : "Not connected").c_str());

				ImGui::InputInt("Redirect time", &mRetryTime, 100, 100000);
				ImGui::Checkbox("Auto redirect", &mAutoRedirect);
				if (ImGui::Button("Flush", ImVec2(120, 25)) && mSerial != nullptr) mSerial->flush();
				ImGui::SameLine();
				if (ImGui::Button("Update COM", ImVec2(120, 25)) && mSerial != nullptr) mDeviceInfos = mSerial->getDeviceList();
				ImGui::SameLine();
				if (ImGui::Button("Disconnect", ImVec2(120, 25))) mSerial->close();

				if (ImGui::TreeNode("COM list")) {
					for (int i = 0; i < mDeviceInfos.size(); i++) {
						ImGui::Text("  id : %i", mDeviceInfos[i].getDeviceID());
						ImGui::Text("name : %s", mDeviceInfos[i].getDeviceName().c_str());
						ImGui::Text("path : %s", mDeviceInfos[i].getDevicePath().c_str());
						ImGui::Text("==============================");
					}
					ImGui::TreePop();
				}
			}
		}


		//--------------------------------------------------------------
		std::shared_ptr<ofSerial> mSerial;
		std::vector<ofSerialDeviceInfo> mDeviceInfos;
		std::string mCOM = "COM1";
		int mBaudRate = 9600;
		bool mAutoRedirect = true;
		uint64_t mDeltaTime = 0, mConnectTime = 0;
		int mRetryTime = 5000;

	};
}