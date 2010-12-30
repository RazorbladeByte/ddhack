#include "StdAfx.h"
#include <varargs.h>



myIDDraw1::myIDDraw1(LPDIRECTDRAW pOriginal)
{
	logf(this, "myIDDraw1 Constructor");
	m_pIDDraw = pOriginal;
}


myIDDraw1::~myIDDraw1(void)
{
	logf(this, "myIDDraw1 Destructor");
}


HRESULT __stdcall myIDDraw1::QueryInterface (REFIID a, LPVOID FAR * b)
{
	char *iid = "?";
	if (a == IID_IDirectDraw) iid = "IID_IDirectDraw";
	if (a == IID_IDirectDraw2) iid = "IID_IDirectDraw2";
	if (a == IID_IDirectDraw4) iid = "IID_IDirectDraw4";
	if (a == IID_IDirectDraw7) iid = "IID_IDirectDraw7";

	logf(this, "myIDDraw1::QueryInterface(%s,%08x)",iid,b);
	

	*b = NULL;

	// call this to increase AddRef at original object
	// and to check if such an interface is there

	HRESULT hRes = m_pIDDraw->QueryInterface(a, b); 

	if (hRes == NOERROR) // if OK, send our "fake" address
	{
		if (a == IID_IDirectDraw2) 
			*b = new myIDDraw2((LPDIRECTDRAW2)*b);
		if (a == IID_IDirectDraw7) 
			*b = new myIDDraw7((LPDIRECTDRAW7)*b);		
	}
	
	return hRes;
}


ULONG   __stdcall myIDDraw1::AddRef(void)
{
	logf(this, "myIDDraw1::AddRef");
	return(m_pIDDraw->AddRef());
}


ULONG   __stdcall myIDDraw1::Release(void)
{
	logf(this, "myIDDraw1::Release");
	
	// call original routine
	ULONG count = m_pIDDraw->Release();
	
	logf(this, "Object Release."); 

    // in case no further Ref is there, the Original Object has deleted itself
	// so do we here
	if (count == 0) 
	{
		m_pIDDraw = NULL;		
		delete(this); 
	}

	return(count);
}


HRESULT  __stdcall myIDDraw1::Compact(void)
{
	logf(this, "myIDDraw1::Compact");
	return(m_pIDDraw->Compact());
}


HRESULT  __stdcall myIDDraw1::CreateClipper(DWORD a, LPDIRECTDRAWCLIPPER FAR* b, IUnknown FAR* c)
{
	logf(this, "myIDDraw1::CreateClipper");
	return(m_pIDDraw->CreateClipper(a, b, c));
}


HRESULT  __stdcall myIDDraw1::CreatePalette(DWORD a, LPPALETTEENTRY b, LPDIRECTDRAWPALETTE FAR* c, IUnknown FAR* d)
{
	HRESULT r = m_pIDDraw->CreatePalette(a, b, c, d);
	*c = new myIDDrawPalette(*c);
	logf(this, "myIDDraw1::CreatePalette(%d,%08x,%08x,%08x) return %d",a,b,c,d,r);
	return r;
}


HRESULT  __stdcall myIDDraw1::CreateSurface(LPDDSURFACEDESC a, LPDIRECTDRAWSURFACE FAR* b, IUnknown FAR* c)
{
	HRESULT r = m_pIDDraw->CreateSurface(a, b, c);
	logf(this, "myIDDraw1::CreateSurface([%d,0x%x,%d,%d,%d,%d,%d], %08x, %08x) return %d", a->dwSize, a->dwFlags, a->dwWidth, a->dwHeight, a->lPitch, a->dwBackBufferCount, a->ddsCaps, b, c, r); 

	*b = new myIDDrawSurface1(*b);
	
	return r;
}


HRESULT  __stdcall myIDDraw1::DuplicateSurface(LPDIRECTDRAWSURFACE a, LPDIRECTDRAWSURFACE FAR* b)
{
	logf(this, "myIDDraw1::DuplicateSurface");
	return(m_pIDDraw->DuplicateSurface(a, b));
}


HRESULT  __stdcall myIDDraw1::EnumDisplayModes(DWORD a, LPDDSURFACEDESC b, LPVOID c, LPDDENUMMODESCALLBACK d)
{
	logf(this, "myIDDraw1::EnumDisplayModes");
	return(m_pIDDraw->EnumDisplayModes(a, b, c, d));
}


HRESULT  __stdcall myIDDraw1::EnumSurfaces(DWORD a, LPDDSURFACEDESC b, LPVOID c, LPDDENUMSURFACESCALLBACK d)
{
	logf(this, "myIDDraw1::EnumSurfaces");
	return(m_pIDDraw->EnumSurfaces(a, b, c, d));
}


