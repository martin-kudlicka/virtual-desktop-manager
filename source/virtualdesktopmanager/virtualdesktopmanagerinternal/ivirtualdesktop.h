#ifndef IVIRTUALDESKTOP_H
#define IVIRTUALDESKTOP_H

#include "iapplicationview.h"

EXTERN_C const IID IID_IVirtualDesktop;

MIDL_INTERFACE("FF72FFDD-BE7E-43FC-9C03-AD81681E88E4") IVirtualDesktop : public IUnknown
{
  public:
    virtual HRESULT STDMETHODCALLTYPE IsViewVisible(IApplicationView *pView, int *pfVisible) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetID        (GUID *pGuid)                             = 0;
};

_COM_SMARTPTR_TYPEDEF(IVirtualDesktop, IID_IVirtualDesktop);

#endif