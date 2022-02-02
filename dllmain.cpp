
#include "dllmain.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

// System Initialization
System_File ISystem_File, * File;
System_Text ISystem_Text, * Text;
Resident_Evil_4_PC_AV IResident_Evil_4_PC_AV, * Bio4Movie;
VOID InitFramework(VOID) {

    // System
    File = &ISystem_File;
	Text = &ISystem_Text;

	Bio4Movie = &IResident_Evil_4_PC_AV;

}

// Entry Point
HMODULE hInstance = nullptr;
CHAR* ModuleDir = nullptr;
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		hInstance = hModule;
		ModuleDir = new CHAR[_MAX_PATH];
		RtlSecureZeroMemory(ModuleDir, _MAX_PATH);
		ModuleDir = _getcwd(ModuleDir, _MAX_PATH);
		InitFramework();
		InitWinMM();
		InitBio4PC((UCHAR*)GetModuleHandle(NULL));
	}
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
