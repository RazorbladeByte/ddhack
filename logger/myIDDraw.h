#pragma once

class myIDDrawInterface
{
public:
	virtual LPDIRECTDRAW getAsDirectDraw() = 0;
};

class myIDDraw1 : public IDirectDraw, public myIDDrawInterface
{
public:
    myIDDraw1(LPDIRECTDRAW pOriginal);
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

	virtual LPDIRECTDRAW getAsDirectDraw()
	{
		return m_pIDDraw;
	}

   	LPDIRECTDRAW FAR m_pIDDraw;
};


class myIDDraw2 : public IDirectDraw2, public myIDDrawInterface
{
public:
    myIDDraw2(LPDIRECTDRAW2 pOriginal);
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

	virtual LPDIRECTDRAW getAsDirectDraw()
	{
		return (LPDIRECTDRAW)m_pIDDraw;
	}

   	LPDIRECTDRAW2 FAR m_pIDDraw;
};

class myIDDraw4 : public IDirectDraw4, public myIDDrawInterface
{
public:
	myIDDraw4(LPDIRECTDRAW4 pOriginal);
	virtual ~myIDDraw4(void);

	// The original DDraw function definitions BEGIN
	HRESULT __stdcall QueryInterface (REFIID a, LPVOID FAR * b);
	ULONG   __stdcall AddRef(void);
	ULONG   __stdcall Release(void);

	HRESULT  __stdcall Compact(void);
	HRESULT  __stdcall CreateClipper(DWORD a, LPDIRECTDRAWCLIPPER FAR* b, IUnknown FAR * c);
	HRESULT  __stdcall CreatePalette(DWORD a, LPPALETTEENTRY b, LPDIRECTDRAWPALETTE FAR* c, IUnknown FAR * d);
	HRESULT  __stdcall CreateSurface(LPDDSURFACEDESC2 a, LPDIRECTDRAWSURFACE4 FAR * b, IUnknown FAR * c);
	HRESULT  __stdcall DuplicateSurface(LPDIRECTDRAWSURFACE4 a, LPDIRECTDRAWSURFACE4 FAR * b);
	HRESULT  __stdcall EnumDisplayModes(DWORD a, LPDDSURFACEDESC2 b, LPVOID c, LPDDENUMMODESCALLBACK2 d);
	HRESULT  __stdcall EnumSurfaces(DWORD a, LPDDSURFACEDESC2 b, LPVOID c,LPDDENUMSURFACESCALLBACK2 d);
	HRESULT  __stdcall FlipToGDISurface(void);
	HRESULT  __stdcall GetCaps(LPDDCAPS a, LPDDCAPS b);
	HRESULT  __stdcall GetDisplayMode(LPDDSURFACEDESC2 a);
	HRESULT  __stdcall GetFourCCCodes(LPDWORD a, LPDWORD b);
	HRESULT  __stdcall GetGDISurface(LPDIRECTDRAWSURFACE4 FAR * a);
	HRESULT  __stdcall GetMonitorFrequency(LPDWORD a);
	HRESULT  __stdcall GetScanLine(LPDWORD a);
	HRESULT  __stdcall GetVerticalBlankStatus(LPBOOL a);
	HRESULT  __stdcall Initialize(GUID FAR * a);
	HRESULT  __stdcall RestoreDisplayMode(void);
	HRESULT  __stdcall SetCooperativeLevel(HWND a, DWORD b);
	HRESULT  __stdcall SetDisplayMode(DWORD a, DWORD b,DWORD c, DWORD d, DWORD e);
	HRESULT  __stdcall WaitForVerticalBlank(DWORD a, HANDLE b);
	/*** Added in the v2 interface ***/
	HRESULT  __stdcall GetAvailableVidMem(LPDDSCAPS2 a, LPDWORD b, LPDWORD c);
	/*** Added in the V4 Interface ***/
	HRESULT  __stdcall GetSurfaceFromDC(HDC a, LPDIRECTDRAWSURFACE4 * b);
	HRESULT  __stdcall RestoreAllSurfaces(void);
	HRESULT  __stdcall TestCooperativeLevel(void);
	HRESULT  __stdcall GetDeviceIdentifier(LPDDDEVICEIDENTIFIER a, DWORD b);
	HRESULT  __stdcall StartModeTest(LPSIZE a, DWORD b, DWORD c);
	HRESULT  __stdcall EvaluateMode(DWORD a, DWORD * b);

