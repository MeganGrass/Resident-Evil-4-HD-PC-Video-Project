#pragma once

#include FRAMEWORK

#ifdef DIRECT_X
#include <d3d9.h>
#include <D3dx9tex.h>
#endif

// Types
typedef __int8				CHAR;
typedef __int8				s8;
typedef unsigned __int8		UCHAR;
typedef unsigned __int8		u8;
typedef __int16				SHORT;
typedef __int16				s16;
typedef unsigned __int16	USHORT;
typedef unsigned __int16	u16;
typedef __int32				INT;
typedef __int32				s32;
typedef unsigned __int32	UINT;
typedef unsigned __int32	u32;
typedef long int			LONG;
typedef unsigned long int	ULONG;
typedef __int64				LLONG;
typedef unsigned __int64	ULLONG;
typedef float				FLOAT;
typedef double				DOUBLE;
typedef long double			LDOUBLE;

// BOOL
#define FAIL		FALSE
#define SUCCESS		TRUE

#define OFF			FALSE
#define ON			TRUE

#define NO			FALSE
#define YES			TRUE

#define DISABLED	FALSE
#define ENABLED		TRUE

#define STATIC		static

#define LO			FALSE
#define HI			TRUE

class System_Type {
private:
public:

	// De/Construction
	System_Type(VOID) {}
	virtual ~System_Type(VOID) {}

	// Bits and Bytes
	uintmax_t GetBit(uintmax_t iBit, uintmax_t Value);
	uintmax_t SetBit(uintmax_t iBit, BOOL OnOff, uintmax_t &Value);
	uintmax_t GetByte(uintmax_t iByte, uintmax_t Value);
	BOOL* GetBitArray(UCHAR Value);

	// x86/x64
	uintmax_t GetValue(uintmax_t Value);
	uintmax_t GetValueFromStr(BOOL HexaDecimal, CONST CHAR* Value);
	uintmax_t GetValueFromStr(BOOL HexaDecimal, CONST WCHAR* Value);
	uintmax_t GetValueFromBits(uintmax_t Value, uintmax_t nBits, uintmax_t iBit);
	uintmax_t GetValueFromBytes(UCHAR n0, UCHAR n1, UCHAR n2, UCHAR n3, UCHAR n4, UCHAR n5, UCHAR n6, UCHAR n7);
	uintmax_t SwapEndianness(uintmax_t Value);

	// precision-point
	FLOAT GetFloat(uintmax_t Value);
	DOUBLE GetFloatFromStr(CONST CHAR* Value);
	DOUBLE GetFloatFromStr(CONST WCHAR* Value);
	DOUBLE GetDouble(uintmax_t Value);
	DOUBLE GetDouble(FLOAT Value);

};

class System_String {
private:
public:

	// Boot
	System_String(VOID) {}
	virtual ~System_String(VOID) {}

	// Random
	CHAR* GetRandomString(VOID);

	// Create
	CHAR* Get(CONST CHAR* _Format, ...);
	WCHAR* Get(CONST WCHAR* _Format, ...);
	std::string Get(CONST std::string _Format, ...);
	std::wstring Get(CONST std::wstring _Format, ...);
	VOID Get(ULONG& StringSize, CHAR& String, CONST CHAR* _Format, ...);

	// Character Conversion
	CHAR* ToA(CONST WCHAR* _Format, ...);
	WCHAR* ToW(CONST CHAR* _Format, ...);
	CHAR* ToUpper(CONST CHAR* _Format, ...);
	WCHAR* ToUpper(CONST WCHAR* _Format, ...);
	CHAR* ToLower(CONST CHAR* _Format, ...);
	WCHAR* ToLower(CONST WCHAR* _Format, ...);

