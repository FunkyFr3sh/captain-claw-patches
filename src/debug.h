#ifndef DEBUG_H 
#define DEBUG_H 

#ifdef __cplusplus
extern "C" {
#endif

#define FILE_EXISTS(a) (GetFileAttributes(a) != INVALID_FILE_ATTRIBUTES)

// ### types ###

// ### Variables ###

// ### Functions ###

LONG WINAPI dbg_exception_handler(EXCEPTION_POINTERS* exception);

#ifdef __cplusplus
};
#endif

#endif
