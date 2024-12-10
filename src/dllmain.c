#include <windows.h>
#include <commctrl.h>
#include "patch.h"
#include "winmain.h"
#include "debug.h"


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch(fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        patch_setdword((DWORD*)(0x004AEEC7 + 1), (DWORD)dbg_exception_handler);
        patch_call((char*)0x004A66B4, (char*)fake_WinMain);
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

EXTERN_C HRESULT WINAPI TaskDialogIndirectHack(
    const TASKDIALOGCONFIG *pTaskConfig, int *pnButton, int *pnRadioButton, BOOL *pfVerificationFlagChecked)
{
    return TaskDialogIndirect(pTaskConfig, pnButton, pnRadioButton, pfVerificationFlagChecked);
}

// petool genproxy - https://github.com/FunkyFr3sh/petool
#if defined(_MSC_VER)
#pragma comment(linker, "/export:_SmackBufferString@8=SMACKW32x._SmackBufferString@8,@1")
#pragma comment(linker, "/export:_SmackBufferOpen@24=SMACKW32x._SmackBufferOpen@24,@2")
#pragma comment(linker, "/export:_SmackBufferBlit@32=SMACKW32x._SmackBufferBlit@32,@3")
#pragma comment(linker, "/export:_SmackBufferFocused@4=SMACKW32x._SmackBufferFocused@4,@4")
#pragma comment(linker, "/export:_SmackBufferNewPalette@12=SMACKW32x._SmackBufferNewPalette@12,@5")
#pragma comment(linker, "/export:_SmackBufferClose@4=SMACKW32x._SmackBufferClose@4,@6")
#pragma comment(linker, "/export:_SmackBufferSetPalette@4=SMACKW32x._SmackBufferSetPalette@4,@7")
#pragma comment(linker, "/export:_SmackBufferClear@8=SMACKW32x._SmackBufferClear@8,@8")
#pragma comment(linker, "/export:_SmackSetSystemRes@4=SMACKW32x._SmackSetSystemRes@4,@9")
#pragma comment(linker, "/export:_SmackBufferToBuffer@32=SMACKW32x._SmackBufferToBuffer@32,@10")
#pragma comment(linker, "/export:_SmackBufferToBufferTrans@36=SMACKW32x._SmackBufferToBufferTrans@36,@11")
#pragma comment(linker, "/export:_SmackBufferFromScreen@16=SMACKW32x._SmackBufferFromScreen@16,@12")
#pragma comment(linker, "/export:_SmackBufferCopyPalette@12=SMACKW32x._SmackBufferCopyPalette@12,@13")
#pragma comment(linker, "/export:_SmackOpen@12=SMACKW32x._SmackOpen@12,@14")
#pragma comment(linker, "/export:_SmackSimulate@4=SMACKW32x._SmackSimulate@4,@15")
#pragma comment(linker, "/export:_SmackFrameRate@4=SMACKW32x._SmackFrameRate@4,@16")
#pragma comment(linker, "/export:_SmackSoundOnOff@8=SMACKW32x._SmackSoundOnOff@8,@17")
#pragma comment(linker, "/export:_SmackClose@4=SMACKW32x._SmackClose@4,@18")
#pragma comment(linker, "/export:_SmackDoFrame@4=SMACKW32x._SmackDoFrame@4,@19")
#pragma comment(linker, "/export:_SmackSummary@8=SMACKW32x._SmackSummary@8,@20")
#pragma comment(linker, "/export:_SmackNextFrame@4=SMACKW32x._SmackNextFrame@4,@21")
#pragma comment(linker, "/export:_SmackToScreen@24=SMACKW32x._SmackToScreen@24,@22")
#pragma comment(linker, "/export:_SmackToBuffer@28=SMACKW32x._SmackToBuffer@28,@23")
#pragma comment(linker, "/export:_SmackColorTrans@8=SMACKW32x._SmackColorTrans@8,@24")
#pragma comment(linker, "/export:_SmackColorRemap@16=SMACKW32x._SmackColorRemap@16,@25")
#pragma comment(linker, "/export:_SmackGetTrackData@12=SMACKW32x._SmackGetTrackData@12,@26")
#pragma comment(linker, "/export:_SmackGoto@8=SMACKW32x._SmackGoto@8,@27")
#pragma comment(linker, "/export:_SmackToBufferRect@8=SMACKW32x._SmackToBufferRect@8,@28")
#pragma comment(linker, "/export:_SmackSoundInTrack@8=SMACKW32x._SmackSoundInTrack@8,@29")
#pragma comment(linker, "/export:_SmackVolumePan@16=SMACKW32x._SmackVolumePan@16,@30")
#pragma comment(linker, "/export:_SmackSoundCheck@0=SMACKW32x._SmackSoundCheck@0,@31")
#pragma comment(linker, "/export:_SmackWait@4=SMACKW32x._SmackWait@4,@32")
#pragma comment(linker, "/export:_SmackSoundUseMSS@4=SMACKW32x._SmackSoundUseMSS@4,@33")
#pragma comment(linker, "/export:_SmackSoundUseDW@12=SMACKW32x._SmackSoundUseDW@12,@34")
#pragma comment(linker, "/export:_donemarker@20=SMACKW32x._donemarker@20,@35")
#pragma comment(linker, "/export:_TimerFunc@20=SMACKW32x._TimerFunc@20,@36")
#pragma comment(linker, "/export:_SetDirectSoundHWND@4=SMACKW32x._SetDirectSoundHWND@4,@37")
#pragma comment(linker, "/export:_SmackSoundUseDirectSound@4=SMACKW32x._SmackSoundUseDirectSound@4,@38")
#pragma comment(linker, "/export:_SmackSoundUseWin@0=SMACKW32x._SmackSoundUseWin@0,@39")
#pragma comment(linker, "/export:TaskDialogIndirectHack=_TaskDialogIndirectHack@16,@40")
#endif
