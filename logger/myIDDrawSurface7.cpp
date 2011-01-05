#include "StdAfx.h"
#include <varargs.h>



myIDDrawSurface7::myIDDrawSurface7(LPDIRECTDRAWSURFACE7 pOriginal)
{
	logf(this, "myIDDrawSurface7 Constructor");
	m_pIDDrawSurface = pOriginal;
}


myIDDrawSurface7::~myIDDrawSurface7(void)
{
	logf(this, "myIDDrawSurface7 Destructor");
}


HRESULT __stdcall myIDDrawSurface7::QueryInterface (REFIID, LPVOID FAR * b)
{
	logf(this, "myIDDrawSurface7::QueryInterface");
	
	*b = NULL;

	return E_NOTIMPL;
}


ULONG   __stdcall myIDDrawSurface7::AddRef(void)
{
	logf(this, "myIDDrawSurface7::AddRef");
	return(m_pIDDrawSurface->AddRef());
}


ULONG   __stdcall myIDDrawSurface7::Release(void)
{
	logf(this, "myIDDrawSurface7::Release");
	
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



HRESULT  __stdcall myIDDrawSurface7::AddAttachedSurface(LPDIRECTDRAWSURFACE7 a)
{
	logf(this, "myIDDrawSurface7::AddAttachedSurface");
	return m_pIDDrawSurface->AddAttachedSurface(((myIDDrawSurface7*)a)->m_pIDDrawSurface);
}



HRESULT  __stdcall myIDDrawSurface7::AddOverlayDirtyRect(LPRECT a)
{
	logf(this, "myIDDrawSurface7::AddOverlayDirtyRect");
	return m_pIDDrawSurface->AddOverlayDirtyRect(a);
}



HRESULT  __stdcall myIDDrawSurface7::Blt(LPRECT a,LPDIRECTDRAWSURFACE7 b, LPRECT c,DWORD d, LPDDBLTFX e)
{
	if (a && c)
		logf(this, "myIDDrawSurface7::Blt([%d,%d,%d,%d],%08x,[%d,%d,%d,%d],%d,%08x)",
			a->top,a->left,a->bottom,a->right,
			b,
			c->top,c->left,c->bottom,c->right,
			d,
			e->dwDDFX);
	else
	if (a)
		logf(this, "myIDDrawSurface7::Blt([%d,%d,%d,%d],%08x,[null],%d,%08x)",
			a->top,a->left,a->bottom,a->right,
			b,
			d,
			e->dwDDFX);
	else
	if (c)
		logf(this, "myIDDrawSurface7::Blt([null],%08x,[%d,%d,%d,%d],%d,%08x)",
			b,
			c->top,c->left,c->bottom,c->right,
			d,
			e->dwDDFX);
	else
		logf(this, "myIDDrawSurface7::Blt([null],%08x,[null],%d,%08x)",
			b,
			d,
			e->dwDDFX);
	if (b) b = ((myIDDrawSurface7*)b)->m_pIDDrawSurface;
	return m_pIDDrawSurface->Blt(a,b,c,d,e);
}



HRESULT  __stdcall myIDDrawSurface7::BltBatch(LPDDBLTBATCH a, DWORD b, DWORD c)
{
	logf(this, "myIDDrawSurface7::BltBatch");
	return m_pIDDrawSurface->BltBatch(a,b,c);
}



HRESULT  __stdcall myIDDrawSurface7::BltFast(DWORD a,DWORD b,LPDIRECTDRAWSURFACE7 c, LPRECT d,DWORD e)
{
	logf(this, "myIDDrawSurface7::BltFast");
	return m_pIDDrawSurface->BltFast(a,b,((myIDDrawSurface7*)c)->m_pIDDrawSurface,d,e);
}



HRESULT  __stdcall myIDDrawSurface7::DeleteAttachedSurface(DWORD a,LPDIRECTDRAWSURFACE7 b)
{
	logf(this, "myIDDrawSurface7::DeleteAttachedSurface");
	return m_pIDDrawSurface->DeleteAttachedSurface(a,((myIDDrawSurface7*)b)->m_pIDDrawSurface);
}



HRESULT  __stdcall myIDDrawSurface7::EnumAttachedSurfaces(LPVOID a,LPDDENUMSURFACESCALLBACK7 b)
{
	logf(this, "myIDDrawSurface7::EnumAttachedSurfaces");
	return m_pIDDrawSurface->EnumAttachedSurfaces(a,b);
}



HRESULT  __stdcall myIDDrawSurface7::EnumOverlayZOrders(DWORD a,LPVOID b,LPDDENUMSURFACESCALLBACK7 c)
{
	logf(this, "myIDDrawSurface7::EnumOverlayZOrders");
	return m_pIDDrawSurface->EnumOverlayZOrders(a,b,c);
}



HRESULT  __stdcall myIDDrawSurface7::Flip(LPDIRECTDRAWSURFACE7 a, DWORD b)
{
	logf(this, "myIDDrawSurface7::Flip(%08x,%d)", a, b);
	if (a) a = ((myIDDrawSurface7*)a)->m_pIDDrawSurface;
	return m_pIDDrawSurface->Flip(a,b);
}



HRESULT  __stdcall myIDDrawSurface7::GetAttachedSurface(LPDDSCAPS2 a, LPDIRECTDRAWSURFACE7 FAR * b)
{
	HRESULT r = m_pIDDrawSurface->GetAttachedSurface(a,b);
    *b = new myIDDrawSurface7(*b);

	logf(this, "myIDDrawSurface7::GetAttachedSurface([%d], %08x) return %d",
		a->dwCaps, b, r);
	
	return r;
}



HRESULT  __stdcall myIDDrawSurface7::GetBltStatus(DWORD a)
{
	logf(this, "myIDDrawSurface7::GetBltStatus");
	return m_pIDDrawSurface->GetBltStatus(a);
}



HRESULT  __stdcall myIDDrawSurface7::GetCaps(LPDDSCAPS2 a)
{
	logf(this, "myIDDrawSurface7::GetCaps");
	return m_pIDDrawSurface->GetCaps(a);
}



HRESULT  __stdcall myIDDrawSurface7::GetClipper(LPDIRECTDRAWCLIPPER FAR* a)
{
	logf(this, "myIDDrawSurface7::GetClipper");
	return m_pIDDrawSurface->GetClipper(a);
}



HRESULT  __stdcall myIDDrawSurface7::GetColorKey(DWORD a, LPDDCOLORKEY b)
{
	logf(this, "myIDDrawSurface7::GetColorKey");
	return m_pIDDrawSurface->GetColorKey(a,b);
}



HRESULT  __stdcall myIDDrawSurface7::GetDC(HDC FAR *a)
{
	logf(this, "myIDDrawSurface7::GetDC");
	return m_pIDDrawSurface->GetDC(a);
}



HRESULT  __stdcall myIDDrawSurface7::GetFlipStatus(DWORD a)
{
	logf(this, "myIDDrawSurface7::GetFlipStatus");
	return m_pIDDrawSurface->GetFlipStatus(a);
}



HRESULT  __stdcall myIDDrawSurface7::GetOverlayPosition(LPLONG a, LPLONG b)
{
	logf(this, "myIDDrawSurface7::GetOverlayPosition");
	return m_pIDDrawSurface->GetOverlayPosition(a,b);
}



HRESULT  __stdcall myIDDrawSurface7::GetPalette(LPDIRECTDRAWPALETTE FAR*a)
{
	logf(this, "myIDDrawSurface7::GetPalette");
	return m_pIDDrawSurface->GetPalette(a);
}



HRESULT  __stdcall myIDDrawSurface7::GetPixelFormat(LPDDPIXELFORMAT a)
{
	logf(this, "myIDDrawSurface7::GetPixelFormat");
	return m_pIDDrawSurface->GetPixelFormat(a);
}



HRESULT  __stdcall myIDDrawSurface7::GetSurfaceDesc(LPDDSURFACEDESC2 a)
{
	HRESULT r = m_pIDDrawSurface->GetSurfaceDesc(a);
	logf(this, "myIDDrawSurface7::GetSurfaceDesc([%x %x %x %x %x %x %x %x %x [%x %x %x %x %x %x %x %x] %x]) return %d",
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



HRESULT  __stdcall myIDDrawSurface7::Initialize(LPDIRECTDRAW a, LPDDSURFACEDESC2 b)
{
	logf(this, "myIDDrawSurface7::Initialize");
	return m_pIDDrawSurface->Initialize(a,b);
}



HRESULT  __stdcall myIDDrawSurface7::IsLost()
{
	logf(this, "myIDDrawSurface7::IsLost");
	return m_pIDDrawSurface->IsLost();
}



HRESULT  __stdcall myIDDrawSurface7::Lock(LPRECT a,LPDDSURFACEDESC2 b,DWORD c,HANDLE d)
{
	if (a)	
		logf(this, "myIDDrawSurface7::Lock([%d,%d,%d,%d],%08x,%d,%d)",a->top,a->left,a->bottom,a->right,b,c,d);
	else
		logf(this, "myIDDrawSurface7::Lock([null],%08x,%d,%d)",b,c,d);
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



HRESULT  __stdcall myIDDrawSurface7::ReleaseDC(HDC a)
{
	logf(this, "myIDDrawSurface7::ReleaseDC");
	return m_pIDDrawSurface->ReleaseDC(a);
}



HRESULT  __stdcall myIDDrawSurface7::Restore()
{
	logf(this, "myIDDrawSurface7::Restore");
	return m_pIDDrawSurface->Restore();
}



HRESULT  __stdcall myIDDrawSurface7::SetClipper(LPDIRECTDRAWCLIPPER a)
{
	logf(this, "myIDDrawSurface7::SetClipper");
	return m_pIDDrawSurface->SetClipper(a);
}



HRESULT  __stdcall myIDDrawSurface7::SetColorKey(DWORD a, LPDDCOLORKEY b)
{
	logf(this, "myIDDrawSurface7::SetColorKey");
	return m_pIDDrawSurface->SetColorKey(a,b);
}



HRESULT  __stdcall myIDDrawSurface7::SetOverlayPosition(LONG a, LONG b)
{
	logf(this, "myIDDrawSurface7::SetOverlayPosition");
	return m_pIDDrawSurface->SetOverlayPosition(a,b);
}



HRESULT  __stdcall myIDDrawSurface7::SetPalette(LPDIRECTDRAWPALETTE a)
{
	logf(this, "myIDDrawSurface7::SetPalette(%08x)",a);
	if (a) a = ((myIDDrawPalette*)a)->m_pIDDrawPalette;
	return m_pIDDrawSurface->SetPalette(a);
}



HRESULT  __stdcall myIDDrawSurface7::Unlock(LPRECT a)
{
	logf(this, "myIDDrawSurface7::Unlock(%08x)",a);
	return m_pIDDrawSurface->Unlock(a);
}



HRESULT  __stdcall myIDDrawSurface7::UpdateOverlay(LPRECT a, LPDIRECTDRAWSURFACE7 b,LPRECT c,DWORD d, LPDDOVERLAYFX e)
{
	logf(this, "myIDDrawSurface7::UpdateOverlay");
	return m_pIDDrawSurface->UpdateOverlay(a,((myIDDrawSurface7*)b)->m_pIDDrawSurface,c,d,e);
}



HRESULT  __stdcall myIDDrawSurface7::UpdateOverlayDisplay(DWORD a)
{
	logf(this, "myIDDrawSurface7::UpdateOverlayDisplay");
	return m_pIDDrawSurface->UpdateOverlayDisplay(a);
}



HRESULT  __stdcall myIDDrawSurface7::UpdateOverlayZOrder(DWORD a, LPDIRECTDRAWSURFACE7 b)
{
	logf(this, "myIDDrawSurface7::UpdateOverlayZOrder");
	return m_pIDDrawSurface->UpdateOverlayZOrder(a,((myIDDrawSurface7*)b)->m_pIDDrawSurface);
}

HRESULT  __stdcall  myIDDrawSurface7::GetDDInterface(LPVOID FAR * a)
{
	logf(this, "myIDDrawSurface7::GetDDInterface");
	return m_pIDDrawSurface->GetDDInterface(a);

}

HRESULT  __stdcall  myIDDrawSurface7::PageLock(DWORD a)
{
	logf(this, "myIDDrawSurface7::PageLock");
	return m_pIDDrawSurface->PageLock(a);

}

HRESULT  __stdcall  myIDDrawSurface7::PageUnlock(DWORD a)
{
	logf(this, "myIDDrawSurface7::PageUnlock");
	return m_pIDDrawSurface->PageUnlock(a);
}

HRESULT  __stdcall myIDDrawSurface7::SetSurfaceDesc(LPDDSURFACEDESC2 a, DWORD b)
{
	logf(this, "myIDDrawSurface7::SetSurfaceDesc");
	return m_pIDDrawSurface->SetSurfaceDesc(a, b);

}

HRESULT  __stdcall myIDDrawSurface7::SetPrivateData(REFGUID a, LPVOID  b, DWORD c, DWORD d)
{
	logf(this, "myIDDrawSurface7::SetPrivateData");
	return m_pIDDrawSurface->SetPrivateData(a, b,c, d);
}

HRESULT  __stdcall myIDDrawSurface7::GetPrivateData(REFGUID a, LPVOID  b, LPDWORD c)
{
	logf(this, "myIDDrawSurface7::GetPrivateData");
	return m_pIDDrawSurface->GetPrivateData( a,  b,  c);
}

HRESULT  __stdcall myIDDrawSurface7::FreePrivateData(REFGUID a)
{
	logf(this, "myIDDrawSurface7::FreePrivateData");
	return m_pIDDrawSurface->FreePrivateData(a);
}

HRESULT  __stdcall myIDDrawSurface7::GetUniquenessValue(LPDWORD a)
{
	logf(this, "myIDDrawSurface7::GetUniquenessValue");
	return m_pIDDrawSurface->GetUniquenessValue(a);
}

HRESULT  __stdcall myIDDrawSurface7::ChangeUniquenessValue()
{
	logf(this, "myIDDrawSurface7::ChangeUniquenessValue");
	return m_pIDDrawSurface->ChangeUniquenessValue();
}

HRESULT  __stdcall myIDDrawSurface7::SetPriority(DWORD a)
{
	logf(this, "myIDDrawSurface7::SetPriority");
	return m_pIDDrawSurface->SetPriority(a);
}

HRESULT  __stdcall myIDDrawSurface7::GetPriority(LPDWORD a)
{
	logf(this, "myIDDrawSurface7::GetPriority");
	return m_pIDDrawSurface->GetPriority(a);
}

HRESULT  __stdcall myIDDrawSurface7::SetLOD(DWORD a)
{
	logf(this, "myIDDrawSurface7::SetLOD");
	return m_pIDDrawSurface->SetLOD(a);

}

HRESULT  __stdcall myIDDrawSurface7:: GetLOD(LPDWORD a)
{
	logf(this, "myIDDrawSurface7::GetLOD");
	return m_pIDDrawSurface->GetLOD(a);
}
