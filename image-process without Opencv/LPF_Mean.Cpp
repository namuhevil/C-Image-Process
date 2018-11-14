#include <cstdio>

using namespace std;

void local_mean(unsigned char **input_image, unsigned char **output_image, int row, int col, int mask)
{
	int Kernel[mask][mask];
	int expectation, sum, mean;
    int start = -(mask-1)/2;
    int end = -start;

	for (int idx = 0; idx < row; idx++)
		for (int idy = 0; idy < col; idy++)
		{
			sum = 0;
			mean = 0;
			for (int x = start; x <= end; x++)
			{
				for (int y = start; y <= end; y++)
				{
					if (idx < end || idy < end || idx> row - end - 1 || idy > col - end -1)
					{
						Kernel[x + end][y + end] = input_image[i][idy];
						if (idy < end && idy > col - end -1)
						{
							Kernel[x + end][y + end] = input_image[i][idy + y];
						}

						if (idx< end && idx> row - end -1)
						{
							Kernel[x + end][y + end] = input_image[idx+ x][idy];
						}
					}
					else
					{
						Kernel[x + end][y + end] = input_image[idx+ x][idy + y];
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
			output_image[idx][idy] = expectation;
		}
}