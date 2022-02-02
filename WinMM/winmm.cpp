
#include "..\\dllmain.h"

#define WINMM_API __declspec(naked)

#define DLOG

HMODULE hModule = nullptr;
FARPROC pProcess[184];

// Load and link to the real "winmm.dll"
VOID InitWinMM(VOID) {

	if (!hModule)
	{
		char lpLibFileName[MAX_PATH];
		CopyMemory(lpLibFileName + GetSystemDirectoryA(lpLibFileName, MAX_PATH - 10), "\\winmm.dll", 11);

		hModule = LoadLibraryA(lpLibFileName);
		if (!hModule) return;
	}

	pProcess[3] = GetProcAddress(hModule, "mciExecute");
	pProcess[4] = GetProcAddress(hModule, "CloseDriver");
	pProcess[5] = GetProcAddress(hModule, "DefDriverProc");
	pProcess[6] = GetProcAddress(hModule, "DriverCallback");
	pProcess[7] = GetProcAddress(hModule, "DrvGetModuleHandle");
	pProcess[8] = GetProcAddress(hModule, "GetDriverModuleHandle");
	pProcess[9] = GetProcAddress(hModule, "OpenDriver");
	pProcess[10] = GetProcAddress(hModule, "PlaySound");
	pProcess[11] = GetProcAddress(hModule, "PlaySoundA");
	pProcess[12] = GetProcAddress(hModule, "PlaySoundW");
	pProcess[13] = GetProcAddress(hModule, "SendDriverMessage");
	pProcess[14] = GetProcAddress(hModule, "WOWAppExit");
	pProcess[15] = GetProcAddress(hModule, "auxGetDevCapsA");
	pProcess[16] = GetProcAddress(hModule, "auxGetDevCapsW");
	pProcess[17] = GetProcAddress(hModule, "auxGetNumDevs");
	pProcess[18] = GetProcAddress(hModule, "auxGetVolume");
	pProcess[19] = GetProcAddress(hModule, "auxOutMessage");
	pProcess[20] = GetProcAddress(hModule, "auxSetVolume");
	pProcess[21] = GetProcAddress(hModule, "joyConfigChanged");
	pProcess[22] = GetProcAddress(hModule, "joyGetDevCapsA");
	pProcess[23] = GetProcAddress(hModule, "joyGetDevCapsW");
	pProcess[24] = GetProcAddress(hModule, "joyGetNumDevs");
	pProcess[25] = GetProcAddress(hModule, "joyGetPos");
	pProcess[26] = GetProcAddress(hModule, "joyGetPosEx");
	pProcess[27] = GetProcAddress(hModule, "joyGetThreshold");
	pProcess[28] = GetProcAddress(hModule, "joyReleaseCapture");
	pProcess[29] = GetProcAddress(hModule, "joySetCapture");
	pProcess[30] = GetProcAddress(hModule, "joySetThreshold");
	pProcess[31] = GetProcAddress(hModule, "mciDriverNotify");
	pProcess[32] = GetProcAddress(hModule, "mciDriverYield");
	pProcess[33] = GetProcAddress(hModule, "mciFreeCommandResource");
	pProcess[34] = GetProcAddress(hModule, "mciGetCreatorTask");
	pProcess[35] = GetProcAddress(hModule, "mciGetDeviceIDA");
	pProcess[36] = GetProcAddress(hModule, "mciGetDeviceIDFromElementIDA");
	pProcess[37] = GetProcAddress(hModule, "mciGetDeviceIDFromElementIDW");
	pProcess[38] = GetProcAddress(hModule, "mciGetDeviceIDW");
	pProcess[39] = GetProcAddress(hModule, "mciGetDriverData");
	pProcess[40] = GetProcAddress(hModule, "mciGetErrorStringA");
	pProcess[41] = GetProcAddress(hModule, "mciGetErrorStringW");
	pProcess[42] = GetProcAddress(hModule, "mciGetYieldProc");
	pProcess[43] = GetProcAddress(hModule, "mciLoadCommandResource");
	pProcess[44] = GetProcAddress(hModule, "mciSendCommandA");
	pProcess[45] = GetProcAddress(hModule, "mciSendCommandW");
	pProcess[46] = GetProcAddress(hModule, "mciSendStringA");
	pProcess[47] = GetProcAddress(hModule, "mciSendStringW");
	pProcess[48] = GetProcAddress(hModule, "mciSetDriverData");
	pProcess[49] = GetProcAddress(hModule, "mciSetYieldProc");
	pProcess[50] = GetProcAddress(hModule, "midiConnect");
	pProcess[51] = GetProcAddress(hModule, "midiDisconnect");
	pProcess[52] = GetProcAddress(hModule, "midiInAddBuffer");
	pProcess[53] = GetProcAddress(hModule, "midiInClose");
	pProcess[54] = GetProcAddress(hModule, "midiInGetDevCapsA");
	pProcess[55] = GetProcAddress(hModule, "midiInGetDevCapsW");
	pProcess[56] = GetProcAddress(hModule, "midiInGetErrorTextA");
	pProcess[57] = GetProcAddress(hModule, "midiInGetErrorTextW");
	pProcess[58] = GetProcAddress(hModule, "midiInGetID");
	pProcess[59] = GetProcAddress(hModule, "midiInGetNumDevs");
	pProcess[60] = GetProcAddress(hModule, "midiInMessage");
	pProcess[61] = GetProcAddress(hModule, "midiInOpen");
	pProcess[62] = GetProcAddress(hModule, "midiInPrepareHeader");
	pProcess[63] = GetProcAddress(hModule, "midiInReset");
	pProcess[64] = GetProcAddress(hModule, "midiInStart");
	pProcess[65] = GetProcAddress(hModule, "midiInStop");
	pProcess[66] = GetProcAddress(hModule, "midiInUnprepareHeader");
	pProcess[67] = GetProcAddress(hModule, "midiOutCacheDrumPatches");
	pProcess[68] = GetProcAddress(hModule, "midiOutCachePatches");
	pProcess[69] = GetProcAddress(hModule, "midiOutClose");
	pProcess[70] = GetProcAddress(hModule, "midiOutGetDevCapsA");
	pProcess[71] = GetProcAddress(hModule, "midiOutGetDevCapsW");
	pProcess[72] = GetProcAddress(hModule, "midiOutGetErrorTextA");
	pProcess[73] = GetProcAddress(hModule, "midiOutGetErrorTextW");
	pProcess[74] = GetProcAddress(hModule, "midiOutGetID");
	pProcess[75] = GetProcAddress(hModule, "midiOutGetNumDevs");
	pProcess[76] = GetProcAddress(hModule, "midiOutGetVolume");
	pProcess[77] = GetProcAddress(hModule, "midiOutLongMsg");
	pProcess[78] = GetProcAddress(hModule, "midiOutMessage");
	pProcess[79] = GetProcAddress(hModule, "midiOutOpen");
	pProcess[80] = GetProcAddress(hModule, "midiOutPrepareHeader");
	pProcess[81] = GetProcAddress(hModule, "midiOutReset");
	pProcess[82] = GetProcAddress(hModule, "midiOutSetVolume");
	pProcess[83] = GetProcAddress(hModule, "midiOutShortMsg");
	pProcess[84] = GetProcAddress(hModule, "midiOutUnprepareHeader");
	pProcess[85] = GetProcAddress(hModule, "midiStreamClose");
	pProcess[86] = GetProcAddress(hModule, "midiStreamOpen");
	pProcess[87] = GetProcAddress(hModule, "midiStreamOut");
	pProcess[88] = GetProcAddress(hModule, "midiStreamPause");
	pProcess[89] = GetProcAddress(hModule, "midiStreamPosition");
	pProcess[90] = GetProcAddress(hModule, "midiStreamProperty");
	pProcess[91] = GetProcAddress(hModule, "midiStreamRestart");
	pProcess[92] = GetProcAddress(hModule, "midiStreamStop");
	pProcess[93] = GetProcAddress(hModule, "mixerClose");
	pProcess[94] = GetProcAddress(hModule, "mixerGetControlDetailsA");
	pProcess[95] = GetProcAddress(hModule, "mixerGetControlDetailsW");
	pProcess[96] = GetProcAddress(hModule, "mixerGetDevCapsA");
	pProcess[97] = GetProcAddress(hModule, "mixerGetDevCapsW");
	pProcess[98] = GetProcAddress(hModule, "mixerGetID");
	pProcess[99] = GetProcAddress(hModule, "mixerGetLineControlsA");
	pProcess[100] = GetProcAddress(hModule, "mixerGetLineControlsW");
	pProcess[101] = GetProcAddress(hModule, "mixerGetLineInfoA");
	pProcess[102] = GetProcAddress(hModule, "mixerGetLineInfoW");
	pProcess[103] = GetProcAddress(hModule, "mixerGetNumDevs");
	pProcess[104] = GetProcAddress(hModule, "mixerMessage");
	pProcess[105] = GetProcAddress(hModule, "mixerOpen");
	pProcess[106] = GetProcAddress(hModule, "mixerSetControlDetails");
	pProcess[107] = GetProcAddress(hModule, "mmDrvInstall");
	pProcess[108] = GetProcAddress(hModule, "mmGetCurrentTask");
	pProcess[109] = GetProcAddress(hModule, "mmTaskBlock");
	pProcess[110] = GetProcAddress(hModule, "mmTaskCreate");
	pProcess[111] = GetProcAddress(hModule, "mmTaskSignal");
	pProcess[112] = GetProcAddress(hModule, "mmTaskYield");
	pProcess[113] = GetProcAddress(hModule, "mmioAdvance");
	pProcess[114] = GetProcAddress(hModule, "mmioAscend");
	pProcess[115] = GetProcAddress(hModule, "mmioClose");
	pProcess[116] = GetProcAddress(hModule, "mmioCreateChunk");
	pProcess[117] = GetProcAddress(hModule, "mmioDescend");
	pProcess[118] = GetProcAddress(hModule, "mmioFlush");
	pProcess[119] = GetProcAddress(hModule, "mmioGetInfo");
	pProcess[120] = GetProcAddress(hModule, "mmioInstallIOProcA");
	pProcess[121] = GetProcAddress(hModule, "mmioInstallIOProcW");
	pProcess[122] = GetProcAddress(hModule, "mmioOpenA");
	pProcess[123] = GetProcAddress(hModule, "mmioOpenW");
	pProcess[124] = GetProcAddress(hModule, "mmioRead");
	pProcess[125] = GetProcAddress(hModule, "mmioRenameA");
	pProcess[126] = GetProcAddress(hModule, "mmioRenameW");
	pProcess[127] = GetProcAddress(hModule, "mmioSeek");
	pProcess[128] = GetProcAddress(hModule, "mmioSendMessage");
	pProcess[129] = GetProcAddress(hModule, "mmioSetBuffer");
	pProcess[130] = GetProcAddress(hModule, "mmioSetInfo");
	pProcess[131] = GetProcAddress(hModule, "mmioStringToFOURCCA");
	pProcess[132] = GetProcAddress(hModule, "mmioStringToFOURCCW");
	pProcess[133] = GetProcAddress(hModule, "mmioWrite");
	pProcess[134] = GetProcAddress(hModule, "mmsystemGetVersion");
	pProcess[135] = GetProcAddress(hModule, "sndPlaySoundA");
	pProcess[136] = GetProcAddress(hModule, "sndPlaySoundW");
	pProcess[137] = GetProcAddress(hModule, "timeBeginPeriod");
	pProcess[138] = GetProcAddress(hModule, "timeEndPeriod");
	pProcess[139] = GetProcAddress(hModule, "timeGetDevCaps");
	pProcess[140] = GetProcAddress(hModule, "timeGetSystemTime");
	pProcess[141] = GetProcAddress(hModule, "timeGetTime");
	pProcess[142] = GetProcAddress(hModule, "timeKillEvent");
	pProcess[143] = GetProcAddress(hModule, "timeSetEvent");
	pProcess[144] = GetProcAddress(hModule, "waveInAddBuffer");
	pProcess[145] = GetProcAddress(hModule, "waveInClose");
	pProcess[146] = GetProcAddress(hModule, "waveInGetDevCapsA");
	pProcess[147] = GetProcAddress(hModule, "waveInGetDevCapsW");
	pProcess[148] = GetProcAddress(hModule, "waveInGetErrorTextA");
	pProcess[149] = GetProcAddress(hModule, "waveInGetErrorTextW");
	pProcess[150] = GetProcAddress(hModule, "waveInGetID");
	pProcess[151] = GetProcAddress(hModule, "waveInGetNumDevs");
	pProcess[152] = GetProcAddress(hModule, "waveInGetPosition");
	pProcess[153] = GetProcAddress(hModule, "waveInMessage");
	pProcess[154] = GetProcAddress(hModule, "waveInOpen");
	pProcess[155] = GetProcAddress(hModule, "waveInPrepareHeader");
	pProcess[156] = GetProcAddress(hModule, "waveInReset");
	pProcess[157] = GetProcAddress(hModule, "waveInStart");
	pProcess[158] = GetProcAddress(hModule, "waveInStop");
	pProcess[159] = GetProcAddress(hModule, "waveInUnprepareHeader");
	pProcess[160] = GetProcAddress(hModule, "waveOutBreakLoop");
	pProcess[161] = GetProcAddress(hModule, "waveOutClose");
	pProcess[162] = GetProcAddress(hModule, "waveOutGetDevCapsA");
	pProcess[163] = GetProcAddress(hModule, "waveOutGetDevCapsW");
	pProcess[164] = GetProcAddress(hModule, "waveOutGetErrorTextA");
	pProcess[165] = GetProcAddress(hModule, "waveOutGetErrorTextW");
	pProcess[166] = GetProcAddress(hModule, "waveOutGetID");
	pProcess[167] = GetProcAddress(hModule, "waveOutGetNumDevs");
	pProcess[168] = GetProcAddress(hModule, "waveOutGetPitch");
	pProcess[169] = GetProcAddress(hModule, "waveOutGetPlaybackRate");
	pProcess[170] = GetProcAddress(hModule, "waveOutGetPosition");
	pProcess[171] = GetProcAddress(hModule, "waveOutGetVolume");
	pProcess[172] = GetProcAddress(hModule, "waveOutMessage");
	pProcess[173] = GetProcAddress(hModule, "waveOutOpen");
	pProcess[174] = GetProcAddress(hModule, "waveOutPause");
	pProcess[175] = GetProcAddress(hModule, "waveOutPrepareHeader");
	pProcess[176] = GetProcAddress(hModule, "waveOutReset");
	pProcess[177] = GetProcAddress(hModule, "waveOutRestart");
	pProcess[178] = GetProcAddress(hModule, "waveOutSetPitch");
	pProcess[179] = GetProcAddress(hModule, "waveOutSetPlaybackRate");
	pProcess[180] = GetProcAddress(hModule, "waveOutSetVolume");
	pProcess[181] = GetProcAddress(hModule, "waveOutUnprepareHeader");
	pProcess[182] = GetProcAddress(hModule, "waveOutWrite");

}

