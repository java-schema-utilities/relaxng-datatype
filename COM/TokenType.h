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

	$Id: TokenType.h,v 1.1 2001/08/18 20:16:37 kkawa Exp $
*/
#pragma once
#include "DatatypeImpl.h"

class ATL_NO_VTABLE CTokenBaseType   :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IDatatype, &IID_IDatatype, &LIBID_RELAXNGDATATYPELib>
{
public:
	CTokenBaseType() {}

DECLARE_PROTECT_FINAL_CONSTRUCT()
DECLARE_CLASSFACTORY_SINGLETON(CTokenBaseType)

BEGIN_COM_MAP(CTokenBaseType)
	COM_INTERFACE_ENTRY(IDatatype)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

private:
	static inline bool IsWhitespace( wchar_t ch )
	{
		return ch==L' ' || ch==L'\t' || ch==L'\r' || ch==L'\n';
	}

// IDatatype
public:

	STDMETHOD(CreateValue)( BSTR literal, IValidationContext* pContext, VARIANT* pRetVal )
	{
		int len = wcslen(literal);
		wchar_t* pBuf = new wchar_t[ len+1 ];
		wcscpy(pBuf,literal);

		wchar_t* p = pBuf;
		// remove head spaces
		while(IsWhitespace(*p))	p++;

		wchar_t* q = pBuf+(len-1);
		while(IsWhitespace(*q) && p<q)	q--;
		*(q+1)=L'\0';

		HRESULT hr = CComVariant(p).Detach(pRetVal);
		delete pBuf;
		return hr;
	}
};

typedef CDatatypeImpl<CTokenBaseType> CTokenType;

