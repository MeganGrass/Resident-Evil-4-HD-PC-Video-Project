
#include "..\\dllmain.h"

DOUBLE* InternalResolutionWidth;
DOUBLE* InternalResolutionHeight;
DOUBLE* dAspectR;
FLOAT* AspectRatio;

UINT* ScreenWidth;
UINT* ScreenHeight;

FLOAT* ZNEAR;
FLOAT* ZFAR;
FLOAT* ORTHO_T;
BYTE* system_vcnt;
FLOAT* ORTHO_B;
FLOAT* ORTHO_L;
FLOAT* ORTHO_R;
tagScreen* Screen;
UCHAR* pSys_10;
SHORT* ReSizeWidth;
SHORT* ReSizeHeight;

// Screen
VOID SetAspectRatio(FLOAT NewAspectRatio) { *AspectRatio = NewAspectRatio; }
UINT GetScreenWidth(VOID) { return *ScreenWidth; }
UINT GetScreenHeight(VOID) { return *ScreenHeight; }
VOID SystemScreenInit(VOID) {

	*ZNEAR = Bio4Config.Znear;
	*ZFAR = Bio4Config.Zfar;
	*ORTHO_T = Bio4Config.OrthoT;
	*system_vcnt = Bio4Config.Vcount;
	*ORTHO_B = Bio4Config.OrthoB;
	*ORTHO_L = Bio4Config.OrthoL;
	*ORTHO_R = Bio4Config.OrthoR;
	*&Screen->X = 0.0f;
	*&Screen->Y = 0.0f;
	*&Screen->Width = *(SHORT*)ReSizeWidth;
	*&Screen->Height = *(SHORT*)ReSizeHeight;
	*pSys_10 = 0x40;

	__asm {ret}
}