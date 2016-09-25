#ifndef IAPPLICATIONVIEWCOLLECTION_H
#define IAPPLICATIONVIEWCOLLECTION_H

#include <ObjectArray.h>
#include "iapplicationview.h"

EXTERN_C const IID IID_IApplicatonViewCollection;

MIDL_INTERFACE("2C08ADF0-A386-4B35-9250-0FE183476FCC") IApplicationViewCollection : public IUnknown
{
  public:
    virtual HRESULT STDMETHODCALLTYPE GetViews(IObjectArray **pArray) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetViewsByZOrder(IObjectArray **pArray) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetViewsByAppUserModelId(BSTR pId, IObjectArray **pArray) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetViewForHwnd(HWND pHwnd, IApplicationView **pView) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetViewForApplication(void *pApplication, IApplicationView **pView) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetViewForAppUserModelId(BSTR pId, IApplicationView **pView) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetViewInFocus(int *pView) = 0;
    virtual HRESULT STDMETHODCALLTYPE outreshCollection() = 0;
    virtual HRESULT STDMETHODCALLTYPE RegisterForApplicationViewChanges(void *pListener, int *pCookie) = 0;
    virtual HRESULT STDMETHODCALLTYPE RegisterForApplicationViewPositionChanges(void *pListener, int *pCookie) = 0;
    virtual HRESULT STDMETHODCALLTYPE UnregisterForApplicationViewChanges(int pCookie) = 0;
};

_COM_SMARTPTR_TYPEDEF(IApplicationViewCollection, IID_IApplicatonViewCollection);

#endif