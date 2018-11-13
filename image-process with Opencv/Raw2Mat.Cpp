#include <cstdio>

#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

void Raw2Mat(unsigned char **img_matrix, Mat output_image, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			output_image.at<uchar>(i, j) = img_matrix[i][j];
		}
	}
}