	virtual LPDIRECTDRAW getAsDirectDraw()
	{
		return (LPDIRECTDRAW)m_pIDDraw;
	}

	LPDIRECTDRAW4 FAR m_pIDDraw;
};

class myIDDraw7 : public IDirectDraw7, public myIDDrawInterface
{
public:
	myIDDraw7(LPDIRECTDRAW7 pOriginal);
	virtual ~myIDDraw7(void);

	// The original DDraw function definitions BEGIN
	HRESULT __stdcall QueryInterface (REFIID a, LPVOID FAR * b);
	ULONG   __stdcall AddRef(void);
	ULONG   __stdcall Release(void);

	HRESULT  __stdcall Compact(void);
	HRESULT  __stdcall CreateClipper(DWORD a, LPDIRECTDRAWCLIPPER FAR* b, IUnknown FAR * c);
	HRESULT  __stdcall CreatePalette(DWORD a, LPPALETTEENTRY b, LPDIRECTDRAWPALETTE FAR* c, IUnknown FAR * d);
	HRESULT  __stdcall CreateSurface(LPDDSURFACEDESC2 a, LPDIRECTDRAWSURFACE7 FAR * b, IUnknown FAR * c);
	HRESULT  __stdcall DuplicateSurface(LPDIRECTDRAWSURFACE7 a, LPDIRECTDRAWSURFACE7 FAR * b);
	HRESULT  __stdcall EnumDisplayModes(DWORD a, LPDDSURFACEDESC2 b, LPVOID c, LPDDENUMMODESCALLBACK2 d);
	HRESULT  __stdcall EnumSurfaces(DWORD a, LPDDSURFACEDESC2 b, LPVOID c,LPDDENUMSURFACESCALLBACK7 d);
	HRESULT  __stdcall FlipToGDISurface(void);
	HRESULT  __stdcall GetCaps(LPDDCAPS a, LPDDCAPS b);
	HRESULT  __stdcall GetDisplayMode(LPDDSURFACEDESC2 a);
	HRESULT  __stdcall GetFourCCCodes(LPDWORD a, LPDWORD b);
	HRESULT  __stdcall GetGDISurface(LPDIRECTDRAWSURFACE7 FAR * a);
	HRESULT  __stdcall GetMonitorFrequency(LPDWORD a);
	HRESULT  __stdcall GetScanLine(LPDWORD a);
	HRESULT  __stdcall GetVerticalBlankStatus(LPBOOL a);
	HRESULT  __stdcall Initialize(GUID FAR * a);
	HRESULT  __stdcall RestoreDisplayMode(void);
	HRESULT  __stdcall SetCooperativeLevel(HWND a, DWORD b);
	HRESULT  __stdcall SetDisplayMode(DWORD a, DWORD b,DWORD c, DWORD d, DWORD e);
	HRESULT  __stdcall WaitForVerticalBlank(DWORD a, HANDLE b);
	/*** Added in the v2 interface ***/
	HRESULT  __stdcall GetAvailableVidMem(LPDDSCAPS2 a, LPDWORD b, LPDWORD c);
	/*** Added in the V4 Interface ***/
	HRESULT  __stdcall GetSurfaceFromDC(HDC a, LPDIRECTDRAWSURFACE7 * b);
	HRESULT  __stdcall RestoreAllSurfaces(void);
	HRESULT  __stdcall TestCooperativeLevel(void);
	HRESULT  __stdcall GetDeviceIdentifier(LPDDDEVICEIDENTIFIER2 a, DWORD b);
	HRESULT  __stdcall StartModeTest(LPSIZE a, DWORD b, DWORD c);
	HRESULT  __stdcall EvaluateMode(DWORD a, DWORD * b);

