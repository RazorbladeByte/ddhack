#include "StdAfx.h"
#include <varargs.h>


myIDDrawSurface1::myIDDrawSurface1(LPDDSURFACEDESC a)
{
	logf("myIDDrawSurface1 Constructor");

	mWidth = gScreenWidth;
	mHeight = gScreenHeight;
	mSurfaceDesc = *a;

	if (a->dwFlags & DDSD_WIDTH) mWidth = a->dwWidth;
	if (a->dwFlags & DDSD_HEIGHT) mHeight = a->dwHeight;
	// we don't need no stinking extra pitch bytes..
	mPitch = mWidth * gScreenBits / 8;
	
	if (a->dwFlags & DDSD_PITCH) mPitch = a->lPitch;
	if (a->dwFlags & DDSD_CAPS)
	{
		if (a->ddsCaps.dwCaps & DDSCAPS_PRIMARYSURFACE)
		{
			gPrimarySurface = this;
			init_gl();
		}
	}

	mSurfaceDesc.dwWidth = mWidth;
	mSurfaceDesc.dwHeight = mHeight;
	mSurfaceDesc.lPitch = mPitch;
	mSurfaceDesc.dwFlags |= DDSD_WIDTH | DDSD_HEIGHT | DDSD_PITCH;

	// Let's pad the framebuffer by a couple of megs, in case
	// the app writes outside bounds..
	// (we have enough trouble being stable as it is)
	mRealSurfaceData = new unsigned char[mHeight * mPitch + 2 * 1024 * 1024];
	mSurfaceData = mRealSurfaceData + 1024 * 1024 * 1;
	memset(mSurfaceData, 0, mHeight * mPitch);

	mCurrentPalette = NULL;
}


myIDDrawSurface1::~myIDDrawSurface1(void)
{
	logf("myIDDrawSurface1 Destructor");

	if (this == gPrimarySurface)
	{
		gPrimarySurface = NULL;
		delete gBackBuffer;
		gBackBuffer = NULL;
	}
	delete[] mRealSurfaceData;
}


HRESULT __stdcall myIDDrawSurface1::QueryInterface (REFIID, LPVOID FAR * b)
{
	logf("myIDDrawSurface1::QueryInterface");
	
	*b = NULL;

	return DDERR_UNSUPPORTED;
}


ULONG   __stdcall myIDDrawSurface1::AddRef(void)
{
	logf("myIDDrawSurface1::AddRef");
	return 1;
}


ULONG   __stdcall myIDDrawSurface1::Release(void)
{
	logf("myIDDrawSurface1::Release");
	delete this;
	
	return 0;
}



