
#include "..\\dllmain.h"

VOID Bio4_Functions(VOID) {

	// Debug
	mprc.DbMenuExec = (FARPROC)((0x005a8490 - EXE_BASE) + AllocationBase);

	// Direct-X
	mprc.GetDx9Device = (FARPROC)((0x0095a900 - EXE_BASE) + AllocationBase);
	mprc.GetFullScreenFlag = (FARPROC)((0x0093a470 - EXE_BASE) + AllocationBase);
	mprc.ScreenReSize = (FARPROC)((0x00657ad0 - EXE_BASE) + AllocationBase);

	// Graphics
	mprc.GXEndProcessEvent = (FARPROC)((0x00954ff0 - EXE_BASE) + AllocationBase);
	mprc.FUN_00958bb0 = (FARPROC)((0x00958bb0 - EXE_BASE) + AllocationBase);

	// Memory
	mprc.Mem_free = (FARPROC)((0x00655f80 - EXE_BASE) + AllocationBase);
	mprc.memclr_asm = (FARPROC)((0x0095b760 - EXE_BASE) + AllocationBase);

	// DVD
	mprc.DvdReadN = (FARPROC)((0x005acbd0 - EXE_BASE) + AllocationBase);
	mprc.cDvd_ReadCheck = (FARPROC)((0x005ac550 - EXE_BASE) + AllocationBase);

	// Gamepad
	mprc.PadRead = (FARPROC)((0x00967360 - EXE_BASE) + AllocationBase);

	// Task
	mprc.TaskSleep = (FARPROC)((0x006c5460 - EXE_BASE) + AllocationBase);
	mprc.TaskChain = (FARPROC)((0x006c5550 - EXE_BASE) + AllocationBase);
	mprc.TaskExit = (FARPROC)((0x006c55e0 - EXE_BASE) + AllocationBase);
	mprc.TaskKill0 = (FARPROC)((0x006c5650 - EXE_BASE) + AllocationBase);
	mprc.TaskSuspend = (FARPROC)((0x006c56f0 - EXE_BASE) + AllocationBase);
	mprc.TaskSignal = (FARPROC)((0x006c5730 - EXE_BASE) + AllocationBase);
	mprc.TaskStatus = (FARPROC)((0x006c5790 - EXE_BASE) + AllocationBase);
	mprc.iTaskKill = (FARPROC)((0x006c5810 - EXE_BASE) + AllocationBase);
	mprc.iTaskExit = (FARPROC)((0x006c5830 - EXE_BASE) + AllocationBase);
	mprc.iTaskSuspend = (FARPROC)((0x006c58a0 - EXE_BASE) + AllocationBase);
	mprc.TaskSchedulerInit = (FARPROC)((0x006c5900 - EXE_BASE) + AllocationBase);
	mprc.TaskSchedulerMain = (FARPROC)((0x006c5a00 - EXE_BASE) + AllocationBase);
	mprc.TaskExec = (FARPROC)((0x006c5c10 - EXE_BASE) + AllocationBase);
	mprc.TaskKill1 = (FARPROC)((0x006c5ca0 - EXE_BASE) + AllocationBase);
	mprc.iTaskScheduler = (FARPROC)((0x006c5cd0 - EXE_BASE) + AllocationBase);
	mprc.iTaskExec = (FARPROC)((0x006c5d40 - EXE_BASE) + AllocationBase);
	mprc.TaskAllClear = (FARPROC)((0x006c5d80 - EXE_BASE) + AllocationBase);
	mprc.TaskScheduler = (FARPROC)((0x006c5dc0 - EXE_BASE) + AllocationBase);

	// Message
	mprc.MessageControl_setupFont = (FARPROC)((0x00716770 - EXE_BASE) + AllocationBase);
	mprc.MessageControl_Delete = (FARPROC)((0x00716f60 - EXE_BASE) + AllocationBase);
	mprc.MessageControl_setLayout = (FARPROC)((0x00718900 - EXE_BASE) + AllocationBase);

	// System
	mprc.systemVISetBlack = (FARPROC)((0x00656910 - EXE_BASE) + AllocationBase);
	mprc.SetSystemVcnt = (FARPROC)((0x00652190 - EXE_BASE) + AllocationBase);
	mprc.GetSystemVcnt = (FARPROC)((0x006521b0 - EXE_BASE) + AllocationBase);

	// Scenario
	mprc.SceSleep = (FARPROC)((0x006c4e30 - EXE_BASE) + AllocationBase);

	// CRI
	mprc.MWSFCRS_Create = (FARPROC)((0x00a19520 - EXE_BASE) + AllocationBase);
	mprc.ADXM_Lock = (FARPROC)((0x009f0e70 - EXE_BASE) + AllocationBase);
	mprc.ADXM_Unlock = (FARPROC)((0x009f0e90 - EXE_BASE) + AllocationBase);
	mprc.ADXM_WaitVsync = (FARPROC)((0x009ef4b0 - EXE_BASE) + AllocationBase);
	mprc.ADXM_ExecMain = (FARPROC)((0x009f0fa0 - EXE_BASE) + AllocationBase);
	mprc.FUN_006ccd90 = (FARPROC)((0x006ccd90 - EXE_BASE) + AllocationBase);
	mprc.cSofdec_setCamera = (FARPROC)((0x006ccd90 - EXE_BASE) + AllocationBase);

	mprc.FUN_005a6780 = (FARPROC)((0x005a6780 - EXE_BASE) + AllocationBase);
	mprc.FUN_00971530 = (FARPROC)((0x00971530 - EXE_BASE) + AllocationBase);
	mprc.FUN_00970a30 = (FARPROC)((0x00970a30 - EXE_BASE) + AllocationBase);
	mprc.FUN_0071aa90 = (FARPROC)((0x0071aa90 - EXE_BASE) + AllocationBase);
	mprc.FUN_0071a9b0 = (FARPROC)((0x0071a9b0 - EXE_BASE) + AllocationBase);
	mprc.FUN_0071aa20 = (FARPROC)((0x0071aa20 - EXE_BASE) + AllocationBase);
	mprc.FUN_0071ab00 = (FARPROC)((0x0071ab00 - EXE_BASE) + AllocationBase);
	mprc.FUN_0071ab30 = (FARPROC)((0x0071ab30 - EXE_BASE) + AllocationBase);
	mprc.FUN_0071abb0 = (FARPROC)((0x0071abb0 - EXE_BASE) + AllocationBase);
	mprc.EventMgr_DivEvent = (FARPROC)((0x00620770 - EXE_BASE) + AllocationBase);
	mprc.EventMgr_SetFunc = (FARPROC)((0x00622580 - EXE_BASE) + AllocationBase);
	mprc.EventMgr_EvtReadMram = (FARPROC)((0x00627470 - EXE_BASE) + AllocationBase);
}

