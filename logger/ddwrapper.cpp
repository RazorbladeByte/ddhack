/*  DirectDraw Wrapper
 *  version 1.0, August 6th, 2010
 *
 *  Copyright (C) 2010 Jari Komppa
 *
 *  This software is provided 'as-is', without any express or implied
 *  warranty.  In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *  1. The origin of this software must not be misrepresented; you must not
 *     claim that you wrote the original software. If you use this software
 *     in a product, an acknowledgment in the product documentation would be
 *     appreciated but is not required.
 *  2. Altered source versions must be plainly marked as such, and must not be
 *     misrepresented as being the original software.
 *  3. This notice may not be removed or altered from any source distribution.
 *
 * Jari Komppa http://iki.fi/sol/
 *
 *************************************
 *
 * Based on a zlib/libpng licensed source code found on the net, 
 * http://www.mikoweb.eu/index.php?node=28
 * re-worked so much that there's fairly little left of the original.
 */
#include "stdafx.h"
#include <varargs.h>

//#define LOG_DLL_ATTACH

// global variables
#pragma data_seg (".ddraw_shared")
HINSTANCE           gl_hOriginalDll;
HINSTANCE           gl_hThisInstance;
#pragma data_seg ()

void logf(void * thisptr, char *msg, ...)
{	
	va_list argp;
	FILE * f = fopen("\\ddraw.log","a");	
	static int t = -1;
	if (t == -1)
		t = GetTickCount();
	int tn = GetTickCount();
	
	fprintf(f,"[%+6dms] (%08x) ", tn-t, thisptr);
	t = tn;
	
	va_start(argp, msg);
	vfprintf(f, msg, argp);
	va_end(argp);
	
	fprintf(f,"\n");

	fclose(f);
}


BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{	
    LPVOID lpDummy = lpReserved;
    lpDummy = NULL;
    
    switch (ul_reason_for_call)
	{
	    case DLL_PROCESS_ATTACH: 
#ifdef LOG_DLL_ATTACH
			logf(this, "DllMain(%08X,%08X,%08X) DLL_PROCESS_ATTACH",hModule, ul_reason_for_call, lpReserved); 
#endif
			InitInstance(hModule); break;
	    case DLL_PROCESS_DETACH: 
#ifdef LOG_DLL_ATTACH
			logf(this, "DllMain(%08X,%08X,%08X) DLL_PROCESS_DETACH",hModule, ul_reason_for_call, lpReserved);
#endif
			ExitInstance(); break;
        
        case DLL_THREAD_ATTACH:  
#ifdef LOG_DLL_ATTACH
			logf(this, "DllMain(%08X,%08X,%08X) DLL_THREAD_ATTACH",hModule, ul_reason_for_call, lpReserved); 
#endif
			break;
	    case DLL_THREAD_DETACH:  
#ifdef LOG_DLL_ATTACH
			logf(this, "DllMain(%08X,%08X,%08X) DLL_THREAD_DETACH",hModule, ul_reason_for_call, lpReserved); 
#endif
			break;
		default:
			logf(0, "DllMain(%08X,%08X,%08X) unknown reason",hModule, ul_reason_for_call, lpReserved);
	}
    return(true);
}


HRESULT WINAPI DirectDrawCreate(GUID FAR *lpGUID, LPDIRECTDRAW FAR *lplpDD, IUnknown FAR *pUnkOuter)
{
	logf(0, "DirectDrawCreate(%08X,%08X,%08X)", lpGUID, lplpDD, pUnkOuter);

	if (!gl_hOriginalDll) LoadOriginalDll(); // looking for the "right ddraw.dll"

	// Hooking DDRAW interface from Original Library IDirectDraw *pDD; 

	typedef HRESULT (WINAPI* DirectDrawCreate_Type)(GUID FAR *, LPVOID *, IUnknown FAR *);
		
    DirectDrawCreate_Type DirectDrawCreate_fn = (DirectDrawCreate_Type) GetProcAddress( gl_hOriginalDll, _T("DirectDrawCreate"));
        
	if (!DirectDrawCreate_fn) 
    {
        logf(0, "Original function not found");
        ::ExitProcess(0);
    }

	LPDIRECTDRAW FAR dummy;
	HRESULT h = DirectDrawCreate_fn(lpGUID, (LPVOID*) &dummy, pUnkOuter);
	*lplpDD = (LPDIRECTDRAW) new myIDDraw1(dummy);

	logf(0, "IDDRAW1 creation result: %x ptr %08x",h,lplpDD);
	
	return (h);
}


