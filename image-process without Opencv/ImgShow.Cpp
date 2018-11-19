#include <cstdio>

#include <opencv2/opencv.hpp>

using namespace std;

using namespace cv;

/*How to use*/
/* img_show(img_matrix, "apple", 256, 256);*/

void img_show(unsigned char** input_img, String Window_name, int row, int col)
{
	CvMat *image = cvCreateMat(row, col, CV_8UC1);
	cvSetData(image, input_img[0], image->step);
	namedWindow(Window_name, CV_WINDOW_AUTOSIZE);
	cvShowImage(Window_name.c_str(), image);
}