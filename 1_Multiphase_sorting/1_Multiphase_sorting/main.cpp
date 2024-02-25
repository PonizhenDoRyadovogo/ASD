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

void MultiphaseSort(std::string &fileName, const int countFiles = 3)
{
	//1
	std::vector<std::ofstream> files = CreateFilesVector(countFiles);
	std::ifstream originFile(fileName);
	if (!originFile.is_open())
	{
		std::cout << "Error!File don't open!\n";
		exit(-1);
	}
	int* ms = new int[countFiles];
	int* ip = new int[countFiles];
	for (int i = 0; i < countFiles; ++i)
	{
		ip[i] = 1;
		ms[i] = 1;
		if (i == countFiles - 1)
		{
			ip[i] = 0;
			ms[i] = 0;
		}
	}
	int level = 1, it = 0, actual, next;
	//2
	originFile >> actual;
	while (!originFile.eof())
	{
		files[it] << actual << " ";
		originFile >> next;
		while (!originFile.eof() && (actual <= next))
		{
			actual = next;
			files[it] << actual << " ";
			originFile >> next;
		}
		ms[it]--;
	//3
		if (ms[it] < ms[it + 1])
			++it;
		else if (ms[it] == 0)
		{
	//4
			++level;
			int ip0 = ip[0];
			it = 0;
			for (int k = 0; k < countFiles - 2; ++k)
			{
				ms[k] = ip[k + 1] - ip[k] + ip0;
				ip[k] = ip[k + 1] + ip0;
			}
		}
		else
			it = 0;
		actual = next;
		if (originFile.eof())
			files[it] << actual;
	}

}

int main()
{
	std::string file = "originFile.txt";
	MultiphaseSort(file, 4);
}