HRESULT WINAPI DirectDrawCreateEx(GUID FAR * lpGuid, LPVOID  *lplpDD, REFIID  iid, IUnknown FAR *pUnkOuter)
{
	logf(0, "DirectDrawCreateEx(%08X,%08X,(guid),%08X)",lpGuid, lplpDD, pUnkOuter);

	if (!gl_hOriginalDll) LoadOriginalDll(); // looking for the "right ddraw.dll"

	// Hooking DDRAW interface from Original Library IDirectDraw *pDD; 

	typedef HRESULT (WINAPI* DirectDrawCreateEx_Type)(GUID FAR *, LPVOID *, REFIID, IUnknown FAR *);
		
    DirectDrawCreateEx_Type DirectDrawCreateEx_fn = (DirectDrawCreateEx_Type) GetProcAddress( gl_hOriginalDll, _T("DirectDrawCreateEx"));
        
	if (!DirectDrawCreateEx_fn) 
    {
        logf(0, "Original function not found");
        ::ExitProcess(0);
    }

	if (iid == IID_IDirectDraw)
	{
		LPDIRECTDRAW FAR dummy;
		HRESULT h = DirectDrawCreateEx_fn(lpGuid, (LPVOID*) &dummy, iid, pUnkOuter);
		*lplpDD = (LPVOID) new myIDDraw1(dummy);

		logf(0, "IDDRAW1 creation result: %x ptr %08x",h,lplpDD);
		
		return (h);
	}

	if (iid == IID_IDirectDraw2)
	{
		LPDIRECTDRAW2 FAR dummy;
		HRESULT h = DirectDrawCreateEx_fn(lpGuid, (LPVOID*) &dummy, iid, pUnkOuter);
		*lplpDD = (LPVOID) new myIDDraw2(dummy);

		logf(0, "IDDRAW2 creation result: %x ptr %08x",h,lplpDD);
		
		return (h);
	}

	if (iid == IID_IDirectDraw4)
	{
		LPDIRECTDRAW4 FAR dummy;
		HRESULT h = DirectDrawCreateEx_fn(lpGuid, (LPVOID*) &dummy, iid, pUnkOuter);
		*lplpDD = (LPVOID) new myIDDraw4(dummy);

		logf(0, "IDDRAW4 creation result: %x ptr %08x",h,lplpDD);
		
		return (h);
	}

	if (iid == IID_IDirectDraw7)
	{
		LPDIRECTDRAW7 FAR dummy;
		HRESULT h = DirectDrawCreateEx_fn(lpGuid, (LPVOID*) &dummy, iid, pUnkOuter);
		*lplpDD = (LPVOID) new myIDDraw7(dummy);

		logf(0, "IDDRAW7 creation result: %x ptr %08x",h,lplpDD);
		
		return (h);
	}

	logf(0, "Unsupported ddraw interface version");
    ::ExitProcess(0);	
		
}


HRESULT WINAPI DirectDrawCreateClipper(DWORD dwFlags, LPDIRECTDRAWCLIPPER FAR *lplpDDClipper, IUnknown FAR *pUnkOuter)
{
	logf(0, "Exported function DirectDrawCreateClipper");
	
	if (!gl_hOriginalDll) LoadOriginalDll(); // looking for the "right ddraw.dll"
	
	// Hooking DDRAW interface from Original Library IDirectDraw *pDD; 
	typedef HRESULT (WINAPI* DirectDrawCreateClipper_Type)(DWORD, LPDIRECTDRAWCLIPPER FAR *, IUnknown FAR *);
		
    DirectDrawCreateClipper_Type DirectDrawCreateClipper_fn = (DirectDrawCreateClipper_Type) GetProcAddress( gl_hOriginalDll, _T("DirectDrawCreateClipper"));
    
    //Debug
	if (!DirectDrawCreateClipper_fn) 
    {
        logf(0, "Pointer to original DirectDrawCreateClipper function not received");
        ::ExitProcess(0);
    }
	
	HRESULT h = DirectDrawCreateClipper_fn(dwFlags, lplpDDClipper, pUnkOuter);
		
	return (h);
}


