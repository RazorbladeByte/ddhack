#include "StdAfx.h"
#include <varargs.h>



myIDDrawSurface1::myIDDrawSurface1(LPDIRECTDRAWSURFACE pOriginal)
{
	logf(this, "myIDDrawSurface1 Constructor");
	m_pIDDrawSurface = pOriginal;
}


myIDDrawSurface1::~myIDDrawSurface1(void)
{
	logf(this, "myIDDrawSurface1 Destructor");
}


HRESULT __stdcall myIDDrawSurface1::QueryInterface (REFIID, LPVOID FAR * b)
{
	logf(this, "myIDDrawSurface1::QueryInterface");
	
	*b = NULL;

	return E_NOTIMPL;
}


ULONG   __stdcall myIDDrawSurface1::AddRef(void)
{
	logf(this, "myIDDrawSurface1::AddRef");
	return(m_pIDDrawSurface->AddRef());
}


ULONG   __stdcall myIDDrawSurface1::Release(void)
{
	logf(this, "myIDDrawSurface1::Release");
	
	// call original routine
	ULONG count = m_pIDDrawSurface->Release();
	
	logf(this, "Object Release."); 

    // in case no further Ref is there, the Original Object has deleted itself
	// so do we here
	if (count == 0) 
	{
		m_pIDDrawSurface = NULL;		
		delete(this); 
	}

	return(count);
}



HRESULT  __stdcall myIDDrawSurface1::AddAttachedSurface(LPDIRECTDRAWSURFACE a)
{
	logf(this, "myIDDrawSurface1::AddAttachedSurface");
	return m_pIDDrawSurface->AddAttachedSurface(((myIDDrawSurface1*)a)->m_pIDDrawSurface);
}



HRESULT  __stdcall myIDDrawSurface1::AddOverlayDirtyRect(LPRECT a)
{
	logf(this, "myIDDrawSurface1::AddOverlayDirtyRect");
	return m_pIDDrawSurface->AddOverlayDirtyRect(a);
}



HRESULT  __stdcall myIDDrawSurface1::Blt(LPRECT a,LPDIRECTDRAWSURFACE b, LPRECT c,DWORD d, LPDDBLTFX e)
{
	if (a && c)
		logf(this, "myIDDrawSurface1::Blt([%d,%d,%d,%d],%08x,[%d,%d,%d,%d],%d,%08x)",
			a->top,a->left,a->bottom,a->right,
			b,
			c->top,c->left,c->bottom,c->right,
			d,
			e->dwDDFX);
	else
	if (a)
		logf(this, "myIDDrawSurface1::Blt([%d,%d,%d,%d],%08x,[null],%d,%08x)",
			a->top,a->left,a->bottom,a->right,
			b,
			d,
			e->dwDDFX);
	else
	if (c)
		logf(this, "myIDDrawSurface1::Blt([null],%08x,[%d,%d,%d,%d],%d,%08x)",
			b,
			c->top,c->left,c->bottom,c->right,
			d,
			e->dwDDFX);
	else
		logf(this, "myIDDrawSurface1::Blt([null],%08x,[null],%d,%08x)",
			b,
			d,
			e->dwDDFX);
	if (b) b = ((myIDDrawSurface1*)b)->m_pIDDrawSurface;
	return m_pIDDrawSurface->Blt(a,b,c,d,e);
}



HRESULT  __stdcall myIDDrawSurface1::BltBatch(LPDDBLTBATCH a, DWORD b, DWORD c)
{
	logf(this, "myIDDrawSurface1::BltBatch");
	return m_pIDDrawSurface->BltBatch(a,b,c);
}



HRESULT  __stdcall myIDDrawSurface1::BltFast(DWORD a,DWORD b,LPDIRECTDRAWSURFACE c, LPRECT d,DWORD e)
{
	logf(this, "myIDDrawSurface1::BltFast");
	return m_pIDDrawSurface->BltFast(a,b,((myIDDrawSurface1*)c)->m_pIDDrawSurface,d,e);
}



HRESULT  __stdcall myIDDrawSurface1::DeleteAttachedSurface(DWORD a,LPDIRECTDRAWSURFACE b)
{
	logf(this, "myIDDrawSurface1::DeleteAttachedSurface");
	return m_pIDDrawSurface->DeleteAttachedSurface(a,((myIDDrawSurface1*)b)->m_pIDDrawSurface);
}



