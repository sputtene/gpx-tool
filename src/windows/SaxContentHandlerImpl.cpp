#include "SaxContentHandlerImpl.h"

#include "../common.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


SaxContentHandlerImpl::SaxContentHandlerImpl()
{
}

SaxContentHandlerImpl::~SaxContentHandlerImpl()
{
}



HRESULT STDMETHODCALLTYPE SaxContentHandlerImpl::putDocumentLocator(
        /* [in] */ ISAXLocator __RPC_FAR *UNUSED(pLocator)
        )
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE SaxContentHandlerImpl::startDocument()
{
    return S_OK;
}



HRESULT STDMETHODCALLTYPE SaxContentHandlerImpl::endDocument()
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE SaxContentHandlerImpl::startPrefixMapping(
        /* [in] */ const wchar_t __RPC_FAR *UNUSED(pwchPrefix),
        /* [in] */ int UNUSED(cchPrefix),
        /* [in] */ const wchar_t __RPC_FAR *UNUSED(pwchUri),
        /* [in] */ int UNUSED(cchUri))
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE SaxContentHandlerImpl::endPrefixMapping(
        /* [in] */ const wchar_t __RPC_FAR *UNUSED(pwchPrefix),
        /* [in] */ int UNUSED(cchPrefix))
{
    return S_OK;
}



HRESULT STDMETHODCALLTYPE SaxContentHandlerImpl::startElement(
        /* [in] */ const wchar_t __RPC_FAR *UNUSED(pwchNamespaceUri),
        /* [in] */ int UNUSED(cchNamespaceUri),
        /* [in] */ const wchar_t __RPC_FAR *UNUSED(pwchLocalName),
        /* [in] */ int UNUSED(cchLocalName),
        /* [in] */ const wchar_t __RPC_FAR *UNUSED(pwchRawName),
        /* [in] */ int UNUSED(cchRawName),
        /* [in] */ ISAXAttributes __RPC_FAR *UNUSED(pAttributes))
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE SaxContentHandlerImpl::endElement(
        /* [in] */ const wchar_t __RPC_FAR *UNUSED(pwchNamespaceUri),
        /* [in] */ int UNUSED(cchNamespaceUri),
        /* [in] */ const wchar_t __RPC_FAR *UNUSED(pwchLocalName),
        /* [in] */ int UNUSED(cchLocalName),
        /* [in] */ const wchar_t __RPC_FAR *UNUSED(pwchRawName),
        /* [in] */ int UNUSED(cchRawName))
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE SaxContentHandlerImpl::characters(
        /* [in] */ const wchar_t __RPC_FAR *UNUSED(pwchChars),
        /* [in] */ int UNUSED(cchChars))
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE SaxContentHandlerImpl::ignorableWhitespace(
        /* [in] */ const wchar_t __RPC_FAR *UNUSED(pwchChars),
        /* [in] */ int UNUSED(cchChars))
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE SaxContentHandlerImpl::processingInstruction(
        /* [in] */ const wchar_t __RPC_FAR *UNUSED(pwchTarget),
        /* [in] */ int UNUSED(cchTarget),
        /* [in] */ const wchar_t __RPC_FAR *UNUSED(pwchData),
        /* [in] */ int UNUSED(cchData))
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE SaxContentHandlerImpl::skippedEntity(
        /* [in] */ const wchar_t __RPC_FAR *UNUSED(pwchVal),
        /* [in] */ int UNUSED(cchVal))
{
    return S_OK;
}


long __stdcall SaxContentHandlerImpl::QueryInterface(const struct _GUID &UNUSED(riid) ,void ** UNUSED(ppvObject))
{
    return 0;
}

unsigned long __stdcall SaxContentHandlerImpl::AddRef()
{
    return 0;
}

unsigned long __stdcall SaxContentHandlerImpl::Release()
{
    return 0;
}

