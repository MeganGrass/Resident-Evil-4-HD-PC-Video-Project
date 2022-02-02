
#include "..\\dllmain.h"

// Direct-X
LPDIRECT3D9* pInterface;	// Use GetDx9Interface()
LPDIRECT3DDEVICE9 pDevice;
LPDIRECT3DSURFACE9* pdx9Surface;
LPDIRECT3DSURFACE9* pDestSurface;
LPDIRECT3DSURFACE9* pBackBufferSurface;

// Direct-X
HWND GetDx9Window(VOID) {
	pDevice = GetDx9Device();
	D3DDEVICE_CREATION_PARAMETERS Parameters;
	pDevice->GetCreationParameters(&Parameters);
	if (!IsWindow(Parameters.hFocusWindow)) { return GetBio4Window(); }
	return Parameters.hFocusWindow;
}
LPDIRECT3D9 GetDx9Interface(VOID) { return *pInterface; }
LPDIRECT3DSURFACE9 GenerateRenderSurface(UINT w, UINT h, bool lockable) {
	pDevice = GetDx9Device();
	LPDIRECT3DSURFACE9 pSurf = nullptr;
	pDevice->CreateRenderTarget(w, h, D3DFMT_A8B8G8R8, D3DMULTISAMPLE_NONE, 0, lockable, &pSurf, nullptr);
	return pSurf;
	//return *pDestSurface;
}
VOID EnumAdaptersDx9(INT Width, INT Height, D3DDISPLAYMODE* DisplayMode) {

	DisplayMode->Width = GetScreenWidth();
	DisplayMode->Height = GetScreenHeight();
	DisplayMode->RefreshRate = Bio4Config.RefreshRate;
	DisplayMode->Format = D3DFMT_X8R8G8B8;

}
VOID FUN_0097fa30(LPDIRECT3DTEXTURE9 pTexture, int param_2, int param_3, UINT* param_4) {

	D3DLOCKED_RECT Rect;
	pTexture->LockRect(0, &Rect, (RECT*)0x0, 0);
	if (param_3 != 0) {
		do {
			memcpy((UINT*)Rect.pBits, param_4, Rect.Pitch);
			param_4 = (UINT*)((int)param_4 + param_2);
			Rect.pBits = (void*)((int)Rect.pBits + Rect.Pitch);
			param_3 = param_3 + -1;
		} while (param_3 != 0);
	}
	pTexture->UnlockRect(0);

}