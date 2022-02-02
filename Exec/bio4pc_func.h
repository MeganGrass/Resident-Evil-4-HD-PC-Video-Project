#pragma once

VOID Bio4_Functions(VOID);

// Executable
typedef struct tagEngineCall {

	// Debug
	FARPROC DbMenuExec;

	// Direct-X
	FARPROC GetDx9Device;
	FARPROC GetFullScreenFlag;
	FARPROC ScreenReSize;

	// Graphics
	FARPROC GXEndProcessEvent;
	FARPROC FUN_00958bb0;

	// Memory
	FARPROC Mem_free;
	FARPROC memclr_asm;

	// DVD
	FARPROC DvdReadN;
	FARPROC cDvd_ReadCheck;

	// Gamepad
	FARPROC PadRead;

	// Task
	FARPROC TaskExec_hook;
	FARPROC TaskSleep;
	FARPROC TaskChain;
	FARPROC TaskExit;
	FARPROC TaskKill0;
	FARPROC TaskSuspend;
	FARPROC TaskSignal;
	FARPROC TaskStatus;
	FARPROC SetTaskModelPtr;
	FARPROC iTaskKill;
	FARPROC iTaskExit;
	FARPROC iTaskSuspend;
	FARPROC TaskSchedulerInit;
	FARPROC TaskSchedulerMain;
	FARPROC TaskExec;
	FARPROC TaskKill1;
	FARPROC iTaskScheduler;
	FARPROC iTaskExec;
	FARPROC TaskAllClear;
	FARPROC TaskScheduler;

	// Message
	FARPROC MessageControl_setupFont;
	FARPROC MessageControl_Delete;
	FARPROC MessageControl_setLayout;

	// System
	FARPROC systemVISetBlack;
	FARPROC SetSystemVcnt;
	FARPROC GetSystemVcnt;

	// Scenario
	FARPROC SceSleep;

	// CRI
	FARPROC MWSFCRS_Create;
	FARPROC ADXM_Lock;
	FARPROC ADXM_Unlock;
	FARPROC ADXM_WaitVsync;
	FARPROC ADXM_ExecMain;
	FARPROC FUN_006ccd90;
	FARPROC cSofdec_setCamera;

	FARPROC FUN_005a6780;
	FARPROC FUN_00971530;
	FARPROC FUN_00970a30;
	FARPROC FUN_0071aa90;
	FARPROC FUN_0071a9b0;
	FARPROC FUN_0071aa20;
	FARPROC FUN_0071ab00;
	FARPROC FUN_0071ab30;
	FARPROC FUN_0071abb0;
	FARPROC SceEventStart;
	FARPROC EventMgr_DivEvent;
	FARPROC EventMgr_SetFunc;
	FARPROC EventMgr_EvtReadMram;

} ENGINE_CALL;
static ENGINE_CALL mprc;

#define JUMP(x)				__asm { jmp[mprc.(x)]}
#define ASSIGN(_y, x)		mprc._y = (FARPROC)&pExecutable[(x) - EXE_BASE]

// 
VOID FUN_005a6780(INT param);
VOID FUN_00971530(VOID);
VOID FUN_00970a30(VOID);
VOID FUN_0071aa90(VOID);
VOID FUN_0071a9b0(VOID);
VOID FUN_0071aa20(VOID);
VOID FUN_0071ab00(VOID);
VOID FUN_0071ab30(VOID);
VOID FUN_0071abb0(VOID);
VOID SceEventStart(CHAR p1);
VOID EventMgr_DivEvent(CHAR param);
VOID EventMgr_SetFunc(INT p1, CHAR* p2, VOID(*Func)());
VOID EventMgr_EvtReadMram(INT p1, CHAR* p2, byte p3, CHAR* p4, INT p5, UINT p6);

// stub
VOID nullStub(VOID);

// Debug
VOID DbMenuExec(VOID);

// Direct-X
LPDIRECT3DDEVICE9 GetDx9Device(VOID);
BYTE GetFullScreenFlag(VOID);
VOID ScreenReSize(USHORT Width, USHORT Height);

// Graphics
VOID GXEndProcessEvent(VOID);
VOID FUN_00958bb0(UINT param_1, USHORT param_2);

// Memory
VOID Mem_free(INT param_1);
VOID* memclr_asm(VOID* __s, size_t __n);

// DVD
UINT DvdReadN(CHAR* Filename, UINT param_2, UINT param_3, UINT param_4, UINT param_5, USHORT param_6, CHAR* Source, UINT SrcLine);
VOID cDvd_ReadCheck(VOID* cDVD, INT param_1, UINT* param_2, UINT* param_3, UINT* param_4);

// Gamepad
VOID PadRead(VOID);

// Task
VOID TaskSleep(INT Level);
VOID TaskChain(VOID(*Func)(), VOID* Ret);
VOID TaskExit(VOID);
VOID TaskKill0(INT Level);
VOID TaskSuspend(INT Level);
VOID TaskSignal(INT Level);
UINT TaskStatus(INT Level);
VOID iTaskKill(VOID);
VOID iTaskExit(VOID);
VOID iTaskSuspend(VOID);
VOID TaskSchedulerInit(VOID);
VOID TaskSchedulerMain(VOID* OSThread);
ULONG TaskExec(INT Level, VOID(*Func)(), VOID* Ret);
VOID TaskKill1(INT Level);
VOID iTaskScheduler(VOID);
ULONG iTaskExec(VOID(*Func)());
VOID TaskAllClear(VOID);
VOID TaskScheduler(VOID);

// Message
VOID MessageControl_setupFont(VOID* cMessage, UCHAR param_2, UCHAR param_3, int* param_4, UCHAR param_5);
VOID MessageControl_Delete(VOID* cMessage, INT param_1);
VOID MessageControl_setLayout(VOID* cMessage, INT param_1, INT param_2);

// System
VOID systemVISetBlack(INT Flag);
VOID SetSystemVcnt(INT Vcnt);
UCHAR GetSystemVcnt(VOID);

// Scenario
VOID SceSleep(INT Level);

// CRI
VOID MWSFCRS_Create(VOID);
VOID ADXM_Lock(VOID);
VOID ADXM_Unlock(VOID);
VOID ADXM_WaitVsync(VOID);
VOID ADXM_ExecMain(VOID);
VOID FUN_006ccd90(VOID);
VOID cSofdec_setCamera(VOID);
