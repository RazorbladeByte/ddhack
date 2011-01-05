#include "StdAfx.h"
#include <varargs.h>



myIDDrawSurface2::myIDDrawSurface2(LPDIRECTDRAWSURFACE2 pOriginal)
{
	logf(this, "myIDDrawSurface2 Constructor");
	m_pIDDrawSurface = pOriginal;
}


myIDDrawSurface2::~myIDDrawSurface2(void)
{
	logf(this, "myIDDrawSurface2 Destructor");
}


HRESULT __stdcall myIDDrawSurface2::QueryInterface (REFIID, LPVOID FAR * b)
{
	logf(this, "myIDDrawSurface2::QueryInterface");
	
	*b = NULL;

	return E_NOTIMPL;
}


ULONG   __stdcall myIDDrawSurface2::AddRef(void)
{
	logf(this, "myIDDrawSurface2::AddRef");
	return(m_pIDDrawSurface->AddRef());
}


ULONG   __stdcall myIDDrawSurface2::Release(void)
{
	logf(this, "myIDDrawSurface2::Release");
	
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



HRESULT  __stdcall myIDDrawSurface2::AddAttachedSurface(LPDIRECTDRAWSURFACE2 a)
{
	logf(this, "myIDDrawSurface2::AddAttachedSurface");
	return m_pIDDrawSurface->AddAttachedSurface(((myIDDrawSurface2*)a)->m_pIDDrawSurface);
}



HRESULT  __stdcall myIDDrawSurface2::AddOverlayDirtyRect(LPRECT a)
{
	logf(this, "myIDDrawSurface2::AddOverlayDirtyRect");
	return m_pIDDrawSurface->AddOverlayDirtyRect(a);
}



HRESULT  __stdcall myIDDrawSurface2::Blt(LPRECT a,LPDIRECTDRAWSURFACE2 b, LPRECT c,DWORD d, LPDDBLTFX e)
{
	if (a && c)
		logf(this, "myIDDrawSurface2::Blt([%d,%d,%d,%d],%08x,[%d,%d,%d,%d],%d,%08x)",
			a->top,a->left,a->bottom,a->right,
			b,
			c->top,c->left,c->bottom,c->right,
			d,
			e->dwDDFX);
	else
	if (a)
		logf(this, "myIDDrawSurface2::Blt([%d,%d,%d,%d],%08x,[null],%d,%08x)",
			a->top,a->left,a->bottom,a->right,
			b,
			d,
			e->dwDDFX);
	else
	if (c)
		logf(this, "myIDDrawSurface2::Blt([null],%08x,[%d,%d,%d,%d],%d,%08x)",
			b,
			c->top,c->left,c->bottom,c->right,
			d,
			e->dwDDFX);
	else
		logf(this, "myIDDrawSurface2::Blt([null],%08x,[null],%d,%08x)",
			b,
			d,
			e->dwDDFX);
	if (b) b = ((myIDDrawSurface2*)b)->m_pIDDrawSurface;
	return m_pIDDrawSurface->Blt(a,b,c,d,e);
}



HRESULT  __stdcall myIDDrawSurface2::BltBatch(LPDDBLTBATCH a, DWORD b, DWORD c)
{
	logf(this, "myIDDrawSurface2::BltBatch");
	return m_pIDDrawSurface->BltBatch(a,b,c);
}



HRESULT  __stdcall myIDDrawSurface2::BltFast(DWORD a,DWORD b,LPDIRECTDRAWSURFACE2 c, LPRECT d,DWORD e)
{
	logf(this, "myIDDrawSurface2::BltFast");
	return m_pIDDrawSurface->BltFast(a,b,((myIDDrawSurface2*)c)->m_pIDDrawSurface,d,e);
}



HRESULT  __stdcall myIDDrawSurface2::DeleteAttachedSurface(DWORD a,LPDIRECTDRAWSURFACE2 b)
{
	logf(this, "myIDDrawSurface2::DeleteAttachedSurface");
	return m_pIDDrawSurface->DeleteAttachedSurface(a,((myIDDrawSurface2*)b)->m_pIDDrawSurface);
}



HRESULT  __stdcall myIDDrawSurface2::EnumAttachedSurfaces(LPVOID a,LPDDENUMSURFACESCALLBACK b)
{
	logf(this, "myIDDrawSurface2::EnumAttachedSurfaces");
	return m_pIDDrawSurface->EnumAttachedSurfaces(a,b);
}



HRESULT  __stdcall myIDDrawSurface2::EnumOverlayZOrders(DWORD a,LPVOID b,LPDDENUMSURFACESCALLBACK c)
{
	logf(this, "myIDDrawSurface2::EnumOverlayZOrders");
	return m_pIDDrawSurface->EnumOverlayZOrders(a,b,c);
}



HRESULT  __stdcall myIDDrawSurface2::Flip(LPDIRECTDRAWSURFACE2 a, DWORD b)
{
	logf(this, "myIDDrawSurface2::Flip(%08x,%d)", a, b);
	if (a) a = ((myIDDrawSurface2*)a)->m_pIDDrawSurface;
	return m_pIDDrawSurface->Flip(a,b);
}



HRESULT  __stdcall myIDDrawSurface2::GetAttachedSurface(LPDDSCAPS a, LPDIRECTDRAWSURFACE2 FAR * b)
{
	HRESULT r = m_pIDDrawSurface->GetAttachedSurface(a,b);
    *b = new myIDDrawSurface2(*b);

	logf(this, "myIDDrawSurface2::GetAttachedSurface([%d], %08x) return %d",
		a->dwCaps, b, r);
	
	return r;
}



HRESULT  __stdcall myIDDrawSurface2::GetBltStatus(DWORD a)
{
	logf(this, "myIDDrawSurface2::GetBltStatus");
	return m_pIDDrawSurface->GetBltStatus(a);
}



HRESULT  __stdcall myIDDrawSurface2::GetCaps(LPDDSCAPS a)
{
	logf(this, "myIDDrawSurface2::GetCaps");
	return m_pIDDrawSurface->GetCaps(a);
}



HRESULT  __stdcall myIDDrawSurface2::GetClipper(LPDIRECTDRAWCLIPPER FAR* a)
{
	logf(this, "myIDDrawSurface2::GetClipper");
	return m_pIDDrawSurface->GetClipper(a);
}



HRESULT  __stdcall myIDDrawSurface2::GetColorKey(DWORD a, LPDDCOLORKEY b)
{
	logf(this, "myIDDrawSurface2::GetColorKey");
	return m_pIDDrawSurface->GetColorKey(a,b);
}



HRESULT  __stdcall myIDDrawSurface2::GetDC(HDC FAR *a)
{
	logf(this, "myIDDrawSurface2::GetDC");
	return m_pIDDrawSurface->GetDC(a);
}



HRESULT  __stdcall myIDDrawSurface2::GetFlipStatus(DWORD a)
{
	logf(this, "myIDDrawSurface2::GetFlipStatus");
	return m_pIDDrawSurface->GetFlipStatus(a);
}



HRESULT  __stdcall myIDDrawSurface2::GetOverlayPosition(LPLONG a, LPLONG b)
{
	logf(this, "myIDDrawSurface2::GetOverlayPosition");
	return m_pIDDrawSurface->GetOverlayPosition(a,b);
}



HRESULT  __stdcall myIDDrawSurface2::GetPalette(LPDIRECTDRAWPALETTE FAR*a)
{
	logf(this, "myIDDrawSurface2::GetPalette");
	return m_pIDDrawSurface->GetPalette(a);
}



HRESULT  __stdcall myIDDrawSurface2::GetPixelFormat(LPDDPIXELFORMAT a)
{
	logf(this, "myIDDrawSurface2::GetPixelFormat");
	return m_pIDDrawSurface->GetPixelFormat(a);
}



HRESULT  __stdcall myIDDrawSurface2::GetSurfaceDesc(LPDDSURFACEDESC a)
{
	HRESULT r = m_pIDDrawSurface->GetSurfaceDesc(a);
	logf(this, "myIDDrawSurface2::GetSurfaceDesc([%x %x %x %x %x %x %x %x %x [%x %x %x %x %x %x %x %x] %x]) return %d",
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



HRESULT  __stdcall myIDDrawSurface2::Initialize(LPDIRECTDRAW a, LPDDSURFACEDESC b)
{
	logf(this, "myIDDrawSurface2::Initialize");
	return m_pIDDrawSurface->Initialize(a,b);
}



HRESULT  __stdcall myIDDrawSurface2::IsLost()
{
	logf(this, "myIDDrawSurface2::IsLost");
	return m_pIDDrawSurface->IsLost();
}



HRESULT  __stdcall myIDDrawSurface2::Lock(LPRECT a,LPDDSURFACEDESC b,DWORD c,HANDLE d)
{
	if (a)	
		logf(this, "myIDDrawSurface2::Lock([%d,%d,%d,%d],%08x,%d,%d)",a->top,a->left,a->bottom,a->right,b,c,d);
	else
		logf(this, "myIDDrawSurface2::Lock([null],%08x,%d,%d)",b,c,d);
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



HRESULT  __stdcall myIDDrawSurface2::ReleaseDC(HDC a)
{
	logf(this, "myIDDrawSurface2::ReleaseDC");
	return m_pIDDrawSurface->ReleaseDC(a);
}



HRESULT  __stdcall myIDDrawSurface2::Restore()
{
	logf(this, "myIDDrawSurface2::Restore");
	return m_pIDDrawSurface->Restore();
}



HRESULT  __stdcall myIDDrawSurface2::SetClipper(LPDIRECTDRAWCLIPPER a)
{
	logf(this, "myIDDrawSurface2::SetClipper");
	return m_pIDDrawSurface->SetClipper(a);
}



HRESULT  __stdcall myIDDrawSurface2::SetColorKey(DWORD a, LPDDCOLORKEY b)
{
	logf(this, "myIDDrawSurface2::SetColorKey");
	return m_pIDDrawSurface->SetColorKey(a,b);
}



HRESULT  __stdcall myIDDrawSurface2::SetOverlayPosition(LONG a, LONG b)
{
	logf(this, "myIDDrawSurface2::SetOverlayPosition");
	return m_pIDDrawSurface->SetOverlayPosition(a,b);
}



HRESULT  __stdcall myIDDrawSurface2::SetPalette(LPDIRECTDRAWPALETTE a)
{
	logf(this, "myIDDrawSurface2::SetPalette(%08x)",a);
	if (a) a = ((myIDDrawPalette*)a)->m_pIDDrawPalette;
	return m_pIDDrawSurface->SetPalette(a);
}



HRESULT  __stdcall myIDDrawSurface2::Unlock(LPVOID a)
{
	logf(this, "myIDDrawSurface2::Unlock(%08x)",a);
	return m_pIDDrawSurface->Unlock(a);
}



HRESULT  __stdcall myIDDrawSurface2::UpdateOverlay(LPRECT a, LPDIRECTDRAWSURFACE2 b,LPRECT c,DWORD d, LPDDOVERLAYFX e)
{
	logf(this, "myIDDrawSurface2::UpdateOverlay");
	return m_pIDDrawSurface->UpdateOverlay(a,((myIDDrawSurface2*)b)->m_pIDDrawSurface,c,d,e);
}



HRESULT  __stdcall myIDDrawSurface2::UpdateOverlayDisplay(DWORD a)
{
	logf(this, "myIDDrawSurface2::UpdateOverlayDisplay");
	return m_pIDDrawSurface->UpdateOverlayDisplay(a);
}



HRESULT  __stdcall myIDDrawSurface2::UpdateOverlayZOrder(DWORD a, LPDIRECTDRAWSURFACE2 b)
{
	logf(this, "myIDDrawSurface2::UpdateOverlayZOrder");
	return m_pIDDrawSurface->UpdateOverlayZOrder(a,((myIDDrawSurface2*)b)->m_pIDDrawSurface);
}


HRESULT  __stdcall  myIDDrawSurface2::GetDDInterface(LPVOID FAR * a)
{
	logf(this, "myIDDrawSurface2::GetDDInterface");
	return m_pIDDrawSurface->GetDDInterface(a);

}


HRESULT  __stdcall  myIDDrawSurface2::PageLock(DWORD a)
{
	logf(this, "myIDDrawSurface2::PageLock");
	return m_pIDDrawSurface->PageLock(a);

}

HRESULT  __stdcall  myIDDrawSurface2::PageUnlock(DWORD a)
{
	logf(this, "myIDDrawSurface2::PageUnlock");
	return m_pIDDrawSurface->PageUnlock(a);
}