	virtual LPDIRECTDRAW getAsDirectDraw()
	{
		return (LPDIRECTDRAW)m_pIDDraw;
	}

	LPDIRECTDRAW7 FAR m_pIDDraw;
};

class myIDDrawPalette : public IDirectDrawPalette
{
public:
	myIDDrawPalette(LPDIRECTDRAWPALETTE pOriginal);
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


	LPDIRECTDRAWPALETTE FAR m_pIDDrawPalette;
};

class myIDDrawSurface1 : public IDirectDrawSurface
{
public:
	myIDDrawSurface1(LPDIRECTDRAWSURFACE pOriginal);
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


   	LPDIRECTDRAWSURFACE FAR m_pIDDrawSurface;
};


class myIDDrawSurface2 : public IDirectDrawSurface2
{
public:
	myIDDrawSurface2(LPDIRECTDRAWSURFACE2 pOriginal);
	virtual ~myIDDrawSurface2(void);
	// The original DDraw function definitions BEGIN
	HRESULT __stdcall QueryInterface (REFIID a, LPVOID FAR * b);
	ULONG   __stdcall AddRef(void);
	ULONG   __stdcall Release(void);
	/*** IDirectDrawSurface methods ***/
	HRESULT  __stdcall AddAttachedSurface(LPDIRECTDRAWSURFACE2);
	HRESULT  __stdcall AddOverlayDirtyRect(LPRECT);
	HRESULT  __stdcall Blt(LPRECT,LPDIRECTDRAWSURFACE2, LPRECT,DWORD, LPDDBLTFX);
	HRESULT  __stdcall BltBatch(LPDDBLTBATCH, DWORD, DWORD );
	HRESULT  __stdcall BltFast(DWORD,DWORD,LPDIRECTDRAWSURFACE2, LPRECT,DWORD);
	HRESULT  __stdcall DeleteAttachedSurface(DWORD,LPDIRECTDRAWSURFACE2);
	HRESULT  __stdcall EnumAttachedSurfaces(LPVOID,LPDDENUMSURFACESCALLBACK);
	HRESULT  __stdcall EnumOverlayZOrders(DWORD,LPVOID,LPDDENUMSURFACESCALLBACK);
	HRESULT  __stdcall Flip(LPDIRECTDRAWSURFACE2, DWORD);
	HRESULT  __stdcall GetAttachedSurface(LPDDSCAPS, LPDIRECTDRAWSURFACE2 FAR *);
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
	HRESULT  __stdcall UpdateOverlay(LPRECT, LPDIRECTDRAWSURFACE2,LPRECT,DWORD, LPDDOVERLAYFX);
	HRESULT  __stdcall UpdateOverlayDisplay(DWORD);
	HRESULT  __stdcall UpdateOverlayZOrder(DWORD, LPDIRECTDRAWSURFACE2);

	/*** Added in the v2 interface ***/
	HRESULT  __stdcall GetDDInterface(LPVOID FAR * a);
	HRESULT  __stdcall PageLock(DWORD);
	HRESULT  __stdcall PageUnlock(DWORD);

	LPDIRECTDRAWSURFACE2 FAR m_pIDDrawSurface;
};


