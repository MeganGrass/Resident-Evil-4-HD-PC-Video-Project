
#include "..\\dllmain.h"

// Inject
VOID InjectNop(ULONG Address, ULONG Count) {

	UCHAR* Pointer = nullptr;
	for (ULONG n = NULL; n < Count; n++)
	{
		Pointer = (UCHAR*)&pExecutable[Address - EXE_BASE];
		*Pointer = 0x90;
		Address++;
	}
}
VOID InjectThis(ULONG Address, UCHAR Id, UCHAR Value) { INJECT_THIS((Address - EXE_BASE) + AllocationBase, Id, Value); }
VOID InjectPushByte(ULONG Address, UCHAR Value) { INJECT_PUSH_BYTE((Address - EXE_BASE) + AllocationBase, Value); }
VOID InjectPush(ULONG Address, ULONG Value) { INJECT_PUSH((Address - EXE_BASE) + AllocationBase, Value); }
VOID InjectAdd(ULONG Address, ULONG Value) { INJECT_ADD((Address - EXE_BASE) + AllocationBase, Value); }
