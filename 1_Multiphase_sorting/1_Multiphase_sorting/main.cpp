#include <iostream>
#include <fstream>
#include <string>

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

void MultiphaseSort(std::string &fileName, const int countFiles = 3)
{

}

int main()
{

}