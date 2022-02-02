
#include "system.h"

// Status
BOOL System_File::IsOpen(_iobuf* FILE) {
	if ((_get_osfhandle(_fileno(FILE))) != -1) { return SUCCESS; }
	else { return FAIL; }
}
// Size
ULLONG System_File::Size(_iobuf* FILE) {

	// Error
	if (!IsOpen(FILE)) { return NULL; }

	// Pointer
	_fseeki64(FILE, 0x00, SEEK_END);

	// Complete
	return static_cast<ULLONG>(_ftelli64(FILE));
}
// Find
ULLONG System_File::Find(_iobuf* FILE, ULLONG _Offset, PVOID _SrcBuf, ULLONG _ElementSize) {

	// Error
	if (!IsOpen(FILE)) { return -1; }

	// Search
	size_t Buffer = NULL;
	ULLONG _Filesize = Size(FILE);
	for (ULLONG n = 0; n < _Filesize; n++, _Offset++)
	{
		// Error
		if (feof(FILE)) { break; }

		// Read
		Read(FILE, _Offset, &Buffer, _ElementSize);

		// Test
		if (memcmp(&Buffer, _SrcBuf, _ElementSize) == 0) { return _Offset; }
	}

	// Terminate
	return -1;
}
ULLONG System_File::Find(_iobuf* FILE, ULLONG _Offset, PVOID _SrcBuf, ULLONG _ElementSize, BOOL Seek) {

	// Error
	if (!IsOpen(FILE)) { return -1; }

	// Search
	size_t Buffer = NULL;
	ULLONG _Filesize = Size(FILE);
	for (ULLONG n = 0; n < _Filesize; n++, _Offset++)
	{
		// Error
		if (feof(FILE)) { break; }

		// Read
		Read(FILE, _Offset, &Buffer, _ElementSize);

		// Test
		if (memcmp(&Buffer, _SrcBuf, _ElementSize) == 0)
		{
			if (Seek) {
				rewind(FILE);
				_fseeki64(FILE, _Offset, SEEK_SET);
				return _Offset;
			}
			else { return _Offset; }
		}
	}

	// Terminate
	return -1;
}
// Read
UCHAR* System_File::Read(_iobuf* FILE, ULLONG _Offset, PVOID _Buffer, ULLONG _ElementSize) {

	// Error
	if (!IsOpen(FILE)) { return nullptr; }

	// Pointer
	_fseeki64(FILE, _Offset, SEEK_SET);

	// Read
	fread_s(_Buffer, _ElementSize, _ElementSize, 1, FILE);

	// Complete
	return static_cast<UCHAR*>(_Buffer);
}
UCHAR* System_File::Read(_iobuf* FILE, ULLONG _Offset, ULLONG _ElementSize) {

	// Error
	if (!IsOpen(FILE)) { return nullptr; }

	// Pointer
	_fseeki64(FILE, _Offset, SEEK_SET);

	// Read
	UCHAR* _Buffer = new UCHAR[_ElementSize];
	RtlSecureZeroMemory(_Buffer, _ElementSize);
	fread_s(_Buffer, _ElementSize, _ElementSize, 1, FILE);

	// Complete
	return static_cast<UCHAR*>(_Buffer);
}
UCHAR* System_File::ReadNext(_iobuf* FILE, PVOID _Buffer, ULLONG _ElementSize) {

	// Error
	if (!IsOpen(FILE)) { return nullptr; }

	// Pointer
	_fseeki64(FILE, 0x00, SEEK_END);

	// Read
	fread_s(_Buffer, _ElementSize, _ElementSize, 1, FILE);

	// Complete
	return static_cast<UCHAR*>(_Buffer);
}
// Write
ULLONG System_File::Write(_iobuf* FILE, ULLONG _Offset, PVOID _Buffer, ULLONG _ElementSize) {

	// Error
	if (!IsOpen(FILE)) { return NULL; }

	// Pointer
	_fseeki64(FILE, _Offset, SEEK_SET);

	// Write
	fwrite(_Buffer, _ElementSize, 1, FILE);

	// Complete
	return (_Offset += _ElementSize);
}
ULLONG System_File::Write(_iobuf* FILE, ULLONG _Offset, ULLONG Value, ULLONG _ElementSize) {

	// Error
	if (!IsOpen(FILE)) { return NULL; }

	// Pointer
	_fseeki64(FILE, _Offset, SEEK_SET);

	// Write
	fwrite(&Value, _ElementSize, 1, FILE);

	// Complete
	return (_Offset += _ElementSize);
}
ULLONG System_File::WriteNext(_iobuf* FILE, PVOID _Buffer, ULLONG _ElementSize) {

	// Error
	if (!IsOpen(FILE)) { return NULL; }

	// Pointer
	_fseeki64(FILE, 0x00, SEEK_END);
	ULLONG _Offset = _ftelli64(FILE);

	// Write
	fwrite(_Buffer, _ElementSize, 1, FILE);

	// Complete
	return (_Offset + _ElementSize);
}
// Disk
ULLONG System_File::Align(ULLONG nAlign, ULLONG Value) {
	return Value = (Value + nAlign - 1) / nAlign * nAlign;
}