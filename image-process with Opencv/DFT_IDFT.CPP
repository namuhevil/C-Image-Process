#include <cstdio>

#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;


void CV_DFT_Transform(Mat input_image, String filename, String idft_name, int row, int col)
{
	clock_t start, end;
	start = clock(); //開始時間
	Mat padded;                            //expand input image to optimal size
	int m = getOptimalDFTSize(input_image.rows);
	int n = getOptimalDFTSize(input_image.cols); // on the border add zero values
	copyMakeBorder(input_image, padded, 0, m - input_image.rows, 0, n - input_image.cols, BORDER_CONSTANT, Scalar::all(0));
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexI;
	merge(planes, 2, complexI);         // Add to the expanded another plane with zeros
	dft(complexI, complexI);            // this way the result may fit in the source matrix
	// compute the magnitude and switch to logarithmic scale
	// => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))

	split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
	Mat magI = planes[0];
	magI += Scalar::all(1);                    // switch to logarithmic scale
	log(magI, magI);
	// crop the spectrum, if it has an odd number of rows or columns
	magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));
	// rearrange the quadrants of Fourier image  so that the origin is at the image center
	int cx = magI.cols / 2;
	int cy = magI.rows / 2;
	Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
	Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
	Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right
	Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);
	normalize(magI, magI, 0, 1, NORM_MINMAX); // Transform the matrix with float values into a

	end = clock(); //結束時間
	printf("Opencv的Dft %.3f秒\n", double(end - start) / CLOCKS_PER_SEC); //顯示運算時間

	// 輸出結果
	magI.convertTo(magI, CV_8UC3, 255.0);
	imshow(filename, magI);
	imwrite(filename + ".png", magI);
	   
	//逆向傅立葉轉換
	start = clock(); //開始時間
	Mat ifft;
	idft(complexI, ifft, DFT_REAL_OUTPUT);
	normalize(ifft, ifft, 0, 1, CV_MINMAX);
	end = clock(); //結束時間
	printf("Opencv的IDft %.3f秒\n", double(end - start) / CLOCKS_PER_SEC); //顯示運算時間

	ifft.convertTo(ifft, CV_8UC3, 255.0);
	imshow(idft_name, ifft);
	imwrite(idft_name + ".jpg", ifft);
}