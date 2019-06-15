#include  "test_run_process_with_result.h"

#include <Windows.h>
#include <string>


#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "Wtsapi32.lib")
#pragma comment(lib, "psapi.lib")
bool runProcess2(wchar_t* command, bool is_blocking = true, unsigned long  *exit_code = NULL, wchar_t* start_in = L"")
{
    wchar_t current_directory[MAX_PATH] = { 0 };

    if (wcslen(start_in) > 0)
        wcscpy_s(current_directory, _countof(current_directory), start_in);
    else
        GetCurrentDirectoryW(sizeof(current_directory), current_directory);

    bool ret = false;

    HANDLE hToken = NULL;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_DUPLICATE, &hToken))
    {
        HANDLE hDuplicate = NULL;
        if (DuplicateTokenEx(hToken, TOKEN_ASSIGN_PRIMARY | TOKEN_DUPLICATE | TOKEN_QUERY | TOKEN_ADJUST_DEFAULT | TOKEN_ADJUST_SESSIONID, NULL, SecurityImpersonation, TokenPrimary, &hDuplicate))
        {
            STARTUPINFOW StartupInfo;
            ZeroMemory(&StartupInfo, sizeof(STARTUPINFO));
            StartupInfo.cb = sizeof(STARTUPINFO);
            StartupInfo.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
            StartupInfo.wShowWindow = SW_HIDE;

            PROCESS_INFORMATION ProcessInformation;
            ZeroMemory(&ProcessInformation, sizeof(PROCESS_INFORMATION));


            //---------------//--------
            GetStartupInfo(&StartupInfo);      //set startupinfo for the spawned process
            SECURITY_ATTRIBUTES saAttr;

            saAttr.lpSecurityDescriptor = NULL;
            saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
            saAttr.bInheritHandle = true;         //allow inheritable handles

            std::string strResult;
            HANDLE newstdin, newstdout, read_stdout, write_stdin;  //pipe handles
            CreatePipe(&newstdin, &write_stdin, &saAttr, 0);   //create stdin pipe

            CreatePipe(&read_stdout, &newstdout, &saAttr, 0);  //create stdout pipe
            StartupInfo.hStdOutput = newstdout;
            StartupInfo.hStdError = newstdout;     //set the new handles for the child process
            StartupInfo.hStdInput = newstdin;
            //--------
            if (CreateProcessWithTokenW(hDuplicate, LOGON_WITH_PROFILE, NULL, command, CREATE_NO_WINDOW, NULL, current_directory, &StartupInfo, &ProcessInformation))
            {
                if (is_blocking)
                    WaitForSingleObject(ProcessInformation.hProcess, INFINITE);


                bool bProcessEnded = false;


                for (;;)
                {
                    char buf[1024];
                    DWORD dwRead = 0;
                    DWORD dwAvail = 0;
                    unsigned long bread;   //bytes read

                    PeekNamedPipe(read_stdout, buf, 1023, &bread, &dwAvail, NULL);


                    if (bread != 0)
                    {
                        if (dwAvail > 1023)
                        {
                            while (bread >= 1023)
                            {
                                ReadFile(read_stdout, buf, 1023, &bread, NULL);  //read the stdout pipe
                                printf("%s", buf);
                            }
                        }
                        else {
                            ReadFile(read_stdout, buf, 1023, &bread, NULL);
                            printf("%s", buf);
                        }
                    }
                }

                if (exit_code != NULL) {
                    if (!GetExitCodeProcess(ProcessInformation.hProcess, exit_code))
                        *exit_code = -1;
                }


                CloseHandle(ProcessInformation.hThread);
                ProcessInformation.hThread = NULL;
                CloseHandle(ProcessInformation.hProcess);
                ProcessInformation.hProcess = NULL;

                CloseHandle(newstdin);
                CloseHandle(newstdout);
                CloseHandle(read_stdout);
                CloseHandle(write_stdin);

                newstdin = NULL;
                newstdout = NULL;
                read_stdout = NULL;
                write_stdin = NULL;

                ret = true;
            }
            CloseHandle(hDuplicate);
            if (newstdin)CloseHandle(newstdin);
            if (newstdout)CloseHandle(newstdout);
            if (read_stdout)CloseHandle(read_stdout);
            if (write_stdin)CloseHandle(write_stdin);

        }
        CloseHandle(hToken);
        hToken = NULL;

    }
    return ret;
}


