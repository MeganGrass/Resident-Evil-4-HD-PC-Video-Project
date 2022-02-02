
#include "system.h"

// Read
BOOL System_Text::ReadLine(TextFileA* Text, _iobuf* FILE, ULLONG _Offset, ULLONG StrLen) {

	// Error
	if (Text == nullptr) { return FAIL; }
	if (!File->IsOpen(FILE)) { return FAIL; }
	if (StrLen == NULL) { return FAIL; }

	// Read
	UCHAR* Buffer = new UCHAR[StrLen + 2];
	RtlSecureZeroMemory(Buffer, StrLen + 2);
	File->Read(FILE, _Offset, Buffer, StrLen);

	// Clean
	for (ULLONG n = 0; n < StrLen; n++)
	{
		if (Buffer[n] == 0x0D) { Buffer[n] = 0x00; }
		if (Buffer[n] == 0x0A) { Buffer[n] = 0x00; }
	}

	// Copy
	Text->Line.push_back((CHAR*)Buffer);

	// Complete
	return SUCCESS;
}
BOOL System_Text::ReadLine(TextFileW* Text, _iobuf* FILE, ULLONG _Offset, ULLONG StrLen) {

	// Error
	if (Text == nullptr) { return FAIL; }
	if (!File->IsOpen(FILE)) { return FAIL; }
	if (StrLen == NULL) { return FAIL; }

	// Read
	UCHAR* Buffer = new UCHAR[StrLen + 2];
	RtlSecureZeroMemory(Buffer, StrLen + 2);
	File->Read(FILE, _Offset, Buffer, StrLen);

	// Clean
	for (ULLONG n = 0; n < StrLen; n++)
	{
		if (Buffer[n] == 0x0D) { Buffer[n] = 0x00; }
		if (Buffer[n] == 0x0A) { Buffer[n] = 0x00; }
	}

	// Copy
	Text->Line.push_back((WCHAR*)Buffer);

	// Complete
	return SUCCESS;
}
TextFileA* System_Text::OpenA(_iobuf* FILE, ULLONG _Offset, ULLONG _ElementSize) {

	// Error
	if (!File->IsOpen(FILE)) { return nullptr; }

	// Encoding
	USHORT Endian = NULL;
	File->Read(FILE, _Offset, &Endian, 0x02);
	if (Endian == 0xFEFF || Endian == 0xFFFE) { return nullptr; }

	// Buffer
	TextFileA* Text = new TextFileA;

	// Parse
	UCHAR Char = NULL;
	ULLONG Begin = _Offset;
	ULLONG StrLen = NULL;
	BOOL Complete = FALSE;
	do {

		// Test
		File->Read(FILE, _Offset, &Char, 1);
		switch (Char)
		{
		case 0x0D:
		case 0x0A:
			StrLen++;
			_Offset++;
			File->Read(FILE, _Offset, &Char, 1);
			if (Char == 0x0A) { _Offset++; StrLen++; }
			if (!ReadLine(Text, FILE, Begin, StrLen)) { Complete = TRUE; }
			StrLen = NULL;
			Begin = _Offset;
			break;
		default:
			StrLen++;
			_Offset++;
		}

		// Complete
		if (Complete) { break; }
		if (_Offset >= _ElementSize) {
			ReadLine(Text, FILE, Begin, StrLen);
			break;
		}

	} while (_Offset < _ElementSize);

	// Arugments
	ULONG NumArgs = NULL;
	CHAR** List = nullptr;
	std::vector <std::string> Args;
	for (size_t n = 0; n < Text->Line.size(); n++)
	{
		// Parse
		List = File->CommandLine(NumArgs, Text->Line[n].c_str());
		if (NULL == List) { Args.push_back((CHAR*)L"\0\0"); }
		else if (NumArgs == NULL) { Args.push_back((CHAR*)L"\0\0"); }
		else {
			for (size_t x = 0; x < NumArgs; x++)
			{
				// Delete EndLine
				for (size_t i = 0; i < strlen(List[x]); i++)
				{
					if (List[x][i] == 0x0D) { List[x][i] = 0x00; }
					if (List[x][i] == 0x0A) { List[x][i] = 0x00; }
				}

				// Complete
				Args.push_back(List[x]);
			}
		}
		Text->Args.push_back(Args);
		Args.clear();
	}

	// Complete
	return Text;

}
TextFileW* System_Text::OpenW(_iobuf* FILE, ULLONG _Offset, ULLONG _ElementSize) {

	// Error
	if (!File->IsOpen(FILE)) { return nullptr; }

	// Encoding
	USHORT Endian = NULL;
	File->Read(FILE, _Offset, &Endian, 0x02);
	if (Endian == 0xFEFF || Endian == 0xFFFE) {}
	else { return nullptr; }
	_Offset += 0x02;

	// Buffer
	TextFileW* Text = new TextFileW;
	Text->Encoding = Endian;

	// Parse
	USHORT Short = NULL;
	ULLONG Begin = _Offset;
	ULLONG StrLen = NULL;
	BOOL Complete = FALSE;
	do {

		// Test
		File->Read(FILE, _Offset, &Short, 2);
		switch (Short)
		{
		case 0x0D:
		case 0x0A:
			StrLen += 2;
			_Offset += 2;
			File->Read(FILE, _Offset, &Short, 2);
			if (Short == 0x0A) { _Offset += 2; StrLen += 2; }
			if (!ReadLine(Text, FILE, Begin, StrLen)) { Complete = TRUE; }
			StrLen = NULL;
			Begin = _Offset;
			break;
		default:
			StrLen += 2;
			_Offset += 2;
		}

		// Complete
		if (Complete) { break; }
		if (_Offset >= _ElementSize) {
			ReadLine(Text, FILE, Begin, StrLen);
			break;
		}

	} while (_Offset < _ElementSize);

	// Arugments
	INT NumArgs = NULL;
	WCHAR** List = nullptr;
	std::vector <std::wstring> Args;
	for (size_t n = 0; n < Text->Line.size(); n++)
	{
		// Parse
		List = CommandLineToArgvW(Text->Line[n].c_str(), &NumArgs);
		if (NULL == List) { Args.push_back((WCHAR*)L"\0\0"); }
		else if (NumArgs == NULL) { Args.push_back((WCHAR*)L"\0\0"); }
		else {
			for (size_t x = 0; x < NumArgs; x++)
			{
				// Delete EndLine
				for (size_t i = 0; i < wcslen(List[x]); i++)
				{
					if (List[x][i] == 0x0D) { List[x][i] = 0x00; }
					if (List[x][i] == 0x0A) { List[x][i] = 0x00; }
				}

				// Complete
				Args.push_back(List[x]);
			}
		}
		Text->Args.push_back(Args);
		Args.clear();
	}

	// Complete
	return Text;

}
// Open
TextFileA* System_Text::OpenA(CONST std::string _Filename, ...) {

	// Format
	va_list _ArgList;
	__crt_va_start(_ArgList, _Filename);
	INT _StrLen = (_vscprintf(_Filename.c_str(), _ArgList) + 1);
	CHAR* String = new CHAR[_StrLen];
	RtlSecureZeroMemory(String, _StrLen);
	vsprintf_s(String, _StrLen, _Filename.c_str(), _ArgList);
	__crt_va_end(_ArgList);
	std::unique_ptr<CHAR[]> formatted(String);

	// Open
	_iobuf* _File = File->Open(READ_FILE, std::string(formatted.get()).c_str());
	std::string(formatted.get()).clear();
	if (!_File) { return NULL; }

	// Buffer
	ULLONG _ElementSize = File->Size(_File);
	TextFileA* Text = OpenA(_File, 0x00, _ElementSize);

	// Close
	fclose(_File);

	// Complete
	return Text;

}
TextFileA* System_Text::OpenA(CONST std::wstring _Filename, ...) {

	// Format
	va_list _ArgList;
	__crt_va_start(_ArgList, _Filename);
	INT _StrLen = (_vscwprintf(_Filename.c_str(), _ArgList) + 2);
	WCHAR* String = new WCHAR[_StrLen];
	RtlSecureZeroMemory(String, _StrLen);
	vswprintf_s(String, _StrLen, _Filename.c_str(), _ArgList);
	__crt_va_end(_ArgList);
	std::unique_ptr<WCHAR[]> formatted(String);

	// Open
	_iobuf* _File = File->Open(READ_FILE, std::wstring(formatted.get()).c_str());
	std::wstring(formatted.get()).clear();
	if (!_File) { return NULL; }

	// Buffer
	ULLONG _ElementSize = File->Size(_File);
	TextFileA* Text = OpenA(_File, 0x00, _ElementSize);

	// Close
	fclose(_File);

	// Complete
	return Text;

}
TextFileW* System_Text::OpenW(CONST std::string _Filename, ...) {

	// Format
	va_list _ArgList;
	__crt_va_start(_ArgList, _Filename);
	INT _StrLen = (_vscprintf(_Filename.c_str(), _ArgList) + 1);
	CHAR* String = new CHAR[_StrLen];
	RtlSecureZeroMemory(String, _StrLen);
	vsprintf_s(String, _StrLen, _Filename.c_str(), _ArgList);
	__crt_va_end(_ArgList);
	std::unique_ptr<CHAR[]> formatted(String);

	// Open
	_iobuf* _File = File->Open(READ_FILE, std::string(formatted.get()).c_str());
	std::string(formatted.get()).clear();
	if (!_File) { return NULL; }

	// Buffer
	ULLONG _ElementSize = File->Size(_File);
	TextFileW* Text = OpenW(_File, 0x00, _ElementSize);

	// Close
	fclose(_File);

	// Complete
	return Text;

}
TextFileW* System_Text::OpenW(CONST std::wstring _Filename, ...) {

    // Format
    va_list _ArgList;
    __crt_va_start(_ArgList, _Filename);
    INT _StrLen = (_vscwprintf(_Filename.c_str(), _ArgList) + 2);
    WCHAR* String = new WCHAR[_StrLen];
    RtlSecureZeroMemory(String, _StrLen);
	vswprintf_s(String, _StrLen, _Filename.c_str(), _ArgList);
    __crt_va_end(_ArgList);
    std::unique_ptr<WCHAR[]> formatted(String);

	// Open
	_iobuf* _File = File->Open(READ_FILE, std::wstring(formatted.get()).c_str());
	std::wstring(formatted.get()).clear();
	if (!_File) { return NULL; }

	// Buffer
	ULLONG _ElementSize = File->Size(_File);
	TextFileW* Text = OpenW(_File, 0x00, _ElementSize);

	// Close
	fclose(_File);

	// Complete
	return Text;

}
// Close
VOID System_Text::Close(TextFileA* Text) {

	// Error
	if (Text == nullptr) { return; }

	// Cleanup
	for (size_t n = 0; n < Text->Line.size(); n++)
	{
		for (size_t x = 0; x < Text->Args[n].size(); x++) { Text->Args[n][x].clear(); }
		Text->Args[n].clear();
		Text->Line[n].clear();
	}

	// 
	Text->Args.clear();
	Text->Line.clear();

}
VOID System_Text::Close(TextFileW* Text) {

	// Error
	if (Text == nullptr) { return; }

	// Cleanup
	for (size_t n = 0; n < Text->Line.size(); n++)
	{
		for (size_t x = 0; x < Text->Args[n].size(); x++) { Text->Args[n][x].clear(); }
		Text->Args[n].clear();
		Text->Line[n].clear();
	}

	// 
	Text->Args.clear();
	Text->Line.clear();

}