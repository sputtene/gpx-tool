#include "SaxContentHandlerImpl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


SAXContentHandlerImpl::SAXContentHandlerImpl()
{
}

SAXContentHandlerImpl::~SAXContentHandlerImpl()
{
}



HRESULT STDMETHODCALLTYPE SAXContentHandlerImpl::putDocumentLocator(
        /* [in] */ ISAXLocator __RPC_FAR *pLocator
        )
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE SAXContentHandlerImpl::startDocument()
{
    return S_OK;
}



HRESULT STDMETHODCALLTYPE SAXContentHandlerImpl::endDocument( void)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE SAXContentHandlerImpl::startPrefixMapping(
        /* [in] */ const wchar_t __RPC_FAR *pwchPrefix,
        /* [in] */ int cchPrefix,
        /* [in] */ const wchar_t __RPC_FAR *pwchUri,
        /* [in] */ int cchUri)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE SAXContentHandlerImpl::endPrefixMapping(
        /* [in] */ const wchar_t __RPC_FAR *pwchPrefix,
        /* [in] */ int cchPrefix)
{
    return S_OK;
}



HRESULT STDMETHODCALLTYPE SAXContentHandlerImpl::startElement(
        /* [in] */ const wchar_t __RPC_FAR *pwchNamespaceUri,
        /* [in] */ int cchNamespaceUri,
        /* [in] */ const wchar_t __RPC_FAR *pwchLocalName,
        /* [in] */ int cchLocalName,
        /* [in] */ const wchar_t __RPC_FAR *pwchRawName,
        /* [in] */ int cchRawName,
        /* [in] */ ISAXAttributes __RPC_FAR *pAttributes)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE SAXContentHandlerImpl::endElement(
        /* [in] */ const wchar_t __RPC_FAR *pwchNamespaceUri,
        /* [in] */ int cchNamespaceUri,
        /* [in] */ const wchar_t __RPC_FAR *pwchLocalName,
        /* [in] */ int cchLocalName,
        /* [in] */ const wchar_t __RPC_FAR *pwchRawName,
        /* [in] */ int cchRawName)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE SAXContentHandlerImpl::characters(
        /* [in] */ const wchar_t __RPC_FAR *pwchChars,
        /* [in] */ int cchChars)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE SAXContentHandlerImpl::ignorableWhitespace(
        /* [in] */ const wchar_t __RPC_FAR *pwchChars,
        /* [in] */ int cchChars)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE SAXContentHandlerImpl::processingInstruction(
        /* [in] */ const wchar_t __RPC_FAR *pwchTarget,
        /* [in] */ int cchTarget,
        /* [in] */ const wchar_t __RPC_FAR *pwchData,
        /* [in] */ int cchData)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE SAXContentHandlerImpl::skippedEntity(
        /* [in] */ const wchar_t __RPC_FAR *pwchVal,
        /* [in] */ int cchVal)
{
    return S_OK;
}


long __stdcall SAXContentHandlerImpl::QueryInterface(const struct _GUID &riid,void ** ppvObject)
{
    return 0;
}

unsigned long __stdcall SAXContentHandlerImpl::AddRef()
{
    return 0;
}

unsigned long __stdcall SAXContentHandlerImpl::Release()
{
    return 0;
}

