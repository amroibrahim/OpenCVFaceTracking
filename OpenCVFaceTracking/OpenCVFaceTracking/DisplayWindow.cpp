#include "DisplayWindow.h"

#include "opencv2/highgui.hpp"

using namespace cv;

void DisplayWindow::Render(cv::Mat &frame)
{
	imshow("Capture - Face detection", frame);
}

int DisplayWindow::HandleEvents()
{
	return (waitKey(10) != 27);
}
