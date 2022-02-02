
#include "system.h"

// Status
BOOL System_File::Exists(CONST CHAR* _Filename, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscprintf(_Filename, _ArgList) + 1);
	CHAR* Filename = new CHAR[StringSize];
	RtlSecureZeroMemory(Filename, StringSize);
	vsprintf_s(Filename, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	// Test
	struct _stat64i32 Status;
	if (_stat64i32(Filename, &Status)) {
		delete[] Filename;
		return FAIL;
	}
	else {
		delete[] Filename;
		return SUCCESS;
	}

}
// Meta
CHAR* System_File::GetDirectory(CONST CHAR* _Filename, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscprintf(_Filename, _ArgList) + 1);
	CHAR* String = new CHAR[StringSize];
	RtlSecureZeroMemory(String, StringSize);
	vsprintf_s(String, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	// Parse
	CHAR Drive[_MAX_DRIVE];
	CHAR Directory[_MAX_DIR];
	CHAR Name[_MAX_FNAME];
	CHAR Extension[_MAX_EXT];
	_splitpath_s(String, Drive, Directory, Name, Extension);

	// Directory
	if (!strlen(Extension) && (String[strlen(String) - 1] != 0x5C)) {
		String = Get("%s\\", String);
	}

	// Drive
	if (PathGetDriveNumberA(String) == -1) {
		if (String[0] != 0x5C) { String = Get("\\%s", String); }
		String = Get("%s\\%s", _getcwd(NULL, NULL), PathSkipRootA(String));
	}

	// Parse
	_splitpath_s(String, Drive, Directory, Name, Extension);
	delete[] String;

	// Complete
	return Get("%s%s", Drive, Directory);
}
CHAR* System_File::GetNamebase(CONST CHAR* _Filename, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscprintf(_Filename, _ArgList) + 1);
	CHAR* String = new CHAR[StringSize];
	RtlSecureZeroMemory(String, StringSize);
	vsprintf_s(String, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	// Parse
	CHAR Drive[_MAX_DRIVE];
	CHAR Directory[_MAX_DIR];
	CHAR Name[_MAX_FNAME];
	CHAR Extension[_MAX_EXT];
	_splitpath_s(String, Drive, Directory, Name, Extension);
	delete[] String;

	// Complete
	return Get(Name);
}
CHAR* System_File::GetExtension(CONST CHAR* _Filename, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscprintf(_Filename, _ArgList) + 1);
	CHAR* String = new CHAR[StringSize];
	RtlSecureZeroMemory(String, StringSize);
	vsprintf_s(String, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	// Parse
	CHAR Drive[_MAX_DRIVE];
	CHAR Directory[_MAX_DIR];
	CHAR Name[_MAX_FNAME];
	CHAR Extension[_MAX_EXT];
	_splitpath_s(String, Drive, Directory, Name, Extension);
	delete[] String;

	// Complete
	return Get(Extension);
}
// Memory
UCHAR* System_File::Buffer(CONST CHAR* _Filename, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscprintf(_Filename, _ArgList) + 1);
	CHAR* Filename = new CHAR[StringSize];
	RtlSecureZeroMemory(Filename, StringSize);
	vsprintf_s(Filename, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	// Error
	if (!Exists(Filename)) { delete[] Filename; return nullptr; }

	// Open
	_iobuf* _File = Open(READ_FILE, Filename);
	if (!IsOpen(_File)) { delete[] Filename; return nullptr; }

	// Read
	ULLONG _ElementSize = Size(_File);
	UCHAR* _Buffer = Read(_File, 0x00, _ElementSize);

	// Cleanup
	fclose(_File);
	delete[] Filename;

	// Complete
	return _Buffer;
}
UCHAR* System_File::Buffer(ULLONG& _ElementSize, CONST CHAR* _Filename, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscprintf(_Filename, _ArgList) + 1);
	CHAR* Filename = new CHAR[StringSize];
	RtlSecureZeroMemory(Filename, StringSize);
	vsprintf_s(Filename, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	// Error
	if (!Exists(Filename)) { delete[] Filename; return nullptr; }

	// Open
	_iobuf* _File = Open(READ_FILE, Filename);
	if (!IsOpen(_File)) { delete[] Filename; return nullptr; }

	// Read
	_ElementSize = Size(_File);
	UCHAR* _Buffer = Read(_File, 0x00, _ElementSize);

	// Cleanup
	fclose(_File);
	delete[] Filename;

	// Complete
	return _Buffer;
}
UCHAR* System_File::Buffer(ULLONG _Offset, ULLONG& _ElementSize, CONST CHAR* _Filename, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscprintf(_Filename, _ArgList) + 1);
	CHAR* Filename = new CHAR[StringSize];
	RtlSecureZeroMemory(Filename, StringSize);
	vsprintf_s(Filename, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	// Error
	if (!Exists(Filename)) { delete[] Filename; return nullptr; }

	// Open
	_iobuf* _File = Open(READ_FILE, Filename);
	if (!IsOpen(_File)) { delete[] Filename; return nullptr; }

	// Read
	_ElementSize = Size(_File);
	UCHAR* _Buffer = Read(_File, _Offset, _ElementSize);

	// Cleanup
	fclose(_File);
	delete[] Filename;

	// Complete
	return _Buffer;

}
// Input
_iobuf* System_File::Open(OpenFileMode _Mode, CONST CHAR* _Filename, ...) {

	// _FileName
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscprintf(_Filename, _ArgList) + 1);
	CHAR* Filename = new CHAR[StringSize];
	RtlSecureZeroMemory(Filename, StringSize);
	vsprintf_s(Filename, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	// Parse
	CONST CHAR* Mode = nullptr;
	switch (_Mode)
	{
	case READ_FILE:
		if (!Exists(Filename)) { delete[] Filename; return nullptr; }
		Mode = "rb";
		break;
	case CREATE_FILE:
		CreateDir(Filename);
		Mode = "wb";
		break;
	case EDIT_FILE:
		CreateDir(Filename);
		Mode = "rb+";
		break;
	case APPEND_FILE:
		CreateDir(Filename);
		Mode = "ab+";
		break;
	default:
		delete[] Filename;
		return nullptr;
	}

	// Open
	_iobuf* _Stream = nullptr;
	errno_t Open = fopen_s(&_Stream, Filename, Mode);
	if (!_Stream || Open != 0) { delete[] Filename; return nullptr; }

	// Cleanup
	delete[] Filename;

	// Complete
	return _Stream;
}
CHAR* System_File::GetFilename(HWND hwndOwner, CONST CHAR* DefExt, CONST CHAR* Filter) {

	CHAR* _Filename = new char[_MAX_PATH];

	OPENFILENAMEA OpenFilename;
	RtlSecureZeroMemory(&OpenFilename, sizeof(OPENFILENAMEA));

	OpenFilename.lStructSize = sizeof(OPENFILENAMEA);
	OpenFilename.hwndOwner = hwndOwner;
	OpenFilename.lpstrFilter = Filter;
	OpenFilename.lpstrFile = _Filename;
	OpenFilename.lpstrFile[0] = '\0';
	OpenFilename.nMaxFile = _MAX_PATH;
	OpenFilename.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_DONTADDTORECENT;
	OpenFilename.lpstrDefExt = DefExt;

	if (!GetOpenFileNameA(&OpenFilename)) { return nullptr; }
	else { return _Filename; }
}
CHAR* System_File::GetSavename(HWND hwndOwner, CONST CHAR* DefExt, CONST CHAR* Filter) {

	CHAR* _Filename = new char[_MAX_PATH];

	OPENFILENAMEA SaveFilename;
	RtlSecureZeroMemory(&SaveFilename, sizeof(OPENFILENAMEA));

	SaveFilename.lStructSize = sizeof(OPENFILENAMEA);
	SaveFilename.hwndOwner = hwndOwner;
	SaveFilename.lpstrFilter = Filter;
	SaveFilename.lpstrFile = _Filename;
	SaveFilename.lpstrFile[0] = '\0';
	SaveFilename.nMaxFile = _MAX_PATH;
	SaveFilename.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_DONTADDTORECENT;
	SaveFilename.lpstrDefExt = DefExt;

	if (!GetSaveFileNameA(&SaveFilename)) { return nullptr; }
	else { return _Filename; }
}
// Output
VOID System_File::CreateDummy(ULLONG Size, CONST CHAR* _Filename, ...) {

	// _FileName
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscprintf(_Filename, _ArgList) + 1);
	CHAR* Filename = new CHAR[StringSize];
	RtlSecureZeroMemory(Filename, StringSize);
	vsprintf_s(Filename, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	// Open
	_iobuf* _File = Open(CREATE_FILE, Filename);
	if (!IsOpen(_File)) { delete[] Filename; return; }

	// Write
	UCHAR* Buffer = new UCHAR[Size];
	RtlSecureZeroMemory(Buffer, Size);
	Write(_File, 0x00, Buffer, Size);

	// Cleanup
	delete[] Filename;
	delete[] Buffer;
	fclose(_File);
}
VOID System_File::CreateDir(CONST CHAR* _Directory, ...) {

	// _FileName
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Directory);
	INT StringSize = (_vscprintf(_Directory, _ArgList) + 1);
	CHAR* Directory = new CHAR[StringSize];
	RtlSecureZeroMemory(Directory, StringSize);
	vsprintf_s(Directory, StringSize, _Directory, _ArgList);
	__crt_va_end(_ArgList);

	// Create
	CHAR* lpPathName = GetDirectory(Directory);
	SHCreateDirectoryExA(nullptr, lpPathName, nullptr);
	delete[] lpPathName;
}
BOOL System_File::CreateFromSource(UCHAR* _SrcBuf, ULLONG _ElementSize, CONST CHAR* _Filename, ...) {

	// Error
	if (_SrcBuf == nullptr) { return FAIL; }
	if(_ElementSize == NULL) { return FAIL; }

	// _FileName
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscprintf(_Filename, _ArgList) + 1);
	CHAR* Filename = new CHAR[StringSize];
	RtlSecureZeroMemory(Filename, StringSize);
	vsprintf_s(Filename, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	// Open
	_iobuf* _File = Open(CREATE_FILE, Filename);
	if (!IsOpen(_File)) { delete[] Filename; return FAIL; }
	delete[] Filename;

	// Write
	if (!Write(_File, 0x00, &_SrcBuf[0x00], _ElementSize)) { fclose(_File); return FAIL; }

	// Cleanup
	fclose(_File);

	// Complete
	return SUCCESS;
}
BOOL System_File::CreateFromSource(_iobuf* FILE, ULLONG _Offset, ULLONG _ElementSize, CONST CHAR* _Filename, ...) {

	// Error
	if (!IsOpen(FILE)) { return FAIL; }

	// _FileName
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscprintf(_Filename, _ArgList) + 1);
	CHAR* Filename = new CHAR[StringSize];
	RtlSecureZeroMemory(Filename, StringSize);
	vsprintf_s(Filename, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	// Open
	_iobuf* _File = Open(CREATE_FILE, Filename);
	delete[] Filename;
	if (!IsOpen(_File)) { return FAIL; }

	// Write
	if (_ElementSize != NULL) {
		UCHAR* _SrcBuf = Read(FILE, _Offset, _ElementSize);
		if (_SrcBuf == nullptr) { fclose(_File); return FAIL; }
		if (!Write(_File, 0x00, &_SrcBuf[0x00], _ElementSize)) { fclose(_File); return FAIL; }
		delete[] _SrcBuf;
	}

	// Cleanup
	fclose(_File);

	// Complete
	return SUCCESS;
}
// Size
ULLONG System_File::Size(CONST CHAR* _Filename, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscprintf(_Filename, _ArgList) + 1);
	CHAR* Filename = new CHAR[StringSize];
	RtlSecureZeroMemory(Filename, StringSize);
	vsprintf_s(Filename, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	// Open
	_iobuf* _File = Open(READ_FILE, Filename);
	if (!IsOpen(_File)) { delete[]Filename; return NULL; }
	delete[]Filename;

	// Size
	ULLONG _ElementSize = Size(_File);

	// Cleanup
	fclose(_File);

	// Complete
	return _ElementSize;
}
// Print
ULLONG System_File::Print(_iobuf* FILE, ULLONG _Offset, CONST CHAR* _Format, ...) {

	// Error
	if (!IsOpen(FILE)) { return NULL; }

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscprintf(_Format, _ArgList) + 1);
	CHAR* String = new CHAR[StringSize];
	RtlSecureZeroMemory(String, StringSize);
	vsprintf_s(String, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Write
	StringSize--;
	_fseeki64(FILE, _Offset, SEEK_SET);
	fwrite(String, StringSize, 1, FILE);

	// Cleanup
	delete[] String;

	// Complete
	return StringSize;
}
ULLONG System_File::Print(_iobuf* FILE, CONST CHAR* _Format, ...) {

	// Error
	if (!IsOpen(FILE)) { return NULL; }

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscprintf(_Format, _ArgList) + 1);
	CHAR* String = new CHAR[StringSize];
	RtlSecureZeroMemory(String, StringSize);
	vsprintf_s(String, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Write
	StringSize--;
	_fseeki64(FILE, 0x00, SEEK_END);
	fwrite(String, StringSize, 1, FILE);

	// Cleanup
	delete[] String;

	// Complete
	return StringSize;
}
// Align
VOID System_File::Align(ULLONG nAlign, CONST CHAR* _Filename, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscprintf(_Filename, _ArgList) + 1);
	CHAR* Filename = new CHAR[StringSize];
	RtlSecureZeroMemory(Filename, StringSize);
	vsprintf_s(Filename, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	// Source
	ULLONG SourceSize = NULL;
	UCHAR* Source = Buffer(SourceSize, Filename);
	if (Source == nullptr) { return; }

	// Align
	if (SourceSize) {

		// Buffer
		ULLONG BufferSize = (SourceSize + nAlign - 1) / nAlign * nAlign;
		UCHAR* Buffer = new UCHAR[BufferSize];
		RtlSecureZeroMemory(Buffer, BufferSize);

		// Write
		memcpy_s(&Buffer[0x00], BufferSize, &Source[0x00], SourceSize);
		CreateFromSource(Buffer, BufferSize, Filename);

		// Cleanup
		delete[] Buffer;
	}

	// Cleanup
	delete[] Source;
	delete[] Filename;
}