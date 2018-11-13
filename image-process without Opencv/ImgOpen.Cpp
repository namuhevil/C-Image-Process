#include <cstdio>

using namespace std;

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
	while (checkFile(filename))
	{
		cout << "This File does not exist, please enter another filename: ";
		cin >> filename;
		cout << endl << endl;
	}
	input_files.open(filename.c_str(), ios_base::binary);
}