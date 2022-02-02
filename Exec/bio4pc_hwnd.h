#pragma once

extern DWORD processID;
extern HWND hWnd;

// 
VOID MakePageWritable(ULONG ulAddress, ULONG ulSize);
DWORD FindProcessId(const std::wstring& processName);
BOOL CALLBACK EnumWindowsProcMy(HWND Window, LPARAM lParam);
HWND GetBio4Window(VOID);
