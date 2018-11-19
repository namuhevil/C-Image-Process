#include <cstdio>

using namespace std;

/*How to use*/
/* ReadFile("apple", img_matrix, 256, 256);*/

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
