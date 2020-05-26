#ifndef IVIRTUALDESKTOPMANAGER_H
#define IVIRTUALDESKTOPMANAGER_H

//EXTERN_C const CLSID CLSID_IVirtualDesktopManager;
EXTERN_C const IID IID_IVirtualDesktopManager;

MIDL_INTERFACE("A5CD92FF-29BE-454C-8D04-D82879FB3F1B") IVirtualDesktopManager : public IUnknown
{
  public:
    virtual HRESULT STDMETHODCALLTYPE IsWindowOnCurrentVirtualDesktop(/* [in] */ __RPC__in HWND topLevelWindow, /* [out] */ __RPC__out BOOL *onCurrentDesktop) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetWindowDesktopId             (/* [in] */ __RPC__in HWND topLevelWindow, /* [out] */ __RPC__out GUID *desktopId)        = 0;
    virtual HRESULT STDMETHODCALLTYPE MoveWindowToDesktop            (/* [in] */ __RPC__in HWND topLevelWindow, /* [in] */ __RPC__in REFGUID desktopId)        = 0;
};

_COM_SMARTPTR_TYPEDEF(IVirtualDesktopManager, IID_IVirtualDesktopManager);

#endif