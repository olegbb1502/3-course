/*#include <iostream>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}*/
#include <windows.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#pragma warning(disable: 4996);

using namespace std;

struct FileInfo {
	string name;
	bool dir = false;
	FILETIME fileCreation;
	DWORD Size;
};

vector<FileInfo> fileInfo;

void FindFile(char path[256]) {
	WIN32_FIND_DATA search_data;
	HANDLE handle = FindFirstFile(strcat(path, "//*"), &search_data);
	while (handle != INVALID_HANDLE_VALUE)
	{
	    printf("ggggg\n");
		FileInfo temp_info;
		temp_info.name = search_data.cFileName;
		temp_info.fileCreation = search_data.ftCreationTime;
		temp_info.Size = (search_data.nFileSizeHigh * (MAXDWORD + 1)) + search_data.nFileSizeLow;
		if (search_data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
			temp_info.dir = true;
		fileInfo.push_back(temp_info);
		if (FindNextFile(handle, &search_data) == FALSE)
			break;
	}
	FindClose(handle);
}

void PrintFile() {
	vector<FileInfo>::iterator iter;
	for (iter = fileInfo.begin(); iter != fileInfo.end(); ++iter) {
		SYSTEMTIME ftCreation;
		FileTimeToSystemTime(&(*iter).fileCreation, &ftCreation);
		printf("%02d/%02d/%d  %02d:%02d   ", ftCreation.wDay, ftCreation.wMonth, ftCreation.wYear, ftCreation.wHour, ftCreation.wMinute);
		if ((*iter).dir) {
			printf("          ");
			printf("  <DIR>  ");
		}
		else {
			printf("%7d KB", (*iter).Size / 1024);
			printf("         ");
		}
		printf("%s\n", ((*iter).name).c_str());
	}
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	char directory[256];
	printf("Please, enter the dir: ");
	scanf("%s", directory);
	//printf(directory, "\n");
	FindFile(directory);
	PrintFile();
	return 0;
}