// 
VOID FUN_005a6780(INT param) { JUMP(FUN_005a6780); }
VOID FUN_00971530(VOID) { JUMP(FUN_00971530); }
VOID FUN_00970a30(VOID) { JUMP(FUN_00970a30); }
VOID FUN_0071aa90(VOID) { JUMP(FUN_0071aa90); }
VOID FUN_0071a9b0(VOID) { JUMP(FUN_0071a9b0); }
VOID FUN_0071aa20(VOID) { JUMP(FUN_0071aa20); }
VOID FUN_0071ab00(VOID) { JUMP(FUN_0071ab00); }
VOID FUN_0071ab30(VOID) { JUMP(FUN_0071ab30); }
VOID FUN_0071abb0(VOID) { JUMP(FUN_0071abb0); }
VOID SceEventStart(CHAR p1) { JUMP(SceEventStart); }
VOID EventMgr_DivEvent(CHAR param) { JUMP(EventMgr_DivEvent); }
VOID EventMgr_SetFunc(INT p1, CHAR* p2, VOID(*Func)()) { JUMP(EventMgr_SetFunc); }
VOID EventMgr_EvtReadMram(INT p1, CHAR* p2, byte p3, CHAR* p4, INT p5, UINT p6) { JUMP(EventMgr_EvtReadMram); }

// stub
VOID nullStub(VOID) { __asm {ret} }

// Debug
NAKED VOID DbMenuExec(VOID) { JUMP(DbMenuExec); }

// Direct-X
NAKED LPDIRECT3DDEVICE9 GetDx9Device(VOID) { JUMP(GetDx9Device); }
NAKED BYTE GetFullScreenFlag(VOID) { JUMP(GetFullScreenFlag); }
NAKED VOID ScreenReSize(USHORT Width, USHORT Height) { JUMP(ScreenReSize); }