class myIDDrawSurface3 : public IDirectDrawSurface3
{
public:
	myIDDrawSurface3(LPDIRECTDRAWSURFACE3 pOriginal);
	virtual ~myIDDrawSurface3(void);
	// The original DDraw function definitions BEGIN
	HRESULT __stdcall QueryInterface (REFIID a, LPVOID FAR * b);
	ULONG   __stdcall AddRef(void);
	ULONG   __stdcall Release(void);
	/*** IDirectDrawSurface methods ***/
	HRESULT  __stdcall AddAttachedSurface(LPDIRECTDRAWSURFACE3);
	HRESULT  __stdcall AddOverlayDirtyRect(LPRECT);
	HRESULT  __stdcall Blt(LPRECT,LPDIRECTDRAWSURFACE3, LPRECT,DWORD, LPDDBLTFX);
	HRESULT  __stdcall BltBatch(LPDDBLTBATCH, DWORD, DWORD );
	HRESULT  __stdcall BltFast(DWORD,DWORD,LPDIRECTDRAWSURFACE3, LPRECT,DWORD);
	HRESULT  __stdcall DeleteAttachedSurface(DWORD,LPDIRECTDRAWSURFACE3);
	HRESULT  __stdcall EnumAttachedSurfaces(LPVOID,LPDDENUMSURFACESCALLBACK);
	HRESULT  __stdcall EnumOverlayZOrders(DWORD,LPVOID,LPDDENUMSURFACESCALLBACK);
	HRESULT  __stdcall Flip(LPDIRECTDRAWSURFACE3, DWORD);
	HRESULT  __stdcall GetAttachedSurface(LPDDSCAPS, LPDIRECTDRAWSURFACE3 FAR *);
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
	HRESULT  __stdcall UpdateOverlay(LPRECT, LPDIRECTDRAWSURFACE3,LPRECT,DWORD, LPDDOVERLAYFX);
	HRESULT  __stdcall UpdateOverlayDisplay(DWORD);
	HRESULT  __stdcall UpdateOverlayZOrder(DWORD, LPDIRECTDRAWSURFACE3);
	/*** Added in the v2 interface ***/
	HRESULT  __stdcall GetDDInterface(LPVOID FAR *);
	HRESULT  __stdcall PageLock(DWORD);
	HRESULT  __stdcall PageUnlock(DWORD);
	/*** Added in the V3 interface ***/
	HRESULT  __stdcall SetSurfaceDesc(LPDDSURFACEDESC, DWORD);

	LPDIRECTDRAWSURFACE3 FAR m_pIDDrawSurface;
};

