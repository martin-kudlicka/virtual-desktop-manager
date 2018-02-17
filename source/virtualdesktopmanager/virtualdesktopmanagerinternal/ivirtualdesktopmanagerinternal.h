#ifndef IVIRTUALDESKTOPMANAGERINTERNAL_H
#define IVIRTUALDESKTOPMANAGERINTERNAL_H

#include "iapplicationview.h"
#include "ivirtualdesktop.h"
#include <ObjectArray.h>

EXTERN_C const IID IID_IVirtualDesktopManagerInternal;

enum AdjacentDesktop
{
  LeftDirection  = 3,
  RightDirection = 4
};

MIDL_INTERFACE("F31574D6-B682-4CDC-BD56-1827860ABEC6") IVirtualDesktopManagerInternal : public IUnknown
{
  public:
    virtual HRESULT STDMETHODCALLTYPE GetCount           (UINT *pCount)                                                                                        = 0;
    virtual HRESULT STDMETHODCALLTYPE MoveViewToDesktop  (IApplicationView *pView, IVirtualDesktop *pDesktop)                                                  = 0;
    virtual HRESULT STDMETHODCALLTYPE CanViewMoveDesktops(IApplicationView *pView, int *pfCanViewMoveDesktops)                                                 = 0;
    virtual HRESULT STDMETHODCALLTYPE GetCurrentDesktop  (IVirtualDesktop** desktop)                                                                           = 0;
    virtual HRESULT STDMETHODCALLTYPE GetDesktops        (IObjectArray **ppDesktops)                                                                           = 0;
    virtual HRESULT STDMETHODCALLTYPE GetAdjacentDesktop (IVirtualDesktop *pDesktopReference, AdjacentDesktop uDirection, IVirtualDesktop **ppAdjacentDesktop) = 0;
    virtual HRESULT STDMETHODCALLTYPE SwitchDesktop      (IVirtualDesktop *pDesktop)                                                                           = 0;
    virtual HRESULT STDMETHODCALLTYPE CreateDesktopW     (IVirtualDesktop **ppNewDesktop)                                                                      = 0;
    virtual HRESULT STDMETHODCALLTYPE RemoveDesktop      (IVirtualDesktop *pRemove, IVirtualDesktop *pFallbackDesktop)                                         = 0;
    virtual HRESULT STDMETHODCALLTYPE FindDesktop        (GUID *desktopId, IVirtualDesktop **ppDesktop)                                                        = 0;
};

_COM_SMARTPTR_TYPEDEF(IVirtualDesktopManagerInternal, IID_IVirtualDesktopManagerInternal);

#endif