#include <windows.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#pragma warning(disable: 4996);

// C:\Users\Katya

using namespace std;

struct FileInfo {
	string name;
	bool dir = false;
	FILETIME fileCreator;
	unsigned int sizeFile = 0;
};

vector<FileInfo> fileInfo;

void PrintFile() {
	vector<FileInfo>::iterator iter;
	for (iter = fileInfo.begin(); iter != fileInfo.end(); ++iter) {
		SYSTEMTIME ftCreation;
		FileTimeToSystemTime(&(*iter).fileCreator, &ftCreation);
		printf("%02d/%02d/%d  %02d:%02d   ", ftCreation.wDay, ftCreation.wMonth, ftCreation.wYear, ftCreation.wHour, ftCreation.wMinute);
		if ((*iter).dir)
			printf("<DIR>  ");
		else
			printf("       ");
        if ((*iter).dir)
			printf("        \t\t");
		else
			cout << (*iter).sizeFile << " byte \t\t";

		printf("%s", ((*iter).name).c_str());
		cout << endl;
	}
}

void FindFile(char path[256]) {
	WIN32_FIND_DATA search_data;
	HANDLE handle = FindFirstFile(strcat(path, "//*"), &search_data);//дескриптор обэкта
	while (handle != INVALID_HANDLE_VALUE)
	{
		FileInfo temp_info;
		temp_info.name = search_data.cFileName;
		temp_info.fileCreator = search_data.ftCreationTime;
		if (search_data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)//если каталог
			temp_info.dir = true;
        temp_info.sizeFile = (search_data.nFileSizeHigh * (MAXDWORD + 1)) + search_data.nFileSizeLow;
		fileInfo.push_back(temp_info);
		if (FindNextFile(handle, &search_data) == FALSE)
			break;
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
	PrintFile();
	return 0;
}