HRESULT  __stdcall myIDDraw1::FlipToGDISurface(void)
{
	logf(this, "myIDDraw1::FlipToGDISurface");
	return(m_pIDDraw->FlipToGDISurface());
}


HRESULT  __stdcall myIDDraw1::GetCaps(LPDDCAPS a, LPDDCAPS b)
{
	logf(this, "myIDDraw1::GetCaps(%08x, %08x)", a, b);
	HRESULT r = m_pIDDraw->GetCaps(a, b);
	if (a)
	{
		logf(this, "surface caps: %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x",
		a->dwCaps, 
		a->dwCaps2, 
		a->dwCKeyCaps, 
		a->dwFXCaps, 
		a->dwFXAlphaCaps, 
		a->dwPalCaps, 
		a->dwSVCaps, 
		a->dwVidMemTotal,
		a->dwVidMemFree, 
		a->dwAlignBoundarySrc,
		a->dwAlignSizeSrc,
		a->dwAlignBoundaryDest,
		a->dwAlignSizeDest,
		a->dwAlignStrideAlign,		
		a->ddsCaps.dwCaps);
	}
	if (b)
	{
		logf(this, "HEL caps: %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x",
		b->dwCaps, 
		b->dwCaps2, 
		b->dwCKeyCaps, 
		b->dwFXCaps, 
		b->dwFXAlphaCaps, 
		b->dwPalCaps, 
		b->dwSVCaps, 
		b->dwVidMemTotal,
		b->dwVidMemFree, 
		b->dwAlignBoundarySrc,
		b->dwAlignSizeSrc,
		b->dwAlignBoundaryDest,
		b->dwAlignSizeDest,
		b->dwAlignStrideAlign,		
		b->ddsCaps.dwCaps);
	}
	return r;
}


HRESULT  __stdcall myIDDraw1::GetDisplayMode(LPDDSURFACEDESC a)
{
	logf(this, "myIDDraw1::GetDisplayMode");
	return(m_pIDDraw->GetDisplayMode(a));
}


HRESULT  __stdcall myIDDraw1::GetFourCCCodes(LPDWORD a, LPDWORD b)
{
	logf(this, "myIDDraw1::GetFourCCCodes");
	return(m_pIDDraw->GetFourCCCodes(a, b));
}


HRESULT  __stdcall myIDDraw1::GetGDISurface(LPDIRECTDRAWSURFACE FAR * a)
{
	logf(this, "myIDDraw1::GetGDISurface");
	return(m_pIDDraw->GetGDISurface(a));
}


HRESULT  __stdcall myIDDraw1::GetMonitorFrequency(LPDWORD a)
{
	logf(this, "myIDDraw1::GetMonitorFrequency");
	return(m_pIDDraw->GetMonitorFrequency(a));
}


HRESULT  __stdcall myIDDraw1::GetScanLine(LPDWORD a)
{
	logf(this, "myIDDraw1::GetScanLine");
	return(m_pIDDraw->GetScanLine(a));
}


HRESULT  __stdcall myIDDraw1::GetVerticalBlankStatus(LPBOOL a)
{
	logf(this, "myIDDraw1::GetVerticalBlankStatus");
	return(m_pIDDraw->GetVerticalBlankStatus(a));
}


HRESULT  __stdcall myIDDraw1::Initialize(GUID FAR* a)
{
	logf(this, "myIDDraw1::Initialize");
	return(m_pIDDraw->Initialize(a));
}


HRESULT  __stdcall myIDDraw1::RestoreDisplayMode(void)
{
	logf(this, "myIDDraw1::RestoreDisplayMode");
	return(m_pIDDraw->RestoreDisplayMode());
}


HRESULT  __stdcall myIDDraw1::SetCooperativeLevel(HWND a, DWORD b)
{

	HRESULT h = m_pIDDraw->SetCooperativeLevel(a, b); 

	logf(this, "myIDDraw1::SetCooperativeLevel(%08x, %d) return %d", a, b, h);
	
	return(h);
}


HRESULT  __stdcall myIDDraw1::SetDisplayMode(DWORD a, DWORD b, DWORD c)
{
	HRESULT h = m_pIDDraw->SetDisplayMode(a, b, c);

	logf(this, "myIDDraw1::SetDisplayMode(%d, %d, %d) return %d",a,b,c,h);
	
	return(h); 
}


HRESULT  __stdcall myIDDraw1::WaitForVerticalBlank(DWORD a, HANDLE b)
{
	logf(this, "myIDDraw1::WaitForVerticalBlank");
	return(m_pIDDraw->WaitForVerticalBlank(a, b));
}