HRESULT WINAPI DirectDrawEnumerateW(LPDDENUMCALLBACKW lpCallback, LPVOID lpContext)
{
	logf(0, "Exported function DirectDrawEnumerateW");
	
	if (!gl_hOriginalDll) LoadOriginalDll(); // looking for the "right ddraw.dll"
	
	// Hooking DDRAW interface from Original Library IDirectDraw *pDD; 
	typedef HRESULT (WINAPI* DirectDrawEnumerateW_Type)(LPDDENUMCALLBACKW, LPVOID);
		
    DirectDrawEnumerateW_Type DirectDrawEnumerateW_fn = (DirectDrawEnumerateW_Type) GetProcAddress( gl_hOriginalDll, _T("DirectDrawEnumerateW"));
    
    //Debug
	if (!DirectDrawEnumerateW_fn) 
    {
        logf(0, "Pointer to original DirectDrawEnumerateW function not received");
        ::ExitProcess(0);
    }
	
	HRESULT h = DirectDrawEnumerateW_fn(lpCallback, lpContext);
	
	return (h); 
}


HRESULT WINAPI DirectDrawEnumerateA(LPDDENUMCALLBACKA lpCallback, LPVOID lpContext)
{
	logf(0, "Exported function DirectDrawEnumerateA");
	
	if (!gl_hOriginalDll) LoadOriginalDll(); // looking for the "right ddraw.dll"
	
	// Hooking DDRAW interface from Original Library IDirectDraw *pDD; 
	typedef HRESULT (WINAPI* DirectDrawEnumerateA_Type)(LPDDENUMCALLBACKA, LPVOID);
		
    DirectDrawEnumerateA_Type DirectDrawEnumerateA_fn = (DirectDrawEnumerateA_Type) GetProcAddress( gl_hOriginalDll, _T("DirectDrawEnumerateA"));
    
    //Debug
	if (!DirectDrawEnumerateA_fn) 
    {
        logf(0, "Pointer to original DirectDrawEnumerateA function not received");
        ::ExitProcess(0);
    }
	
	HRESULT h = DirectDrawEnumerateA_fn(lpCallback, lpContext);

	return (h);
}


HRESULT WINAPI DirectDrawEnumerateExW(LPDDENUMCALLBACKEXW lpCallback, LPVOID lpContext, DWORD dwFlags)
{
	logf(0, "Exported function DirectDrawEnumerateExW");
	
	if (!gl_hOriginalDll) LoadOriginalDll(); // looking for the "right ddraw.dll"
	
	// Hooking DDRAW interface from Original Library IDirectDraw *pDD; 
	typedef HRESULT (WINAPI* DirectDrawEnumerateExW_Type)(LPDDENUMCALLBACKEXW, LPVOID, DWORD);
		
    DirectDrawEnumerateExW_Type DirectDrawEnumerateExW_fn = (DirectDrawEnumerateExW_Type) GetProcAddress( gl_hOriginalDll, _T("DirectDrawEnumerateExW"));
    
    //Debug
	if (!DirectDrawEnumerateExW_fn) 
    {
        logf(0, "Pointer to original DirectDrawEnumerateExW function not received");
        ::ExitProcess(0);
    }
	
	HRESULT h = DirectDrawEnumerateExW_fn(lpCallback, lpContext, dwFlags);

	return (h); 
}


HRESULT WINAPI DirectDrawEnumerateExA(LPDDENUMCALLBACKEXA lpCallback, LPVOID lpContext, DWORD dwFlags)
{
	logf(0, "Exported function DirectDrawEnumerateExA");
	
	if (!gl_hOriginalDll) LoadOriginalDll(); // looking for the "right ddraw.dll"
	
	// Hooking DDRAW interface from Original Library IDirectDraw *pDD; 
	typedef HRESULT (WINAPI* DirectDrawEnumerateExA_Type)(LPDDENUMCALLBACKEXA, LPVOID, DWORD);
		
    DirectDrawEnumerateExA_Type DirectDrawEnumerateExA_fn = (DirectDrawEnumerateExA_Type) GetProcAddress( gl_hOriginalDll, _T("DirectDrawEnumerateExA"));
    
    //Debug
	if (!DirectDrawEnumerateExA_fn) 
    {
        logf(0, "Pointer to original DirectDrawEnumerateExA function not received");
        ::ExitProcess(0);
    }

	HRESULT h = DirectDrawEnumerateExA_fn(lpCallback, lpContext, dwFlags);

	return (h);
}


