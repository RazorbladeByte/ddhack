#include "StdAfx.h"
#include <varargs.h>



myIDDraw4::myIDDraw4(LPDIRECTDRAW4 pOriginal)
{
	logf(this, "myIDDraw4 Constructor");
	m_pIDDraw = pOriginal;
}


myIDDraw4::~myIDDraw4(void)
{
	logf(this, "myIDDraw4 Destructor");
}


HRESULT __stdcall myIDDraw4::QueryInterface (REFIID a, LPVOID FAR * b)
{

	char *iid = "?";
	if (a == IID_IDirectDraw) iid = "IID_IDirectDraw";
	if (a == IID_IDirectDraw2) iid = "IID_IDirectDraw2";
	if (a == IID_IDirectDraw4) iid = "IID_IDirectDraw4";
	if (a == IID_IDirectDraw7) iid = "IID_IDirectDraw7";

	logf(this, "myIDDraw4::QueryInterface(%s,%08x)",iid,b);

	*b = NULL;

	// call this to increase AddRef at original object
	// and to check if such an interface is there

	HRESULT hRes = m_pIDDraw->QueryInterface(a, b); 

	if (hRes == NOERROR) // if OK, send our "fake" address
	{
		if (a == IID_IDirectDraw4)
			*b = this;
	}

	return hRes;
}


ULONG   __stdcall myIDDraw4::AddRef(void)
{
	logf(this, "myIDDraw4::AddRef");
	return(m_pIDDraw->AddRef());
}


