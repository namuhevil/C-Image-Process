#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdio>
#include <iostream>  
#include <algorithm>
#include <vector>

#include <opencv2/opencv.hpp>

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

void CV_IDFT(Mat img[2], string saveFileName, string direction, int D0, int order) {
	double tic = clock();  //開始時間

	Mat padded0, padded1;                            //expand input image to 符合FFT的大小
	int m = getOptimalDFTSize(img[0].rows);
	int n = getOptimalDFTSize(img[0].cols); // on the border add zero values
	//原圖size變m*n，填充的位置補零
	copyMakeBorder(img[0], padded0, 0, m - img[0].rows, 0, n - img[0].cols, BORDER_CONSTANT, Scalar::all(0));
	copyMakeBorder(img[1], padded1, 0, m - img[0].rows, 0, n - img[0].cols, BORDER_CONSTANT, Scalar::all(0));
	Mat planes[] = { Mat_<float>(padded0), Mat_<float>(padded1) };

	Mat complexImg;
	merge(planes, 2, complexImg);

	Mat ifft;
	idft(complexImg, ifft, DFT_INVERSE | DFT_REAL_OUTPUT);

	Mat magI = ifft;
	magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));  //令邊長為偶數
	normalize(magI, magI, 0, 1, CV_MINMAX);
	magI.convertTo(magI, CV_8UC3, 255.0);
	imshow(string(saveFileName + to_string(D0) + "_" + to_string(order)+ "_IDFT"), magI);
	imwrite(string(direction + "/" + saveFileName + "_IDFT" + to_string(D0) + "_" + to_string(order) + ".png"), magI);

	double toc = clock();  //結束時間
	cout << saveFileName << "_IDFT execution time: " << toc - tic << " ms" << endl;
}