HRESULT  __stdcall myIDDrawSurface1::AddAttachedSurface(LPDIRECTDRAWSURFACE a)
{
	logf("myIDDrawSurface1::AddAttachedSurface");
	return DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawSurface1::AddOverlayDirtyRect(LPRECT a)
{
	logf("myIDDrawSurface1::AddOverlayDirtyRect");
	return DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawSurface1::Blt(LPRECT a,LPDIRECTDRAWSURFACE b, LPRECT c,DWORD d, LPDDBLTFX e)
{
	myIDDrawSurface1 *src = NULL;
	if (b) src = (myIDDrawSurface1*)b;

	//Sorry, removed logging from here until we work out why AOE crashes here with it on....

	if (b == NULL)
	{
		// no source - probably fill then; assuming clear request.
		memset(mSurfaceData, 0, mHeight * mPitch);
	}
	else
	{
		// Othewise we're scaling a 320x240 to 640x480.. or we're scaling the
		// video on screen.

		if (a && c && gWc3SmallVid)
		{
			int i, j;
			for (i = c->top; i < c->bottom; i++)
				for (j = c->left; j < c->right; j++)
					mSurfaceData[(i + (480 - c->bottom)/2) * mPitch + j + 160] = src->mSurfaceData[i * src->mPitch + j];		
		}
		else
		{
			int i, j;
			if (a && c)
			{
				for (i = 0; i < a->bottom - a->top; i++)
					for (j = 0; j < a->right - a->left; j++)
						mSurfaceData[(i + a->top) * mPitch + j + a->left] = src->mSurfaceData[(i / 2 + c->top) * src->mPitch + j / 2 + c->left];		
			}
			else
			{
				for (i = 0; i < mHeight; i++)
					for (j = 0; j < mWidth; j++)
						mSurfaceData[i * mPitch + j] = src->mSurfaceData[(i / 2) * src->mPitch + j / 2];		
			}
		}
	}


	return DD_OK;
}



HRESULT  __stdcall myIDDrawSurface1::BltBatch(LPDDBLTBATCH a, DWORD b, DWORD c)
{
	logf("myIDDrawSurface1::BltBatch");
	return DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawSurface1::BltFast(DWORD a,DWORD b,LPDIRECTDRAWSURFACE c, LPRECT d,DWORD e)
{
	logf("myIDDrawSurface1::BltFast");
	return DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawSurface1::DeleteAttachedSurface(DWORD a,LPDIRECTDRAWSURFACE b)
{
	logf("myIDDrawSurface1::DeleteAttachedSurface");
	return DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawSurface1::EnumAttachedSurfaces(LPVOID a,LPDDENUMSURFACESCALLBACK b)
{
	logf("myIDDrawSurface1::EnumAttachedSurfaces");
	return DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawSurface1::EnumOverlayZOrders(DWORD a,LPVOID b,LPDDENUMSURFACESCALLBACK c)
{
	logf("myIDDrawSurface1::EnumOverlayZOrders");
	return DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawSurface1::Flip(LPDIRECTDRAWSURFACE a, DWORD b)
{
	logf("myIDDrawSurface1::Flip");
	updatescreen();
	return DD_OK;
}



HRESULT  __stdcall myIDDrawSurface1::GetAttachedSurface(LPDDSCAPS a, LPDIRECTDRAWSURFACE FAR * b)
{
	logf("myIDDrawSurface1::GetAttachedSurface([%d], %08x)",
		a->dwCaps, b);

	// wc3 and wc4 call this function to access the back buffer..
	// hack: make a new surface which still uses the primary's
	// surface data.

	// Potential memory leak; should check and return gBackBuffer
	// if already exists... but the games I've checked don't call
	// this several times, so why bother.
	// And yes, I realize the checking code would take less space
	// than this comment that's complaining about it.
	// On the other hand, you wouldn't have so much fun reading 
	// this if I just deleted it and wrote the check, now would you?
	
	DDSURFACEDESC newdesc = mSurfaceDesc;
	
	newdesc.ddsCaps.dwCaps |= a->dwCaps;	
	newdesc.ddsCaps.dwCaps &= ~DDSCAPS_PRIMARYSURFACE;

	myIDDrawSurface1 * n = new myIDDrawSurface1(&newdesc);
	n->mSurfaceData = mSurfaceData;
	*b = n;
	gBackBuffer = n;

	return DD_OK;
}



HRESULT  __stdcall myIDDrawSurface1::GetBltStatus(DWORD a)
{
	logf("myIDDrawSurface1::GetBltStatus");
	return DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawSurface1::GetCaps(LPDDSCAPS a)
{
	logf("myIDDrawSurface1::GetCaps");
	return DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawSurface1::GetClipper(LPDIRECTDRAWCLIPPER FAR* a)
{
	logf("myIDDrawSurface1::GetClipper");
	return DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawSurface1::GetColorKey(DWORD a, LPDDCOLORKEY b)
{
	logf("myIDDrawSurface1::GetColorKey");
	return DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawSurface1::GetDC(HDC FAR *a)
{
	logf("myIDDrawSurface1::GetDC");
	return DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawSurface1::GetFlipStatus(DWORD a)
{
	logf("myIDDrawSurface1::GetFlipStatus");
	return DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawSurface1::GetOverlayPosition(LPLONG a, LPLONG b)
{
	logf("myIDDrawSurface1::GetOverlayPosition");
	return DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawSurface1::GetPalette(LPDIRECTDRAWPALETTE FAR*a)
{
	logf("myIDDrawSurface1::GetPalette");
	*a = mCurrentPalette;
	return DD_OK;
}



HRESULT  __stdcall myIDDrawSurface1::GetPixelFormat(LPDDPIXELFORMAT a)
{
	logf("myIDDrawSurface1::GetPixelFormat");
	// Return codes based on what ddwrapper reported..
	if (gScreenBits == 8)
	{
		a->dwSize = 0x20;
		a->dwFlags = 0x60;
		a->dwFourCC = 0;
		a->dwRGBBitCount = 0x8;
		a->dwRBitMask = 0;
		a->dwGBitMask = 0;	
		a->dwBBitMask = 0;
		a->dwRGBAlphaBitMask = 0;
	}
	else
	if (gScreenBits == 16)
	{
		a->dwSize = 0x20;
		a->dwFlags = 0x40;
		a->dwFourCC = 0;
		a->dwRGBBitCount = 0x10;
		a->dwRBitMask = 0xf800;
		a->dwGBitMask = 0x07e0;
		a->dwBBitMask = 0x001f;
		a->dwRGBAlphaBitMask = 0;
	}
	else
	if (gScreenBits == 24)
	{
		a->dwSize = 0x20;
		a->dwFlags = 0x40;
		a->dwFourCC = 0;
		a->dwRGBBitCount = 24;
		a->dwRBitMask = 0xff0000;
		a->dwGBitMask = 0x00ff00;
		a->dwBBitMask = 0x0000ff;
		a->dwRGBAlphaBitMask = 0;
	}
	return DD_OK;
}



HRESULT  __stdcall myIDDrawSurface1::GetSurfaceDesc(LPDDSURFACEDESC a)
{
	logf("myIDDrawSurface1::GetSurfaceDesc([%d %d %d %d %d %d %d %d])",
		a->dwSize, a->dwFlags, a->dwWidth, a->dwHeight, a->lPitch, a->dwBackBufferCount,
		a->lpSurface, a->ddsCaps.dwCaps);
	*a = mSurfaceDesc;
	if (gScreenBits == 8)
	{
		a->ddpfPixelFormat.dwSize = 0x20;
		a->ddpfPixelFormat.dwFlags = 0x60;
		a->ddpfPixelFormat.dwFourCC = 0;
		a->ddpfPixelFormat.dwRGBBitCount = 0x8;
		a->ddpfPixelFormat.dwRBitMask = 0;
		a->ddpfPixelFormat.dwGBitMask = 0;	
		a->ddpfPixelFormat.dwBBitMask = 0;
		a->ddpfPixelFormat.dwRGBAlphaBitMask = 0;
	}
	else
	if (gScreenBits == 16)
	{
		a->ddpfPixelFormat.dwSize = 0x20;
		a->ddpfPixelFormat.dwFlags = 0x40;
		a->ddpfPixelFormat.dwFourCC = 0;
		a->ddpfPixelFormat.dwRGBBitCount = 0x10;
		a->ddpfPixelFormat.dwRBitMask = 0xf800;
		a->ddpfPixelFormat.dwGBitMask = 0x07e0;
		a->ddpfPixelFormat.dwBBitMask = 0x001f;
		a->ddpfPixelFormat.dwRGBAlphaBitMask = 0;
	}
	else
	if (gScreenBits == 24)
	{
		a->ddpfPixelFormat.dwSize = 0x20;
		a->ddpfPixelFormat.dwFlags = 0x40;
		a->ddpfPixelFormat.dwFourCC = 0;
		a->ddpfPixelFormat.dwRGBBitCount = 24;
		a->ddpfPixelFormat.dwRBitMask = 0xff0000;
		a->ddpfPixelFormat.dwGBitMask = 0x00ff00;
		a->ddpfPixelFormat.dwBBitMask = 0x0000ff;
		a->ddpfPixelFormat.dwRGBAlphaBitMask = 0;
	}
	logf("pixel format: %d bit, R%08x G%08x B%08x", a->ddpfPixelFormat.dwRGBBitCount, a->ddpfPixelFormat.dwRBitMask, a->ddpfPixelFormat.dwGBitMask, a->ddpfPixelFormat.dwBBitMask);
	return DD_OK;//DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawSurface1::Initialize(LPDIRECTDRAW a, LPDDSURFACEDESC b)
{
	logf("myIDDrawSurface1::Initialize");
	return DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawSurface1::IsLost()
{
	logf("myIDDrawSurface1::IsLost");
	// We're never lost..
	return DD_OK;
}



HRESULT  __stdcall myIDDrawSurface1::Lock(LPRECT a,LPDDSURFACEDESC b,DWORD aFlags,HANDLE d)
{
	char *extra = "";
	if (this == gPrimarySurface)
		extra = " primary";
	if (this == gBackBuffer)
		extra = " backbuffer";	

	if (a)	
		logf("myIDDrawSurface1::Lock([%d,%d,%d,%d],%08x,%d,%d)%s",a->top,a->left,a->bottom,a->right,b,aFlags,d,extra);
	else
		logf("myIDDrawSurface1::Lock([null],%08x,%d,%d)%s",b,aFlags,d,extra);

	gGDI = 0;

	*b = mSurfaceDesc;

	b->dwFlags |= DDSD_LPSURFACE | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PITCH;
	b->lpSurface = mSurfaceData;

	b->dwWidth = mWidth;
	b->dwHeight = mHeight;
	b->lPitch = mPitch;

	return NOERROR;
}



HRESULT  __stdcall myIDDrawSurface1::ReleaseDC(HDC a)
{
	logf("myIDDrawSurface1::ReleaseDC");
	return DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawSurface1::Restore()
{
	logf("myIDDrawSurface1::Restore");
	// we can't lose surfaces, so..
	return DD_OK;
}



HRESULT  __stdcall myIDDrawSurface1::SetClipper(LPDIRECTDRAWCLIPPER a)
{
	logf("myIDDrawSurface1::SetClipper");
	return DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawSurface1::SetColorKey(DWORD a, LPDDCOLORKEY b)
{
	logf("myIDDrawSurface1::SetColorKey");
	return DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawSurface1::SetOverlayPosition(LONG a, LONG b)
{
	logf("myIDDrawSurface1::SetOverlayPosition");
	return DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawSurface1::SetPalette(LPDIRECTDRAWPALETTE a)
{
	logf("myIDDrawSurface1::SetPalette(%08x)",a);
	mCurrentPalette = (myIDDrawPalette *)a;
	return NOERROR;
}

HRESULT  __stdcall myIDDrawSurface1::Unlock(LPVOID a)
{
	logf("myIDDrawSurface1::Unlock(%08x)",a);

	// if primary has been updated, flush..
	// otherwise wc2 misses some screens
	// (no retrace, flip, or even message pump)
	if (this == gPrimarySurface)
		updatescreen();

	return NOERROR;
}



HRESULT  __stdcall myIDDrawSurface1::UpdateOverlay(LPRECT a, LPDIRECTDRAWSURFACE b,LPRECT c,DWORD d, LPDDOVERLAYFX e)
{
	logf("myIDDrawSurface1::UpdateOverlay");
	return DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawSurface1::UpdateOverlayDisplay(DWORD a)
{
	logf("myIDDrawSurface1::UpdateOverlayDisplay");
	return DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawSurface1::UpdateOverlayZOrder(DWORD a, LPDIRECTDRAWSURFACE b)
{
	logf("myIDDrawSurface1::UpdateOverlayZOrder");
	return DDERR_UNSUPPORTED;
}

