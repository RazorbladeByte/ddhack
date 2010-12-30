// stdafx.h 

#pragma once

#define WIN32_LEAN_AND_MEAN		

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <gl/gl.h>

#include "ddraw.h"
#include "myIDDraw.h"
#include "ddhack.h"

#define STFU(x) warning(disable: x)
#pragma STFU(4100) // unreferenced formal parameter