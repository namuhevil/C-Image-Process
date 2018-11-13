#include <cstdio>

using namespace std;

bool ImgRead(ifstream& input_files, unsigned char **img_matrix, int row, int col)
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