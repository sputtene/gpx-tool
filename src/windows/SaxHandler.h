#ifndef INC_SAX_HANDLER
#define INC_SAX_HANDLER

#include "SaxContentHandlerImpl.h"
#include "SaxErrorHandlerImpl.h"

class SaxHandler : public SaxContentHandlerImpl,
    public SaxErrorHandlerImpl
{
public:
    SaxHandler();
    virtual ~SaxHandler();

    virtual HRESULT STDMETHODCALLTYPE startElement(
        /* [in] */ const wchar_t __RPC_FAR *pwchNamespaceUri,
        /* [in] */ int cchNamespaceUri,
        /* [in] */ const wchar_t __RPC_FAR *pwchLocalName,
        /* [in] */ int cchLocalName,
        /* [in] */ const wchar_t __RPC_FAR *pwchRawName,
        /* [in] */ int cchRawName,
        /* [in] */ ISAXAttributes __RPC_FAR *pAttributes);

    virtual HRESULT STDMETHODCALLTYPE endElement(
        /* [in] */ const wchar_t __RPC_FAR *pwchNamespaceUri,
        /* [in] */ int cchNamespaceUri,
        /* [in] */ const wchar_t __RPC_FAR *pwchLocalName,
        /* [in] */ int cchLocalName,
        /* [in] */ const wchar_t __RPC_FAR *pwchRawName,
        /* [in] */ int cchRawName);

    virtual HRESULT STDMETHODCALLTYPE characters(
        /* [in] */ const wchar_t __RPC_FAR *pwchChars,
        /* [in] */ int cchChars);

    virtual HRESULT STDMETHODCALLTYPE startDocument();

private:
    void prt(
        /* [in] */ const wchar_t * pwchFmt,
        /* [in] */ const wchar_t __RPC_FAR *pwchVal,
        /* [in] */ int cchVal);
    int idnt;
};


#endif  // INC_SAX_HANDLER
