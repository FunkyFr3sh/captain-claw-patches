#ifndef DEBUG_H 
#define DEBUG_H 

#define FILE_EXISTS(a) (GetFileAttributes(a) != INVALID_FILE_ATTRIBUTES)

// ### types ###

// ### Variables ###

// ### Functions ###

LONG WINAPI dbg_exception_handler(EXCEPTION_POINTERS* exception);

#endif