VOID WINAPI AcquireDDThreadLock()
{
	logf(0, "Exported function AcquireDDThreadLock");
	
	if (!gl_hOriginalDll) LoadOriginalDll(); // looking for the "right ddraw.dll"
	
	// Hooking DDRAW interface from Original Library IDirectDraw *pDD; 
	typedef VOID (WINAPI* AcquireDDThreadLock_Type)(VOID);
		
    AcquireDDThreadLock_Type AcquireDDThreadLock_fn = (AcquireDDThreadLock_Type) GetProcAddress( gl_hOriginalDll, _T("AcquireDDThreadLock"));
    
    //Debug
	if (!AcquireDDThreadLock_fn) 
    {
        logf(0, "Pointer to original AcquireDDThreadLock function not received");
        ::ExitProcess(0);
    }

	AcquireDDThreadLock_fn();
}


VOID WINAPI ReleaseDDThreadLock()
{
	logf(0, "Exported function ReleaseDDThreadLock");
	
	if (!gl_hOriginalDll) LoadOriginalDll(); // looking for the "right ddraw.dll"
	
	// Hooking DDRAW interface from Original Library IDirectDraw *pDD; 
	typedef VOID (WINAPI* ReleaseDDThreadLock_Type)(VOID);
		
    ReleaseDDThreadLock_Type ReleaseDDThreadLock_fn = (ReleaseDDThreadLock_Type) GetProcAddress( gl_hOriginalDll, _T("ReleaseDDThreadLock"));
    
    //Debug
	if (!ReleaseDDThreadLock_fn) 
    {
        logf(0, "Pointer to original ReleaseDDThreadLock function not received");
        ::ExitProcess(0);
    }

	ReleaseDDThreadLock_fn();
}


DWORD WINAPI D3DParseUnknownCommand(LPVOID lpCmd, LPVOID *lpRetCmd)
{
	logf(0, "Exported function D3DParseUnknownCommand");
	
	if (!gl_hOriginalDll) LoadOriginalDll(); // looking for the "right ddraw.dll"
	
	// Hooking DDRAW interface from Original Library IDirectDraw *pDD; 
	typedef DWORD (WINAPI* D3DParseUnknownCommand_Type)(LPVOID lpCmd, LPVOID *lpRetCmd);
		
    D3DParseUnknownCommand_Type D3DParseUnknownCommand_fn = (D3DParseUnknownCommand_Type) GetProcAddress( gl_hOriginalDll, _T("D3DParseUnknownCommand"));
    
    //Debug
	if (!D3DParseUnknownCommand_fn) 
    {
        logf(0, "Pointer to original D3DParseUnknownCommand function not received");
        ::ExitProcess(0);
    }

	DWORD dw = D3DParseUnknownCommand_fn(lpCmd, lpRetCmd);
	
	return(dw);
}


HRESULT WINAPI DllCanUnloadNow(void)
{
	logf(0, "Exported function DllCanUnloadNow");
	
	if (!gl_hOriginalDll) LoadOriginalDll(); // looking for the "right ddraw.dll"
	
	typedef HRESULT (WINAPI *DllCanUnloadNow_Type)(void);
	DllCanUnloadNow_Type DllCanUnloadNow_fn = (DllCanUnloadNow_Type) GetProcAddress( gl_hOriginalDll, "DllCanUnloadNow");
    
    // Debug
	if (!DllCanUnloadNow_fn) 
    {
        logf(0, "Pointer to original DllCanUnloadNow function not received");
        ::ExitProcess(0);
    }

	// Call original dll and return
	HRESULT h = DllCanUnloadNow_fn();

	return(h);
}

