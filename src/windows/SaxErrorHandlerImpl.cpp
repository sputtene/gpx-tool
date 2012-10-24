#include "SaxErrorHandlerImpl.h"

#include "../common.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SaxErrorHandlerImpl::SaxErrorHandlerImpl()
{

}

SaxErrorHandlerImpl::~SaxErrorHandlerImpl()
{

}

HRESULT STDMETHODCALLTYPE SaxErrorHandlerImpl::error(
            /* [in] */ ISAXLocator __RPC_FAR *UNUSED(pLocator),
            /* [in] */ const wchar_t * UNUSED(pwchErrorMessage),
            /* [in] */ HRESULT UNUSED(errCode))
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE SaxErrorHandlerImpl::fatalError(
            /* [in] */ ISAXLocator __RPC_FAR *UNUSED(pLocator),
            /* [in] */ const wchar_t * UNUSED(pwchErrorMessage),
            /* [in] */ HRESULT UNUSED(errCode))
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE SaxErrorHandlerImpl::ignorableWarning(
            /* [in] */ ISAXLocator __RPC_FAR *UNUSED(pLocator),
            /* [in] */ const wchar_t * UNUSED(pwchErrorMessage),
            /* [in] */ HRESULT UNUSED(errCode))
{
    return S_OK;
}

long __stdcall SaxErrorHandlerImpl::QueryInterface(const struct _GUID &,void ** )
{
    return 0;
}

unsigned long __stdcall SaxErrorHandlerImpl::AddRef()
{
    return 0;
}

unsigned long __stdcall SaxErrorHandlerImpl::Release()
{
    return 0;
}
