#include "test_process.h"
#include <windows.h>

#include <stdio.h>

// Kernel32.lib on Windows 7 and Windows Server 2008 R2,

// Psapi.lib on Windows Server 2008, Windows Vista,

// Windows Server 2003, and Windows XP/2000

#include <psapi.h>

#pragma comment(lib, "psapi.lib")

BOOL findProcess(const char* process_name, int* pid, char* exe_path)
{
    DWORD aProcesses[1024];
    DWORD cbNeeded, cProcesses;
    BOOL res = 0;

    memset(aProcesses, 0, _countof(aProcesses));
    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
        return 1;

    // Calculate how many process identifiers were returned.
    cProcesses = cbNeeded / sizeof(DWORD);
    // Print the name and process identifier for each process.

    for (unsigned int i = 0; i < cProcesses; i++)
    {
        if (aProcesses[i] != 0)
        {
            char szProcessName[MAX_PATH] = { 0 };
            HMODULE hMod;
            // Get a handle to the process.
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);
            // Get the process name.
            if (hProcess != NULL)
            {
                if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
                {
                    GetModuleBaseNameA(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(WCHAR));
                }
            }
            exe_path[0] = '\0';
            if (_stricmp(szProcessName, process_name) == 0)
            {

                if (pid) *pid = aProcesses[i];
                res = 1;
                unsigned long k = MAX_PATH;

                QueryFullProcessImageNameA(hProcess, 0, exe_path, &k);
                CloseHandle(hProcess);
                // printf("LProcess #%i: %s\t(pID: %ld)\n", i, szProcessName, aProcesses[i]);
                break;
            }
            CloseHandle(hProcess);
            hProcess = NULL;
            i++;


        }

    }

    return res;
}

typedef struct    
{
    char processName[MAX_PATH];
    int pID;
   
} ProcessList;

BOOL findProcessList(const char* process_name, ProcessList *process_list,const unsigned int max_array,int* number_of_find)
{
    if (!process_list) return  0;

    DWORD aProcesses[1024];
    DWORD cbNeeded, cProcesses;
    BOOL res = 0;
 
    for (unsigned int t = 0; t < max_array; t++)
    {
        memset(&process_list[t], 0, sizeof(process_list[t]));
    }

    memset(aProcesses, 0, _countof(aProcesses));
    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
        return 1;

    // Calculate how many process identifiers were returned.
    cProcesses = cbNeeded / sizeof(DWORD);
    // Print the name and process identifier for each process.

    for (unsigned int i = 0; i < cProcesses; i++)
    {
        if (aProcesses[i] != 0)
        {
            char szProcessName[MAX_PATH] = { 0 };
            HMODULE hMod;
            // Get a handle to the process.
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);
            // Get the process name.
            if (hProcess != NULL)
            {
                if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
                {
                    GetModuleBaseNameA(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(WCHAR));
                }
            }
           
            if (_stricmp(szProcessName, process_name) == 0)
            {
                process_list[(*number_of_find)].pID = aProcesses[i];
                res = 1;
                unsigned long k = MAX_PATH;

                QueryFullProcessImageNameA(hProcess, 0, process_list[(*number_of_find)].processName, &k);
                CloseHandle(hProcess);
                (*number_of_find)++;
                // printf("LProcess #%i: %s\t(pID: %ld)\n", i, szProcessName, aProcesses[i]);
            }else
            CloseHandle(hProcess);
        }

    }

    return res;
}
void run_test_process(void)
{
   // int pID = 0;
   // char pp[MAX_PATH];
    ProcessList t[10];
    int number_of_find=0;
    //int t = findProcess("calculator.exe", &pID, pp);
    int rr = findProcessList("server64.exe", t,10, &number_of_find);
    printf("%d", rr);
}