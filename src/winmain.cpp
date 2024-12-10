#include <windows.h>
#include "patch.h"
#include "wine.h"

int(WINAPI* claw_WinMain)(HINSTANCE, HINSTANCE, PSTR, int) = 
    (int(WINAPI*)(HINSTANCE, HINSTANCE, PSTR, int))0x004A3490;

int APIENTRY fake_WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    if (wine_add_dll_overrides())
    {
        /* newly added dll overrides only work after a restart */
        char exe_path[MAX_PATH] = {0};
        GetModuleFileNameA(NULL, exe_path, _countof(exe_path));
        
        ShellExecuteA(NULL, "open", exe_path, cmdline, NULL, cmdshow);
        return 0;
    }
    
    /* WINE does not set the working directory correctly in some cases */
    WCHAR exe_path[MAX_PATH] = {0};
    GetModuleFileNameW(NULL, exe_path, _countof(exe_path));
    
    WCHAR drive[MAX_PATH] = {0};
    WCHAR dir[MAX_PATH] = {0};
    _wsplitpath(exe_path, drive, dir, NULL, NULL);
    
    WCHAR working_dir[MAX_PATH] = {0};
    _wmakepath(working_dir, drive, dir, NULL, NULL);
    
    SetCurrentDirectoryW(working_dir);

    return claw_WinMain(hInst, hInstPrev, cmdline, cmdshow);
}
