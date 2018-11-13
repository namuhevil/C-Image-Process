#include <cstdio>

using namespace std;

void local_mean(unsigned char **input_image, unsigned char **output_image, int row, int col, int mask)
{
	int Kernel[mask][mask];
	int expectation, sum, mean;
    int start = -(mask-1)/2;
    int end = -start;

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			sum = 0;
			mean = 0;
			for (int x = start; x <= end; x++)
			{
				for (int y = start; y <= end; y++)
				{
					if (i < end || j < end || i > row - end - 1 || j > col - end -1)
					{
						Kernel[x + end][y + end] = input_image[i][j];
						if (j < end && j > col - end -1)
						{
							Kernel[x + end][y + end] = input_image[i][j + y];
						}

						if (i < end && i > row - end -1)
						{
							Kernel[x + end][y + end] = input_image[i + x][j];
						}
					}
					else
					{
						Kernel[x + end][y + end] = input_image[i + x][j + y];
					}
					mean += Kernel[x + end][y + end] * Kernel[x + end][y + end];
					sum += Kernel[x + end][y + end];
				}
			}
			if (sum == 0)
			{
				sum = 1;
			}
			expectation = mean / sum;
			output_image[i][j] = expectation;
		}
}