ULONG   __stdcall myIDDraw4::Release(void)
{
	logf(this, "myIDDraw4::Release");

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


HRESULT  __stdcall myIDDraw4::Compact(void)
{
	logf(this, "myIDDraw4::Compact");
	return(m_pIDDraw->Compact());
}


HRESULT  __stdcall myIDDraw4::CreateClipper(DWORD a, LPDIRECTDRAWCLIPPER FAR* b, IUnknown FAR* c)
{
	logf(this, "myIDDraw4::CreateClipper");
	return(m_pIDDraw->CreateClipper(a, b, c));
}


HRESULT  __stdcall myIDDraw4::CreatePalette(DWORD a, LPPALETTEENTRY b, LPDIRECTDRAWPALETTE FAR* c, IUnknown FAR* d)
{
	HRESULT r = m_pIDDraw->CreatePalette(a, b, c, d);
	*c = new myIDDrawPalette(*c);
	logf(this, "myIDDraw4::CreatePalette(%d,%08x,%08x,%08x) return %d",a,b,c,d,r);
	return r;
}


HRESULT  __stdcall myIDDraw4::CreateSurface(LPDDSURFACEDESC2 a, LPDIRECTDRAWSURFACE4 FAR* b, IUnknown FAR* c)
{
	HRESULT r = m_pIDDraw->CreateSurface(a, b, c);
	logf(this, "myIDDraw4::CreateSurface([%d,0x%x,%d,%d,%d,%d,%d], %08x, %08x) return %d", a->dwSize, a->dwFlags, a->dwWidth, a->dwHeight, a->lPitch, a->dwBackBufferCount, a->ddsCaps, b, c, r); 


	*b = new myIDDrawSurface4(*b);

	return r;
}


HRESULT  __stdcall myIDDraw4::DuplicateSurface(LPDIRECTDRAWSURFACE4 a, LPDIRECTDRAWSURFACE4 FAR* b)
{
	logf(this, "myIDDraw4::DuplicateSurface");
	return(m_pIDDraw->DuplicateSurface(a, b));
}


HRESULT  __stdcall myIDDraw4::EnumDisplayModes(DWORD a, LPDDSURFACEDESC2 b, LPVOID c, LPDDENUMMODESCALLBACK2 d)
{
	logf(this, "myIDDraw4::EnumDisplayModes");
	return(m_pIDDraw->EnumDisplayModes(a, b, c, d));
}


HRESULT  __stdcall myIDDraw4::EnumSurfaces(DWORD a, LPDDSURFACEDESC2 b, LPVOID c, LPDDENUMSURFACESCALLBACK2 d)
{
	logf(this, "myIDDraw4::EnumSurfaces");
	return(m_pIDDraw->EnumSurfaces(a, b, c, d));
}


HRESULT  __stdcall myIDDraw4::FlipToGDISurface(void)
{
	logf(this, "myIDDraw4::FlipToGDISurface");
	return(m_pIDDraw->FlipToGDISurface());
}


HRESULT  __stdcall myIDDraw4::GetCaps(LPDDCAPS a, LPDDCAPS b)
{
	logf(this, "myIDDraw4::GetCaps");
	return(m_pIDDraw->GetCaps(a, b));
}


HRESULT  __stdcall myIDDraw4::GetDisplayMode(LPDDSURFACEDESC2 a)
{
	logf(this, "myIDDraw4::GetDisplayMode");
	return(m_pIDDraw->GetDisplayMode(a));
}


HRESULT  __stdcall myIDDraw4::GetFourCCCodes(LPDWORD a, LPDWORD b)
{
	logf(this, "myIDDraw4::GetFourCCCodes");
	return(m_pIDDraw->GetFourCCCodes(a, b));
}


HRESULT  __stdcall myIDDraw4::GetGDISurface(LPDIRECTDRAWSURFACE4 FAR * a)
{
	logf(this, "myIDDraw4::GetGDISurface");
	return(m_pIDDraw->GetGDISurface(a));
}


HRESULT  __stdcall myIDDraw4::GetMonitorFrequency(LPDWORD a)
{
	logf(this, "myIDDraw4::GetMonitorFrequency");
	return(m_pIDDraw->GetMonitorFrequency(a));
}


HRESULT  __stdcall myIDDraw4::GetScanLine(LPDWORD a)
{
	logf(this, "myIDDraw4::GetScanLine");
	return(m_pIDDraw->GetScanLine(a));
}


HRESULT  __stdcall myIDDraw4::GetVerticalBlankStatus(LPBOOL a)
{
	logf(this, "myIDDraw4::GetVerticalBlankStatus");
	return(m_pIDDraw->GetVerticalBlankStatus(a));
}


HRESULT  __stdcall myIDDraw4::Initialize(GUID FAR* a)
{
	logf(this, "myIDDraw4::Initialize");
	return(m_pIDDraw->Initialize(a));
}


HRESULT  __stdcall myIDDraw4::RestoreDisplayMode(void)
{
	logf(this, "myIDDraw4::RestoreDisplayMode");
	return(m_pIDDraw->RestoreDisplayMode());
}


HRESULT  __stdcall myIDDraw4::SetCooperativeLevel(HWND a, DWORD b)
{

	HRESULT h = m_pIDDraw->SetCooperativeLevel(a, b); 

	logf(this, "myIDDraw4::SetCooperativeLevel(%08x, %d) return %d", a, b, h);

	return(h);
}


HRESULT  __stdcall myIDDraw4::SetDisplayMode(DWORD a, DWORD b, DWORD c, DWORD d, DWORD e)
{
	HRESULT h = m_pIDDraw->SetDisplayMode(a, b, c, d, e);

	logf(this, "myIDDraw4::SetDisplayMode(%d, %d, %d, %d, %d) return %d",a,b,c,d,e,h);

	return(h); 
}


HRESULT  __stdcall myIDDraw4::WaitForVerticalBlank(DWORD a, HANDLE b)
{
	logf(this, "myIDDraw4::WaitForVerticalBlank(%d,%d)",a,b);
	return(m_pIDDraw->WaitForVerticalBlank(a, b));
}


HRESULT  __stdcall myIDDraw4::GetAvailableVidMem(LPDDSCAPS2 a, LPDWORD b, LPDWORD c)
{
	logf(this, "myIDDraw4::GetAvailableVidMem");
	return(m_pIDDraw->GetAvailableVidMem(a, b, c));
}


HRESULT  __stdcall myIDDraw4::GetSurfaceFromDC(HDC a, LPDIRECTDRAWSURFACE4 * b)
{
	logf(this, "myIDDraw4::GetSurfaceFromDC");
	return(m_pIDDraw->GetSurfaceFromDC(a, b));
}


HRESULT  __stdcall myIDDraw4::RestoreAllSurfaces(void)
{
	logf(this, "myIDDraw4::RestoreAllSurfaces");
	return(m_pIDDraw->RestoreAllSurfaces());
}


HRESULT  __stdcall myIDDraw4::TestCooperativeLevel(void)
{
	logf(this, "myIDDraw4::TestCooperativeLevel");
	return(m_pIDDraw->TestCooperativeLevel());
}


HRESULT  __stdcall myIDDraw4::GetDeviceIdentifier(LPDDDEVICEIDENTIFIER a, DWORD b)
{
	logf(this, "myIDDraw4::GetDeviceIdentifier");
	return(m_pIDDraw->GetDeviceIdentifier(a, b));
}
