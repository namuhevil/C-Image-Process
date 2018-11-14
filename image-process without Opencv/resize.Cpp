#include <cstdio>

using namespace std;

void resize(unsigned char **input_matrix, unsigned char **output_matrix, int row, int col, double ratio)
{
	int idx, idy;
	int tr_idx, tr_idy;
	
	for (idx = 0; idx < row; idx++)
	{
		for (idy = 0; idy < col; idy++)
		{
			tr_idx = int(idx * ratio + 0.5);
			tr_idy = int(idy * ratio + 0.5);
			if (tr_idx > row*ratio-1) tr_idx = row*ratio-1;
			if (tr_idy > col*ratio-1) tr_idy = col*ratio-1;
			output_matrix[tr_idx][tr_idy] = input_matrix[idx][idy];
		}
	}
}