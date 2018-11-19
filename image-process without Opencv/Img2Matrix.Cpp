#include <cstdio>

using namespace std;

/* How to use */
/* unsigend char ** img_matrix = img2matrix(256, 256);*/

unsigned char** img2matrix(int row, int col)
{
	unsigned char **img_matrix;
	img_matrix = new unsigned char*[row];
	img_matrix[0] = new unsigned char[row * col];
	for (int idx = 0; idx < row; idx++)
	{
		img_matrix[idx] = img_matrix[0] + idx * col;
	}
	return img_matrix;
}