#include "SaxErrorHandlerImpl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SAXErrorHandlerImpl::SAXErrorHandlerImpl()
{

}

SAXErrorHandlerImpl::~SAXErrorHandlerImpl()
{

}

HRESULT STDMETHODCALLTYPE SAXErrorHandlerImpl::error(
            /* [in] */ ISAXLocator __RPC_FAR *pLocator,
            /* [in] */ const wchar_t * pwchErrorMessage,
            /* [in] */ HRESULT errCode)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE SAXErrorHandlerImpl::fatalError(
            /* [in] */ ISAXLocator __RPC_FAR *pLocator,
            /* [in] */ const wchar_t * pwchErrorMessage,
            /* [in] */ HRESULT errCode)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE SAXErrorHandlerImpl::ignorableWarning(
            /* [in] */ ISAXLocator __RPC_FAR *pLocator,
            /* [in] */ const wchar_t * pwchErrorMessage,
            /* [in] */ HRESULT errCode)
{
    return S_OK;
}

long __stdcall SAXErrorHandlerImpl::QueryInterface(const struct _GUID &,void ** )
{
    return 0;
}

unsigned long __stdcall SAXErrorHandlerImpl::AddRef()
{
    return 0;
}

unsigned long __stdcall SAXErrorHandlerImpl::Release()
{
    return 0;
}
