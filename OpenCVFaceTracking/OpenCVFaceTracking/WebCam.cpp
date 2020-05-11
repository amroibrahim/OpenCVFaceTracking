#include "WebCam.h"

using namespace cv;

WebCam::WebCam(int iDeviceIndex)
{
	capture.open(iDeviceIndex); //camera_device
	if (!capture.isOpened())
	{
		exit(1);
	}
}

WebCam::WebCam(std::string sName)
{
}

void WebCam::GetFrame(cv::Mat &frame)
{
	capture.read(frame);
}