	// Integer Conversion
	CHAR* FromInt(LLONG Value);
	CHAR* FromIntU(ULLONG Value);
	LONG ToInt(CONST CHAR* _Format, ...);
	ULONG ToIntU(CONST CHAR* _Format, ...);
	ULONG ToIntU(CONST WCHAR* _Format, ...);
	LLONG ToInt64(CONST CHAR* _Format, ...);
	ULLONG ToIntU64(CONST CHAR* _Format, ...);

	// Floating-Point Conversion
	CHAR* FromFloat(DOUBLE Value);
	DOUBLE ToFloat(CONST CHAR* _Format, ...);
	DOUBLE ToFloat(CONST WCHAR* _Format, ...);

	// Commandline
	CHAR** CommandLine(ULONG& nArgs, CONST CHAR* _Format, ...);
	ULONG GetArgCount(CONST CHAR* _Format, ...);
	ULONG GetArgCountW(CONST WCHAR* _Format, ...);
	CHAR* GetArg(ULONG iArg, CONST CHAR* _Format, ...);
	WCHAR* GetArgW(ULONG iArg, CONST WCHAR* _Format, ...);

	// Message Box
	VOID Message(CONST CHAR* _Format, ...);
	VOID MessageW(CONST WCHAR* _Format, ...);
	INT MessageYesNo(HWND hWndOwner, CONST CHAR* _Format, ...);
	INT MessageYesNoW(HWND hWndOwner, CONST WCHAR* _Format, ...);

	// BOOL
	BOOL GetBoolFromStr(CONST WCHAR* String);
	WCHAR* GetStrFromBool(BOOL Flag);

};