class myIDDrawSurface4 : public IDirectDrawSurface4
{
public:
	myIDDrawSurface4(LPDIRECTDRAWSURFACE4 pOriginal);
	virtual ~myIDDrawSurface4(void);
	// The original DDraw function definitions BEGIN
	HRESULT __stdcall QueryInterface (REFIID a, LPVOID FAR * b);
	ULONG   __stdcall AddRef(void);
	ULONG   __stdcall Release(void);
	/*** IDirectDrawSurface methods ***/
	HRESULT  __stdcall AddAttachedSurface(LPDIRECTDRAWSURFACE4);
	HRESULT  __stdcall AddOverlayDirtyRect(LPRECT);
	HRESULT  __stdcall Blt(LPRECT,LPDIRECTDRAWSURFACE4, LPRECT,DWORD, LPDDBLTFX);
	HRESULT  __stdcall BltBatch(LPDDBLTBATCH, DWORD, DWORD );
	HRESULT  __stdcall BltFast(DWORD,DWORD,LPDIRECTDRAWSURFACE4, LPRECT,DWORD);
	HRESULT  __stdcall DeleteAttachedSurface(DWORD,LPDIRECTDRAWSURFACE4);
	HRESULT  __stdcall EnumAttachedSurfaces(LPVOID,LPDDENUMSURFACESCALLBACK2);
	HRESULT  __stdcall EnumOverlayZOrders(DWORD,LPVOID,LPDDENUMSURFACESCALLBACK2);
	HRESULT  __stdcall Flip(LPDIRECTDRAWSURFACE4, DWORD);
	HRESULT  __stdcall GetAttachedSurface(LPDDSCAPS2, LPDIRECTDRAWSURFACE4 FAR *);
	HRESULT  __stdcall GetBltStatus(DWORD);
	HRESULT  __stdcall GetCaps(LPDDSCAPS2);
	HRESULT  __stdcall GetClipper(LPDIRECTDRAWCLIPPER FAR*);
	HRESULT  __stdcall GetColorKey(DWORD, LPDDCOLORKEY);
	HRESULT  __stdcall GetDC(HDC FAR *);
	HRESULT  __stdcall GetFlipStatus(DWORD);
	HRESULT  __stdcall GetOverlayPosition(LPLONG, LPLONG );
	HRESULT  __stdcall GetPalette(LPDIRECTDRAWPALETTE FAR*);
	HRESULT  __stdcall GetPixelFormat(LPDDPIXELFORMAT);
	HRESULT  __stdcall GetSurfaceDesc(LPDDSURFACEDESC2);
	HRESULT  __stdcall Initialize(LPDIRECTDRAW, LPDDSURFACEDESC2);
	HRESULT  __stdcall IsLost();
	HRESULT  __stdcall Lock(LPRECT,LPDDSURFACEDESC2,DWORD,HANDLE);
	HRESULT  __stdcall ReleaseDC(HDC);
	HRESULT  __stdcall Restore();
	HRESULT  __stdcall SetClipper(LPDIRECTDRAWCLIPPER);
	HRESULT  __stdcall SetColorKey(DWORD, LPDDCOLORKEY);
	HRESULT  __stdcall SetOverlayPosition(LONG, LONG );
	HRESULT  __stdcall SetPalette(LPDIRECTDRAWPALETTE);
	HRESULT  __stdcall Unlock(LPRECT);
	HRESULT  __stdcall UpdateOverlay(LPRECT, LPDIRECTDRAWSURFACE4,LPRECT,DWORD, LPDDOVERLAYFX);
	HRESULT  __stdcall UpdateOverlayDisplay(DWORD);
	HRESULT  __stdcall UpdateOverlayZOrder(DWORD, LPDIRECTDRAWSURFACE4);

	/*** Added in the v2 interface ***/
	HRESULT  __stdcall GetDDInterface(LPVOID FAR *);
	HRESULT  __stdcall PageLock(DWORD);
	HRESULT  __stdcall PageUnlock(DWORD);
	/*** Added in the V3 interface ***/
	HRESULT  __stdcall SetSurfaceDesc(LPDDSURFACEDESC2, DWORD);
	/*** Added in the v4 interface ***/
	HRESULT  __stdcall SetPrivateData(REFGUID, LPVOID, DWORD, DWORD);
	HRESULT  __stdcall GetPrivateData(REFGUID, LPVOID, LPDWORD);
	HRESULT  __stdcall FreePrivateData(REFGUID);
	HRESULT  __stdcall GetUniquenessValue(LPDWORD);
	HRESULT  __stdcall ChangeUniquenessValue();

	LPDIRECTDRAWSURFACE4 FAR m_pIDDrawSurface;
};

