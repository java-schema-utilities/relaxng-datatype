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

	$Id: DatatypeBuilderImpl.h,v 1.1 2001/08/18 20:16:37 kkawa Exp $
*/
#pragma once

class ATL_NO_VTABLE CDatatypeBuilderImpl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IDatatypeBuilder, &IID_IDatatypeBuilder, &LIBID_RELAXNGDATATYPELib>
{
public:
	CDatatypeBuilderImpl() {}
	
	IDatatype* m_pDatatype;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDatatypeBuilderImpl)
	COM_INTERFACE_ENTRY(IDatatypeBuilder)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IDatatypeBuilder
public:
	STDMETHOD(AddParameter)(BSTR name,BSTR value,IValidationContext* pContext)
	{
		return E_INVALIDARG;
	}
	STDMETHOD(CreateDatatype)(IDatatype** ppDatatype)
	{
		*ppDatatype = m_pDatatype;
		(*ppDatatype)->AddRef();
		return S_OK;
	}
};
