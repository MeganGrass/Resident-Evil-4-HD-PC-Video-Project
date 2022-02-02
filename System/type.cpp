
#include "system.h"

// Bits and Bytes
uintmax_t System_Type::GetBit(uintmax_t iBit, uintmax_t Value) {
	uintmax_t Mask = 1;
	return (Value & (Mask << iBit)) >> iBit;
}
uintmax_t System_Type::SetBit(uintmax_t iBit, BOOL OnOff, uintmax_t& Value) {
	uintmax_t Mask = 1;
	if (OnOff) { Value |= Mask << iBit; }
	else { Value &= ~(Mask << iBit); }
	return Value;
}
BOOL * System_Type::GetBitArray(UCHAR Value) {
	BOOL * Bits = new BOOL[8];
	for (UCHAR i = 0; i < 8; i++) { Bits[i] = GetBit(i, Value); }
	return Bits;
}
uintmax_t System_Type::GetByte(uintmax_t iByte, uintmax_t Value) {

	uintmax_t Byte = NULL;
	switch (iByte)
	{
	case 0:
		Byte = ((Value << 24) >> 24);
	break;
	case 1:
		Byte = ((Value << 16) >> 24);
	break;
	case 2:
		Byte = ((Value & 0x0000FF00) >> 8);
	break;
	case 3:
		Byte = ((Value & 0x000000FF));
	break;
	}

	// Terminate
	return static_cast<uintmax_t>(Value);
}

// x86/x64
uintmax_t System_Type::GetValue(uintmax_t Value) {
	return static_cast<uintmax_t>(Value);
}
uintmax_t System_Type::GetValueFromStr(BOOL HexaDecimal, CONST CHAR * Value) {

	if (HexaDecimal) {
		ULONG Output = NULL;
		sscanf_s(Value, "%X", &Output);
		return static_cast<uintmax_t>(Output);
	} else {
		if (sizeof(uintmax_t) != sizeof(ULLONG)) {
			return static_cast<uintmax_t>(atoi(Value));
		} else {
			return static_cast<uintmax_t>(_atoi64(Value));
		}
	}

}
uintmax_t System_Type::GetValueFromStr(BOOL HexaDecimal, CONST WCHAR * Value) {

	if (HexaDecimal) {
		ULONG Output = NULL;
		swscanf_s(Value, L"%X", &Output);
		return static_cast<uintmax_t>(Output);
	} else {
		ULONG Output = NULL;
		swscanf_s(Value, L"%d", &Output);
		return static_cast<uintmax_t>(Output);
	}

}
uintmax_t System_Type::GetValueFromBits(uintmax_t Value, uintmax_t nBits, uintmax_t iBit) {
	return (((1 << nBits) - 1) & (Value >> (iBit - 1)));
}
uintmax_t System_Type::GetValueFromBytes(UCHAR n0, UCHAR n1, UCHAR n2, UCHAR n3, UCHAR n4, UCHAR n5, UCHAR n6, UCHAR n7) {
	if (sizeof(uintmax_t) != sizeof(ULLONG)) {
		return static_cast<uintmax_t>(GetValue(n0 | (n1 << 8) | (n2 << 16) | (n3 << 24)));
	} else {
		uintmax_t v0 = GetValue(n0 | (n1 << 8) | (n2 << 16) | (n3 << 24));
		uintmax_t v1 = GetValue(n4 | (n5 << 8) | (n6 << 16) | (n7 << 24));
		return static_cast<uintmax_t>(GetValue(v0 | (v1 << 24)));
	}
}
uintmax_t System_Type::SwapEndianness(uintmax_t Value) {
	if (sizeof(uintmax_t) != sizeof(ULLONG)) {
		uintmax_t n0 = GetValue((Value & 0xFF000000) >> 24);
		uintmax_t n1 = GetValue((Value & 0x00FF0000) >> 16);
		uintmax_t n2 = GetValue((Value & 0x0000FF00) >> 8);
		uintmax_t n3 = GetValue((Value & 0x000000FF));
		uintmax_t Output = n0 | (n1 << 8) | (n2 << 16) | (n3 << 24);
		return static_cast<uintmax_t>(Output);
	} else {
		uintmax_t n0 = GetValue((Value & 0xFF00000000000000) >> 56);
		uintmax_t n1 = GetValue((Value & 0x00FF000000000000) >> 48);
		uintmax_t n2 = GetValue((Value & 0x0000FF0000000000) >> 40);
		uintmax_t n3 = GetValue((Value & 0x000000FF00000000) >> 32);
		uintmax_t n4 = GetValue((Value & 0x00000000FF000000) >> 24);
		uintmax_t n5 = GetValue((Value & 0x0000000000FF0000) >> 16);
		uintmax_t n6 = GetValue((Value & 0x000000000000FF00) >> 8);
		uintmax_t n7 = GetValue((Value & 0x00000000000000FF));
		uintmax_t Output = n0 | (n1 << 8) | (n2 << 16) | (n3 << 24) | (n4 << 32) | (n5 << 40) | (n6 << 48) | (n7 << 56);
		return static_cast<uintmax_t>(Output);
	}
}

// precision-point
FLOAT System_Type::GetFloat(uintmax_t Value) {
	return static_cast<FLOAT>(Value);
}
DOUBLE System_Type::GetFloatFromStr(CONST CHAR* Value) {
	return static_cast<DOUBLE>(atof(Value));
}
DOUBLE System_Type::GetFloatFromStr(CONST WCHAR* Value) {
	return static_cast<DOUBLE>(_wtof(Value));
}
DOUBLE System_Type::GetDouble(uintmax_t Value) {
	return static_cast<DOUBLE>(Value);
}
DOUBLE System_Type::GetDouble(FLOAT Value) {
	return static_cast<DOUBLE>(Value);
}