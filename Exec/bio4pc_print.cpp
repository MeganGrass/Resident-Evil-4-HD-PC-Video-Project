
#include "..\\dllmain.h"

BOOL UseDebugLogging = FALSE;

// Print
VOID OSReport(CHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT _StrLen = (_vscprintf(_Format, _ArgList) + 1);
	CHAR* _Buffer = new CHAR[_StrLen + 1];
	RtlSecureZeroMemory(_Buffer, _StrLen);
	vsprintf_s(_Buffer, _StrLen, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Log
	std::ofstream log_file("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Resident Evil 4\\Bin32\\OSReport.log", std::ios_base::out | std::ios_base::app);
	log_file << _Buffer;

}
VOID LogWarning(UINT num0, UINT num1, CHAR* _Format, ...) {

	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT _StrLen = (_vscprintf(_Format, _ArgList) + 1);
	CHAR* _Buffer = new CHAR[_StrLen + 1];
	RtlSecureZeroMemory(_Buffer, _StrLen);
	vsprintf_s(_Buffer, _StrLen, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Log
	std::ofstream log_file("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Resident Evil 4\\Bin32\\Warning.log", std::ios_base::out | std::ios_base::app);
	log_file << "[" << num0 << "]" << "[" << num1 << "]" << " " << _Buffer;

}
VOID SrcReport(CHAR* SourceFile, UINT LineNo, CHAR* _Format, ...) {
	// VOID SrcReport(CHAR* SourceFile, UINT LineNo, WCHAR* _Format, ...) {

		// _Format is actually Chinese "Big5 (Traditional)"

		// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT _StrLen = (_vscprintf(_Format, _ArgList) + 1);
	CHAR* _Buffer = new CHAR[_StrLen + 1];
	RtlSecureZeroMemory(_Buffer, _StrLen);
	vsprintf_s(_Buffer, _StrLen, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Log
	std::ofstream log_file("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Resident Evil 4\\Bin32\\Source.log", std::ios_base::out | std::ios_base::app);
	log_file << SourceFile << "(" << LineNo << ")" << " " << _Buffer;

}
VOID ErrReport(ULONG param_1, INT param_2, CHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT _StrLen = (_vscprintf(_Format, _ArgList) + 1);
	CHAR* _Buffer = new CHAR[_StrLen + 1];
	RtlSecureZeroMemory(_Buffer, _StrLen);
	vsprintf_s(_Buffer, _StrLen, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Log
	std::ofstream log_file("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Resident Evil 4\\Bin32\\Error.log", std::ios_base::out | std::ios_base::app);
	log_file << _Buffer << std::endl;

}
INT Fakesprintf(CHAR* _Dest, CHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT _StrLen = (_vscprintf(_Format, _ArgList) + 1);
	CHAR* _Buffer = new CHAR[_StrLen + 1];
	RtlSecureZeroMemory(_Buffer, _StrLen);
	vsprintf_s(_Buffer, _StrLen, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Log
	std::ofstream log_file("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Resident Evil 4\\Bin32\\sprintf_s.log", std::ios_base::out | std::ios_base::app);
	log_file << _Buffer << std::endl;

	return sprintf_s(_Dest, _StrLen + 1, _Buffer);
}
INT Fakesnprintf(CHAR* _Dest, size_t _Count, CHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT _StrLen = (_vscprintf(_Format, _ArgList) + 1);
	CHAR* _Buffer = new CHAR[_StrLen + 1];
	RtlSecureZeroMemory(_Buffer, _StrLen);
	vsprintf_s(_Buffer, _StrLen, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Log
	std::ofstream log_file("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Resident Evil 4\\Bin32\\snprintf.log", std::ios_base::out | std::ios_base::app);
	log_file << _Buffer << std::endl;

	return snprintf(_Dest, _StrLen + 1, _Buffer);
}
INT Fakevsprintf(CHAR* _Dest, CHAR* _Format, va_list _Args) {
	int iVar1 = _vsprintf_l(_Dest, _Format, (_locale_t)0x0, _Args);
	std::ofstream log_file("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Resident Evil 4\\Bin32\\_vsprintf_l.log", std::ios_base::out | std::ios_base::app);
	log_file << _Dest << std::endl;
	return iVar1;
}
INT Fakevsprintf_s(CHAR* _DstBuf, size_t _SizeInBytes, CHAR* _Format, va_list _ArgList) {
	int iVar1 = _vsprintf_s_l(_DstBuf, _SizeInBytes, _Format, (_locale_t)0x0, _ArgList);
	std::ofstream log_file("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Resident Evil 4\\Bin32\\_vsprintf_s_l.log", std::ios_base::out | std::ios_base::app);
	log_file << _DstBuf << std::endl;
	return iVar1;
}