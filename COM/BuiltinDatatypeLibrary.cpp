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

	$Id: BuiltinDatatypeLibrary.cpp,v 1.1 2001/08/18 20:16:37 kkawa Exp $
*/
#include "stdafx.h"
#include "RelaxngDatatype.h"
#include "BuiltinDatatypeLibrary.h"
#include "StringType.h"
#include "TokenType.h"
#include "DatatypeBuilderImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CBuiltinDatatypeLibrary

STDMETHODIMP CBuiltinDatatypeLibrary::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IDatatypeLibrary
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


CComObjectGlobal<CStringType>	stringType;
CComObjectGlobal<CTokenType>	tokenType;
CComObjectGlobal<CStreamingValidatorImpl>	streamingValidator;

STDMETHODIMP CBuiltinDatatypeLibrary::CreateDatatype( BSTR typeName, IDatatype** ppRetVal )
{
	if( !wcscmp(typeName,L"string") )
	{
		*ppRetVal = &stringType;
		stringType.AddRef();
		return S_OK;
	}

	if( !wcscmp(typeName,L"token") )
	{
		*ppRetVal = &tokenType;
		tokenType.AddRef();
		return S_OK;
	}
	
	// unrecognized types
	*ppRetVal = NULL;
	return E_INVALIDARG;
}

STDMETHODIMP CBuiltinDatatypeLibrary::CreateDatatypeBuilder( BSTR typeName, IDatatypeBuilder** ppRetVal )
{
	IDatatype* pDatatype;
	HRESULT hr = CreateDatatype(typeName,&pDatatype);
	if(FAILED(hr))
	{// the type name was wrong.
		*ppRetVal = NULL;
		return hr;
	}

	CComObject<CDatatypeBuilderImpl>* p;

	hr = CComObject<CDatatypeBuilderImpl>::CreateInstance(&p);
	if(FAILED(hr))	return hr;

	// no need to call AddRef here.
	p->m_pDatatype = pDatatype;

	p->AddRef();
	*ppRetVal = p;
	return hr;
}