// Binary File
typedef enum tagOpenFileMode {
	READ_FILE = 0x00,		// rb
	CREATE_FILE = 0x01,		// wb
	EDIT_FILE = 0x02,		// rb+
	APPEND_FILE = 0x03		// ab+
	// To edit an existing file, use w+ for Mode
} OpenFileMode;
class System_File :
	public System_Type,
	public System_String {
private:
public:

	// Boot
	System_File(VOID) {}
	virtual ~System_File(VOID) {}

	// Status
	BOOL IsOpen(_iobuf* FILE);
	BOOL Exists(CONST CHAR* _Filename, ...);
	BOOL Exists(CONST WCHAR* _Filename, ...);

	// Meta
	CHAR* GetDirectory(CONST CHAR* _Directory, ...);
	WCHAR* GetDirectory(CONST WCHAR* _Directory, ...);
	CHAR* GetNamebase(CONST CHAR* _Filename, ...);
	WCHAR* GetNamebase(CONST WCHAR* _Filename, ...);
	CHAR* GetExtension(CONST CHAR* _Filename, ...);
	WCHAR* GetExtension(CONST WCHAR* _Filename, ...);

	// Memory
	UCHAR* Buffer(CONST CHAR* _Filename, ...);
	UCHAR* Buffer(CONST WCHAR* _Filename, ...);
	UCHAR* Buffer(ULLONG& _ElementSize, CONST CHAR* _Filename, ...);
	UCHAR* Buffer(ULLONG& _ElementSize, CONST WCHAR* _Filename, ...);
	UCHAR* Buffer(ULLONG _Offset, ULLONG& _ElementSize, CONST CHAR* _Filename, ...);
	UCHAR* Buffer(ULLONG _Offset, ULLONG& _ElementSize, CONST WCHAR* _Filename, ...);

	// Input
	_iobuf* Open(OpenFileMode _Mode, CONST CHAR* _Filename, ...);
	_iobuf* Open(OpenFileMode _Mode, CONST WCHAR* _Filename, ...);
	CHAR* GetFilename(HWND hwndOwner, CONST CHAR* DefExt, CONST CHAR* Filter);
	WCHAR* GetFilename(HWND hwndOwner, CONST WCHAR* DefExt, CONST WCHAR* Filter);
	CHAR* GetSavename(HWND hwndOwner, CONST CHAR* DefExt, CONST CHAR* Filter);
	WCHAR* GetSavename(HWND hwndOwner, CONST WCHAR* DefExt, CONST WCHAR* Filter);
	_iobuf* OpenFromFile(_iobuf* FILE, ULLONG _Offset, ULLONG _ElementSize, CONST CHAR* _Format, ...);
	_iobuf* OpenFromSource(UCHAR* _SrcBuf, ULLONG _ElementSize, CONST CHAR* _Format, ...);

	// Size
	ULLONG Size(_iobuf* FILE);
	ULLONG Size(CONST CHAR* _Filename, ...);
	ULLONG Size(CONST WCHAR* _Filename, ...);

	// Find
	ULLONG Find(_iobuf* FILE, ULLONG _Offset, PVOID _SrcBuf, ULLONG _ElementSize);
	ULLONG Find(_iobuf* FILE, ULLONG _Offset, PVOID _SrcBuf, ULLONG _ElementSize, BOOL Seek);

	// Output
	VOID CreateDummy(ULLONG Size, CONST CHAR* _Filename, ...);
	VOID CreateDummy(ULLONG Size, CONST WCHAR* _Filename, ...);
	VOID CreateDir(CONST CHAR* _Directory, ...);
	VOID CreateDir(CONST WCHAR* _Directory, ...);
	BOOL CreateFromSource(UCHAR* _SrcBuf, ULLONG _ElementSize, CONST CHAR* _Filename, ...);
	BOOL CreateFromSource(UCHAR* _SrcBuf, ULLONG _ElementSize, CONST WCHAR* _Filename, ...);
	BOOL CreateFromSource(_iobuf* FILE, ULLONG _Offset, ULLONG _ElementSize, CONST CHAR* _Filename, ...);
	BOOL CreateFromSource(_iobuf* FILE, ULLONG _Offset, ULLONG _ElementSize, CONST WCHAR* _Filename, ...);

	// Read
	UCHAR* Read(_iobuf* FILE, ULLONG _Offset, PVOID _Buffer, ULLONG _ElementSize);
	UCHAR* Read(_iobuf* FILE, ULLONG _Offset, ULLONG _ElementSize);
	UCHAR* ReadNext(_iobuf* FILE, PVOID _Buffer, ULLONG _ElementSize);

	// Write
	ULLONG Write(_iobuf* FILE, ULLONG _Offset, PVOID _Buffer, ULLONG _ElementSize);
	ULLONG Write(_iobuf* FILE, ULLONG _Offset, ULLONG Value, ULLONG _ElementSize);
	ULLONG WriteNext(_iobuf* FILE, PVOID _Buffer, ULLONG _ElementSize);

	// Print
	ULLONG Print(_iobuf* FILE, ULLONG _Offset, CONST CHAR* _Format, ...);
	ULLONG Print(_iobuf* FILE, ULLONG _Offset, CONST WCHAR* _Format, ...);
	ULLONG Print(_iobuf* FILE, CONST CHAR* _Format, ...);
	ULLONG Print(_iobuf* FILE, CONST  WCHAR* _Format, ...);

	// Disk
	ULLONG Align(ULLONG nAlign, ULLONG Value);
	VOID Align(ULLONG nAlign, CONST CHAR* _Filename, ...);
	VOID Align(ULLONG nAlign, CONST WCHAR* _Filename, ...);

};

// Text File
typedef struct tagTextFileA {
	std::vector <std::vector <std::string>> Args;	// Individual arguments (excluding any mix of 0x0D and/or 0x0A)
	std::vector <std::string> Line;					// Line of text (excluding any mix of 0x0D and/or 0x0A)
} TextFileA;
typedef struct tagTextFileW {
	std::vector <std::vector <std::wstring>> Args;	// Individual arguments (excluding any mix of 0x0D and/or 0x0A)
	std::vector <std::wstring> Line;				// Line of text (excluding any mix of 0x0D and/or 0x0A)
	USHORT Encoding{};								// 0xFEFF = UTF-16 Little Endian
													// 0xFFFE = UTF-16 Big Endian
} TextFileW;
class System_Text {
private:

