#include "applicationviewcollection.h"

#include <QtCore/QtGlobal>
#include "virtualdesktopmanagerinternal/immersiveshell.h"

ApplicationViewCollection::ApplicationViewCollection()
{
  _COM_SMARTPTR_TYPEDEF(IServiceProvider, IID_IServiceProvider);
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