#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <fstream>
#include <cstdio>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


bool checkFile(string filename)
{
	ifstream testFile;
	testFile.open(filename.c_str(), ios_base::binary);

	if (testFile)
	{
		return false;
	}
	else
	{
		return true;
	}
	testFile.close();
}

void OpenFiles(ifstream& input_files, string filename)
{	
	filename = filename + ".raw";
	while (checkFile(filename))
	{
		cout << "This File does not exist, please enter another filename: ";
		cin >> filename;
		cout << endl << endl;
	}
	input_files.open(filename.c_str(), ios_base::binary);
}

bool ReadFile(string filename, unsigned char** img_matrix, int row, int col)
{	
	ifstream input_files;
	OpenFiles(input_files, filename);

	char temp;
	input_files.seekg(0, ios::beg);

	for (int idx = 0; idx < row; idx++)
	{
		for (int idy = 0; idy < col; idy++)
		{
			input_files.get(temp);
			img_matrix[idx][idy] = (unsigned char)temp;
		}
	}
	return true;
}

Mat Cv_imread(int row, int col, String filename)
{	
	unsigned char** img_matrix = img2matrix(row,col);
	ReadFile(filename, img_matrix, row, col);
	Mat output_image(row, col, CV_8UC1);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			output_image.at<uchar>(i, j) = img_matrix[i][j];
		}
	}
	return output_image;
}