	// System
	System_File ISystem_File, * File;

	// Read
	BOOL ReadLine(TextFileA* Text, _iobuf* FILE, ULLONG _Offset, ULLONG StrLen);
	BOOL ReadLine(TextFileW* Text, _iobuf* FILE, ULLONG _Offset, ULLONG StrLen);

public:

	// Boot
	System_Text(VOID) { File = &ISystem_File; }
	virtual ~System_Text(VOID) {}

	// Read
	TextFileA* OpenA(_iobuf* FILE, ULLONG _Offset, ULLONG _ElementSize);
	TextFileW* OpenW(_iobuf* FILE, ULLONG _Offset, ULLONG _ElementSize);

	// Open
	TextFileA* OpenA(CONST std::string _Filename, ...);
	TextFileA* OpenA(CONST std::wstring _Filename, ...);
	TextFileW* OpenW(CONST std::string _Filename, ...);
	TextFileW* OpenW(CONST std::wstring _Filename, ...);

	// Close
	VOID Close(TextFileA* Text);
	VOID Close(TextFileW* Text);

};

// Window
typedef struct tagMouseDevice {
	SHORT X;
	SHORT Y;
	SHORT Key;
	SHORT Delta;
	BOOL IsHot;
	TRACKMOUSEEVENT Event;
} MouseDevice;
class System_Window {
private:

	// Framework
	System_File ISystem_File, * File;

public:

	// Windows
	WNDCLASSEXW Class{};
	HINSTANCE hInstance;
	HACCEL hAccelTable;

	// Main
	HWND hWnd;
	LONG Width;
	LONG Height;
	RECT Rect{};
	HMENU Menu;

	// Devices
	MouseDevice Mouse{};
	SHORT VKey[256]{};

	// Toolbar
	BOOL UseToolBar;
	HWND ToolBar;
	INT ToolBarIconSize;

	// Status
	BOOL UseStatusBar;
	UINT nStatusBarParts;
	HWND StatusBar;

#ifdef DIRECT_X

	// Device
	IDirect3D9* D3D;
	D3DPRESENT_PARAMETERS d3dpp;
	IDirect3DDevice9* Device;
	D3DDISPLAYMODE Mode{};

	// Direct-X 9
	HWND dxWnd;
	RECT dxRect;

#endif // DIRECT_X

	// Boot
	System_Window(VOID) {
		File = &ISystem_File;
		hInstance = nullptr;
		hAccelTable = nullptr;
		hWnd = nullptr;
		Width = NULL;
		Height = NULL;
		UseToolBar = FALSE;
		ToolBar = nullptr;
		ToolBarIconSize = NULL;
		UseStatusBar = FALSE;
		nStatusBarParts = NULL;
		StatusBar = nullptr;
#ifdef DIRECT_X
		D3D = nullptr;
		d3dpp = { NULL };
		Device = nullptr;
		dxWnd = nullptr;
		dxRect = { NULL };
#endif // DIRECT_X
	}
	virtual ~System_Window(VOID) {}

	// Boot
	ATOM Register(HINSTANCE hInstance, WNDPROC WndProc);
	BOOL Init(LONG WindowWidth, LONG WindowHeight, HINSTANCE hInstance, int nCmdShow, WNDPROC WndProc);

	// Devices
	BOOL InitDevices(VOID);
	UINT GetDeviceInput(WPARAM wParam, LPARAM lParam);

	// ToolBar
	VOID CreateToolbar(VOID);

	// StatusBar
	VOID Status(UINT id, CONST CHAR* _Format, ...);

	// 
	RECT GetLocalCoordinates(HWND Parent, HWND Child);

#ifdef DIRECT_X

	// Direct-X 9
	BOOL InitD3D(VOID);
	VOID Screenshot(INT Width, INT Height, CONST WCHAR* _Filename, ...);

#endif // DIRECT_X

};
