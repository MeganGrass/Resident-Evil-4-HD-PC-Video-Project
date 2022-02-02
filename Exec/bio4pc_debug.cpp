
#include "..\\dllmain.h"

ULONG* Dalloc_flg;
UCHAR* Debug_flg;

// Debug Menu
VOID DebugMenu(VOID) {

	SetBit(ConfigFlag, CFG_LOCK_ON, ON);
	SetBit(DebugFlag, DBG_PL_LOCK_FOLLOW, ON);

	SetBit(SystemFlag, SYS_DTV480P, ON);

	SetBit(StatusFlag, STA_LOWPOLY_USE, OFF);
	//DbMenuExec();
	__asm {ret}
}
ULONG out_data_size = NULL;
ULONG in_data_addr = NULL;
struct yz2_struct {
    ULONG in_data_addr;
    ULONG field_0x4;
    ULONG field_0x8;
    ULONG in_data_size;
    ULONG out_data_size;
};
yz2_struct in_ev;
ULONG Yz2DecodeSet(char* param_1, ULONG param_2) {
    char* local_20[3];

    local_20[0] = param_1;
    in_ev.in_data_size = strtoul(param_1, local_20, 0x10);
    local_20[0] = local_20[0] + 1;
    in_ev.out_data_size = strtoul(local_20[0], local_20, 0x10);
    in_ev.in_data_addr = (UINT)(local_20[0] + 0x20) & 0xffffffe0;
    in_ev.field_0x4 = param_2;
    in_ev.field_0x8 = param_2;
    return in_ev.out_data_size;
}