std::string ReadFromPipe(PROCESS_INFORMATION piProcInfo, HANDLE pipout_r) {
    const int buffer_size = 1024;
    CHAR chBuf[buffer_size];
    DWORD dwRead;
    DWORD available;
    bool bSuccess = FALSE;
    bool tSuccess = FALSE;
    std::string out = "";
    for (size_t i = 0; i < 20; i++)
    {
        Sleep(1);
        tSuccess = PeekNamedPipe(pipout_r, chBuf, sizeof(chBuf), &dwRead, &available, NULL);
        if (tSuccess) {
            int temp_available = available;
            while (temp_available > 0) {
                bSuccess = ReadFile(pipout_r, chBuf, buffer_size, &dwRead, NULL);
                if (!bSuccess || dwRead == 0) break;
                std::string s(chBuf, dwRead);
                out += s;
                temp_available = temp_available - buffer_size;
            }
        }
        if (available == 0)
            break;
    }
    return out;

}
bool runProcessWithResultW(wchar_t* cmdline, unsigned long *exit_code, std::string &result_out, wchar_t* start_in = L"")
{
    wchar_t current_directory[MAX_PATH] = { 0 };

    if (wcslen(start_in) > 0)
        wcscpy_s(current_directory, _countof(current_directory), start_in);
    else
        GetCurrentDirectoryW(sizeof(current_directory), current_directory);


    STARTUPINFOW sti = { 0 };
    SECURITY_ATTRIBUTES sats = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    HANDLE pipin_w, pipin_r, pipout_w, pipout_r;
    // DWORD writ;

    pipin_w = pipin_r = pipout_w = pipout_r = NULL;

    //set SECURITY_ATTRIBUTES struct fields
    sats.nLength = sizeof(sats);
    sats.bInheritHandle = TRUE;
    sats.lpSecurityDescriptor = NULL;


    //*********************** CREATE PIP *******************************
    //create child's stdout pipes
    if (!CreatePipe(&pipout_r, &pipout_w, &sats, 0))  return false;
    //and its stdin pipes
    if (!CreatePipe(&pipin_r, &pipin_w, &sats, 0)) return false;

    //now set STARTUPINFO struct fields (from the child's point of view)
    sti.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    sti.wShowWindow = SW_HIDE;
    sti.hStdInput = pipin_r;
    sti.hStdOutput = pipout_w;
    sti.hStdError = pipout_w;
    HANDLE hToken = nullptr;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_DUPLICATE, &hToken))
    {
        HANDLE hDuplicate = nullptr;
        if (DuplicateTokenEx(hToken, TOKEN_ASSIGN_PRIMARY | TOKEN_DUPLICATE | TOKEN_QUERY | TOKEN_ADJUST_DEFAULT | TOKEN_ADJUST_SESSIONID, NULL, SecurityImpersonation, TokenPrimary, &hDuplicate))
        {
            //create the process...
            if (CreateProcessWithTokenW(hDuplicate, LOGON_WITH_PROFILE, NULL, cmdline, CREATE_NO_WINDOW, NULL, current_directory, &sti, &pi))
            {
                WaitForSingleObject(pi.hProcess, 3000);
                if (exit_code != nullptr) {
                    if (!GetExitCodeProcess(pi.hProcess, exit_code))
                        *exit_code = -1;
                }
                result_out = ReadFromPipe(pi, pipout_r);

                if (pi.hProcess != nullptr) CloseHandle(pi.hProcess);
                if (pi.hThread != nullptr) CloseHandle(pi.hThread);

                pi.hProcess = nullptr;
                pi.hThread = nullptr;
            }
            CloseHandle(hDuplicate);
            hDuplicate = nullptr;
        }

        CloseHandle(hToken);
        hToken = nullptr;
    }

    //clean up any unfinished business
    if (pipin_w != nullptr) CloseHandle(pipin_w);
    if (pipin_r != nullptr) CloseHandle(pipin_r);
    if (pipout_w != nullptr) CloseHandle(pipout_w);
    if (pipout_r != nullptr) CloseHandle(pipout_r);

    pipin_w = nullptr;
    pipin_r = nullptr;
    pipout_w = nullptr;
    pipout_r = nullptr;
    return true;
}

void run_test()
{
    wchar_t command[MAX_PATH] = { 0 };
    swprintf_s(command, _countof(command) - 1, L"C:\\Program Files\\MySQL\\MySQL Server 8.0\\bin\\mysql.exe  --defaults-file=\"C:\\Users\\AT\\MySQL\\mysql-sandboxes\\3311\\my.cnf\"  --database=\"sys\" --password=\"%s\" -e \"select now(); \"", L"12342");
    // swprintf_s(command,  _countof(command) - 1, L"C:\\Users\\AT\\Desktop\\process_test\\appChildProcess\\x64\\Debug\\appChildProcess.exe");
    unsigned long exit_code;
    std::string result_out;
    runProcessWithResultW(command, &exit_code, result_out);

    if (!runProcessWithResultW(command, &exit_code, result_out) || exit_code != S_OK)
    {

        printf("failed: \n\r %s", result_out.c_str());
    }
    else {

        printf("%s", result_out.c_str());
    }
    getchar();
}