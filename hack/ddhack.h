#pragma once

class myIDDrawSurface1;

// global variables
#pragma data_seg (".ddraw_shared")
extern HINSTANCE gHinst;
extern HWND      gHwnd;
extern myIDDrawSurface1 * gPrimarySurface;
extern myIDDrawSurface1 * gBackBuffer;
extern int gScreenWidth;
extern int gScreenHeight;
extern int gScreenBits;
extern int gRealScreenWidth;
extern int gRealScreenHeight;
extern int gAltWinPos;
extern int gWc3SmallVid;
extern int gGDI;
extern unsigned char logo[];
#pragma data_seg ()

void logf(char *msg, ...);
void updatescreen();
void init_gl();
void getgdibitmap();

// Exported function
HRESULT WINAPI DirectDrawCreate(GUID FAR *lpGUID, LPDIRECTDRAW FAR *lplpDD, IUnknown FAR *pUnkOuter);
HRESULT WINAPI DirectDrawCreateEx(GUID FAR *lpGuid, LPVOID  *lplpDD, REFIID  iid,IUnknown FAR *pUnkOuter);
HRESULT WINAPI DirectDrawCreateClipper(DWORD dwFlags, LPDIRECTDRAWCLIPPER FAR *lplpDDClipper, IUnknown FAR *pUnkOuter);

HRESULT WINAPI DirectDrawEnumerateW(LPDDENUMCALLBACKW lpCallback, LPVOID lpContext);
HRESULT WINAPI DirectDrawEnumerateA(LPDDENUMCALLBACKA lpCallback, LPVOID lpContext);
HRESULT WINAPI DirectDrawEnumerateExW(LPDDENUMCALLBACKEXW lpCallback, LPVOID lpContext, DWORD dwFlags);
HRESULT WINAPI DirectDrawEnumerateExA(LPDDENUMCALLBACKEXA lpCallback, LPVOID lpContext, DWORD dwFlags);
VOID WINAPI AcquireDDThreadLock(void);
VOID WINAPI ReleaseDDThreadLock(void);
DWORD WINAPI D3DParseUnknownCommand(LPVOID lpCmd, LPVOID *lpRetCmd);
HRESULT WINAPI DllCanUnloadNow(void);
HRESULT WINAPI DllGetClassObject (const CLSID &rclsid, const IID &riid, void **ppv);

// Exported functions still missing
/*
GetSurfaceFromDC
CheckFullscreen
CompleteCreateSysmemSurface
DDGetAttachedSurfaceLcl
DDInternalLock
DDInternalUnlock
DSoundHelp
GetDDSurfaceLocal
GetOLEThunkData
RegisterSpecialCase
*/

// regular functions
void InitInstance(HANDLE hModule);
void ExitInstance(void);
