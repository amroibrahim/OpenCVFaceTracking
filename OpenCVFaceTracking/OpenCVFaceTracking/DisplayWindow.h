#pragma once

#include "opencv2/imgproc.hpp"

class DisplayWindow
{
public:
	DisplayWindow() = default;
	void Render(cv::Mat &frame);
	int HandleEvents();
};
