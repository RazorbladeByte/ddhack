#include "StdAfx.h"
#include <varargs.h>



myIDDraw2::myIDDraw2(LPDIRECTDRAW2 pOriginal)
{
	logf(this, "myIDDraw2 Constructor");
	m_pIDDraw = pOriginal;
}


myIDDraw2::~myIDDraw2(void)
{
	logf(this, "myIDDraw2 Destructor");
}


HRESULT __stdcall myIDDraw2::QueryInterface (REFIID a, LPVOID FAR * b)
{
	
	char *iid = "?";
	if (a == IID_IDirectDraw) iid = "IID_IDirectDraw";
	if (a == IID_IDirectDraw2) iid = "IID_IDirectDraw2";
	if (a == IID_IDirectDraw4) iid = "IID_IDirectDraw4";
	if (a == IID_IDirectDraw7) iid = "IID_IDirectDraw7";

	logf(this, "myIDDraw2::QueryInterface(%s,%08x)",iid,b);

	*b = NULL;

	// call this to increase AddRef at original object
	// and to check if such an interface is there

	HRESULT hRes = m_pIDDraw->QueryInterface(a, b); 

	if (hRes == NOERROR) // if OK, send our "fake" address
	{
		if (a == IID_IDirectDraw2) 
			*b = this;
	}
	
	return hRes;
}


ULONG   __stdcall myIDDraw2::AddRef(void)
{
	logf(this, "myIDDraw2::AddRef");
	return(m_pIDDraw->AddRef());
}


