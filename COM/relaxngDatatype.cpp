/*
RELAX NG Datatype Interface COM Implementation
==============================================
	Copyright (c) 2001, Kohsuke Kawaguchi (kohsukekawaguchi@yahoo.com)
	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions
	are met:

	* Redistributions of source code must retain the above copyright
	  notice, this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer
	  in the documentation and/or other materials provided with the
	  distribution. 
	* Neither the name of the author nor the names of its contributors
	  may be used to endorse or promote products derived from this
	  software without specific prior written permission. 

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
	FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE REGENTS
	OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
	TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
	THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
	DAMAGE.

	$Id: relaxngDatatype.cpp,v 1.1 2001/08/18 20:16:37 kkawa Exp $
*/


// Memo: Proxy/Stub
//  To build a separate proxy/stub DLL, execute the following command
//	from the project working directory.
//      nmake -f relaxngDatatypeps.mak

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "relaxngDatatype.h"

#include "relaxngDatatype_i.c"
#include "BuiltinDatatypeLibrary.h"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_BuiltinDatatypeLibrary, CBuiltinDatatypeLibrary)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL entry point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_RELAXNGDATATYPELib);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();
    return TRUE;    // ok
}

STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

STDAPI DllRegisterServer(void)
{
    return _Module.RegisterServer(TRUE);
}

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}


