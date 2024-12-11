#include <windows.h>
#include <dbghelp.h>
#include <stdio.h>
#include <time.h>
#include "debug.h"

LONG (WINAPI* claw_TopLevelExceptionFilter)(EXCEPTION_POINTERS*) = (LONG(WINAPI*)(EXCEPTION_POINTERS*))0x004AEE81;

LONG WINAPI dbg_exception_handler(EXCEPTION_POINTERS* exception)
{
    static int dmp_count;
    
    if (dmp_count >= 10 || !exception || !exception->ExceptionRecord)
    {
        return claw_TopLevelExceptionFilter(exception);
    }

    CreateDirectoryA("Errors", NULL);

    char file_name[MAX_PATH] = {0};

    SYSTEMTIME st;
    GetLocalTime(&st);

    _snprintf(
        file_name,
        sizeof(file_name) - 1,
        "Errors\\%04d-%02d-%02d_%02d-%02d-%02d-%03d_0x%p.dmp",
        st.wYear,
        st.wMonth,
        st.wDay,
        st.wHour,
        st.wMinute,
        st.wSecond,
        st.wMilliseconds,
        exception->ExceptionRecord->ExceptionAddress);
        
    HANDLE dmp_file =
        CreateFile(
            file_name,
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_WRITE | FILE_SHARE_READ,
            0,
            CREATE_NEW,
            0,
            0);

    if (dmp_file != INVALID_HANDLE_VALUE)
    {
        dmp_count++;

        MINIDUMP_EXCEPTION_INFORMATION info;
        info.ThreadId = GetCurrentThreadId();
        info.ExceptionPointers = exception;
        info.ClientPointers = TRUE;

        MiniDumpWriteDump(
            GetCurrentProcess(),
            GetCurrentProcessId(),
            dmp_file,
            MiniDumpNormal,
            &info,
            NULL,
            NULL);

        CloseHandle(dmp_file);
    }

    return claw_TopLevelExceptionFilter(exception);
}
