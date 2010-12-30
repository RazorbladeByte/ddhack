// stdafx.h 

#pragma once

#define WIN32_LEAN_AND_MEAN		

#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#include "ddraw.h"
#include "myIDDraw.h"
#include "ddwrapper.h"

void logf(void * thisptr, char *msg, ...);
