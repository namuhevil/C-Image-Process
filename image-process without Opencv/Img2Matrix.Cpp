#include <cstdio>

using namespace std;
class Img2Matrix{

    public: 
        Img2Matrix(unsigned char** input_matrix, int row, int col){
            unsigned char  ** DFT_output;
            DFT_output = new unsigned char*[row];
            DFT_output[0] = new unsigned char[row*col];

            {
                for (int idx = 0; idx < row; idx++)
                {
                    input_matrix[idx] = input_matrix[0] + idx * col;
                }
            }
        }

        int row(){return _row;}
        int col(){return _col;}

        void row(int row)
        { 
            _row = row;
        }
        void row(int row)
        { 
            _col = row;
        }
}