// Graphics
NAKED VOID GXEndProcessEvent(VOID) { JUMP(GXEndProcessEvent); }
NAKED VOID FUN_00958bb0(UINT param_1, USHORT param_2) { JUMP(FUN_00958bb0); }

// Memory
NAKED VOID Mem_free(INT param_1) { JUMP(Mem_free); }
NAKED VOID* memclr_asm(VOID* __s, size_t __n) { JUMP(memclr_asm); }

// DVD
NAKED UINT DvdReadN(CHAR* Filename, UINT param_2, UINT param_3, UINT param_4, UINT param_5, USHORT param_6, CHAR* Source, UINT SrcLine) { JUMP(DvdReadN); }
NAKED VOID cDvd_ReadCheck(VOID* cDVD, INT param_1, UINT* param_2, UINT* param_3, UINT* param_4) { JUMP(cDvd_ReadCheck); }

// Gamepad
NAKED VOID PadRead(VOID) { JUMP(PadRead); }

// Task
NAKED VOID TaskSleep(INT Level) { JUMP(TaskSleep); }
NAKED VOID TaskChain(VOID(*Func)(), VOID* Ret) { JUMP(TaskChain); }
NAKED VOID TaskExit(VOID) { JUMP(TaskExit); }
NAKED VOID TaskKill0(INT Level) { JUMP(TaskKill0); }
NAKED VOID TaskSuspend(INT Level) { JUMP(TaskSuspend); }
NAKED VOID TaskSignal(INT Level) { JUMP(TaskSignal); }
NAKED UINT TaskStatus(INT Level) { JUMP(TaskStatus); }
NAKED VOID iTaskKill(VOID) { JUMP(iTaskKill); }
NAKED VOID iTaskExit(VOID) { JUMP(iTaskExit); }
NAKED VOID iTaskSuspend(VOID) { JUMP(iTaskSuspend); }
NAKED VOID TaskSchedulerInit(VOID) { JUMP(TaskSchedulerInit); }
NAKED VOID TaskSchedulerMain(VOID* OSThread) { JUMP(TaskSchedulerMain); }
NAKED ULONG TaskExec(INT Level, VOID(*Func)(), VOID* Ret) { JUMP(TaskExec); }
NAKED VOID TaskKill1(INT Level) { JUMP(TaskKill1); }
NAKED VOID iTaskScheduler(VOID) { JUMP(iTaskScheduler); }
NAKED ULONG iTaskExec(VOID(*Func)()) { JUMP(iTaskExec); }
NAKED VOID TaskAllClear(VOID) { JUMP(TaskAllClear); }
NAKED VOID TaskScheduler(VOID) { JUMP(TaskScheduler); }

// Message
NAKED VOID MessageControl_setupFont(VOID* cMessage, UCHAR param_2, UCHAR param_3, int* param_4, UCHAR param_5) { JUMP(MessageControl_setupFont); }
NAKED VOID MessageControl_Delete(VOID* cMessage, INT param_1) { JUMP(MessageControl_Delete); }
NAKED VOID MessageControl_setLayout(VOID* cMessage, INT param_1, INT param_2) { JUMP(MessageControl_setLayout); }

// System
NAKED VOID systemVISetBlack(INT Flag) { JUMP(systemVISetBlack); }
NAKED VOID SetSystemVcnt(INT Vcnt) { JUMP(SetSystemVcnt); }
NAKED UCHAR GetSystemVcnt(VOID) { JUMP(GetSystemVcnt); }

// Scenario
NAKED VOID SceSleep(INT Level) { JUMP(SceSleep); }

// CRI
NAKED VOID MWSFCRS_Create(VOID) { JUMP(MWSFCRS_Create); }
NAKED VOID ADXM_Lock(VOID) { JUMP(ADXM_Lock); }
NAKED VOID ADXM_Unlock(VOID) { JUMP(ADXM_Unlock); }
NAKED VOID ADXM_WaitVsync(VOID) { JUMP(ADXM_WaitVsync); }
NAKED VOID ADXM_ExecMain(VOID) { JUMP(ADXM_ExecMain); }
NAKED VOID FUN_006ccd90(VOID) { JUMP(FUN_006ccd90); }
NAKED VOID cSofdec_setCamera(VOID) { JUMP(cSofdec_setCamera); }
