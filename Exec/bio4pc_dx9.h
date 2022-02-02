#pragma once

// Direct-X
extern LPDIRECT3D9* pInterface;	// Don't use this variable, Use GetDx9Interface()
extern LPDIRECT3DDEVICE9 pDevice;
extern LPDIRECT3DSURFACE9* pdx9Surface;
extern LPDIRECT3DSURFACE9* pDestSurface;
extern LPDIRECT3DSURFACE9* pBackBufferSurface;

// Direct-X
HWND GetDx9Window(VOID);
LPDIRECT3D9 GetDx9Interface(VOID);
LPDIRECT3DSURFACE9 GenerateRenderSurface(UINT w, UINT h, bool lockable);
VOID EnumAdaptersDx9(INT Width, INT Height, D3DDISPLAYMODE* DisplayMode);
VOID FUN_0097fa30(LPDIRECT3DTEXTURE9 pTexture, int param_2, int param_3, UINT* param_4);
