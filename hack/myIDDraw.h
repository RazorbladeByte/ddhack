#pragma once

class myIDDrawPalette;

class myIDDraw1 : public IDirectDraw
{
public:
    myIDDraw1();
    virtual ~myIDDraw1(void);

	// The original DDraw function definitions BEGIN
    HRESULT __stdcall QueryInterface (REFIID a, LPVOID FAR * b);
    ULONG   __stdcall AddRef(void);
    ULONG   __stdcall Release(void);
    
    HRESULT  __stdcall Compact(void);
    HRESULT  __stdcall CreateClipper(DWORD a, LPDIRECTDRAWCLIPPER FAR* b, IUnknown FAR* c);
	HRESULT  __stdcall CreatePalette(DWORD a, LPPALETTEENTRY b, LPDIRECTDRAWPALETTE FAR* c, IUnknown FAR* d);
	HRESULT  __stdcall CreateSurface(LPDDSURFACEDESC a, LPDIRECTDRAWSURFACE FAR* b, IUnknown FAR* c);
	HRESULT  __stdcall DuplicateSurface(LPDIRECTDRAWSURFACE a, LPDIRECTDRAWSURFACE FAR* b);
	HRESULT  __stdcall EnumDisplayModes(DWORD a, LPDDSURFACEDESC b, LPVOID c, LPDDENUMMODESCALLBACK d);
	HRESULT  __stdcall EnumSurfaces(DWORD a, LPDDSURFACEDESC b, LPVOID c, LPDDENUMSURFACESCALLBACK d);
	HRESULT  __stdcall FlipToGDISurface(void);
	HRESULT  __stdcall GetCaps(LPDDCAPS a, LPDDCAPS b);
    HRESULT  __stdcall GetDisplayMode(LPDDSURFACEDESC a);
    HRESULT  __stdcall GetFourCCCodes(LPDWORD a, LPDWORD b);
    HRESULT  __stdcall GetGDISurface(LPDIRECTDRAWSURFACE FAR * a);
    HRESULT  __stdcall GetMonitorFrequency(LPDWORD a);
    HRESULT  __stdcall GetScanLine(LPDWORD a);
    HRESULT  __stdcall GetVerticalBlankStatus(LPBOOL a);
    HRESULT  __stdcall Initialize(GUID FAR* a);
    HRESULT  __stdcall RestoreDisplayMode(void);
	HRESULT  __stdcall SetCooperativeLevel(HWND a, DWORD b);
	HRESULT  __stdcall SetDisplayMode(DWORD a, DWORD b, DWORD c);
	HRESULT  __stdcall WaitForVerticalBlank(DWORD a, HANDLE b);

};


class myIDDraw2 : public IDirectDraw2
{
public:
    myIDDraw2();
    virtual ~myIDDraw2(void);

	// The original DDraw function definitions BEGIN
    HRESULT __stdcall QueryInterface (REFIID a, LPVOID FAR * b);
    ULONG   __stdcall AddRef(void);
    ULONG   __stdcall Release(void);
    
    HRESULT  __stdcall Compact(void);
    HRESULT  __stdcall CreateClipper(DWORD a, LPDIRECTDRAWCLIPPER FAR* b, IUnknown FAR* c);
	HRESULT  __stdcall CreatePalette(DWORD a, LPPALETTEENTRY b, LPDIRECTDRAWPALETTE FAR* c, IUnknown FAR* d);
	HRESULT  __stdcall CreateSurface(LPDDSURFACEDESC a, LPDIRECTDRAWSURFACE FAR* b, IUnknown FAR* c);
	HRESULT  __stdcall DuplicateSurface(LPDIRECTDRAWSURFACE a, LPDIRECTDRAWSURFACE FAR* b);
	HRESULT  __stdcall EnumDisplayModes(DWORD a, LPDDSURFACEDESC b, LPVOID c, LPDDENUMMODESCALLBACK d);
	HRESULT  __stdcall EnumSurfaces(DWORD a, LPDDSURFACEDESC b, LPVOID c, LPDDENUMSURFACESCALLBACK d);
	HRESULT  __stdcall FlipToGDISurface(void);
	HRESULT  __stdcall GetCaps(LPDDCAPS a, LPDDCAPS b);
    HRESULT  __stdcall GetDisplayMode(LPDDSURFACEDESC a);
    HRESULT  __stdcall GetFourCCCodes(LPDWORD a, LPDWORD b);
    HRESULT  __stdcall GetGDISurface(LPDIRECTDRAWSURFACE FAR * a);
    HRESULT  __stdcall GetMonitorFrequency(LPDWORD a);
    HRESULT  __stdcall GetScanLine(LPDWORD a);
    HRESULT  __stdcall GetVerticalBlankStatus(LPBOOL a);
    HRESULT  __stdcall Initialize(GUID FAR* a);
    HRESULT  __stdcall RestoreDisplayMode(void);
	HRESULT  __stdcall SetCooperativeLevel(HWND a, DWORD b);
	HRESULT  __stdcall SetDisplayMode(DWORD a, DWORD b, DWORD c, DWORD d, DWORD e);
	HRESULT  __stdcall WaitForVerticalBlank(DWORD a, HANDLE b);

