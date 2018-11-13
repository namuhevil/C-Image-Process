#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <fstream>
#include <math.h>
#include <exception>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>      

#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

bool ReadFile(ifstream& input_files, unsigned char **img_matrix, int row, int col)
{
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