HRESULT  __stdcall myIDDrawSurface1::EnumAttachedSurfaces(LPVOID a,LPDDENUMSURFACESCALLBACK b)
{
	logf(this, "myIDDrawSurface1::EnumAttachedSurfaces");
	return m_pIDDrawSurface->EnumAttachedSurfaces(a,b);
}



HRESULT  __stdcall myIDDrawSurface1::EnumOverlayZOrders(DWORD a,LPVOID b,LPDDENUMSURFACESCALLBACK c)
{
	logf(this, "myIDDrawSurface1::EnumOverlayZOrders");
	return m_pIDDrawSurface->EnumOverlayZOrders(a,b,c);
}



HRESULT  __stdcall myIDDrawSurface1::Flip(LPDIRECTDRAWSURFACE a, DWORD b)
{
	logf(this, "myIDDrawSurface1::Flip(%08x,%d)", a, b);
	if (a) a = ((myIDDrawSurface1*)a)->m_pIDDrawSurface;
	return m_pIDDrawSurface->Flip(a,b);
}



HRESULT  __stdcall myIDDrawSurface1::GetAttachedSurface(LPDDSCAPS a, LPDIRECTDRAWSURFACE FAR * b)
{
	HRESULT r = m_pIDDrawSurface->GetAttachedSurface(a,b);
    *b = new myIDDrawSurface1(*b);

	logf(this, "myIDDrawSurface1::GetAttachedSurface([%d], %08x) return %d",
		a->dwCaps, b, r);
	
	return r;
}



HRESULT  __stdcall myIDDrawSurface1::GetBltStatus(DWORD a)
{
	logf(this, "myIDDrawSurface1::GetBltStatus");
	return m_pIDDrawSurface->GetBltStatus(a);
}



HRESULT  __stdcall myIDDrawSurface1::GetCaps(LPDDSCAPS a)
{
	logf(this, "myIDDrawSurface1::GetCaps");
	return m_pIDDrawSurface->GetCaps(a);
}



HRESULT  __stdcall myIDDrawSurface1::GetClipper(LPDIRECTDRAWCLIPPER FAR* a)
{
	logf(this, "myIDDrawSurface1::GetClipper");
	return m_pIDDrawSurface->GetClipper(a);
}



HRESULT  __stdcall myIDDrawSurface1::GetColorKey(DWORD a, LPDDCOLORKEY b)
{
	logf(this, "myIDDrawSurface1::GetColorKey");
	return m_pIDDrawSurface->GetColorKey(a,b);
}



HRESULT  __stdcall myIDDrawSurface1::GetDC(HDC FAR *a)
{
	logf(this, "myIDDrawSurface1::GetDC");
	return m_pIDDrawSurface->GetDC(a);
}



HRESULT  __stdcall myIDDrawSurface1::GetFlipStatus(DWORD a)
{
	logf(this, "myIDDrawSurface1::GetFlipStatus");
	return m_pIDDrawSurface->GetFlipStatus(a);
}



HRESULT  __stdcall myIDDrawSurface1::GetOverlayPosition(LPLONG a, LPLONG b)
{
	logf(this, "myIDDrawSurface1::GetOverlayPosition");
	return m_pIDDrawSurface->GetOverlayPosition(a,b);
}



HRESULT  __stdcall myIDDrawSurface1::GetPalette(LPDIRECTDRAWPALETTE FAR*a)
{
	logf(this, "myIDDrawSurface1::GetPalette");
	return m_pIDDrawSurface->GetPalette(a);
}



HRESULT  __stdcall myIDDrawSurface1::GetPixelFormat(LPDDPIXELFORMAT a)
{
	logf(this, "myIDDrawSurface1::GetPixelFormat");
	return m_pIDDrawSurface->GetPixelFormat(a);
}



HRESULT  __stdcall myIDDrawSurface1::GetSurfaceDesc(LPDDSURFACEDESC a)
{
	HRESULT r = m_pIDDrawSurface->GetSurfaceDesc(a);
	logf(this, "myIDDrawSurface1::GetSurfaceDesc([%x %x %x %x %x %x %x %x %x [%x %x %x %x %x %x %x %x] %x]) return %d",
		a->dwSize, 
		a->dwFlags, 
		a->dwWidth, 
		a->dwHeight, 
		a->lPitch, 
		a->dwBackBufferCount,
		a->dwRefreshRate,
		a->dwAlphaBitDepth,
		a->lpSurface, 	
		a->ddpfPixelFormat.dwSize,			
		a->ddpfPixelFormat.dwFlags,	
		a->ddpfPixelFormat.dwFourCC,	
		a->ddpfPixelFormat.dwRGBBitCount,
		a->ddpfPixelFormat.dwRBitMask,		
		a->ddpfPixelFormat.dwGBitMask,		
		a->ddpfPixelFormat.dwBBitMask,
		a->ddpfPixelFormat.dwRGBAlphaBitMask,
		a->ddsCaps.dwCaps, r);



	return r;
}



