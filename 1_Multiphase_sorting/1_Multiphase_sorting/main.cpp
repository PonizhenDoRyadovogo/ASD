#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool isFileContainsSortedArray(const std::string& fileName)
{
	std::ifstream originFile(fileName);
	if (!originFile.is_open())
	{
		std::cout << "Error! File don't open!\n";
		exit(-1);
	}
	int actual, next;

	while (originFile >> actual)
	{
		originFile >> next;
		if (actual > next)
		{
			originFile.close();
			return false;
		}
	}
	originFile.close();
	return true;
}

std::ofstream createOfstream(const std::string& fileName) {
	std::ofstream stream(fileName);
	return stream;
}

std::vector<std::ofstream> CreateFilesVector(const int countFiles)
{
	std::vector<std::ofstream> filesContainer;
	for (int i = 0; i < countFiles; ++i)
	{
		std::string fileName = "file" + std::to_string(i) + ".txt";
		filesContainer.push_back(createOfstream(fileName));
	}
	return filesContainer;
}

//void MultiphaseSort(std::string &fileName, const int countFiles = 3)
//{
//	std::fstream** files = new std::fstream * [countFiles];
//	for (int i = 0; i < countFiles; ++i)
//		files[i] = new std::fstream();
//}

int main()
{
	std::vector<std::ofstream> files = CreateFilesVector(3);
	files[0] << 52;
}