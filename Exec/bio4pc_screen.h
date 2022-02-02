#pragma once

extern DOUBLE* InternalResolutionWidth;
extern DOUBLE* InternalResolutionHeight;
extern DOUBLE* dAspectR;
extern FLOAT* AspectRatio;

extern UINT* ScreenWidth;
extern UINT* ScreenHeight;

extern FLOAT* ZNEAR;
extern FLOAT* ZFAR;
extern FLOAT* ORTHO_T;
extern BYTE* system_vcnt;
extern FLOAT* ORTHO_B;
extern FLOAT* ORTHO_L;
extern FLOAT* ORTHO_R;
struct tagScreen {
	FLOAT X;
	FLOAT Y;
	FLOAT Width;
	FLOAT Height;
};
extern tagScreen* Screen;
extern UCHAR* pSys_10;
extern SHORT* ReSizeWidth;
extern SHORT* ReSizeHeight;

// Screen
VOID SetAspectRatio(FLOAT NewAspectRatio);
UINT GetScreenWidth(VOID);
UINT GetScreenHeight(VOID);
VOID SystemScreenInit(VOID);
