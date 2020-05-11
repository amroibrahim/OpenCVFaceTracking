#include "FaceClassifier.h"



using namespace cv;

FaceClassifier::FaceClassifier()
{
	String face_cascade_name = "..\\..\\external\\OpenCV4.3.0\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";
	String eyes_cascade_name = "..\\..\\external\\OpenCV4.3.0\\sources\\data\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml";

	// Load the cascades
	face_cascade.load(face_cascade_name);
	eyes_cascade.load(eyes_cascade_name);
}

int FaceClassifier::Detect(cv::Mat frame)
{
	Mat frame_gray;
	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	// Detect faces
	m_Faces.clear();
	face_cascade.detectMultiScale(frame_gray, m_Faces);

	return m_Faces.size();
}

void FaceClassifier::DrawBorderRect(int iFaceIndex, cv::Mat &frame)
{
	if (iFaceIndex >= m_Faces.size())
	{
		return;
	}

	Rect rect(m_Faces[iFaceIndex].x, m_Faces[iFaceIndex].y, m_Faces[iFaceIndex].width, m_Faces[iFaceIndex].height);
	rectangle(frame, rect, cv::Scalar(0, 255, 0), 2);
}

void FaceClassifier::GetDistanceToCenter(int iFaceIndex, cv::Mat &frame, int &iXDirection, int &iYDirection)
{
	if (iFaceIndex >= m_Faces.size())
	{
		return;
	}

	Point FaceCenter(m_Faces[iFaceIndex].x + m_Faces[iFaceIndex].width / 2, m_Faces[iFaceIndex].y + m_Faces[iFaceIndex].height / 2);
	Point FrameCenter(frame.cols / 2, frame.rows / 2);

	int iXCenterRange = 75;
	int iYCenterRange = 75;

	iXDirection = 0;
	iYDirection = 0;

	if (FrameCenter.x - iXCenterRange < FaceCenter.x)
	{
		iXDirection += 1;
	}

	if (FaceCenter.x < FrameCenter.x + iXCenterRange)
	{
		iXDirection += -1;
	}

	if (FrameCenter.y - iYCenterRange < FaceCenter.y)
	{
		iYDirection += +1;
	}

	if (FaceCenter.y < FrameCenter.y + iYCenterRange)
	{
		iYDirection += -1;
	}
}