class myIDDrawSurface7 : public IDirectDrawSurface7
{
public:
	myIDDrawSurface7(LPDIRECTDRAWSURFACE7 pOriginal);
	virtual ~myIDDrawSurface7(void);
	// The original DDraw function definitions BEGIN
	HRESULT __stdcall QueryInterface (REFIID a, LPVOID FAR * b);
	ULONG   __stdcall AddRef(void);
	ULONG   __stdcall Release(void);
	/*** IDirectDrawSurface methods ***/
	HRESULT  __stdcall AddAttachedSurface(LPDIRECTDRAWSURFACE7);
	HRESULT  __stdcall AddOverlayDirtyRect(LPRECT);
	HRESULT  __stdcall Blt(LPRECT,LPDIRECTDRAWSURFACE7, LPRECT,DWORD, LPDDBLTFX);
	HRESULT  __stdcall BltBatch(LPDDBLTBATCH, DWORD, DWORD );
	HRESULT  __stdcall BltFast(DWORD,DWORD,LPDIRECTDRAWSURFACE7, LPRECT,DWORD);
	HRESULT  __stdcall DeleteAttachedSurface(DWORD,LPDIRECTDRAWSURFACE7);
	HRESULT  __stdcall EnumAttachedSurfaces(LPVOID,LPDDENUMSURFACESCALLBACK7);
	HRESULT  __stdcall EnumOverlayZOrders(DWORD,LPVOID,LPDDENUMSURFACESCALLBACK7);
	HRESULT  __stdcall Flip(LPDIRECTDRAWSURFACE7, DWORD);
	HRESULT  __stdcall GetAttachedSurface(LPDDSCAPS2, LPDIRECTDRAWSURFACE7 FAR *);
	HRESULT  __stdcall GetBltStatus(DWORD);
	HRESULT  __stdcall GetCaps(LPDDSCAPS2);
	HRESULT  __stdcall GetClipper(LPDIRECTDRAWCLIPPER FAR*);
	HRESULT  __stdcall GetColorKey(DWORD, LPDDCOLORKEY);
	HRESULT  __stdcall GetDC(HDC FAR *);
	HRESULT  __stdcall GetFlipStatus(DWORD);
	HRESULT  __stdcall GetOverlayPosition(LPLONG, LPLONG );
	HRESULT  __stdcall GetPalette(LPDIRECTDRAWPALETTE FAR*);
	HRESULT  __stdcall GetPixelFormat(LPDDPIXELFORMAT);
	HRESULT  __stdcall GetSurfaceDesc(LPDDSURFACEDESC2);
	HRESULT  __stdcall Initialize(LPDIRECTDRAW, LPDDSURFACEDESC2);
	HRESULT  __stdcall IsLost();
	HRESULT  __stdcall Lock(LPRECT,LPDDSURFACEDESC2,DWORD,HANDLE);
	HRESULT  __stdcall ReleaseDC(HDC);
	HRESULT  __stdcall Restore();
	HRESULT  __stdcall SetClipper(LPDIRECTDRAWCLIPPER);
	HRESULT  __stdcall SetColorKey(DWORD, LPDDCOLORKEY);
	HRESULT  __stdcall SetOverlayPosition(LONG, LONG );
	HRESULT  __stdcall SetPalette(LPDIRECTDRAWPALETTE);
	HRESULT  __stdcall Unlock(LPRECT);
	HRESULT  __stdcall UpdateOverlay(LPRECT, LPDIRECTDRAWSURFACE7,LPRECT,DWORD, LPDDOVERLAYFX);
	HRESULT  __stdcall UpdateOverlayDisplay(DWORD);
	HRESULT  __stdcall UpdateOverlayZOrder(DWORD, LPDIRECTDRAWSURFACE7);

	/*** Added in the v2 interface ***/
	HRESULT  __stdcall GetDDInterface(LPVOID FAR *);
	HRESULT  __stdcall PageLock(DWORD);
	HRESULT  __stdcall PageUnlock(DWORD);
	/*** Added in the V3 interface ***/
	HRESULT  __stdcall SetSurfaceDesc(LPDDSURFACEDESC2, DWORD);
	/*** Added in the v4 interface ***/
	HRESULT  __stdcall SetPrivateData(REFGUID, LPVOID, DWORD, DWORD);
	HRESULT  __stdcall GetPrivateData(REFGUID, LPVOID, LPDWORD);
	HRESULT  __stdcall FreePrivateData(REFGUID);
	HRESULT  __stdcall GetUniquenessValue(LPDWORD);
	HRESULT  __stdcall ChangeUniquenessValue();
	/*** Moved Texture7 methods here ***/
	HRESULT  __stdcall SetPriority(DWORD);
	HRESULT  __stdcall GetPriority(LPDWORD);
	HRESULT  __stdcall SetLOD(DWORD);
	HRESULT  __stdcall GetLOD(LPDWORD);

	LPDIRECTDRAWSURFACE7 FAR m_pIDDrawSurface;
};