HRESULT WINAPI DllGetClassObject (const CLSID &rclsid, const IID &riid, void **ppv)
{
	logf(0, "Exported function DllGetClassObject");
	
	if (!gl_hOriginalDll) LoadOriginalDll(); // looking for the "right ddraw.dll"
	
	typedef HRESULT (WINAPI *DllGetClassObject_Type)(const CLSID &rclsid, const IID &riid, void **ppv);
	DllGetClassObject_Type DllGetClassObject_fn = (DllGetClassObject_Type) GetProcAddress( gl_hOriginalDll, "DllGetClassObject");
    
    // Debug
	if (!DllGetClassObject_fn) 
    {
        logf(0, "Pointer to original DllGetClassObject function not received");
        ::ExitProcess(0);
    }

	// Call original dll and return
	HRESULT h = DllGetClassObject_fn(rclsid, riid, ppv);

	return(h);
}

HRESULT WINAPI CompleteCreateSysmemSurface(int ths, int a2)
{
	logf(0, "Exported function CompleteCreateSysmemSurface");

	if (!gl_hOriginalDll) LoadOriginalDll(); // looking for the "right ddraw.dll"
	
	typedef HRESULT (WINAPI  *CompleteCreateSysmemSurface_Type)(int, int);
		
	CompleteCreateSysmemSurface_Type CompleteCreateSysmemSurface_fn = (CompleteCreateSysmemSurface_Type) GetProcAddress( gl_hOriginalDll, _T("CompleteCreateSysmemSurface"));
    
	if (!CompleteCreateSysmemSurface_fn) 
	{
		logf(0, "Pointer to original CompleteCreateSysmemSurface function not received\r\n");
		::ExitProcess(0);
	}

	HRESULT retVal = CompleteCreateSysmemSurface_fn(ths, a2);
	
	return(retVal);
};

HRESULT WINAPI DDInternalLock(int a1, int a2)
{
	logf(0, "Exported function DDInternalLock");

	if (!gl_hOriginalDll) LoadOriginalDll(); // looking for the "right ddraw.dll"
	
	typedef HRESULT (WINAPI *DDInternalLock_Type)(int, int);
		
    DDInternalLock_Type DDInternalLock_fn = (DDInternalLock_Type) GetProcAddress( gl_hOriginalDll, _T("DDInternalLock"));
    
    //Debug
	if (!DDInternalLock_fn) 
    {
        logf(0, "Pointer to original DDInternalLock function not received");
        ::ExitProcess(0);
    }
	
	HRESULT retVal = DDInternalLock_fn(a1, a2);
		
	return (retVal);
}

HRESULT WINAPI DDInternalUnlock(int a1)
{
	logf(0, "Exported function DDInternalUnlock reached.");

	if (!gl_hOriginalDll) LoadOriginalDll(); // looking for the "right ddraw.dll"
	
	typedef HRESULT (WINAPI *DDInternalUnlock_Type)(int);
		
    DDInternalUnlock_Type DDInternalUnlock_fn = (DDInternalUnlock_Type) GetProcAddress( gl_hOriginalDll, _T("DDInternalUnlock"));
    
    //Debug
	if (!DDInternalUnlock_fn) 
    {
        logf(0, "Pointer to original DDInternalUnlock function not received");
        ::ExitProcess(0);
    }
	
	HRESULT retVal = DDInternalUnlock_fn(a1);
		
	return (retVal);
}


void InitInstance(HANDLE hModule) 
{
	logf(0, "InitInstance.");

	// Initialisation
	gl_hOriginalDll        = NULL;
	gl_hThisInstance       = NULL;
	
	// Storing Instance handle into global var
	gl_hThisInstance = (HINSTANCE)  hModule;
}


void LoadOriginalDll(void)
{
    logf(0, "LoadOriginalDll.");
	
	char buffer[MAX_PATH];
    
    // Getting path to system dir and to d3d9.dll
	::GetSystemDirectory(buffer,MAX_PATH);

	// Append dll name
	strcat(buffer,"\\ddraw.dll");
	
	if (!gl_hOriginalDll) gl_hOriginalDll = ::LoadLibrary(buffer);

	// Debug
	if (!gl_hOriginalDll)
	{
		logf(0, "Original ddraw.dll not loaded");
		::ExitProcess(0); // exit the hard way
	}
}


void ExitInstance() 
{
	logf(0, "ExitInstance.");
    
    if (gl_hOriginalDll)
	{
		::FreeLibrary(gl_hOriginalDll);
	    gl_hOriginalDll = NULL;  
	}
}


