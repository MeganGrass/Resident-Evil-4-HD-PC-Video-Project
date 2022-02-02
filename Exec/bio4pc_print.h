#pragma once

extern BOOL UseDebugLogging;

// Print
VOID OSReport(CHAR* _Format, ...);
VOID LogWarning(UINT num0, UINT num1, CHAR* _Format, ...);
VOID SrcReport(CHAR* SourceFile, UINT LineNo, CHAR* _Format, ...);
VOID ErrReport(ULONG param_1, INT param_2, CHAR* _Format, ...);
INT Fakesprintf(CHAR* _Dest, CHAR* _Format, ...);
INT Fakesnprintf(CHAR* _Dest, size_t _Count, CHAR* _Format, ...);
INT Fakevsprintf(CHAR* _Dest, CHAR* _Format, va_list _Args);
INT Fakevsprintf_s(CHAR* _DstBuf, size_t _SizeInBytes, CHAR* _Format, va_list _ArgList);
