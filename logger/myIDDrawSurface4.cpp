#include "StdAfx.h"
#include <varargs.h>



myIDDrawSurface4::myIDDrawSurface4(LPDIRECTDRAWSURFACE4 pOriginal)
{
	logf(this, "myIDDrawSurface4 Constructor");
	m_pIDDrawSurface = pOriginal;
}


myIDDrawSurface4::~myIDDrawSurface4(void)
{
	logf(this, "myIDDrawSurface4 Destructor");
}


HRESULT __stdcall myIDDrawSurface4::QueryInterface (REFIID, LPVOID FAR * b)
{
	logf(this, "myIDDrawSurface4::QueryInterface");
	
	*b = NULL;

	return E_NOTIMPL;
}


ULONG   __stdcall myIDDrawSurface4::AddRef(void)
{
	logf(this, "myIDDrawSurface4::AddRef");
	return(m_pIDDrawSurface->AddRef());
}


ULONG   __stdcall myIDDrawSurface4::Release(void)
{
	logf(this, "myIDDrawSurface4::Release");
	
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



HRESULT  __stdcall myIDDrawSurface4::AddAttachedSurface(LPDIRECTDRAWSURFACE4 a)
{
	logf(this, "myIDDrawSurface4::AddAttachedSurface");
	return m_pIDDrawSurface->AddAttachedSurface(((myIDDrawSurface4*)a)->m_pIDDrawSurface);
}



HRESULT  __stdcall myIDDrawSurface4::AddOverlayDirtyRect(LPRECT a)
{
	logf(this, "myIDDrawSurface4::AddOverlayDirtyRect");
	return m_pIDDrawSurface->AddOverlayDirtyRect(a);
}



HRESULT  __stdcall myIDDrawSurface4::Blt(LPRECT a,LPDIRECTDRAWSURFACE4 b, LPRECT c,DWORD d, LPDDBLTFX e)
{
	if (a && c)
		logf(this, "myIDDrawSurface4::Blt([%d,%d,%d,%d],%08x,[%d,%d,%d,%d],%d,%08x)",
			a->top,a->left,a->bottom,a->right,
			b,
			c->top,c->left,c->bottom,c->right,
			d,
			e->dwDDFX);
	else
	if (a)
		logf(this, "myIDDrawSurface4::Blt([%d,%d,%d,%d],%08x,[null],%d,%08x)",
			a->top,a->left,a->bottom,a->right,
			b,
			d,
			e->dwDDFX);
	else
	if (c)
		logf(this, "myIDDrawSurface4::Blt([null],%08x,[%d,%d,%d,%d],%d,%08x)",
			b,
			c->top,c->left,c->bottom,c->right,
			d,
			e->dwDDFX);
	else
		logf(this, "myIDDrawSurface4::Blt([null],%08x,[null],%d,%08x)",
			b,
			d,
			e->dwDDFX);
	if (b) b = ((myIDDrawSurface4*)b)->m_pIDDrawSurface;
	return m_pIDDrawSurface->Blt(a,b,c,d,e);
}



HRESULT  __stdcall myIDDrawSurface4::BltBatch(LPDDBLTBATCH a, DWORD b, DWORD c)
{
	logf(this, "myIDDrawSurface4::BltBatch");
	return m_pIDDrawSurface->BltBatch(a,b,c);
}



HRESULT  __stdcall myIDDrawSurface4::BltFast(DWORD a,DWORD b,LPDIRECTDRAWSURFACE4 c, LPRECT d,DWORD e)
{
	logf(this, "myIDDrawSurface4::BltFast");
	return m_pIDDrawSurface->BltFast(a,b,((myIDDrawSurface4*)c)->m_pIDDrawSurface,d,e);
}



HRESULT  __stdcall myIDDrawSurface4::DeleteAttachedSurface(DWORD a,LPDIRECTDRAWSURFACE4 b)
{
	logf(this, "myIDDrawSurface4::DeleteAttachedSurface");
	return m_pIDDrawSurface->DeleteAttachedSurface(a,((myIDDrawSurface4*)b)->m_pIDDrawSurface);
}



HRESULT  __stdcall myIDDrawSurface4::EnumAttachedSurfaces(LPVOID a,LPDDENUMSURFACESCALLBACK2 b)
{
	logf(this, "myIDDrawSurface4::EnumAttachedSurfaces");
	return m_pIDDrawSurface->EnumAttachedSurfaces(a,b);
}



HRESULT  __stdcall myIDDrawSurface4::EnumOverlayZOrders(DWORD a,LPVOID b,LPDDENUMSURFACESCALLBACK2 c)
{
	logf(this, "myIDDrawSurface4::EnumOverlayZOrders");
	return m_pIDDrawSurface->EnumOverlayZOrders(a,b,c);
}



HRESULT  __stdcall myIDDrawSurface4::Flip(LPDIRECTDRAWSURFACE4 a, DWORD b)
{
	logf(this, "myIDDrawSurface4::Flip(%08x,%d)", a, b);
	if (a) a = ((myIDDrawSurface4*)a)->m_pIDDrawSurface;
	return m_pIDDrawSurface->Flip(a,b);
}



HRESULT  __stdcall myIDDrawSurface4::GetAttachedSurface(LPDDSCAPS2 a, LPDIRECTDRAWSURFACE4 FAR * b)
{
	HRESULT r = m_pIDDrawSurface->GetAttachedSurface(a,b);
    *b = new myIDDrawSurface4(*b);

	logf(this, "myIDDrawSurface4::GetAttachedSurface([%d], %08x) return %d",
		a->dwCaps, b, r);
	
	return r;
}



HRESULT  __stdcall myIDDrawSurface4::GetBltStatus(DWORD a)
{
	logf(this, "myIDDrawSurface4::GetBltStatus");
	return m_pIDDrawSurface->GetBltStatus(a);
}



HRESULT  __stdcall myIDDrawSurface4::GetCaps(LPDDSCAPS2 a)
{
	logf(this, "myIDDrawSurface4::GetCaps");
	return m_pIDDrawSurface->GetCaps(a);
}



HRESULT  __stdcall myIDDrawSurface4::GetClipper(LPDIRECTDRAWCLIPPER FAR* a)
{
	logf(this, "myIDDrawSurface4::GetClipper");
	return m_pIDDrawSurface->GetClipper(a);
}



HRESULT  __stdcall myIDDrawSurface4::GetColorKey(DWORD a, LPDDCOLORKEY b)
{
	logf(this, "myIDDrawSurface4::GetColorKey");
	return m_pIDDrawSurface->GetColorKey(a,b);
}



HRESULT  __stdcall myIDDrawSurface4::GetDC(HDC FAR *a)
{
	logf(this, "myIDDrawSurface4::GetDC");
	return m_pIDDrawSurface->GetDC(a);
}



HRESULT  __stdcall myIDDrawSurface4::GetFlipStatus(DWORD a)
{
	logf(this, "myIDDrawSurface4::GetFlipStatus");
	return m_pIDDrawSurface->GetFlipStatus(a);
}



HRESULT  __stdcall myIDDrawSurface4::GetOverlayPosition(LPLONG a, LPLONG b)
{
	logf(this, "myIDDrawSurface4::GetOverlayPosition");
	return m_pIDDrawSurface->GetOverlayPosition(a,b);
}



HRESULT  __stdcall myIDDrawSurface4::GetPalette(LPDIRECTDRAWPALETTE FAR*a)
{
	logf(this, "myIDDrawSurface4::GetPalette");
	return m_pIDDrawSurface->GetPalette(a);
}



HRESULT  __stdcall myIDDrawSurface4::GetPixelFormat(LPDDPIXELFORMAT a)
{
	logf(this, "myIDDrawSurface4::GetPixelFormat");
	return m_pIDDrawSurface->GetPixelFormat(a);
}



HRESULT  __stdcall myIDDrawSurface4::GetSurfaceDesc(LPDDSURFACEDESC2 a)
{
	HRESULT r = m_pIDDrawSurface->GetSurfaceDesc(a);
	logf(this, "myIDDrawSurface4::GetSurfaceDesc([%x %x %x %x %x %x %x %x %x [%x %x %x %x %x %x %x %x] %x]) return %d",
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



HRESULT  __stdcall myIDDrawSurface4::Initialize(LPDIRECTDRAW a, LPDDSURFACEDESC2 b)
{
	logf(this, "myIDDrawSurface4::Initialize");
	return m_pIDDrawSurface->Initialize(a,b);
}



HRESULT  __stdcall myIDDrawSurface4::IsLost()
{
	logf(this, "myIDDrawSurface4::IsLost");
	return m_pIDDrawSurface->IsLost();
}



HRESULT  __stdcall myIDDrawSurface4::Lock(LPRECT a,LPDDSURFACEDESC2 b,DWORD c,HANDLE d)
{
	if (a)	
		logf(this, "myIDDrawSurface4::Lock([%d,%d,%d,%d],%08x,%d,%d)",a->top,a->left,a->bottom,a->right,b,c,d);
	else
		logf(this, "myIDDrawSurface4::Lock([null],%08x,%d,%d)",b,c,d);
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



HRESULT  __stdcall myIDDrawSurface4::ReleaseDC(HDC a)
{
	logf(this, "myIDDrawSurface4::ReleaseDC");
	return m_pIDDrawSurface->ReleaseDC(a);
}



HRESULT  __stdcall myIDDrawSurface4::Restore()
{
	logf(this, "myIDDrawSurface4::Restore");
	return m_pIDDrawSurface->Restore();
}



HRESULT  __stdcall myIDDrawSurface4::SetClipper(LPDIRECTDRAWCLIPPER a)
{
	logf(this, "myIDDrawSurface4::SetClipper");
	return m_pIDDrawSurface->SetClipper(a);
}



HRESULT  __stdcall myIDDrawSurface4::SetColorKey(DWORD a, LPDDCOLORKEY b)
{
	logf(this, "myIDDrawSurface4::SetColorKey");
	return m_pIDDrawSurface->SetColorKey(a,b);
}



HRESULT  __stdcall myIDDrawSurface4::SetOverlayPosition(LONG a, LONG b)
{
	logf(this, "myIDDrawSurface4::SetOverlayPosition");
	return m_pIDDrawSurface->SetOverlayPosition(a,b);
}



HRESULT  __stdcall myIDDrawSurface4::SetPalette(LPDIRECTDRAWPALETTE a)
{
	logf(this, "myIDDrawSurface4::SetPalette(%08x)",a);
	if (a) a = ((myIDDrawPalette*)a)->m_pIDDrawPalette;
	return m_pIDDrawSurface->SetPalette(a);
}



HRESULT  __stdcall myIDDrawSurface4::Unlock(LPRECT a)
{
	logf(this, "myIDDrawSurface4::Unlock(%08x)",a);
	return m_pIDDrawSurface->Unlock(a);
}



HRESULT  __stdcall myIDDrawSurface4::UpdateOverlay(LPRECT a, LPDIRECTDRAWSURFACE4 b,LPRECT c,DWORD d, LPDDOVERLAYFX e)
{
	logf(this, "myIDDrawSurface4::UpdateOverlay");
	return m_pIDDrawSurface->UpdateOverlay(a,((myIDDrawSurface4*)b)->m_pIDDrawSurface,c,d,e);
}



HRESULT  __stdcall myIDDrawSurface4::UpdateOverlayDisplay(DWORD a)
{
	logf(this, "myIDDrawSurface4::UpdateOverlayDisplay");
	return m_pIDDrawSurface->UpdateOverlayDisplay(a);
}



HRESULT  __stdcall myIDDrawSurface4::UpdateOverlayZOrder(DWORD a, LPDIRECTDRAWSURFACE4 b)
{
	logf(this, "myIDDrawSurface4::UpdateOverlayZOrder");
	return m_pIDDrawSurface->UpdateOverlayZOrder(a,((myIDDrawSurface4*)b)->m_pIDDrawSurface);
}

HRESULT  __stdcall  myIDDrawSurface4::GetDDInterface(LPVOID FAR * a)
{
	logf(this, "myIDDrawSurface4::GetDDInterface");
	return m_pIDDrawSurface->GetDDInterface(a);

}

HRESULT  __stdcall  myIDDrawSurface4::PageLock(DWORD a)
{
	logf(this, "myIDDrawSurface4::PageLock");
	return m_pIDDrawSurface->PageLock(a);

}

HRESULT  __stdcall  myIDDrawSurface4::PageUnlock(DWORD a)
{
	logf(this, "myIDDrawSurface4::PageUnlock");
	return m_pIDDrawSurface->PageUnlock(a);
}

HRESULT  __stdcall myIDDrawSurface4::SetSurfaceDesc(LPDDSURFACEDESC2 a, DWORD b)
{
	logf(this, "myIDDrawSurface4::SetSurfaceDesc");
	return m_pIDDrawSurface->SetSurfaceDesc(a, b);

}

HRESULT  __stdcall myIDDrawSurface4::SetPrivateData(REFGUID a, LPVOID  b, DWORD c, DWORD d)
{
	logf(this, "myIDDrawSurface4::SetPrivateData");
	return m_pIDDrawSurface->SetPrivateData(a, b,c, d);
}

HRESULT  __stdcall myIDDrawSurface4::GetPrivateData(REFGUID a, LPVOID  b, LPDWORD c)
{
	logf(this, "myIDDrawSurface4::GetPrivateData");
	return m_pIDDrawSurface->GetPrivateData( a,  b,  c);
}

HRESULT  __stdcall myIDDrawSurface4::FreePrivateData(REFGUID a)
{
	logf(this, "myIDDrawSurface4::FreePrivateData");
	return m_pIDDrawSurface->FreePrivateData(a);
}

HRESULT  __stdcall myIDDrawSurface4::GetUniquenessValue(LPDWORD a)
{
	logf(this, "myIDDrawSurface4::GetUniquenessValue");
	return m_pIDDrawSurface->GetUniquenessValue(a);
}

HRESULT  __stdcall myIDDrawSurface4::ChangeUniquenessValue()
{
	logf(this, "myIDDrawSurface4::ChangeUniquenessValue");
	return m_pIDDrawSurface->ChangeUniquenessValue();
}

