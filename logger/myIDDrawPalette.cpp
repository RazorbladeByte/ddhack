#include "StdAfx.h"
#include <varargs.h>



myIDDrawPalette::myIDDrawPalette(LPDIRECTDRAWPALETTE pOriginal)
{
	logf(this, "myIDDrawPalette Constructor");
	m_pIDDrawPalette = pOriginal;
}


myIDDrawPalette::~myIDDrawPalette(void)
{
	logf(this, "myIDDrawPalette Destructor");
}


HRESULT __stdcall myIDDrawPalette::QueryInterface (REFIID, LPVOID FAR * b)
{
	logf(this, "myIDDrawPalette::QueryInterface");
	
	*b = NULL;

	return E_NOTIMPL;
}


ULONG   __stdcall myIDDrawPalette::AddRef(void)
{
	logf(this, "myIDDrawPalette::AddRef");
	return(m_pIDDrawPalette->AddRef());
}


ULONG   __stdcall myIDDrawPalette::Release(void)
{
	logf(this, "myIDDrawPalette::Release");
	
	// call original routine
	ULONG count = m_pIDDrawPalette->Release();
	
	logf(this, "Object Release."); 

    // in case no further Ref is there, the Original Object has deleted itself
	// so do we here
	if (count == 0) 
	{
		m_pIDDrawPalette = NULL;		
		delete(this); 
	}

	return(count);
}



HRESULT  __stdcall myIDDrawPalette::GetCaps(LPDWORD a)
{
	logf(this, "myIDDrawPalette::GetCaps");
	return m_pIDDrawPalette->GetCaps(a);
}



HRESULT  __stdcall myIDDrawPalette::GetEntries(DWORD a,DWORD b,DWORD c,LPPALETTEENTRY d)
{
	logf(this, "myIDDrawPalette::GetEntries");
	return m_pIDDrawPalette->GetEntries(a,b,c,d);
}



HRESULT  __stdcall myIDDrawPalette::Initialize(LPDIRECTDRAW a, DWORD b, LPPALETTEENTRY c)
{
	logf(this, "myIDDrawPalette::Initialize");
	return m_pIDDrawPalette->Initialize(((myIDDrawInterface*)a)->getAsDirectDraw(),b,c);
}



HRESULT  __stdcall myIDDrawPalette::SetEntries(DWORD a,DWORD b,DWORD c,LPPALETTEENTRY d)
{
	unsigned int i, j;
	char temp[128], temp2[32];
	logf(this, "myIDDrawPalette::SetEntries(%d,%d,%d,%08x)",a,b,c,d);
	j = 0;
	temp[0] = 0;
	for (i = b; i < c; i++)
	{
		sprintf(temp2,"%06X ", ((int*)d)[i-b]);
		strcat(temp, temp2);
		j++;
		if (j == 16)
		{
			logf(this, "paldata %s", temp);
			temp[0] = 0;
			j = 0;
		}
	}
	return m_pIDDrawPalette->SetEntries(a,b,c,d);
}



