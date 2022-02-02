#pragma once

VOID InitBio4PC(UCHAR* pExe);

extern UCHAR* pExecutable;
extern MEMORY_BASIC_INFORMATION MemoryBasicInfo;
extern IMAGE_DOS_HEADER* MzHeader;
extern ULONG AllocationBase;

#define EXE_BASE				0x00400000

// Global
extern UCHAR* pSys;
extern ULONG* pG;

// Screen
#define systemScreenInit__Fv	(0x00652c70 - EXE_BASE)

// Print
#define b4_OSReport				(0x00974020 - EXE_BASE)
#define b4_LogWarning			(0x004ab460 - EXE_BASE)
#define b4_eprint				(0x005e5d60 - EXE_BASE)	// unimplemented
#define b4_Srcprint				(0x00974030 - EXE_BASE)
#define b4_Errprint				(0x00974040 - EXE_BASE)
#define b4_Msgprint				(0x004254f0 - EXE_BASE)	// Message Print?
#define b4_sprintf				(0x00a6e37b - EXE_BASE)
#define b4_snprintf				(0x00a70433 - EXE_BASE)
#define b4_vsprintf				(0x00a6f4a8 - EXE_BASE)
#define b4_vsprintf_s			(0x00a6fbe1 - EXE_BASE)

// Debug Menu
#define DbMenuExec__Fv			(0x005a8490 - EXE_BASE)

// Direct-X
#define Dx9EnumAdapters			(0x009391e0 - EXE_BASE)

// Movie
#define cSofdec_initSub0		(0x006ce630 - EXE_BASE)
#define cSofdec_initSub1		(0x006ce790 - EXE_BASE)
#define cSofdec_PlayPause		(0x006cd5e0 - EXE_BASE)
#define cSofdec_MovieStartWait	(0x006c0af0 - EXE_BASE)
#define cSofdec_finishMovie		(0x006cd6a0 - EXE_BASE)
#define EventMgr_IsAliveEvt		(0x006220c0 - EXE_BASE)

#define MovBrowseWait00			(0x00628b56 - EXE_BASE)
#define MovBrowseWait01			(0x00628b70 - EXE_BASE)
#define MovBrowseTest			(0x0071ad5d - EXE_BASE)
#define Test2					(0x0071adf7 - EXE_BASE)

#define EventPlayer				(0x0071ac40 - EXE_BASE)

// Player
#define _SetPlDamage			(0x00681130 - EXE_BASE)
#define _EndPlDamage			(0x006811a0 - EXE_BASE)
#define _PlSetDamage			(0x005b6050 - EXE_BASE)
#define _dmgCheck				(0x0067eef0 - EXE_BASE)
#define _setDamage				(0x0067ecc0 - EXE_BASE)
#define _damageNormal			(0x007516d0 - EXE_BASE)
#define _damageBlow				(0x00751ec0 - EXE_BASE)
#define _damageBlast			(0x00752550 - EXE_BASE)
#define _LifeDownSet			(0x005bc3e0 - EXE_BASE)
#define _LifeDownSet2			(0x005b5af0 - EXE_BASE)