HRESULT  __stdcall myIDDrawSurface1::Initialize(LPDIRECTDRAW a, LPDDSURFACEDESC b)
{
	logf(this, "myIDDrawSurface1::Initialize");
	return m_pIDDrawSurface->Initialize(a,b);
}



HRESULT  __stdcall myIDDrawSurface1::IsLost()
{
	logf(this, "myIDDrawSurface1::IsLost");
	return m_pIDDrawSurface->IsLost();
}



HRESULT  __stdcall myIDDrawSurface1::Lock(LPRECT a,LPDDSURFACEDESC b,DWORD c,HANDLE d)
{
	if (a)	
		logf(this, "myIDDrawSurface1::Lock([%d,%d,%d,%d],%08x,%d,%d)",a->top,a->left,a->bottom,a->right,b,c,d);
	else
		logf(this, "myIDDrawSurface1::Lock([null],%08x,%d,%d)",b,c,d);
	HRESULT r = m_pIDDrawSurface->Lock(a,b,c,d);
	logf(this, "Locked surface data: %d,%d,%d,%d,%d,%08x,%d,%d",
		b->dwSize,
		b->dwFlags,
		b->dwHeight,
		b->dwWidth,
		b->lPitch,
		b->lpSurface,
		b->ddsCaps,
		b->ddpfPixelFormat);
	return r;
}



HRESULT  __stdcall myIDDrawSurface1::ReleaseDC(HDC a)
{
	logf(this, "myIDDrawSurface1::ReleaseDC");
	return m_pIDDrawSurface->ReleaseDC(a);
}



HRESULT  __stdcall myIDDrawSurface1::Restore()
{
	logf(this, "myIDDrawSurface1::Restore");
	return m_pIDDrawSurface->Restore();
}



HRESULT  __stdcall myIDDrawSurface1::SetClipper(LPDIRECTDRAWCLIPPER a)
{
	logf(this, "myIDDrawSurface1::SetClipper");
	return m_pIDDrawSurface->SetClipper(a);
}



HRESULT  __stdcall myIDDrawSurface1::SetColorKey(DWORD a, LPDDCOLORKEY b)
{
	logf(this, "myIDDrawSurface1::SetColorKey");
	return m_pIDDrawSurface->SetColorKey(a,b);
}



HRESULT  __stdcall myIDDrawSurface1::SetOverlayPosition(LONG a, LONG b)
{
	logf(this, "myIDDrawSurface1::SetOverlayPosition");
	return m_pIDDrawSurface->SetOverlayPosition(a,b);
}



HRESULT  __stdcall myIDDrawSurface1::SetPalette(LPDIRECTDRAWPALETTE a)
{
	logf(this, "myIDDrawSurface1::SetPalette(%08x)",a);
	if (a) a = ((myIDDrawPalette*)a)->m_pIDDrawPalette;
	return m_pIDDrawSurface->SetPalette(a);
}



HRESULT  __stdcall myIDDrawSurface1::Unlock(LPVOID a)
{
	logf(this, "myIDDrawSurface1::Unlock(%08x)",a);
	return m_pIDDrawSurface->Unlock(a);
}



HRESULT  __stdcall myIDDrawSurface1::UpdateOverlay(LPRECT a, LPDIRECTDRAWSURFACE b,LPRECT c,DWORD d, LPDDOVERLAYFX e)
{
	logf(this, "myIDDrawSurface1::UpdateOverlay");
	return m_pIDDrawSurface->UpdateOverlay(a,((myIDDrawSurface1*)b)->m_pIDDrawSurface,c,d,e);
}



HRESULT  __stdcall myIDDrawSurface1::UpdateOverlayDisplay(DWORD a)
{
	logf(this, "myIDDrawSurface1::UpdateOverlayDisplay");
	return m_pIDDrawSurface->UpdateOverlayDisplay(a);
}



HRESULT  __stdcall myIDDrawSurface1::UpdateOverlayZOrder(DWORD a, LPDIRECTDRAWSURFACE b)
{
	logf(this, "myIDDrawSurface1::UpdateOverlayZOrder");
	return m_pIDDrawSurface->UpdateOverlayZOrder(a,((myIDDrawSurface1*)b)->m_pIDDrawSurface);
}