// Proxy Exports
WINMM_API VOID PROXY_mciExecute(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[3 * 4] } }
WINMM_API VOID PROXY_CloseDriver(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[4 * 4] } }
WINMM_API VOID PROXY_DefDriverProc(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[5 * 4] } }
WINMM_API VOID PROXY_DriverCallback(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[6 * 4] } }
WINMM_API VOID PROXY_DrvGetModuleHandle(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[7 * 4] } }
WINMM_API VOID PROXY_GetDriverModuleHandle(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[8 * 4] } }
WINMM_API VOID PROXY_OpenDriver(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[9 * 4] } }
WINMM_API VOID PROXY_PlaySound(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[10 * 4] } }
WINMM_API VOID PROXY_PlaySoundA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[11 * 4] } }
WINMM_API VOID PROXY_PlaySoundW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[12 * 4] } }
WINMM_API VOID PROXY_SendDriverMessage(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[13 * 4] } }
WINMM_API VOID PROXY_WOWAppExit(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[14 * 4] } }
WINMM_API VOID PROXY_auxGetDevCapsA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[15 * 4] } }
WINMM_API VOID PROXY_auxGetDevCapsW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[16 * 4] } }
WINMM_API VOID PROXY_auxGetNumDevs(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[17 * 4] } }
WINMM_API VOID PROXY_auxGetVolume(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[18 * 4] } }
WINMM_API VOID PROXY_auxOutMessage(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[19 * 4] } }
WINMM_API VOID PROXY_auxSetVolume(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[20 * 4] } }
WINMM_API VOID PROXY_joyConfigChanged(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[21 * 4] } }
WINMM_API VOID PROXY_joyGetDevCapsA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[22 * 4] } }
WINMM_API VOID PROXY_joyGetDevCapsW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[23 * 4] } }
WINMM_API VOID PROXY_joyGetNumDevs(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[24 * 4] } }
WINMM_API VOID PROXY_joyGetPos(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[25 * 4] } }
WINMM_API VOID PROXY_joyGetPosEx(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[26 * 4] } }
WINMM_API VOID PROXY_joyGetThreshold(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[27 * 4] } }
WINMM_API VOID PROXY_joyReleaseCapture(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[28 * 4] } }
WINMM_API VOID PROXY_joySetCapture(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[29 * 4] } }
WINMM_API VOID PROXY_joySetThreshold(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[30 * 4] } }
WINMM_API VOID PROXY_mciDriverNotify(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[31 * 4] } }
WINMM_API VOID PROXY_mciDriverYield(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[32 * 4] } }
WINMM_API VOID PROXY_mciFreeCommandResource(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[33 * 4] } }
WINMM_API VOID PROXY_mciGetCreatorTask(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[34 * 4] } }
WINMM_API VOID PROXY_mciGetDeviceIDA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[35 * 4] } }
WINMM_API VOID PROXY_mciGetDeviceIDFromElementIDA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[36 * 4] } }
WINMM_API VOID PROXY_mciGetDeviceIDFromElementIDW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[37 * 4] } }
WINMM_API VOID PROXY_mciGetDeviceIDW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[38 * 4] } }
WINMM_API VOID PROXY_mciGetDriverData(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[39 * 4] } }
WINMM_API VOID PROXY_mciGetErrorStringA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[40 * 4] } }
WINMM_API VOID PROXY_mciGetErrorStringW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[41 * 4] } }
WINMM_API VOID PROXY_mciGetYieldProc(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[42 * 4] } }
WINMM_API VOID PROXY_mciLoadCommandResource(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[43 * 4] } }
WINMM_API VOID PROXY_mciSendCommandA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[44 * 4] } }
WINMM_API VOID PROXY_mciSendCommandW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[45 * 4] } }
WINMM_API VOID PROXY_mciSendStringA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[46 * 4] } }
WINMM_API VOID PROXY_mciSendStringW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[47 * 4] } }
WINMM_API VOID PROXY_mciSetDriverData(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[48 * 4] } }
WINMM_API VOID PROXY_mciSetYieldProc(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[49 * 4] } }
WINMM_API VOID PROXY_midiConnect(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[50 * 4] } }
WINMM_API VOID PROXY_midiDisconnect(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[51 * 4] } }
WINMM_API VOID PROXY_midiInAddBuffer(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[52 * 4] } }
WINMM_API VOID PROXY_midiInClose(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[53 * 4] } }
WINMM_API VOID PROXY_midiInGetDevCapsA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[54 * 4] } }
WINMM_API VOID PROXY_midiInGetDevCapsW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[55 * 4] } }
WINMM_API VOID PROXY_midiInGetErrorTextA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[56 * 4] } }
WINMM_API VOID PROXY_midiInGetErrorTextW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[57 * 4] } }
WINMM_API VOID PROXY_midiInGetID(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[58 * 4] } }
WINMM_API VOID PROXY_midiInGetNumDevs(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[59 * 4] } }
WINMM_API VOID PROXY_midiInMessage(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[60 * 4] } }
WINMM_API VOID PROXY_midiInOpen(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[61 * 4] } }
WINMM_API VOID PROXY_midiInPrepareHeader(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[62 * 4] } }
WINMM_API VOID PROXY_midiInReset(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[63 * 4] } }
WINMM_API VOID PROXY_midiInStart(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[64 * 4] } }
WINMM_API VOID PROXY_midiInStop(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[65 * 4] } }
WINMM_API VOID PROXY_midiInUnprepareHeader(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[66 * 4] } }
WINMM_API VOID PROXY_midiOutCacheDrumPatches(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[67 * 4] } }
WINMM_API VOID PROXY_midiOutCachePatches(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[68 * 4] } }
WINMM_API VOID PROXY_midiOutClose(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[69 * 4] } }
WINMM_API VOID PROXY_midiOutGetDevCapsA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[70 * 4] } }
WINMM_API VOID PROXY_midiOutGetDevCapsW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[71 * 4] } }
WINMM_API VOID PROXY_midiOutGetErrorTextA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[72 * 4] } }
WINMM_API VOID PROXY_midiOutGetErrorTextW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[73 * 4] } }
WINMM_API VOID PROXY_midiOutGetID(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[74 * 4] } }
WINMM_API VOID PROXY_midiOutGetNumDevs(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[75 * 4] } }
WINMM_API VOID PROXY_midiOutGetVolume(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[76 * 4] } }
WINMM_API VOID PROXY_midiOutLongMsg(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[77 * 4] } }
WINMM_API VOID PROXY_midiOutMessage(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[78 * 4] } }
WINMM_API VOID PROXY_midiOutOpen(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[79 * 4] } }
WINMM_API VOID PROXY_midiOutPrepareHeader(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[80 * 4] } }
WINMM_API VOID PROXY_midiOutReset(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[81 * 4] } }
WINMM_API VOID PROXY_midiOutSetVolume(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[82 * 4] } }
WINMM_API VOID PROXY_midiOutShortMsg(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[83 * 4] } }
WINMM_API VOID PROXY_midiOutUnprepareHeader(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[84 * 4] } }
WINMM_API VOID PROXY_midiStreamClose(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[85 * 4] } }
WINMM_API VOID PROXY_midiStreamOpen(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[86 * 4] } }
WINMM_API VOID PROXY_midiStreamOut(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[87 * 4] } }
WINMM_API VOID PROXY_midiStreamPause(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[88 * 4] } }
WINMM_API VOID PROXY_midiStreamPosition(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[89 * 4] } }
WINMM_API VOID PROXY_midiStreamProperty(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[90 * 4] } }
WINMM_API VOID PROXY_midiStreamRestart(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[91 * 4] } }
WINMM_API VOID PROXY_midiStreamStop(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[92 * 4] } }
WINMM_API VOID PROXY_mixerClose(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[93 * 4] } }
WINMM_API VOID PROXY_mixerGetControlDetailsA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[94 * 4] } }
WINMM_API VOID PROXY_mixerGetControlDetailsW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[95 * 4] } }
WINMM_API VOID PROXY_mixerGetDevCapsA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[96 * 4] } }
WINMM_API VOID PROXY_mixerGetDevCapsW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[97 * 4] } }
WINMM_API VOID PROXY_mixerGetID(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[98 * 4] } }
WINMM_API VOID PROXY_mixerGetLineControlsA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[99 * 4] } }
WINMM_API VOID PROXY_mixerGetLineControlsW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[100 * 4] } }
WINMM_API VOID PROXY_mixerGetLineInfoA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[101 * 4] } }
WINMM_API VOID PROXY_mixerGetLineInfoW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[102 * 4] } }
WINMM_API VOID PROXY_mixerGetNumDevs(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[103 * 4] } }
WINMM_API VOID PROXY_mixerMessage(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[104 * 4] } }
WINMM_API VOID PROXY_mixerOpen(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[105 * 4] } }
WINMM_API VOID PROXY_mixerSetControlDetails(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[106 * 4] } }
WINMM_API VOID PROXY_mmDrvInstall(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[107 * 4] } }
WINMM_API VOID PROXY_mmGetCurrentTask(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[108 * 4] } }
WINMM_API VOID PROXY_mmTaskBlock(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[109 * 4] } }
WINMM_API VOID PROXY_mmTaskCreate(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[110 * 4] } }
WINMM_API VOID PROXY_mmTaskSignal(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[111 * 4] } }
WINMM_API VOID PROXY_mmTaskYield(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[112 * 4] } }
WINMM_API VOID PROXY_mmioAdvance(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[113 * 4] } }
WINMM_API VOID PROXY_mmioAscend(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[114 * 4] } }
WINMM_API VOID PROXY_mmioClose(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[115 * 4] } }
WINMM_API VOID PROXY_mmioCreateChunk(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[116 * 4] } }
WINMM_API VOID PROXY_mmioDescend(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[117 * 4] } }
WINMM_API VOID PROXY_mmioFlush(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[118 * 4] } }
WINMM_API VOID PROXY_mmioGetInfo(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[119 * 4] } }
WINMM_API VOID PROXY_mmioInstallIOProcA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[120 * 4] } }
WINMM_API VOID PROXY_mmioInstallIOProcW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[121 * 4] } }
WINMM_API VOID PROXY_mmioOpenA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[122 * 4] } }
WINMM_API VOID PROXY_mmioOpenW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[123 * 4] } }
WINMM_API VOID PROXY_mmioRead(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[124 * 4] } }
WINMM_API VOID PROXY_mmioRenameA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[125 * 4] } }
WINMM_API VOID PROXY_mmioRenameW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[126 * 4] } }
WINMM_API VOID PROXY_mmioSeek(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[127 * 4] } }
WINMM_API VOID PROXY_mmioSendMessage(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[128 * 4] } }
WINMM_API VOID PROXY_mmioSetBuffer(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[129 * 4] } }
WINMM_API VOID PROXY_mmioSetInfo(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[130 * 4] } }
WINMM_API VOID PROXY_mmioStringToFOURCCA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[131 * 4] } }
WINMM_API VOID PROXY_mmioStringToFOURCCW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[132 * 4] } }
WINMM_API VOID PROXY_mmioWrite(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[133 * 4] } }
WINMM_API VOID PROXY_mmsystemGetVersion(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[134 * 4] } }
WINMM_API VOID PROXY_sndPlaySoundA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[135 * 4] } }
WINMM_API VOID PROXY_sndPlaySoundW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[136 * 4] } }
WINMM_API VOID PROXY_timeBeginPeriod(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[137 * 4] } }
WINMM_API VOID PROXY_timeEndPeriod(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[138 * 4] } }
WINMM_API VOID PROXY_timeGetDevCaps(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[139 * 4] } }
WINMM_API VOID PROXY_timeGetSystemTime(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[140 * 4] } }
WINMM_API VOID PROXY_timeGetTime(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[141 * 4] } }
WINMM_API VOID PROXY_timeKillEvent(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[142 * 4] } }
WINMM_API VOID PROXY_timeSetEvent(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[143 * 4] } }
WINMM_API VOID PROXY_waveInAddBuffer(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[144 * 4] } }
WINMM_API VOID PROXY_waveInClose(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[145 * 4] } }
WINMM_API VOID PROXY_waveInGetDevCapsA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[146 * 4] } }
WINMM_API VOID PROXY_waveInGetDevCapsW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[147 * 4] } }
WINMM_API VOID PROXY_waveInGetErrorTextA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[148 * 4] } }
WINMM_API VOID PROXY_waveInGetErrorTextW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[149 * 4] } }
WINMM_API VOID PROXY_waveInGetID(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[150 * 4] } }
WINMM_API VOID PROXY_waveInGetNumDevs(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[151 * 4] } }
WINMM_API VOID PROXY_waveInGetPosition(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[152 * 4] } }
WINMM_API VOID PROXY_waveInMessage(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[153 * 4] } }
WINMM_API VOID PROXY_waveInOpen(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[154 * 4] } }
WINMM_API VOID PROXY_waveInPrepareHeader(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[155 * 4] } }
WINMM_API VOID PROXY_waveInReset(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[156 * 4] } }
WINMM_API VOID PROXY_waveInStart(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[157 * 4] } }
WINMM_API VOID PROXY_waveInStop(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[158 * 4] } }
WINMM_API VOID PROXY_waveInUnprepareHeader(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[159 * 4] } }
WINMM_API VOID PROXY_waveOutBreakLoop(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[160 * 4] } }
WINMM_API VOID PROXY_waveOutClose(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[161 * 4] } }
WINMM_API VOID PROXY_waveOutGetDevCapsA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[162 * 4] } }
WINMM_API VOID PROXY_waveOutGetDevCapsW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[163 * 4] } }
WINMM_API VOID PROXY_waveOutGetErrorTextA(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[164 * 4] } }
WINMM_API VOID PROXY_waveOutGetErrorTextW(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[165 * 4] } }
WINMM_API VOID PROXY_waveOutGetID(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[166 * 4] } }
WINMM_API VOID PROXY_waveOutGetNumDevs(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[167 * 4] } }
WINMM_API VOID PROXY_waveOutGetPitch(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[168 * 4] } }
WINMM_API VOID PROXY_waveOutGetPlaybackRate(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[169 * 4] } }
WINMM_API VOID PROXY_waveOutGetPosition(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[170 * 4] } }
WINMM_API VOID PROXY_waveOutGetVolume(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[171 * 4] } }
WINMM_API VOID PROXY_waveOutMessage(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[172 * 4] } }
WINMM_API VOID PROXY_waveOutOpen(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[173 * 4] } }
WINMM_API VOID PROXY_waveOutPause(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[174 * 4] } }
WINMM_API VOID PROXY_waveOutPrepareHeader(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[175 * 4] } }
WINMM_API VOID PROXY_waveOutReset(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[176 * 4] } }
WINMM_API VOID PROXY_waveOutRestart(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[177 * 4] } }
WINMM_API VOID PROXY_waveOutSetPitch(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[178 * 4] } }
WINMM_API VOID PROXY_waveOutSetPlaybackRate(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[179 * 4] } }
WINMM_API VOID PROXY_waveOutSetVolume(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[180 * 4] } }
WINMM_API VOID PROXY_waveOutUnprepareHeader(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[181 * 4] } }
WINMM_API VOID PROXY_waveOutWrite(VOID) { DLOG(__FUNCTION__); __asm { jmp pProcess[182 * 4] } }