ULONG   __stdcall myIDDraw2::Release(void)
{
	logf(this, "myIDDraw2::Release");
	
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


HRESULT  __stdcall myIDDraw2::Compact(void)
{
	logf(this, "myIDDraw2::Compact");
	return(m_pIDDraw->Compact());
}


HRESULT  __stdcall myIDDraw2::CreateClipper(DWORD a, LPDIRECTDRAWCLIPPER FAR* b, IUnknown FAR* c)
{
	logf(this, "myIDDraw2::CreateClipper");
	return(m_pIDDraw->CreateClipper(a, b, c));
}


HRESULT  __stdcall myIDDraw2::CreatePalette(DWORD a, LPPALETTEENTRY b, LPDIRECTDRAWPALETTE FAR* c, IUnknown FAR* d)
{
	HRESULT r = m_pIDDraw->CreatePalette(a, b, c, d);
	*c = new myIDDrawPalette(*c);
	logf(this, "myIDDraw2::CreatePalette(%d,%08x,%08x,%08x) return %d",a,b,c,d,r);
	return r;
}


HRESULT  __stdcall myIDDraw2::CreateSurface(LPDDSURFACEDESC a, LPDIRECTDRAWSURFACE FAR* b, IUnknown FAR* c)
{
	HRESULT r = m_pIDDraw->CreateSurface(a, b, c);
	logf(this, "myIDDraw2::CreateSurface([%d,0x%x,%d,%d,%d,%d,%d], %08x, %08x) return %d", a->dwSize, a->dwFlags, a->dwWidth, a->dwHeight, a->lPitch, a->dwBackBufferCount, a->ddsCaps, b, c, r); 

	*b = new myIDDrawSurface1(*b);

	return r;
}


HRESULT  __stdcall myIDDraw2::DuplicateSurface(LPDIRECTDRAWSURFACE a, LPDIRECTDRAWSURFACE FAR* b)
{
	logf(this, "myIDDraw2::DuplicateSurface");
	return(m_pIDDraw->DuplicateSurface(a, b));
}


HRESULT  __stdcall myIDDraw2::EnumDisplayModes(DWORD a, LPDDSURFACEDESC b, LPVOID c, LPDDENUMMODESCALLBACK d)
{
	logf(this, "myIDDraw2::EnumDisplayModes");
	return(m_pIDDraw->EnumDisplayModes(a, b, c, d));
}


HRESULT  __stdcall myIDDraw2::EnumSurfaces(DWORD a, LPDDSURFACEDESC b, LPVOID c, LPDDENUMSURFACESCALLBACK d)
{
	logf(this, "myIDDraw2::EnumSurfaces");
	return(m_pIDDraw->EnumSurfaces(a, b, c, d));
}


HRESULT  __stdcall myIDDraw2::FlipToGDISurface(void)
{
	logf(this, "myIDDraw2::FlipToGDISurface");
	return(m_pIDDraw->FlipToGDISurface());
}


HRESULT  __stdcall myIDDraw2::GetCaps(LPDDCAPS a, LPDDCAPS b)
{
	logf(this, "myIDDraw2::GetCaps");
	return(m_pIDDraw->GetCaps(a, b));
}


HRESULT  __stdcall myIDDraw2::GetDisplayMode(LPDDSURFACEDESC a)
{
	logf(this, "myIDDraw2::GetDisplayMode");
	return(m_pIDDraw->GetDisplayMode(a));
}


HRESULT  __stdcall myIDDraw2::GetFourCCCodes(LPDWORD a, LPDWORD b)
{
	logf(this, "myIDDraw2::GetFourCCCodes");
	return(m_pIDDraw->GetFourCCCodes(a, b));
}


HRESULT  __stdcall myIDDraw2::GetGDISurface(LPDIRECTDRAWSURFACE FAR * a)
{
	logf(this, "myIDDraw2::GetGDISurface");
	return(m_pIDDraw->GetGDISurface(a));
}


HRESULT  __stdcall myIDDraw2::GetMonitorFrequency(LPDWORD a)
{
	logf(this, "myIDDraw2::GetMonitorFrequency");
	return(m_pIDDraw->GetMonitorFrequency(a));
}


HRESULT  __stdcall myIDDraw2::GetScanLine(LPDWORD a)
{
	logf(this, "myIDDraw2::GetScanLine");
	return(m_pIDDraw->GetScanLine(a));
}


HRESULT  __stdcall myIDDraw2::GetVerticalBlankStatus(LPBOOL a)
{
	logf(this, "myIDDraw2::GetVerticalBlankStatus");
	return(m_pIDDraw->GetVerticalBlankStatus(a));
}


HRESULT  __stdcall myIDDraw2::Initialize(GUID FAR* a)
{
	logf(this, "myIDDraw2::Initialize");
	return(m_pIDDraw->Initialize(a));
}


HRESULT  __stdcall myIDDraw2::RestoreDisplayMode(void)
{
	logf(this, "myIDDraw2::RestoreDisplayMode");
	return(m_pIDDraw->RestoreDisplayMode());
}


HRESULT  __stdcall myIDDraw2::SetCooperativeLevel(HWND a, DWORD b)
{

	HRESULT h = m_pIDDraw->SetCooperativeLevel(a, b); 

	logf(this, "myIDDraw2::SetCooperativeLevel(%08x, %d) return %d", a, b, h);
	
	return(h);
}


HRESULT  __stdcall myIDDraw2::SetDisplayMode(DWORD a, DWORD b, DWORD c, DWORD d, DWORD e)
{
	HRESULT h = m_pIDDraw->SetDisplayMode(a, b, c, d, e);

	logf(this, "myIDDraw2::SetDisplayMode(%d, %d, %d, %d, %d) return %d",a,b,c,d,e,h);
	
	return(h); 
}


HRESULT  __stdcall myIDDraw2::WaitForVerticalBlank(DWORD a, HANDLE b)
{
	logf(this, "myIDDraw2::WaitForVerticalBlank(%d,%d)",a,b);
	return(m_pIDDraw->WaitForVerticalBlank(a, b));
}


HRESULT  __stdcall myIDDraw2::GetAvailableVidMem(LPDDSCAPS a, LPDWORD b, LPDWORD c)
{
	logf(this, "myIDDraw2::GetAvailableVidMem");
	return(m_pIDDraw->GetAvailableVidMem(a, b, c));
}



