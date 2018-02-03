#include <windows.h>
#include <stdio.h>
#include <psapi.h>
#include <vector>
#include <algorithm>

#pragma warning(disable: 4996);

struct ProcessInfo {
	char * name;
	int id;
	int memory;
	DWORD state;
	int minute;
	int second;
};

std::vector <ProcessInfo> processInfo;

int typeOfSort = 1;

bool compareProcessInfo(const ProcessInfo &a, const ProcessInfo &b) {
	switch (typeOfSort) {
	case 1: return a.name < b.name;
	case 2: return a.id < b.id;
	case 3: return a.memory < b.memory;
	case 4: return a.state < b.state;
	}
	return false;
}

void PrintProcessInfo() {
	int i = 0;
	printf("\n%2s%36s%6s%8s%8s%6s\n", "#", "Process name", " PID", "Size", "Time", "State");
	std::sort(processInfo.begin(), processInfo.end(), compareProcessInfo);
	std::vector<ProcessInfo>::iterator iter;
	for (iter = processInfo.begin(); iter != processInfo.end(); iter++) {
		printf("%2i%36s%6u%5i MB%3um%3us%5d\n", ++i, (*iter).name, (*iter).id, (*iter).memory / (1024 * 1024), (*iter).minute, (*iter).second, (*iter).state);
	}
	printf("\n");
}

int GetProcessInfo()
{
	DWORD arrayProcesses[1024], arrayBytesReturned, countProcesses;
	if (!EnumProcesses(arrayProcesses, sizeof(arrayProcesses), &arrayBytesReturned))
		return 0;
	// Calculate how many process identifiers were returned.
	countProcesses = arrayBytesReturned / sizeof(DWORD);
	for (int i = 0; i < countProcesses; i++) {
		ProcessInfo temp;
		FILETIME ftStartTime = { 0 };
		FILETIME ftExitTime = { 0 };
		FILETIME ftKernelTime = { 0 };
		FILETIME ftUserTime = { 0 };
		SYSTEMTIME stKernel;
		PROCESS_MEMORY_COUNTERS pmc;
		char szProcessName[MAX_PATH] = "unknown";
		DWORD lpExitCode;
		// Get a handle to the process.
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, arrayProcesses[i]);
		// Get the process name.
		if (NULL != hProcess)
		{
			HMODULE hMod;
			DWORD cbNeeded;
			if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
			{
				GetModuleBaseName(hProcess, hMod, szProcessName, MAX_PATH);
				GetProcessTimes(hProcess, &ftStartTime, &ftExitTime, &ftKernelTime, &ftUserTime);
				size_t size = sizeof(szProcessName);
				temp.name = (char *)malloc(size + 1);
				strncpy(temp.name, (char *)szProcessName, size);
				temp.name[size + 1] = '\0';
				temp.id = arrayProcesses[i];
			}
			else continue;
		}
		else continue;
		FileTimeToSystemTime(&ftKernelTime, &stKernel);
		temp.minute = stKernel.wMinute;
		temp.second = stKernel.wSecond;
		GetExitCodeProcess(hProcess, &lpExitCode);
		temp.state = lpExitCode;
		if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
		{
			temp.memory = pmc.WorkingSetSize;
		}
		CloseHandle(hProcess);
		processInfo.push_back(temp);
	}
	PrintProcessInfo();
	return 1;
}

int GetMemoryInfo() {
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	printf("Page size: %d kB\n", info.dwPageSize / 1024);
	//printf("\tNumber of processors: %u\n", info.dwNumberOfProcessors);
	printf("Minimum application address: %lx\n", info.lpMinimumApplicationAddress);
	printf("Maximum application address: %lx\n\n", info.lpMaximumApplicationAddress);
	//printf("\tActive processor mask: %u\n\n", info.dwActiveProcessorMask);

	MEMORYSTATUS lpBuffer;
	GlobalMemoryStatus(&lpBuffer);
	printf("System's current usage of physical and virtual memory\n\n");
	printf("There is  %d %% of memory in use.\n", lpBuffer.dwMemoryLoad);
	printf("There are %d total MB of physical memory.\n", lpBuffer.dwTotalPhys / 1024 / 1024);
	printf("There are %d free  MB of physical memory.\n", lpBuffer.dwAvailPhys / 1024 / 1024);
	printf("There are %d total MB of virtual memory.\n", lpBuffer.dwTotalVirtual / 1024 / 1024);
	printf("There are %d free  MB of virtual memory.\n", lpBuffer.dwAvailVirtual / 1024 / 1024);
	printf("There are %d total MB of paging file.\n", lpBuffer.dwTotalPageFile / 1024 / 1024);
	printf("There are %d free  MB of paging file.\n\n", lpBuffer.dwAvailPageFile / 1024 / 1024);

	MEMORY_BASIC_INFORMATION memoryInfo;
	unsigned char *addr = 0;
	VirtualQuery(addr, &memoryInfo, sizeof(memoryInfo));
	printf("Information about a range of pages in the virtual address space of the calling \n\n");
	printf("A pointer to the base address: %d\n", memoryInfo.BaseAddress);
	printf("A pointer to the base address of a range of pages allocated: %lx\n", memoryInfo.AllocationBase);
	printf("Memory protection option: %d\n", memoryInfo.AllocationProtect);
	printf("Region size: %d\n", memoryInfo.RegionSize);
	printf("State of the pages in the region: %d\n", memoryInfo.State);
	printf("The access protection of the pages in the region: %d\n", memoryInfo.Protect);
	printf("Type of the pages in the region: %d\n\n", memoryInfo.Type);
	return 1;
}

int main()
{
	if (!GetProcessInfo())
		printf("Can't get the info about processes!\n");

	if (!GetMemoryInfo())
		printf("Can't get the memory info!\n");
	return 0;
}

