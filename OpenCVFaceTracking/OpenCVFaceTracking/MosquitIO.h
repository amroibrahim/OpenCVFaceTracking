#pragma once

#include <cstdint>
#include <string>
#include <windows.h>

struct MosquitIOPacket
{
	uint8_t cHeader;     // 255: header, this begins a packet and must always be sent.
	uint8_t cByteCount;  // Number of bytes: total number of bytes (not including the header or this byte) to be sent. There is always 11 in this struct
	uint8_t cTilt;       // Tilt servo: 0-255 for -100 to 100 degrees (approximately)
	uint8_t cPan;        // Pan servo: 0-255 for -100 to 100 degrees (approximately)
	uint8_t cMotor1;     // Motor 1: 0 - 255 0 = full backwards, 128 = stop, 255 = full forwards
	uint8_t cMotor2;     // Motor 2: 0 - 255 0 = full backwards, 128 = stop, 255 = full forwards
	uint8_t cMotorRelay; // Motor Relay: 0-1, On/Off Solid State Relay – Supplies Input Voltage
	uint8_t cdigitalIO1; // Digital IO 1: we set inputs to high since high is the default stable state
	uint8_t cdigitalIO2; // Digital IO 2: we set inputs to high since high is the default stable state
	uint8_t cdigitalIO3; // Digital IO 3: we set inputs to high since high is the default stable state
	uint8_t cdigitalIO4; // Digital IO 4: we set inputs to high since high is the default stable state
	uint8_t cdigitalIO5; // Digital IO 5 we set inputs to high since high is the default stable state
	uint8_t cMode;       // Mode: sending > 0 will reset the controller into JOYSTICK mode.
};

class MosquitIO
{
public:
	MosquitIO() = default;
	MosquitIO(std::wstring sCOMPort);
	bool Init();

	bool ResetPosition();
	bool SetPosition(int8_t cTilt, int8_t cPan);

private:
	void KeepInRange(uint8_t &cMotorRange);

	HANDLE m_hCom;
	std::wstring m_sCOMPort;

	uint8_t m_cTilt;
	uint8_t m_cPan;
};
