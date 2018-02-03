#include <windows.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <map>

#pragma warning(disable: 4996);
#define BLOCK 1048576

using namespace std;

map<unsigned int, unsigned int> fileDiagram;
int counter = 0;

void PrintDiagram() {
	map<unsigned int, unsigned int>::iterator iter;
	for (iter = fileDiagram.begin(); iter != fileDiagram.end(); iter++) {
		printf("%5u Mb -%5u Mb| %5u| ", ((*iter).first), ((*iter).first + 1), (*iter).second);
		int count = ((*iter).second * 50) / counter;
		if (count < 1)
			count = 1;
		for (int i = 0; i < count; i++)
			printf("*");
		printf("\n");
	}
}

void FindFile(char dirName[256]) {
	WIN32_FIND_DATA search_data;
	char olddir[256];
	char dir[256];
	strcpy(dir, dirName);
	unsigned int sizeFile;
	memset(&search_data, 0, sizeof(WIN32_FIND_DATA));
	HANDLE handle = FindFirstFile(strcat(dir, "//*"), &search_data);
	if (handle != INVALID_HANDLE_VALUE)
	{
		do {
			//printf("%s ", search_data.cFileName);
			if (strcmp(search_data.cFileName, ".") == 0 || strcmp(search_data.cFileName, "..") == 0) {
				//printf("ignore directory\n");
				continue;
			}
			if (search_data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) { // если директория
				strcpy(olddir, dirName);
				strcat(dirName, "//");
				strcat(dirName, search_data.cFileName);
				//printf("open directory\n");
				FindFile(dirName);
				strcpy(dirName, olddir);
				continue;
			}
			else {
				//printf("cal size\n");
				counter++;
				sizeFile = (search_data.nFileSizeHigh * (MAXDWORD + 1)) + search_data.nFileSizeLow;
				fileDiagram[sizeFile / BLOCK]++;
			}
		} while (FindNextFile(handle, &search_data));
	}
	FindClose(handle);
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	char directory[256];
	printf("Please, enter the current dir: ");
	scanf("%s", directory);
	FindFile(directory);
	PrintDiagram();
	return 0;
}
