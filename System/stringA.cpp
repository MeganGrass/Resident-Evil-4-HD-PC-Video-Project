
#include "system.h"

#include <random>

CHAR* System_String::GetRandomString(VOID) {
	std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

	std::random_device rd;
	std::mt19937 generator(rd());

	std::shuffle(str.begin(), str.end(), generator);

	std::string rstr = str.substr(0, 32);

	return (CHAR * )rstr.c_str();    // assumes 32 < number of characters in str         
}

// Create
CHAR* System_String::Get(CONST CHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT _StrLen = (_vscprintf(_Format, _ArgList) + 1);
	CHAR* _Buffer = new CHAR[_StrLen];
	RtlSecureZeroMemory(_Buffer, _StrLen);
	vsprintf_s(_Buffer, _StrLen, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Complete
	return _Buffer;
}
std::string System_String::Get(CONST std::string _Format, ...) {

	// Format
	va_list _ArgList;
	__crt_va_start(_ArgList, _Format);
	INT _StrLen = (_vscprintf(_Format.c_str(), _ArgList) + 1);
	CHAR* String = new CHAR[_StrLen];
	RtlSecureZeroMemory(String, _StrLen);
	vsprintf_s(String, _StrLen, _Format.c_str(), _ArgList);
	__crt_va_end(_ArgList);
	std::unique_ptr<CHAR[]> formatted(String);

	// Complete
	return std::string(formatted.get());
}
VOID System_String::Get(ULONG& StringSize, CHAR& String, CONST CHAR* _Format, ...) {

	// Clear Buffer
	if (strlen(&String)) { memset(&String, 0x00, strlen(&String)); }

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	StringSize = (_vscprintf(_Format, _ArgList) + 1);
	CHAR* _Buffer = new CHAR[StringSize];
	RtlSecureZeroMemory(_Buffer, StringSize);
	vsprintf_s(_Buffer, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Create
	RtlSecureZeroMemory(&String, StringSize);
	memcpy_s(&String, StringSize, _Buffer, StringSize);

	// Cleanup
	delete[] _Buffer;
}
// Conversion
CHAR* System_String::ToA(CONST WCHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscwprintf(_Format, _ArgList) + 2);
	WCHAR* String = new WCHAR[StringSize];
	RtlSecureZeroMemory(String, StringSize);
	vswprintf_s(String, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Conversion
	INT _SizeInBytes = WideCharToMultiByte(CP_ACP, 0, String, -1, NULL, NULL, NULL, NULL);
	CHAR* lpMultiByteStr = new CHAR[_SizeInBytes + 2];
	RtlSecureZeroMemory(lpMultiByteStr, (_SizeInBytes + 2));
	WideCharToMultiByte(CP_ACP, 0, String, -1, lpMultiByteStr, _SizeInBytes, NULL, NULL);

	// Terminate
	delete[]String;
	return lpMultiByteStr;
}
CHAR* System_String::ToUpper(CONST CHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscprintf(_Format, _ArgList) + 1);
	CHAR* _Buffer = new CHAR[StringSize];
	RtlSecureZeroMemory(_Buffer, StringSize);
	vsprintf_s(_Buffer, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Convert
	CHAR* String;
	_strupr_s(String = _strdup(_Buffer), strlen(_Buffer) + 1);
	delete[] _Buffer;

	// Complete
	return String;
}
CHAR* System_String::ToLower(CONST CHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscprintf(_Format, _ArgList) + 1);
	CHAR* _Buffer = new CHAR[StringSize];
	RtlSecureZeroMemory(_Buffer, StringSize);
	vsprintf_s(_Buffer, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Convert
	CHAR* String;
	_strlwr_s(String = _strdup(_Buffer), strlen(_Buffer) + 1);
	delete[] _Buffer;

	// Complete
	return String;
}
// Integer
LONG System_String::ToInt(CONST CHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscprintf(_Format, _ArgList) + 1);
	CHAR* String = new CHAR[StringSize];
	RtlSecureZeroMemory(String, StringSize);
	vsprintf_s(String, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Convert
	LONG Value = NULL;
	if (String[1] != 0x58 && String[1] != 0x78) {
		Value = strtol(String, NULL, 10);
	}
	else {
		Value = strtol(String, NULL, 16);
	}
	delete[] String;

	// Complete
	return Value;
}
ULONG System_String::ToIntU(CONST CHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscprintf(_Format, _ArgList) + 1);
	CHAR* String = new CHAR[StringSize];
	RtlSecureZeroMemory(String, StringSize);
	vsprintf_s(String, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Convert
	ULONG Value = NULL;
	if (String[1] != 0x58 && String[1] != 0x78) {
		Value = strtoul(String, NULL, 10);
	}
	else {
		Value = strtoul(String, NULL, 16);
	}
	delete[] String;

	// Complete
	return Value;
}
LLONG System_String::ToInt64(CONST CHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscprintf(_Format, _ArgList) + 1);
	CHAR* String = new CHAR[StringSize];
	RtlSecureZeroMemory(String, StringSize);
	vsprintf_s(String, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Convert
	LLONG Value = NULL;
	if (&String[1] != (CHAR*)0x58 && &String[1] != (CHAR*)0x78) {
		Value = strtoll(String, NULL, 10);
	}
	else {
		Value = strtoll(String, NULL, 16);
	}
	delete[] String;

	// Complete
	return Value;
}
ULLONG System_String::ToIntU64(CONST CHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscprintf(_Format, _ArgList) + 1);
	CHAR* String = new CHAR[StringSize];
	RtlSecureZeroMemory(String, StringSize);
	vsprintf_s(String, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Convert
	ULLONG Value = NULL;
	if (&String[1] != (CHAR*)0x58 && &String[1] != (CHAR*)0x78) {
		Value = strtoull(String, NULL, 10);
	}
	else {
		Value = strtoull(String, NULL, 16);
	}
	delete[] String;

	// Complete
	return Value;
}
CHAR* System_String::FromInt(LLONG Value) {
	CHAR* String = new CHAR[_MAX_U64TOSTR_BASE2_COUNT];
	RtlSecureZeroMemory(String, _MAX_U64TOSTR_BASE2_COUNT);
	_i64toa_s(Value, &String[0x00], _MAX_U64TOSTR_BASE2_COUNT, 10);
	return String;
}
CHAR* System_String::FromIntU(ULLONG Value) {
	CHAR* String = new CHAR[_MAX_U64TOSTR_BASE2_COUNT];
	RtlSecureZeroMemory(String, _MAX_U64TOSTR_BASE2_COUNT);
	_ui64toa_s(Value, &String[0x00], _MAX_U64TOSTR_BASE2_COUNT, 10);
	return String;
}
// Float
DOUBLE System_String::ToFloat(CONST CHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscprintf(_Format, _ArgList) + 1);
	CHAR* String = new CHAR[StringSize];
	RtlSecureZeroMemory(String, StringSize);
	vsprintf_s(String, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	DOUBLE Value = atof(String);
	delete[] String;
	return Value;
}
CHAR* System_String::FromFloat(DOUBLE Value) {
	CHAR* String = new CHAR[_CVTBUFSIZE];
	RtlSecureZeroMemory(String, _CVTBUFSIZE);
	_gcvt_s(&String[0x00], _CVTBUFSIZE, Value, 15);
	return String;
}
// Commandline
CHAR** System_String::CommandLine(ULONG& nArgs, CONST CHAR* _Format, ...) {

	// http://alter.org.ua/docs/win/args/

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscprintf(_Format, _ArgList) + 1);
	CHAR* _Buffer = new CHAR[StringSize];
	RtlSecureZeroMemory(_Buffer, StringSize);
	vsprintf_s(_Buffer, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Error
	nArgs = NULL;
	if (!strlen(_Buffer)) { delete[] _Buffer; return NULL; }

	// Setup
	size_t i = ((StringSize + 2) / 2) * sizeof(PVOID) + sizeof(PVOID);
	PCHAR* argv = (PCHAR*)GlobalAlloc(GMEM_FIXED, i + (StringSize + 2) * sizeof(CHAR));
	PCHAR _argv = (PCHAR)(((PUCHAR)argv) + i);
	if (_argv && argv) { argv[NULL] = _argv; }
	else { delete[] _Buffer; return NULL; }

	// Local
	CHAR a = '\0';
	size_t j = i = NULL;
	BOOLEAN in_QM = FALSE;
	BOOLEAN in_TEXT = FALSE;
	BOOLEAN in_SPACE = TRUE;

	// Parse
	while (_Buffer[i]) {
		a = _Buffer[i];
		if (in_QM) {
			if (a == '\"') { in_QM = FALSE; }
			else { _argv[j] = a; j++; }
		}
		else {
			switch (a) {
			case '\"':
				in_QM = TRUE;
				in_TEXT = TRUE;
				if (in_SPACE) {
					argv[nArgs] = _argv + j;
					nArgs++;
				}
				in_SPACE = FALSE;
				break;
			case ' ':
			case '\t':
			case '\n':
			case '\r':
				if (in_TEXT) {
					_argv[j] = '\0';
					j++;
				}
				in_TEXT = FALSE;
				in_SPACE = TRUE;
				break;
			default:
				in_TEXT = TRUE;
				if (in_SPACE) {
					argv[nArgs] = _argv + j;
					nArgs++;
				}
				_argv[j] = a;
				j++;
				in_SPACE = FALSE;
				break;
			}
		}
		i++;
	}

	// Complete
	delete[] _Buffer;
	_argv[j] = '\0';
	argv[nArgs] = NULL;

	// Terminate
	return argv;
}
ULONG System_String::GetArgCount(CONST CHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscprintf(_Format, _ArgList) + 1);
	CHAR* _Buffer = new CHAR[StringSize];
	RtlSecureZeroMemory(_Buffer, StringSize);
	vsprintf_s(_Buffer, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Parse
	ULONG nArgs = NULL;
	CommandLine(nArgs, _Buffer);
	delete[] _Buffer;

	// Terminate
	return nArgs;
}
CHAR* System_String::GetArg(ULONG iArg, CONST CHAR* _Format, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscprintf(_Format, _ArgList) + 1);
	CHAR* _Buffer = new CHAR[StringSize];
	RtlSecureZeroMemory(_Buffer, StringSize);
	vsprintf_s(_Buffer, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Error
	if (!strlen(_Buffer)) { delete[] _Buffer; return nullptr; }

	// Parse
	ULONG nArgs = NULL;
	CHAR** List = CommandLine(nArgs, _Buffer);
	delete[] _Buffer;

	// Terminate
	if (!nArgs || iArg >= nArgs) { return nullptr; }
	return List[iArg];
}
// Message
VOID System_String::Message(CONST CHAR* _Format, ...) {

	// Filename
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscprintf(_Format, _ArgList) + 1);
	CHAR* lpText = new CHAR[StringSize];
	RtlSecureZeroMemory(lpText, StringSize);
	vsprintf_s(lpText, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Prompt
	MessageBoxA(0, lpText, APPLICATION_NAME_A, 0);

	// Cleanup
	delete[] lpText;
}
INT System_String::MessageYesNo(HWND hWndOwner, CONST CHAR* _Format, ...) {

	// Filename
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscprintf(_Format, _ArgList) + 1);
	CHAR* lpText = new CHAR[StringSize];
	RtlSecureZeroMemory(lpText, StringSize);
	vsprintf_s(lpText, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Prompt
	INT Result = MessageBoxA(0, lpText, APPLICATION_NAME_A, MB_YESNO);

	// Cleanup
	delete[] lpText;

	// Complete
	return Result;
}