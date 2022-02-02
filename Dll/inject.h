#pragma once

#define NAKED	__declspec(naked)

template<typename OUTSTUFF, typename INSTUFF>
OUTSTUFF ForceCast(INSTUFF in)
{
	union
	{
		INSTUFF  in;
		OUTSTUFF out;
	}
	u = { in };

	return u.out;
};

#pragma pack(push, 1)
typedef struct {
	BYTE opCode;	// must be 0xE9;
	DWORD offset;	// jump offset
} JMP;

typedef struct {
	BYTE opCode;	// must be 0x68;
	DWORD offset;	// Value
} PUSH;
typedef struct {
	BYTE opCode;	// must be 0x6A;
	BYTE offset;	// Value
} PUSH_BYTE;

typedef struct
{
	BYTE opCode0;	// must be 0xE8
	DWORD offset0;	// call offset
	BYTE opCode1;	// must be 0xE9
	DWORD offset1;	// reroute offset
} CALLX;

#pragma pack(pop)

#define INJECT_NOP(from) { \
	((PUSH*)(from))->opCode = 0x90; \
}

#define INJECT_PUSH(from,to) { \
	((PUSH*)(from))->opCode = 0x68; \
	((PUSH*)(from))->offset = (DWORD)(to); \
}
#define INJECT_PUSH_BYTE(from,to) { \
	((PUSH_BYTE*)(from))->opCode = 0x6A; \
	((PUSH_BYTE*)(from))->offset = (BYTE)(to); \
}
#define INJECT_MOV_BYTE(from,to) { \
	((PUSH_BYTE*)(from))->opCode = 0x8B; \
	((PUSH_BYTE*)(from))->offset = (BYTE)(to); \
}
#define INJECT_ADD(from,to) { \
	((PUSH*)(from))->opCode = 0x05; \
	((PUSH*)(from))->offset = (DWORD)(to); \
}
#define INJECT_THIS(from,id,to) { \
	((PUSH_BYTE*)(from))->opCode = (BYTE)(id); \
	((PUSH_BYTE*)(from))->offset = (BYTE)(to); \
}

#define INJECT_NEW(from,to) { \
	((JMP*)(from))->opCode = 0xE8; \
	((JMP*)(from))->offset = (DWORD)(to) - ((DWORD)(from) + sizeof(JMP)); \
}


#define INJECT(from,to) { \
	((JMP*)(from))->opCode = 0xE9; \
	((JMP*)(from))->offset = (DWORD)(to) - ((DWORD)(from) + sizeof(JMP)); \
}

#define INJECT_EXT(from,to) (*(DWORD*)(from)) = (DWORD)(to)

#define INJECT_CALL(from,to,size)	{\
	memset(((void*)from), 0x90, size); \
	((JMP*)(from))->opCode = 0xE8; \
	((JMP*)(from))->offset = (DWORD)(to) - ((DWORD)((void*)from) + sizeof(JMP)); \
}

#define INJECT_CALLX(from,fnc,skp)	{\
	((CALLX*)(from))->opCode0 = 0xE8; \
	((CALLX*)(from))->offset0 = (DWORD)(fnc) - ((DWORD)((void*)from) + sizeof(JMP)); \
	((CALLX*)(from))->opCode1 = 0xE9; \
	((CALLX*)(from))->offset1 = (DWORD)(skp) - ((DWORD)((void*)from) + sizeof(CALLX)); \
}\

VOID InjectNop(ULONG Address, ULONG Count);
VOID InjectThis(ULONG Address, UCHAR Id, UCHAR Value);
VOID InjectPushByte(ULONG Address, UCHAR Value);
VOID InjectPush(ULONG Address, ULONG Value);
VOID InjectAdd(ULONG Address, ULONG Value);
