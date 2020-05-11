// WebCamFollow.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>

#include "DisplayWindow.h"
#include "FaceClassifier.h"
#include "MosquitIO.h"
#include "WebCam.h"

using namespace std;

int main(int argc, const char** argv)
{

	DisplayWindow windows;
	WebCam webcam(0);
	FaceClassifier faces;
	MosquitIO mio(L"COM4");

	mio.Init();
	mio.ResetPosition();

	int iTiltDirection;
	int iPanDirection;

	int iTiltSpeed = 5;
	int iPanSpeed = -5;

	cv::Mat CurrentFrame;

	while (windows.HandleEvents())
	{
		webcam.GetFrame(CurrentFrame);
		if (faces.Detect(CurrentFrame))
		{
			faces.DrawBorderRect(0, CurrentFrame);
			faces.GetDistanceToCenter(0, CurrentFrame, iPanDirection, iTiltDirection);
			mio.SetPosition(iPanDirection * iTiltSpeed, iTiltDirection * iPanSpeed);
			windows.Render(CurrentFrame);
		}
		windows.Render(CurrentFrame);
	}

	return 0;
}
