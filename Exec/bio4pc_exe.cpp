
#include "..\\dllmain.h"

// Executable File
UCHAR* pExecutable;
MEMORY_BASIC_INFORMATION MemoryBasicInfo;
IMAGE_DOS_HEADER* MzHeader;
ULONG AllocationBase = NULL;

// Global
UCHAR* pSys;
ULONG* pG;

// Variables
//FLOAT* lr_rate_1504;	// cam-stick range (0.0f = best)
//DOUBLE* TestAim;
// 00b17a08 sub w
// 00b0ff80 sub h

DOUBLE* Value0;
DOUBLE* Value1;

// Initialize
VOID Bio4_Variables(VOID) {

	// Mem1
	UCHAR* Testing = new UCHAR[6];
	Testing[0] = 0x8d;
	Testing[1] = 0x8e;
	Testing[2] = 0x00;
	Testing[3] = 0x00;
	Testing[4] = 0x00;
	Testing[5] = 0x04;
	memcpy_s(&pExecutable[0x006562cb - EXE_BASE], 6, &Testing[0], 6);
	InjectPush(0x00974839, 0x04000000);
	InjectPush(0x0097484d, 0x04000000);
	InjectPush(0x0097486e, 0x04000000);
	InjectAdd(0x0097489c, 0x04000000);

	// Mem2
	InjectPush(0x00974828, 0x08000000);
	InjectPush(0x0097485e, 0x08000000);
	InjectPush(0x00974886, 0x08000000);
	InjectAdd(0x009748b0, 0x08000000);

	// Header
	MzHeader = (IMAGE_DOS_HEADER*)&pExecutable[(ULONG)MemoryBasicInfo.AllocationBase];

	// Direct-X
	pInterface = (LPDIRECT3D9*)&pExecutable[0x010ecb24 - EXE_BASE];
	pdx9Surface = (LPDIRECT3DSURFACE9*)&pExecutable[0x010ed628 - EXE_BASE];
	pDestSurface = (LPDIRECT3DSURFACE9*)&pExecutable[0x010ed67c - EXE_BASE];
	pBackBufferSurface = (LPDIRECT3DSURFACE9*)&pExecutable[0x010c7470 - EXE_BASE];

	// Global
	pSys = (UCHAR*)&pExecutable[0x00c62df0 - EXE_BASE];
	//pG = (ULONG*)&pExecutable[0x00c06f3c - EXE_BASE];
	pG = (ULONG*)&pExecutable[0x00c5a760 - EXE_BASE];

	// Flag
	DebugFlag = (UINT*)&pExecutable[0x00c5a7c0 - EXE_BASE];
	StopFlag = (UINT*)&pExecutable[0x00c5a8d0 - EXE_BASE];
	StatusFlag = (UINT*)&pExecutable[0x00c5f77c - EXE_BASE];
	SystemFlag = (UINT*)&pExecutable[0x00c5a7b4 - EXE_BASE];
	ItemSetFlag = (UINT*)&pExecutable[0x00c5f9ec - EXE_BASE];
	ScenarioFlag = (UINT*)&pExecutable[0x00c5fa2c - EXE_BASE];
	KeyLockFlag = (UINT*)&pExecutable[0x00c5fa4c - EXE_BASE];
	ExtraFlag = (UINT*)&pExecutable[0x00c62df4 - EXE_BASE];
	ConfigFlag = (UINT*)&pExecutable[0x00c62df0 - EXE_BASE];
	DisplayFlag = (UINT*)&pExecutable[0x00c5a7b8 - EXE_BASE];

	// Sofdec
	Sofdec = (UINT*)&pExecutable[0x00c6cd50 - EXE_BASE];

	// Render
	dAspectR = (DOUBLE*)&pExecutable[0x00b13760 - EXE_BASE];
	AspectRatio = (FLOAT*)&pExecutable[0x00b1377c - EXE_BASE];
	*dAspectR = Bio4Config.dAspectR; // 1.77778f;
	*AspectRatio = Bio4Config.AspectRatio; // 1.77778f;
	InternalResolutionWidth = (DOUBLE*)&pExecutable[0x00b20678 - EXE_BASE];
	*InternalResolutionWidth = Bio4Config.InternalWidth;
	InternalResolutionHeight = (DOUBLE*)&pExecutable[0x00b20688 - EXE_BASE];
	*InternalResolutionHeight = Bio4Config.InternalHeight;
	ScreenWidth = (UINT*)&pExecutable[0x010edda0 - EXE_BASE];
	ScreenHeight = (UINT*)&pExecutable[0x010edda4 - EXE_BASE];

	// Screen
	ZNEAR = (FLOAT*)&pExecutable[0x00c62fd0 - EXE_BASE];
	ZFAR = (FLOAT*)&pExecutable[0x00c63a18 - EXE_BASE];
	ORTHO_T = (FLOAT*)&pExecutable[0x00c63a2c - EXE_BASE];
	system_vcnt = (BYTE*)&pExecutable[0x00c5a670 - EXE_BASE];
	ORTHO_B = (FLOAT*)&pExecutable[0x00c63a28 - EXE_BASE];
	ORTHO_L = (FLOAT*)&pExecutable[0x00c5a684 - EXE_BASE];
	ORTHO_R = (FLOAT*)&pExecutable[0x00c5a5bc - EXE_BASE];
	Screen = (tagScreen*)&pExecutable[0x00c62e9c - EXE_BASE];
	pSys_10 = (UCHAR*)&pExecutable[0x00c62dfa - EXE_BASE];
	ReSizeWidth = (SHORT*)&pExecutable[0x00c65d64 - EXE_BASE];
	ReSizeHeight = (SHORT*)&pExecutable[0x00c65d66 - EXE_BASE];

	// Attache Case (Start Game)
	InjectPushByte(0x0070930c, Bio4Config.AttacheSize);	// 0x7F XL Storage
	InjectPushByte(0x0070931b, Bio4Config.StartWeapon);	// 0x34 Weapon
	InjectPushByte(0x00709375, Bio4Config.StartHeal);	// 0x05 F.Aid Spray

	*(UCHAR*)&pExecutable[0x00709bd7 - EXE_BASE] = 0x34;
	//*(UCHAR*)&pExecutable[0x00709beC - EXE_BASE] = 0x6A;
	InjectNop(0x00709c20, 0x05);
	InjectNop(0x00709c3f, 0x05);
	InjectPushByte(0x00709c1c, 0x34);
	InjectPushByte(0x00709ca6, 0x34);

	// IdAllocBuffer (crashes map screen)
	//InjectPush(0x006433a8, 0x100000);
	//InjectPush(0x0064a828, 0x10000);		// IdTexGameInit

	// Debug
	//Dalloc_flg = (ULONG*)&pExecutable[0x00c65cd4 - EXE_BASE];
	//*Dalloc_flg = 1;
	//Debug_flg = (UCHAR*)&pExecutable[0x00c51d2b - EXE_BASE];
	//*Debug_flg = 1;

	// Aim
	//lr_rate_1504 = (FLOAT*)&pExecutable[0x00bfbecc - EXE_BASE];
	//*lr_rate_1504 = 0.0f;
	//TestAim = (DOUBLE*)&pExecutable[0x00c15ba8 - EXE_BASE];
	//*TestAim = 0.0f;

}

