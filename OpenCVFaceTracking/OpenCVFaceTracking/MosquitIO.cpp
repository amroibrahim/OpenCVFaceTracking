#include "MosquitIO.h"

MosquitIO::MosquitIO(std::wstring sCOMPort) : m_sCOMPort(sCOMPort)
{
	m_cTilt = 128;
	m_cPan = 128;
}

bool MosquitIO::Init()
{
	m_hCom = CreateFile(m_sCOMPort.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (m_hCom == INVALID_HANDLE_VALUE)
	{
		return false;
	}


	//  Initialize the DCB structure.
	DCB COMSettings;
	SecureZeroMemory(&COMSettings, sizeof(DCB));
	COMSettings.DCBlength = sizeof(DCB);

	if (!GetCommState(m_hCom, &COMSettings))
	{
		return false;
	}

	COMSettings.BaudRate = CBR_38400;   //  baud rate
	COMSettings.ByteSize = 8;           //  data size, xmit and rcv
	COMSettings.Parity = NOPARITY;      //  parity bit
	COMSettings.StopBits = ONESTOPBIT;  //  stop bit

	if (!SetCommState(m_hCom, &COMSettings))
	{
		return false;
	}

	return true;
}

bool MosquitIO::SetPosition(int8_t cTilt, int8_t cPan)
{
	m_cTilt += cTilt;
	m_cPan += cPan;

	KeepInRange(m_cTilt);
	KeepInRange(m_cPan);

	MosquitIOPacket packet;

	packet.cHeader = 255;
	packet.cByteCount = 11;
	packet.cTilt = m_cTilt;
	packet.cPan = m_cPan;
	packet.cMotor1 = 128;
	packet.cMotor2 = 128;
	packet.cMotorRelay = 0;
	packet.cdigitalIO1 = 1;
	packet.cdigitalIO2 = 1;
	packet.cdigitalIO3 = 1;
	packet.cdigitalIO4 = 1;
	packet.cdigitalIO5 = 1;
	packet.cMode = 0;

	DWORD dBytestoWrite = sizeof(packet);         // No of bytes to write into the port
	DWORD dBytesWritten = 0;     // No of bytes written to the port

	return WriteFile(m_hCom, &packet, dBytestoWrite, &dBytesWritten, NULL);
}

void MosquitIO::KeepInRange(uint8_t &cMotorRange)
{
	if (1 > cMotorRange)
	{
		cMotorRange = 1;
	}

	if (cMotorRange > 255)
	{
		cMotorRange = 255;
	}
}

bool MosquitIO::ResetPosition()
{
	m_cTilt = 128;
	m_cPan = 128;
	return SetPosition(0, 0);
}
