
#include "system.h"

// Create
WCHAR* System_String::Get(CONST WCHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT _StrLen = (_vscwprintf(_Format, _ArgList) + 2);
	WCHAR* _Buffer = new WCHAR[_StrLen];
	RtlSecureZeroMemory(_Buffer, _StrLen);
	vswprintf_s(_Buffer, _StrLen, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// complete
	return _Buffer;
}
std::wstring System_String::Get(CONST std::wstring _Format, ...) {

	// Format
	va_list _ArgList;
	__crt_va_start(_ArgList, _Format);
	INT _StrLen = (_vscwprintf(_Format.c_str(), _ArgList) + 2);
	WCHAR* String = new WCHAR[_StrLen];
	RtlSecureZeroMemory(String, _StrLen);
	vswprintf_s(String, _StrLen, _Format.c_str(), _ArgList);
	__crt_va_end(_ArgList);
	std::unique_ptr<WCHAR[]> formatted(String);

	// Complete
	return std::wstring(formatted.get());
}
// Conversion
WCHAR* System_String::ToW(CONST CHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscprintf(_Format, _ArgList) + 1);
	CHAR* _DstBuf = new CHAR[StringSize];
	RtlSecureZeroMemory(_DstBuf, StringSize);
	vsprintf_s(_DstBuf, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Conversion
	INT _SizeInBytes = MultiByteToWideChar(CP_ACP, 0, _DstBuf, -1, NULL, NULL);
	WCHAR* lpWideCharStr = new WCHAR[(_SizeInBytes * 2) + 2];
	RtlSecureZeroMemory(lpWideCharStr, ((_SizeInBytes * 2) + 2));
	MultiByteToWideChar(CP_ACP, 0, _DstBuf, -1, lpWideCharStr, (_SizeInBytes * 2));

	// Terminate
	delete[]_DstBuf;
	return lpWideCharStr;
}
WCHAR* System_String::ToUpper(CONST WCHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscwprintf(_Format, _ArgList) + 2);
	WCHAR* _Buffer = new WCHAR[StringSize];
	RtlSecureZeroMemory(_Buffer, StringSize);
	vswprintf_s(_Buffer, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Convert
	WCHAR* _String;
	_wcsupr_s(_String = _wcsdup(_Buffer), wcslen(_Buffer) + 1);
	delete[] _Buffer;

	// Complete
	return _String;
}
WCHAR* System_String::ToLower(CONST WCHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscwprintf(_Format, _ArgList) + 2);
	WCHAR* _Buffer = new WCHAR[StringSize];
	RtlSecureZeroMemory(_Buffer, StringSize);
	vswprintf_s(_Buffer, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Convert
	WCHAR* _String;
	_wcslwr_s(_String = _wcsdup(_Buffer), wcslen(_Buffer) + 2);
	delete[] _Buffer;

	// Complete
	return _String;
}
// Integer
ULONG System_String::ToIntU(CONST WCHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT _StrLen = (_vscwprintf(_Format, _ArgList) + 2);
	WCHAR* String = new WCHAR[_StrLen];
	RtlSecureZeroMemory(String, _StrLen);
	vswprintf_s(String, _StrLen, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Convert
	ULONG Value = NULL;
	if (String[1] != 0x58 && String[1] != 0x78) {
		Value = wcstoul(String, NULL, 10);
	}
	else {
		Value = wcstoul(String, NULL, 16);
	}
	delete[] String;

	// Complete
	return Value;
}
// Float
DOUBLE System_String::ToFloat(CONST WCHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscwprintf(_Format, _ArgList) + 2);
	WCHAR* _String = new WCHAR[StringSize];
	RtlSecureZeroMemory(_String, StringSize);
	vswprintf_s(_String, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	DOUBLE Value = _wtof(_String);
	delete[] _String;
	return Value;
}
// Commandline
ULONG System_String::GetArgCountW(CONST WCHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscwprintf(_Format, _ArgList) + 2);
	WCHAR* CmdLine = new WCHAR[StringSize];
	RtlSecureZeroMemory(CmdLine, StringSize);
	vswprintf_s(CmdLine, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	INT NumArgs = NULL;
	CommandLineToArgvW(CmdLine, &NumArgs);
	delete[] CmdLine;
	return NumArgs;
}
WCHAR* System_String::GetArgW(ULONG iArg, CONST WCHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscwprintf(_Format, _ArgList) + 2);
	WCHAR* CmdLine = new WCHAR[StringSize];
	RtlSecureZeroMemory(CmdLine, StringSize);
	vswprintf_s(CmdLine, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	INT NumArgs = NULL;
	LPWSTR* List = CommandLineToArgvW(CmdLine, &NumArgs);
	delete[] CmdLine;
	if (!NumArgs || (INT)iArg >= NumArgs) { return nullptr; }
	return List[iArg];
}
// Message
VOID System_String::MessageW(CONST WCHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscwprintf(_Format, _ArgList) + 2);
	WCHAR* lpText = new WCHAR[StringSize];
	RtlSecureZeroMemory(lpText, StringSize);
	vswprintf_s(lpText, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	MessageBoxW(0, lpText, APPLICATION_NAME_W, 0);
	delete[] lpText;
}
INT System_String::MessageYesNoW(HWND hWndOwner, CONST WCHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscwprintf(_Format, _ArgList) + 2);
	WCHAR* lpText = new WCHAR[StringSize];
	RtlSecureZeroMemory(lpText, StringSize);
	vswprintf_s(lpText, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	INT Result = MessageBoxW(hWndOwner, lpText, APPLICATION_NAME_W, MB_YESNO);
	delete[] lpText;

	return Result;
}
// BOOL
BOOL System_String::GetBoolFromStr(CONST WCHAR* String) {

	// Error
	if (String == nullptr) { return FALSE; }
	if(!wcslen(String)) { return FALSE; }

	// Parse
	BOOL Flag = FALSE;
	WCHAR* NewString = ToUpper(String);
	if (!StrCmpW(L"FALSE", NewString)) { Flag = FALSE; }
	if (!StrCmpW(L"TRUE", NewString)) { Flag = TRUE; }
	if (!StrCmpW(L"OFF", NewString)) { Flag = FALSE; }
	if (!StrCmpW(L"ON", NewString)) { Flag = TRUE; }
	if (!StrCmpW(L"FAIL", NewString)) { Flag = FALSE; }
	if (!StrCmpW(L"SUCCESS", NewString)) { Flag = TRUE; }
	if (!StrCmpW(L"DISABLED", NewString)) { Flag = FALSE; }
	if (!StrCmpW(L"ENABLED", NewString)) { Flag = TRUE; }

	// Complete
	return Flag;
}
WCHAR* System_String::GetStrFromBool(BOOL Flag) {
	if (!Flag) { return Get(L"FALSE"); }
	else { return Get(L"TRUE"); }
}