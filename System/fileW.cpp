
#include "system.h"

// Status
BOOL System_File::Exists(CONST WCHAR* _Filename, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscwprintf(_Filename, _ArgList) + 2);
	WCHAR* Filename = new WCHAR[StringSize];
	RtlSecureZeroMemory(Filename, StringSize);
	vswprintf_s(Filename, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	struct _stat64i32 Status;
	if (_wstat64i32(Filename, &Status)) {
		delete[] Filename;
		return FAIL;
	}
	else {
		delete[] Filename;
		return SUCCESS;
	}
}
// Meta
WCHAR* System_File::GetDirectory(CONST WCHAR* _Filename, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscwprintf(_Filename, _ArgList) + 2);
	WCHAR* String = new WCHAR[StringSize];
	RtlSecureZeroMemory(String, StringSize);
	vswprintf_s(String, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	// Parse
	WCHAR Drive[_MAX_DRIVE];
	WCHAR Directory[_MAX_DIR];
	WCHAR Name[_MAX_FNAME];
	WCHAR Extension[_MAX_EXT];
	_wsplitpath_s(String, Drive, Directory, Name, Extension);

	// Directory
	if (!wcslen(Extension)) {
		if (String[wcslen(String) - 1] != 0x5C) {
			String = Get(L"%ws\\", String);
		}
	}

	// Drive
	if (PathGetDriveNumberW(String) == -1) {
		if (String[0] != 0x5C) {
			String = Get(L"\\%ws", String);
		}
		String = Get(L"%ws\\%ws", _wgetcwd(NULL, NULL), PathSkipRootW(String));
	}

	// Create
	_wsplitpath_s(String, Drive, Directory, Name, Extension);
	delete[] String;

	// Terminate
	return Get(L"%ws%ws", Drive, Directory);
}
WCHAR* System_File::GetNamebase(CONST WCHAR* _Filename, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscwprintf(_Filename, _ArgList) + 2);
	WCHAR* String = new WCHAR[StringSize];
	RtlSecureZeroMemory(String, StringSize);
	vswprintf_s(String, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	// Parse
	WCHAR Drive[_MAX_DRIVE];
	WCHAR Directory[_MAX_DIR];
	WCHAR Name[_MAX_FNAME];
	WCHAR Extension[_MAX_EXT];
	_wsplitpath_s(String, Drive, Directory, Name, Extension);
	delete[] String;

	// Terminate
	return Get(Name);
}
WCHAR* System_File::GetExtension(CONST WCHAR* _Filename, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscwprintf(_Filename, _ArgList) + 2);
	WCHAR* String = new WCHAR[StringSize];
	RtlSecureZeroMemory(String, StringSize);
	vswprintf_s(String, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	// Parse
	WCHAR Drive[_MAX_DRIVE];
	WCHAR Directory[_MAX_DIR];
	WCHAR Name[_MAX_FNAME];
	WCHAR Extension[_MAX_EXT];
	_wsplitpath_s(String, Drive, Directory, Name, Extension);
	delete[] String;

	// Complete
	return Get(Extension);
}
// Memory
UCHAR* System_File::Buffer(CONST WCHAR* _Filename, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscwprintf(_Filename, _ArgList) + 2);
	WCHAR* Filename = new WCHAR[StringSize];
	RtlSecureZeroMemory(Filename, StringSize);
	vswprintf_s(Filename, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	// parse
	if (!Exists(Filename)) { delete[]Filename; return nullptr; }

	// open
	_iobuf* _File = Open(READ_FILE, Filename);
	if (!IsOpen(_File)) { return nullptr; }

	// read
	ULLONG _ElementSize = Size(_File);
	UCHAR* _Src = Read(_File, 0x00, _ElementSize);
	fclose(_File);

	// terminate
	delete[]Filename;
	return _Src;
}
UCHAR* System_File::Buffer(ULLONG& _ElementSize, CONST WCHAR* _Filename, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscwprintf(_Filename, _ArgList) + 2);
	WCHAR* Filename = new WCHAR[StringSize];
	RtlSecureZeroMemory(Filename, StringSize);
	vswprintf_s(Filename, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	// open
	if (!Exists(Filename)) { delete[]Filename; return nullptr; }
	_iobuf* _File = Open(READ_FILE, Filename);
	if (!IsOpen(_File)) { return nullptr; }

	// read
	_ElementSize = Size(_File);
	UCHAR* _Src = Read(_File, 0x00, _ElementSize);
	fclose(_File);

	// terminate
	delete[]Filename;
	return _Src;
}
UCHAR* System_File::Buffer(ULLONG _Offset, ULLONG& _ElementSize, CONST WCHAR* _Filename, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscwprintf(_Filename, _ArgList) + 2);
	WCHAR* Filename = new WCHAR[StringSize];
	RtlSecureZeroMemory(Filename, StringSize);
	vswprintf_s(Filename, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	// open
	if (!Exists(Filename)) { delete[]Filename; return nullptr; }
	_iobuf* _File = Open(READ_FILE, Filename);
	if (!IsOpen(_File)) { return nullptr; }

	// read
	_ElementSize = Size(_File);
	UCHAR* _Src = Read(_File, _Offset, _ElementSize);
	fclose(_File);

	// terminate
	delete[]Filename;
	return _Src;

}
// Input
_iobuf* System_File::Open(OpenFileMode _Mode, CONST WCHAR* _Filename, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscwprintf(_Filename, _ArgList) + 2);
	WCHAR* Filename = new WCHAR[StringSize];
	RtlSecureZeroMemory(Filename, StringSize);
	vswprintf_s(Filename, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	// parse
	CONST WCHAR* Mode = nullptr;
	switch (_Mode)
	{
	case READ_FILE:
		if (!Exists(Filename)) { delete[] Filename; return NULL; }
		Mode = L"rb";
		break;
	case CREATE_FILE:
		CreateDir(Filename);
		Mode = L"wb";
		break;
	case EDIT_FILE:
		CreateDir(Filename);
		Mode = L"rb+";
		break;
	case APPEND_FILE:
		CreateDir(Filename);
		Mode = L"ab+";
	default:
		delete[] Filename;
		return nullptr;
	}

	// open
	_iobuf* _Stream = NULL;
	errno_t Open = _wfopen_s(&_Stream, Filename, Mode);
	if (!_Stream || Open != 0) { delete[] Filename; return NULL; }

	// terminate
	delete[] Filename;
	return _Stream;

}
WCHAR* System_File::GetFilename(HWND hwndOwner, CONST WCHAR* DefExt, CONST WCHAR* Filter) {

	WCHAR* _Filename = new WCHAR[_MAX_PATH];

	OPENFILENAMEW OpenFilename;
	RtlSecureZeroMemory(&OpenFilename, sizeof(OPENFILENAMEW));

	OpenFilename.lStructSize = sizeof(OPENFILENAMEW);
	OpenFilename.hwndOwner = hwndOwner;
	OpenFilename.lpstrFilter = Filter;
	OpenFilename.lpstrFile = _Filename;
	OpenFilename.lpstrFile[0] = '\0';
	OpenFilename.nMaxFile = _MAX_PATH;
	OpenFilename.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_DONTADDTORECENT;
	OpenFilename.lpstrDefExt = DefExt;

	if (!GetOpenFileNameW(&OpenFilename)) { return nullptr; }
	else { return _Filename; }
}
WCHAR* System_File::GetSavename(HWND hwndOwner, CONST WCHAR* DefExt, CONST WCHAR* Filter) {

	WCHAR* _Filename = new WCHAR[_MAX_PATH];

	OPENFILENAMEW SaveFilename;
	RtlSecureZeroMemory(&SaveFilename, sizeof(OPENFILENAMEW));

	SaveFilename.lStructSize = sizeof(OPENFILENAMEW);
	SaveFilename.hwndOwner = hwndOwner;
	SaveFilename.lpstrFilter = Filter;
	SaveFilename.lpstrFile = _Filename;
	SaveFilename.lpstrFile[0] = '\0';
	SaveFilename.nMaxFile = _MAX_PATH;
	SaveFilename.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_DONTADDTORECENT;
	SaveFilename.lpstrDefExt = DefExt;

	if (!GetSaveFileNameW(&SaveFilename)) { return nullptr; }
	else { return _Filename; }
}
// Output
VOID System_File::CreateDummy(ULLONG Size, CONST WCHAR* _Filename, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscwprintf(_Filename, _ArgList) + 2);
	WCHAR* Filename = new WCHAR[StringSize];
	RtlSecureZeroMemory(Filename, StringSize);
	vswprintf_s(Filename, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	// parse
	_iobuf* _File = Open(CREATE_FILE, Filename);
	delete[] Filename;
	if (!_File) { return; }

	// Write
	UCHAR* Buffer = new UCHAR[Size];
	RtlSecureZeroMemory(Buffer, Size);
	Write(_File, 0x00, Buffer, Size);
	delete[] Buffer;

	// Close
	fclose(_File);

}
VOID System_File::CreateDir(CONST WCHAR* _Directory, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Directory);
	INT StringSize = (_vscwprintf(_Directory, _ArgList) + 2);
	WCHAR* Directory = new WCHAR[StringSize];
	RtlSecureZeroMemory(Directory, StringSize);
	vswprintf_s(Directory, StringSize, _Directory, _ArgList);
	__crt_va_end(_ArgList);

	WCHAR* lpPathName = GetDirectory(Directory);
	SHCreateDirectoryExW(NULL, lpPathName, NULL);
	delete[]lpPathName;
}
BOOL System_File::CreateFromSource(UCHAR* _SrcBuf, ULLONG _ElementSize, CONST WCHAR* _Filename, ...) {

	// error
	if (_SrcBuf == NULL) { return FAIL; }

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscwprintf(_Filename, _ArgList) + 2);
	WCHAR* Filename = new WCHAR[StringSize];
	RtlSecureZeroMemory(Filename, StringSize);
	vswprintf_s(Filename, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	// parse
	_iobuf* _File = Open(CREATE_FILE, Filename);
	if (!IsOpen(_File)) { return FAIL; }

	// write
	if (!Write(_File, 0x00, &_SrcBuf[0x00], _ElementSize)) { return FAIL; }

	// cleanup
	delete[] Filename;
	fclose(_File);

	// terminate
	return SUCCESS;
}
BOOL System_File::CreateFromSource(_iobuf* FILE, ULLONG _Offset, ULLONG _ElementSize, CONST WCHAR* _Filename, ...) {

	// error
	if (!IsOpen(FILE)) { return NULL; }

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscwprintf(_Filename, _ArgList) + 2);
	WCHAR* Filename = new WCHAR[StringSize];
	RtlSecureZeroMemory(Filename, StringSize);
	vswprintf_s(Filename, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	// parse
	_iobuf* _File = Open(CREATE_FILE, Filename);
	if (!IsOpen(_File)) { return FAIL; }

	// write
	UCHAR* _SrcBuf = Read(FILE, _Offset, _ElementSize);
	if (!Write(_File, 0x00, &_SrcBuf[0x00], _ElementSize)) { return FAIL; }

	// cleanup
	delete[] Filename;
	delete[] _SrcBuf;
	fclose(_File);

	// terminate
	return SUCCESS;
}
// Size
ULLONG System_File::Size(CONST WCHAR* _Filename, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscwprintf(_Filename, _ArgList) + 2);
	WCHAR* Filename = new WCHAR[StringSize];
	RtlSecureZeroMemory(Filename, StringSize);
	vswprintf_s(Filename, StringSize, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	_iobuf* _File = Open(READ_FILE, Filename);
	if (!IsOpen(_File)) { delete[]Filename; return NULL; }
	ULLONG _ElementSize = Size(_File);
	fclose(_File);
	delete[]Filename;
	return _ElementSize;
}
// Print
ULLONG System_File::Print(_iobuf* FILE, ULLONG _Offset, CONST WCHAR* _Format, ...) {

	// Error
	if (!IsOpen(FILE)) { return NULL; }

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscwprintf(_Format, _ArgList) + 2);
	WCHAR* String = new WCHAR[StringSize];
	RtlSecureZeroMemory(String, StringSize);
	vswprintf_s(String, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Write
	StringSize -= 2;
	_fseeki64(FILE, _Offset, SEEK_SET);
	fwrite(String, StringSize, 1, FILE);

	// Cleanup
	delete[] String;

	// Complete
	return StringSize;
}
ULLONG System_File::Print(_iobuf* FILE, CONST WCHAR* _Format, ...) {

	// Error
	if (!IsOpen(FILE)) { return NULL; }

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Format);
	INT StringSize = (_vscwprintf(_Format, _ArgList) + 2);
	WCHAR* String = new WCHAR[StringSize];
	RtlSecureZeroMemory(String, StringSize);
	vswprintf_s(String, StringSize, _Format, _ArgList);
	__crt_va_end(_ArgList);

	// Write
	fwprintf_s(FILE, String);

	// Cleanup
	delete[] String;

	// Complete
	return StringSize;
}
// Align
VOID System_File::Align(ULLONG nAlign, CONST WCHAR* _Filename, ...) {

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT StringSize = (_vscwprintf(_Filename, _ArgList) + 2);
	WCHAR* Filename = new WCHAR[StringSize];
	RtlSecureZeroMemory(Filename, StringSize);
	vswprintf_s(Filename, StringSize, _Filename, _ArgList);
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