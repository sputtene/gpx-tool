#ifndef INC_SAX_ERROR_HANDLER_IMPL
#define INC_SAX_ERROR_HANDLER_IMPL

class SaxErrorHandlerImpl : public ISAXErrorHandler
{
public:
    SaxErrorHandlerImpl();
    virtual ~SaxErrorHandlerImpl();

    // This must be correctly implemented, if your handler must be a COM Object (in this example it does not)
    long __stdcall QueryInterface(const struct _GUID &,void ** );
    unsigned long __stdcall AddRef(void);
    unsigned long __stdcall Release(void);

    virtual HRESULT STDMETHODCALLTYPE error(
        /* [in] */ ISAXLocator *pLocator,
        /* [in] */ const wchar_t *pwchErrorMessage,
        /* [in] */ HRESULT hrErrorCode);

    virtual HRESULT STDMETHODCALLTYPE fatalError(
        /* [in] */ ISAXLocator *pLocator,
        /* [in] */ const wchar_t *pwchErrorMessage,
        /* [in] */ HRESULT hrErrorCode);

    virtual HRESULT STDMETHODCALLTYPE ignorableWarning(
        /* [in] */ ISAXLocator *pLocator,
        /* [in] */ const wchar_t *pwchErrorMessage,
        /* [in] */ HRESULT hrErrorCode);
};


#endif  // INC_SAX_ERROR_HANDLER_IMPL
