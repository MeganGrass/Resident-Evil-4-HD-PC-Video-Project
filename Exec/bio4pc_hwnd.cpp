
#include "..\\dllmain.h"

DWORD processID;
HWND hWnd;

// makes the exe freely writable on DLL-side of code
VOID MakePageWritable(ULONG ulAddress, ULONG ulSize) {
	MEMORY_BASIC_INFORMATION* mbi = new MEMORY_BASIC_INFORMATION;
	VirtualQuery((VOID*)ulAddress, mbi, ulSize);
	if (mbi->Protect != PAGE_EXECUTE_READWRITE)
	{
		ULONG* ulProtect = new ULONG;
		VirtualProtect((VOID*)ulAddress, ulSize, PAGE_EXECUTE_READWRITE, ulProtect);
		delete ulProtect;
	}
	delete mbi;
}
DWORD FindProcessId(const std::wstring& processName) {
	PROCESSENTRY32W processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	Process32FirstW(processesSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile))
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while (Process32NextW(processesSnapshot, &processInfo))
	{
		if (!processName.compare(processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}

	CloseHandle(processesSnapshot);
	return 0;
}
BOOL CALLBACK EnumWindowsProcMy(HWND Window, LPARAM lParam) {
	DWORD lpdwProcessId;
	GetWindowThreadProcessId(Window, &lpdwProcessId);
	if (lpdwProcessId == lParam)
	{
		hWnd = Window;
		return FALSE;
	}
	return TRUE;
}
HWND GetBio4Window(VOID) {
	processID = FindProcessId(L"bio4.exe");
	EnumWindows(EnumWindowsProcMy, processID);
	if (!IsWindow(hWnd)) { File->Message("IsWindow Fail!"); return nullptr; }
	else return hWnd;
}