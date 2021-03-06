#include "pch.h"
#include "applicationviewcollection.h"

#include "virtualdesktopmanagerinternal/immersiveshell.h"

ApplicationViewCollection::ApplicationViewCollection()
{
  IServiceProviderPtr serviceProvider;
  CoCreateInstance(CLSID_ImmersiveShell, Q_NULLPTR, CLSCTX_LOCAL_SERVER, IID_IServiceProvider, reinterpret_cast<LPVOID *>(&serviceProvider));

  serviceProvider->QueryService(IID_IApplicatonViewCollection, &_iApplicationViewCollection);
}

IApplicationViewPtr ApplicationViewCollection::forHwnd(HWND window) const
{
  IApplicationViewPtr applicationView;
  _iApplicationViewCollection->GetViewForHwnd(window, &applicationView);

  return applicationView;
}