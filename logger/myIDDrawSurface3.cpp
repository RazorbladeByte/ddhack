#include "StdAfx.h"
#include <varargs.h>



myIDDrawSurface3::myIDDrawSurface3(LPDIRECTDRAWSURFACE3 pOriginal)
{
	logf(this, "myIDDrawSurface3 Constructor");
	m_pIDDrawSurface = pOriginal;
}


myIDDrawSurface3::~myIDDrawSurface3(void)
{
	logf(this, "myIDDrawSurface3 Destructor");
}


HRESULT __stdcall myIDDrawSurface3::QueryInterface (REFIID, LPVOID FAR * b)
{
	logf(this, "myIDDrawSurface3::QueryInterface");
	
	*b = NULL;

	return E_NOTIMPL;
}


ULONG   __stdcall myIDDrawSurface3::AddRef(void)
{
	logf(this, "myIDDrawSurface3::AddRef");
	return(m_pIDDrawSurface->AddRef());
}


ULONG   __stdcall myIDDrawSurface3::Release(void)
{
	logf(this, "myIDDrawSurface3::Release");
	
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



HRESULT  __stdcall myIDDrawSurface3::AddAttachedSurface(LPDIRECTDRAWSURFACE3 a)
{
	logf(this, "myIDDrawSurface3::AddAttachedSurface");
	return m_pIDDrawSurface->AddAttachedSurface(((myIDDrawSurface3*)a)->m_pIDDrawSurface);
}



HRESULT  __stdcall myIDDrawSurface3::AddOverlayDirtyRect(LPRECT a)
{
	logf(this, "myIDDrawSurface3::AddOverlayDirtyRect");
	return m_pIDDrawSurface->AddOverlayDirtyRect(a);
}



HRESULT  __stdcall myIDDrawSurface3::Blt(LPRECT a,LPDIRECTDRAWSURFACE3 b, LPRECT c,DWORD d, LPDDBLTFX e)
{
	if (a && c)
		logf(this, "myIDDrawSurface3::Blt([%d,%d,%d,%d],%08x,[%d,%d,%d,%d],%d,%08x)",
			a->top,a->left,a->bottom,a->right,
			b,
			c->top,c->left,c->bottom,c->right,
			d,
			e->dwDDFX);
	else
	if (a)
		logf(this, "myIDDrawSurface3::Blt([%d,%d,%d,%d],%08x,[null],%d,%08x)",
			a->top,a->left,a->bottom,a->right,
			b,
			d,
			e->dwDDFX);
	else
	if (c)
		logf(this, "myIDDrawSurface3::Blt([null],%08x,[%d,%d,%d,%d],%d,%08x)",
			b,
			c->top,c->left,c->bottom,c->right,
			d,
			e->dwDDFX);
	else
		logf(this, "myIDDrawSurface3::Blt([null],%08x,[null],%d,%08x)",
			b,
			d,
			e->dwDDFX);
	if (b) b = ((myIDDrawSurface3*)b)->m_pIDDrawSurface;
	return m_pIDDrawSurface->Blt(a,b,c,d,e);
}



HRESULT  __stdcall myIDDrawSurface3::BltBatch(LPDDBLTBATCH a, DWORD b, DWORD c)
{
	logf(this, "myIDDrawSurface3::BltBatch");
	return m_pIDDrawSurface->BltBatch(a,b,c);
}



HRESULT  __stdcall myIDDrawSurface3::BltFast(DWORD a,DWORD b,LPDIRECTDRAWSURFACE3 c, LPRECT d,DWORD e)
{
	logf(this, "myIDDrawSurface3::BltFast");
	return m_pIDDrawSurface->BltFast(a,b,((myIDDrawSurface3*)c)->m_pIDDrawSurface,d,e);
}



HRESULT  __stdcall myIDDrawSurface3::DeleteAttachedSurface(DWORD a,LPDIRECTDRAWSURFACE3 b)
{
	logf(this, "myIDDrawSurface3::DeleteAttachedSurface");
	return m_pIDDrawSurface->DeleteAttachedSurface(a,((myIDDrawSurface3*)b)->m_pIDDrawSurface);
}



HRESULT  __stdcall myIDDrawSurface3::EnumAttachedSurfaces(LPVOID a,LPDDENUMSURFACESCALLBACK b)
{
	logf(this, "myIDDrawSurface3::EnumAttachedSurfaces");
	return m_pIDDrawSurface->EnumAttachedSurfaces(a,b);
}



HRESULT  __stdcall myIDDrawSurface3::EnumOverlayZOrders(DWORD a,LPVOID b,LPDDENUMSURFACESCALLBACK c)
{
	logf(this, "myIDDrawSurface3::EnumOverlayZOrders");
	return m_pIDDrawSurface->EnumOverlayZOrders(a,b,c);
}



HRESULT  __stdcall myIDDrawSurface3::Flip(LPDIRECTDRAWSURFACE3 a, DWORD b)
{
	logf(this, "myIDDrawSurface3::Flip(%08x,%d)", a, b);
	if (a) a = ((myIDDrawSurface3*)a)->m_pIDDrawSurface;
	return m_pIDDrawSurface->Flip(a,b);
}



HRESULT  __stdcall myIDDrawSurface3::GetAttachedSurface(LPDDSCAPS a, LPDIRECTDRAWSURFACE3 FAR * b)
{
	HRESULT r = m_pIDDrawSurface->GetAttachedSurface(a,b);
    *b = new myIDDrawSurface3(*b);

	logf(this, "myIDDrawSurface3::GetAttachedSurface([%d], %08x) return %d",
		a->dwCaps, b, r);
	
	return r;
}



HRESULT  __stdcall myIDDrawSurface3::GetBltStatus(DWORD a)
{
	logf(this, "myIDDrawSurface3::GetBltStatus");
	return m_pIDDrawSurface->GetBltStatus(a);
}



HRESULT  __stdcall myIDDrawSurface3::GetCaps(LPDDSCAPS a)
{
	logf(this, "myIDDrawSurface3::GetCaps");
	return m_pIDDrawSurface->GetCaps(a);
}



HRESULT  __stdcall myIDDrawSurface3::GetClipper(LPDIRECTDRAWCLIPPER FAR* a)
{
	logf(this, "myIDDrawSurface3::GetClipper");
	return m_pIDDrawSurface->GetClipper(a);
}



HRESULT  __stdcall myIDDrawSurface3::GetColorKey(DWORD a, LPDDCOLORKEY b)
{
	logf(this, "myIDDrawSurface3::GetColorKey");
	return m_pIDDrawSurface->GetColorKey(a,b);
}



HRESULT  __stdcall myIDDrawSurface3::GetDC(HDC FAR *a)
{
	logf(this, "myIDDrawSurface3::GetDC");
	return m_pIDDrawSurface->GetDC(a);
}



HRESULT  __stdcall myIDDrawSurface3::GetFlipStatus(DWORD a)
{
	logf(this, "myIDDrawSurface3::GetFlipStatus");
	return m_pIDDrawSurface->GetFlipStatus(a);
}



HRESULT  __stdcall myIDDrawSurface3::GetOverlayPosition(LPLONG a, LPLONG b)
{
	logf(this, "myIDDrawSurface3::GetOverlayPosition");
	return m_pIDDrawSurface->GetOverlayPosition(a,b);
}



HRESULT  __stdcall myIDDrawSurface3::GetPalette(LPDIRECTDRAWPALETTE FAR*a)
{
	logf(this, "myIDDrawSurface3::GetPalette");
	return m_pIDDrawSurface->GetPalette(a);
}



HRESULT  __stdcall myIDDrawSurface3::GetPixelFormat(LPDDPIXELFORMAT a)
{
	logf(this, "myIDDrawSurface3::GetPixelFormat");
	return m_pIDDrawSurface->GetPixelFormat(a);
}



HRESULT  __stdcall myIDDrawSurface3::GetSurfaceDesc(LPDDSURFACEDESC a)
{
	HRESULT r = m_pIDDrawSurface->GetSurfaceDesc(a);
	logf(this, "myIDDrawSurface3::GetSurfaceDesc([%x %x %x %x %x %x %x %x %x [%x %x %x %x %x %x %x %x] %x]) return %d",
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



HRESULT  __stdcall myIDDrawSurface3::Initialize(LPDIRECTDRAW a, LPDDSURFACEDESC b)
{
	logf(this, "myIDDrawSurface3::Initialize");
	return m_pIDDrawSurface->Initialize(a,b);
}



HRESULT  __stdcall myIDDrawSurface3::IsLost()
{
	logf(this, "myIDDrawSurface3::IsLost");
	return m_pIDDrawSurface->IsLost();
}



HRESULT  __stdcall myIDDrawSurface3::Lock(LPRECT a,LPDDSURFACEDESC b,DWORD c,HANDLE d)
{
	if (a)	
		logf(this, "myIDDrawSurface3::Lock([%d,%d,%d,%d],%08x,%d,%d)",a->top,a->left,a->bottom,a->right,b,c,d);
	else
		logf(this, "myIDDrawSurface3::Lock([null],%08x,%d,%d)",b,c,d);
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



HRESULT  __stdcall myIDDrawSurface3::ReleaseDC(HDC a)
{
	logf(this, "myIDDrawSurface3::ReleaseDC");
	return m_pIDDrawSurface->ReleaseDC(a);
}



HRESULT  __stdcall myIDDrawSurface3::Restore()
{
	logf(this, "myIDDrawSurface3::Restore");
	return m_pIDDrawSurface->Restore();
}



HRESULT  __stdcall myIDDrawSurface3::SetClipper(LPDIRECTDRAWCLIPPER a)
{
	logf(this, "myIDDrawSurface3::SetClipper");
	return m_pIDDrawSurface->SetClipper(a);
}



HRESULT  __stdcall myIDDrawSurface3::SetColorKey(DWORD a, LPDDCOLORKEY b)
{
	logf(this, "myIDDrawSurface3::SetColorKey");
	return m_pIDDrawSurface->SetColorKey(a,b);
}



HRESULT  __stdcall myIDDrawSurface3::SetOverlayPosition(LONG a, LONG b)
{
	logf(this, "myIDDrawSurface3::SetOverlayPosition");
	return m_pIDDrawSurface->SetOverlayPosition(a,b);
}



HRESULT  __stdcall myIDDrawSurface3::SetPalette(LPDIRECTDRAWPALETTE a)
{
	logf(this, "myIDDrawSurface3::SetPalette(%08x)",a);
	if (a) a = ((myIDDrawPalette*)a)->m_pIDDrawPalette;
	return m_pIDDrawSurface->SetPalette(a);
}



HRESULT  __stdcall myIDDrawSurface3::Unlock(LPVOID a)
{
	logf(this, "myIDDrawSurface3::Unlock(%08x)",a);
	return m_pIDDrawSurface->Unlock(a);
}



HRESULT  __stdcall myIDDrawSurface3::UpdateOverlay(LPRECT a, LPDIRECTDRAWSURFACE3 b,LPRECT c,DWORD d, LPDDOVERLAYFX e)
{
	logf(this, "myIDDrawSurface3::UpdateOverlay");
	return m_pIDDrawSurface->UpdateOverlay(a,((myIDDrawSurface3*)b)->m_pIDDrawSurface,c,d,e);
}



HRESULT  __stdcall myIDDrawSurface3::UpdateOverlayDisplay(DWORD a)
{
	logf(this, "myIDDrawSurface3::UpdateOverlayDisplay");
	return m_pIDDrawSurface->UpdateOverlayDisplay(a);
}



HRESULT  __stdcall myIDDrawSurface3::UpdateOverlayZOrder(DWORD a, LPDIRECTDRAWSURFACE3 b)
{
	logf(this, "myIDDrawSurface3::UpdateOverlayZOrder");
	return m_pIDDrawSurface->UpdateOverlayZOrder(a,((myIDDrawSurface3*)b)->m_pIDDrawSurface);
}


HRESULT  __stdcall  myIDDrawSurface3::GetDDInterface(LPVOID FAR * a)
{
	logf(this, "myIDDrawSurface3::GetDDInterface");
	return m_pIDDrawSurface->GetDDInterface(a);

}

HRESULT  __stdcall  myIDDrawSurface3::PageLock(DWORD a)
{
	logf(this, "myIDDrawSurface3::PageLock");
	return m_pIDDrawSurface->PageLock(a);

}

HRESULT  __stdcall  myIDDrawSurface3::PageUnlock(DWORD a)
{
	logf(this, "myIDDrawSurface3::PageUnlock");
	return m_pIDDrawSurface->PageUnlock(a);
}

HRESULT  __stdcall myIDDrawSurface3::SetSurfaceDesc(LPDDSURFACEDESC a, DWORD b)
{
	logf(this, "myIDDrawSurface3::SetSurfaceDesc");
	return m_pIDDrawSurface->SetSurfaceDesc(a, b);

}