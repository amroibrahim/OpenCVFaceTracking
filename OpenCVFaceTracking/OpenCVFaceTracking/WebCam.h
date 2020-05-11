#pragma once

#include "opencv2/videoio.hpp"

class WebCam
{
public:
	WebCam(int iDeviceIndex);
	WebCam(std::string sName);

	void GetFrame(cv::Mat &frame);

protected:
	cv::VideoCapture capture;
};
