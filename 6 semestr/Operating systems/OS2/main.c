/*#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Hello world!\n");
    return 0;
}*/
#include <windows.h>
#include <stdio.h>
#include "psapi.h"

struct Process {
  char * name;
  int id;
  int memory;
  DWORD state;
  int minute;
  int second;
};

int count = 0;

sort_by_memory(struct Process * array)
{
	int i=0;
	int j=0;
	for(i=0; i<count; i++)
	{
		for(j=0; j<count-1; j++)
		{
			if(array[j].memory < array[j+1].memory)
			{
				struct Process buf = array[j+1];
				array[j+1] = array[j];
				array[j] = buf;
			}
		}
	}
}

sort_by_time(struct Process * array)
{
	int i=0;
	int j=0;
	for(i=0; i<count; i++)
	{
		for(j=0; j<count-1; j++)
		{
			int one = array[j].minute*100 + array[j].second;
			int two = array[j+1].minute*100 + array[j+1].second;
			if(one < two)
			{
				struct Process buf = array[j+1];
				array[j+1] = array[j];
				array[j] = buf;
			}
		}
	}
}

void PrintProcessNameAndID( DWORD processID, struct Process * array )
{
 	 FILETIME ftStartTime = {0};
     FILETIME ftExitTime =  {0};
     FILETIME ftKernelTime = {0};
     FILETIME  ftUserTime = {0};
     SYSTEMTIME stKernel;
	 PROCESS_MEMORY_COUNTERS pmc;
	 char szProcessName[MAX_PATH] = "unknown";
	 DWORD lpExitCode;
	 // Get a handle to the process.
	 HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID );
	 // Get the process name.
	 if (NULL != hProcess )
	 {
		 HMODULE hMod;
		 DWORD cbNeeded;
		 if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod),
		 &cbNeeded) )
		 {
			 GetModuleBaseName( hProcess, hMod, szProcessName, sizeof(szProcessName) );
			 GetProcessTimes(hProcess, &ftStartTime, &ftExitTime, &ftKernelTime, &ftUserTime);
			 size_t size = sizeof(szProcessName);
			 array[count].name = malloc(size+1);
			 strncpy(array[count].name, (char *) szProcessName, size);
			 array[count].name[size+1] = '\0';
			 array[count].id = processID;
		 }
		 else return;
	 }
	 else return;
	 FileTimeToSystemTime(&ftKernelTime, &stKernel);
	 array[count].minute = stKernel.wMinute;
	 array[count].second = stKernel.wSecond;
	 GetExitCodeProcess( hProcess, &lpExitCode);
	 array[count].state = lpExitCode;
	 // Print the process name and identifier.
	 //printf( "%s (Process ID: %u)\n", szProcessName, processID );
		if ( GetProcessMemoryInfo( hProcess, &pmc, sizeof(pmc)) )
	    {
	        //printf( "WorkingSetSize: %iMB\n", pmc.WorkingSetSize/1000000 );
	        array[count++].memory = pmc.WorkingSetSize;
	    }
	//printf( "State: %d\n", lpExitCode );
	 //printf("///////////////////////////////////////////////////////////////////////////////\n");
	 CloseHandle( hProcess );
}

void main()
{
	while(1)
	{
		struct Process * array = malloc(1024*sizeof(struct Process));
			 // Get the list of process identifiers.
		 DWORD aProcesses[1024], cbNeeded, cProcesses;
		 unsigned int i;
		 if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
		 	return;
		 // Calculate how many process identifiers were returned.
		 cProcesses = cbNeeded / sizeof(DWORD);
		 // Print the name and process identifier for each process.
		 for ( i = 0; i < cProcesses; i++ )
		 	PrintProcessNameAndID( aProcesses[i], array);
		 sort_by_memory(array);
		 for ( i = 0; i < count; i++ )
		 {
			printf( "%s (Process ID: %u)\n", array[i].name, array[i].id );
			printf( "WorkingSetSize: %iMB\n", array[i].memory/(1024*1024) );
			printf( "Time in kernel mode = %um %us\n", array[i].minute, array[i].second);
			printf( "State: %d\n", array[i].state );
			printf( "///////////////////////////////////////////////////////////////////////////////\n");
		 }
		 count = 0;
		 array = NULL;
		 Sleep(20000);
		 system("cls");
	}
}

