#include <cstdio>

#include <opencv2/opencv.hpp>

using namespace std;

using namespace cv;

void img_show(unsigned char** input_img, String Window_name, int row, int col)
{
	CvMat *image = cvCreateMat(row, col, CV_8UC1);
	cvSetData(image, input_img[0], image->step);
	namedWindow(Window_name, CV_WINDOW_AUTOSIZE);
	cvShowImage(Window_name.c_str(), image);
}