	/*** Added in the v2 interface ***/
    HRESULT  __stdcall GetAvailableVidMem(LPDDSCAPS a, LPDWORD b, LPDWORD c);

};

class myIDDrawSurface1 : public IDirectDrawSurface
{
public:
	myIDDrawSurface1(LPDDSURFACEDESC a);
    virtual ~myIDDrawSurface1(void);

	// The original DDraw function definitions BEGIN
    HRESULT __stdcall QueryInterface (REFIID a, LPVOID FAR * b);
    ULONG   __stdcall AddRef(void);
    ULONG   __stdcall Release(void);

	/*** IDirectDrawSurface methods ***/
    HRESULT  __stdcall AddAttachedSurface(LPDIRECTDRAWSURFACE);
    HRESULT  __stdcall AddOverlayDirtyRect(LPRECT);
    HRESULT  __stdcall Blt(LPRECT,LPDIRECTDRAWSURFACE, LPRECT,DWORD, LPDDBLTFX);
    HRESULT  __stdcall BltBatch(LPDDBLTBATCH, DWORD, DWORD );
    HRESULT  __stdcall BltFast(DWORD,DWORD,LPDIRECTDRAWSURFACE, LPRECT,DWORD);
    HRESULT  __stdcall DeleteAttachedSurface(DWORD,LPDIRECTDRAWSURFACE);
    HRESULT  __stdcall EnumAttachedSurfaces(LPVOID,LPDDENUMSURFACESCALLBACK);
    HRESULT  __stdcall EnumOverlayZOrders(DWORD,LPVOID,LPDDENUMSURFACESCALLBACK);
    HRESULT  __stdcall Flip(LPDIRECTDRAWSURFACE, DWORD);
    HRESULT  __stdcall GetAttachedSurface(LPDDSCAPS, LPDIRECTDRAWSURFACE FAR *);
    HRESULT  __stdcall GetBltStatus(DWORD);
    HRESULT  __stdcall GetCaps(LPDDSCAPS);
    HRESULT  __stdcall GetClipper(LPDIRECTDRAWCLIPPER FAR*);
    HRESULT  __stdcall GetColorKey(DWORD, LPDDCOLORKEY);
    HRESULT  __stdcall GetDC(HDC FAR *);
    HRESULT  __stdcall GetFlipStatus(DWORD);
    HRESULT  __stdcall GetOverlayPosition(LPLONG, LPLONG );
    HRESULT  __stdcall GetPalette(LPDIRECTDRAWPALETTE FAR*);
    HRESULT  __stdcall GetPixelFormat(LPDDPIXELFORMAT);
    HRESULT  __stdcall GetSurfaceDesc(LPDDSURFACEDESC);
    HRESULT  __stdcall Initialize(LPDIRECTDRAW, LPDDSURFACEDESC);
    HRESULT  __stdcall IsLost();
    HRESULT  __stdcall Lock(LPRECT,LPDDSURFACEDESC,DWORD,HANDLE);
    HRESULT  __stdcall ReleaseDC(HDC);
    HRESULT  __stdcall Restore();
    HRESULT  __stdcall SetClipper(LPDIRECTDRAWCLIPPER);
    HRESULT  __stdcall SetColorKey(DWORD, LPDDCOLORKEY);
    HRESULT  __stdcall SetOverlayPosition(LONG, LONG );
    HRESULT  __stdcall SetPalette(LPDIRECTDRAWPALETTE);
    HRESULT  __stdcall Unlock(LPVOID);
    HRESULT  __stdcall UpdateOverlay(LPRECT, LPDIRECTDRAWSURFACE,LPRECT,DWORD, LPDDOVERLAYFX);
    HRESULT  __stdcall UpdateOverlayDisplay(DWORD);
    HRESULT  __stdcall UpdateOverlayZOrder(DWORD, LPDIRECTDRAWSURFACE);

	DDSURFACEDESC mSurfaceDesc;
	myIDDrawPalette *mCurrentPalette;
	unsigned char * mSurfaceData;
	unsigned char * mRealSurfaceData;
	int mWidth;
	int mHeight;
	int mPitch;
};

class myIDDrawPalette : public IDirectDrawPalette
{
public:
    myIDDrawPalette(DWORD a, LPPALETTEENTRY b);
    virtual ~myIDDrawPalette(void);

	// The original DDraw function definitions BEGIN
    HRESULT __stdcall QueryInterface (REFIID a, LPVOID FAR * b);
    ULONG   __stdcall AddRef(void);
    ULONG   __stdcall Release(void);
    
    /*** IDirectDrawPalette methods ***/
    HRESULT  __stdcall GetCaps(LPDWORD);
    HRESULT  __stdcall GetEntries(DWORD,DWORD,DWORD,LPPALETTEENTRY);
    HRESULT  __stdcall Initialize(LPDIRECTDRAW, DWORD, LPPALETTEENTRY);
    HRESULT  __stdcall SetEntries(DWORD,DWORD,DWORD,LPPALETTEENTRY);

	PALETTEENTRY mPal[256];
};