// Initialize
VOID ThisTest02(VOID) {
	
	// 
	//if ((CkBit(StatusFlag, STA_67)) == 0) { FUN_00971530(); }
	//else { FUN_00970a30(); }

	// Fix Count
	int i = 1;
	__asm {mov i, esi}
	OSReport("We're here 2: %d\n", i);
	if (i >= 1024) {
		i = 1;
		__asm {mov esi, i}
		OSReport("Value fixed: %d\n", i);
	}

	OSReport("Test func complete\n");
	__asm {ret}
}
VOID InitBio4PC(UCHAR* pExe) {

	// Allocation Base
	VirtualQuery(&pExe[0], &MemoryBasicInfo, sizeof(MemoryBasicInfo));
	AllocationBase = (ULONG)MemoryBasicInfo.AllocationBase;
	MakePageWritable((ULONG)MemoryBasicInfo.AllocationBase, 0x8B65D0);

	// Initialize
	::pExecutable = pExe;
	Bio4_Functions();
	Bio4OpenConfig();
	Bio4_Variables();

	// Print
	remove("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Resident Evil 4\\Bin32\\OSReport.log");
	remove("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Resident Evil 4\\Bin32\\Warning.log");
	remove("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Resident Evil 4\\Bin32\\Source.log");
	remove("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Resident Evil 4\\Bin32\\Error.log");
	remove("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Resident Evil 4\\Bin32\\sprintf_s.log");
	remove("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Resident Evil 4\\Bin32\\snprintf.log");
	remove("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Resident Evil 4\\Bin32\\_vsprintf_l.log");
	remove("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Resident Evil 4\\Bin32\\_vsprintf_s_l.log");
	if (UseDebugLogging) {
		INJECT(b4_OSReport + AllocationBase, OSReport);
		INJECT(b4_LogWarning + AllocationBase, LogWarning);
		INJECT(b4_Srcprint + AllocationBase, SrcReport);
		INJECT(b4_Errprint + AllocationBase, ErrReport);
		INJECT(b4_sprintf + AllocationBase, Fakesprintf);
		INJECT(b4_snprintf + AllocationBase, Fakesnprintf);
		INJECT(b4_vsprintf + AllocationBase, Fakevsprintf);
		INJECT(b4_vsprintf_s + AllocationBase, Fakevsprintf_s);
	}

	// Debug
	INJECT_NEW((0x00654b05 - EXE_BASE) + AllocationBase, DebugMenu);

	// Screen
	INJECT(systemScreenInit__Fv + AllocationBase, SystemScreenInit);

	// Movie
	if (!Bio4Movie->UseSofdecVideo) {
		INJECT(cSofdec_initSub0 + AllocationBase, PlayMovie);
		INJECT(cSofdec_initSub1 + AllocationBase, PlayMovie);
		INJECT(cSofdec_PlayPause + AllocationBase, nullStub);
		INJECT(cSofdec_MovieStartWait + AllocationBase, MovieStartWait);
		INJECT(cSofdec_finishMovie + AllocationBase, FinishMovie);
	}
	//INJECT_NEW((0x0071adf7 - EXE_BASE) + AllocationBase, ThisTest02);
	//InjectNop(0x0071adfc, 0x18);
	InjectNop(0x0071ae42, 2);

	// SubScreen Test
	InjectNop(0x00787a31, 5);
	InjectNop(0x00787a48, 4);

	// Direct-X
	INJECT(Dx9EnumAdapters + AllocationBase, EnumAdaptersDx9);

	// Post-Processing
	//InjectNop(0x006e9f81, 5);

	// Player Slow
	InjectNop(0x0063e695, 5);
	InjectNop(0x0063e6a0, 10);

}
