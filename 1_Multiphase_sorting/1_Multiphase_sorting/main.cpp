#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int MinIndex(int *arr, const int size)
{
	int minIndex, min, f;
	minIndex = 0;
	min = arr[0];
	for (int i = 1; i <= size - 2; ++i)
	{
		f = arr[i];
		if (f < min)
		{
			min = f;
			minIndex = i;
		}
	}
	return minIndex;
}

bool IsFileContainsSortedArray(const std::string& fileName)
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

//std::fstream CreateOfstream(const std::string& fileName) {
//	std::fstream stream(fileName, std::ios::out);
//	return stream;
//}

std::vector<std::fstream*> CreateFilesVector(const int countFiles, std::string *names)
{
	std::fstream* file = nullptr;
	std::vector<std::fstream*> filesContainer;
	for (int i = 0; i < countFiles; ++i)
	{
		std::string fileName = "file" + std::to_string(i) + ".txt";
		names[i] = fileName;
		file = new std::fstream(fileName);
		file->open(fileName, std::ios::out);
		filesContainer.push_back(file);
	}
	return filesContainer;
}

void MultiphaseSort(std::string& fileName, const int countFiles = 3)
{
	//1
	std::string* namesFiles = new std::string[countFiles];
	std::vector<std::fstream*> files = CreateFilesVector(countFiles, namesFiles);
	std::ifstream originFile(fileName);
	if (!originFile.is_open())
	{
		std::cout << "Error!File don't open!\n";
		exit(-1);
	}
	int* ms = new int[countFiles];
	int* ip = new int[countFiles];
	for (int i = 0; i <= countFiles - 2; ++i)
	{
		ip[i] = 1;
		ms[i] = 1;
	}
	ip[countFiles - 1] = ms[countFiles - 1] = 0;
	int level = 1, it = 0, actual, next, countSeparator = 0;
	//2
	originFile >> actual;
	while (!originFile.eof())
	{
		if (actual != INT_MAX)
		{
			*files[it] << actual << " ";
		}
		else
			countSeparator += 1;
		originFile >> next;
		while (!originFile.eof() && (actual <= next))
		{
			actual = next;
			if (actual != INT_MAX)
				*files[it] << actual << " ";
			else
				countSeparator += 1;
			originFile >> next;
		}
		ms[it]--;
		*files[it] << INT_MAX << " ";
		//3
		if (ms[it] < ms[it + 1])
			++it;
		else if (ms[it] == 0)
		{
			//4
			++level;
			int ip0 = ip[0];
			it = 0;
			for (int k = 0; k <= countFiles - 2; ++k)
			{
				ms[k] = ip[k + 1] - ip[k] + ip0;
				ip[k] = ip[k + 1] + ip0;
			}
		}
		else
			it = 0;
		actual = next;
		if (originFile.eof() && actual != INT_MAX)
		{
			*files[it] << actual << " " << INT_MAX;
			--ms[it];
		}
	}
	//2 end
	for (int i = 0; i < countFiles; ++i)
	{
		files[i]->close();
	}
	originFile.close();

	//5
	for (int i = 0; i <= countFiles - 2; ++i)
	{
		files[i]->open(namesFiles[i], std::ios::in);
	}
	files[countFiles - 1]->open(namesFiles[countFiles - 1], std::ios::out);

	while (level != 0)
	{
		while (*files[countFiles - 2] >> ip[countFiles - 2])
		{
			int haveFictitious = 1;
			for (int i = 0; i <= countFiles - 2; ++i)
				haveFictitious *= ms[i];
			while (haveFictitious)
			{
				for (int i = 0; i <= countFiles - 2; ++i)
				{
					--ms[i];
					haveFictitious *= ms[i];
				}
				++ms[countFiles - 1];
			}
			//7.2
			for (int i = 0; i <= countFiles - 2; ++i)
			{
				if (ms[i] == 0)
				{
					if (i == countFiles - 2)
						continue;
					*files[i] >> ip[i];
				}
				else if (ms[i] > 0)
				{
					if (i == countFiles - 2)
					{
						files[countFiles - 2]->close();
						files[countFiles - 2]->open(namesFiles[countFiles - 2], std::ios::in);
					}
					--ms[i];
					ip[i] = INT_MAX;
				}
			}
			/*std::cout << "\n"<<"ip: ";
			for (int i = 0; i < countFiles; ++i)
			{
				std::cout << ip[i] << " ";
			}*/
			for (; ;)
			{
				int indexMin = MinIndex(ip, countFiles);
				if (ip[indexMin] == INT_MAX)
					break;
				*files[countFiles - 1] << ip[indexMin] << " ";
				*files[indexMin] >> ip[indexMin];
				/*std::cout << "\n" << "ip: ";
				for (int i = 0; i < countFiles; ++i)
				{
					std::cout << ip[i] << " ";
				}*/
			}
			if (level != 1)
			{
				*files[countFiles - 1] << INT_MAX << " ";
			}
		}
		//8
		--level;
		files[countFiles - 1]->close();
		files[countFiles - 2]->close();
		files[countFiles - 2]->open(namesFiles[countFiles - 2], std::ios::out);
		if (!files[countFiles - 2]->is_open())
			return;
		files[countFiles - 1]->open(namesFiles[countFiles - 1], std::ios::in);
		if (!files[countFiles - 1]->is_open())
			return;
		for (int i = countFiles - 1; i > 0; --i)
		{
			std::swap(namesFiles[i], namesFiles[i - 1]);
			std::swap(files[i], files[i - 1]);
			std::swap(ms[i], ms[i - 1]);
		}
		/*std::cout << level << "\n" << "ms: ";
		for (int i = 0; i < countFiles; ++i)
		{
			std::cout << ms[i]<< " ";
		}
		std::cout << "\n";*/
	}

	for (int i = 0; i < countFiles; ++i)
	{
		files[i]->close();
		delete files[i];
	}
	delete[]ms;
	delete[]ip;
	delete[]namesFiles;
}

int main()
{
	std::string file = "originFile.txt";
	MultiphaseSort(file, 4);
}