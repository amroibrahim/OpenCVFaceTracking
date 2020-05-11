#pragma once
#include <vector>

#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"

class FaceClassifier
{
public:
	FaceClassifier();
	int Detect(cv::Mat frame);

	void DrawBorderRect(int iFaceIndex, cv::Mat &frame);
	void GetDistanceToCenter(int iFaceIndex, cv::Mat &frame, int &iXDirection, int &iYDirection);

protected:
	cv::CascadeClassifier face_cascade;
	cv::CascadeClassifier eyes_cascade;

	std::vector<cv::Rect> m_Faces;
};
