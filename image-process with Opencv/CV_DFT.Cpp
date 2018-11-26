#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdio>
#include <iostream>  
#include <algorithm>
#include <vector>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void fft_shift(Mat img) {
	int cx = img.cols / 2;
	int cy = img.rows / 2;
	Mat q0(img, Rect(0, 0, cx, cy));
	Mat q1(img, Rect(cx, 0, cx, cy));
	Mat q2(img, Rect(0, cy, cx, cy));
	Mat q3(img, Rect(cx, cy, cx, cy));
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
}

void CV_DFT(Mat img, Mat dst[2], string saveFileName, string direction) {
	double tic = clock();  //開始時間
	Mat padded;                            //expand input image to 符合FFT的大小
	int m = getOptimalDFTSize(img.rows);
	int n = getOptimalDFTSize(img.cols); // on the border add zero values
	//原圖size變m*n，填充的位置補零
	copyMakeBorder(img, padded, 0, m - img.rows, 0, n - img.cols, BORDER_CONSTANT, Scalar::all(0));
	//獲取兩個Mat，一個存實部，一個存虛部
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexImg;
	merge(planes, 2, complexImg);         // Add to the expanded another plane with zeros
	dft(complexImg, complexImg);            // this way the result may fit in the source matrix

	split(complexImg, planes);                  //分離通道，planes[0]為實數部分，planes[1]為虛數部分 
	//輸出實部虛部
	dst[0] = planes[0];
	dst[1] = planes[1];

	Mat magI;
	magnitude(planes[0], planes[1], magI); //planes[0] = sqrt((planes[0])^2 + (planes[1])^2))

	log(magI, magI);//尺度變換
	magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));  //令邊長為偶數
	fft_shift(magI);  //平移

	normalize(magI, magI, 0, 1, CV_MINMAX);
	magI.convertTo(magI, CV_8U, 255.0);
	imshow(string(saveFileName + "_DFT"), magI);
	imwrite(string(direction + "/" + saveFileName + "_DFT" + ".png"), magI);

	double toc = clock();  //結束時間
	cout << saveFileName << "_DFT execution time: " << toc - tic << " ms" << endl;
}