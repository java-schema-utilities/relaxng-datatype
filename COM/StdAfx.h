#pragma once

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>

extern CComModule _Module;
#include <atlcom.h>
#include <comdef.h>

//{{AFX_INSERT_LOCATION}}

