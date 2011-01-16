#include "StdAfx.h"
#include <varargs.h>

void logf(char *msg, ...);
void updatescreen();

myIDDrawPalette::myIDDrawPalette(DWORD aFlags, LPPALETTEENTRY aPalette)
{
	logf("myIDDrawPalette Constructor");
	// Could check aFlags for DDCAPS_8BIT, but that's basically
	// the only sane mode.. right?
	memcpy(mPal, aPalette, sizeof(PALETTEENTRY) * 256);
}


myIDDrawPalette::~myIDDrawPalette(void)
{
	logf("myIDDrawPalette Destructor");
}


HRESULT __stdcall myIDDrawPalette::QueryInterface (REFIID, LPVOID FAR * b)
{
	logf("myIDDrawPalette::QueryInterface");
	
	*b = NULL;

	return DDERR_UNSUPPORTED;
}


ULONG   __stdcall myIDDrawPalette::AddRef(void)
{
	logf("myIDDrawPalette::AddRef");
	return 1;
}


ULONG   __stdcall myIDDrawPalette::Release(void)
{
	logf("myIDDrawPalette::Release");
	delete this;
	return 0;
}



HRESULT  __stdcall myIDDrawPalette::GetCaps(LPDWORD a)
{
	logf("myIDDrawPalette::GetCaps");
	return DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawPalette::GetEntries(DWORD a,DWORD b,DWORD c,LPPALETTEENTRY d)
{
	logf("myIDDrawPalette::GetEntries");
	return DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawPalette::Initialize(LPDIRECTDRAW a, DWORD b, LPPALETTEENTRY c)
{
	logf("myIDDrawPalette::Initialize");
	return DDERR_UNSUPPORTED;
}



HRESULT  __stdcall myIDDrawPalette::SetEntries(DWORD aFlags,DWORD aStartEntry,DWORD aCount,LPPALETTEENTRY aPalEntries)
{
	logf("myIDDrawPalette::SetEntries(%d,%d,%d,%08x)", aFlags, aStartEntry, aCount, aPalEntries);
	memcpy(mPal, aPalEntries, 256 * sizeof(PALETTEENTRY));
	updatescreen();
	return NOERROR;
}



