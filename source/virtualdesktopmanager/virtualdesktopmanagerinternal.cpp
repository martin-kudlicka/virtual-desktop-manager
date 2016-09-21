#include "virtualdesktopmanagerinternal.h"

#include "virtualdesktopmanagerinternal/immersiveshell.h"
#include "virtualdesktopmanagerinternal/virtualdesktopapiunknown.h"

VirtualDesktopManagerInternal::VirtualDesktopManagerInternal()
{
  _COM_SMARTPTR_TYPEDEF(IServiceProvider, IID_IServiceProvider);
  IServiceProvider *serviceProvider = nullptr;
  CoCreateInstance(CLSID_ImmersiveShell, nullptr, CLSCTX_SERVER, IID_IServiceProvider, reinterpret_cast<LPVOID *>(&serviceProvider));

  serviceProvider->QueryService(CLSID_VirtualDesktopAPI_Unknown, IID_IVirtualDesktopManagerInternal, reinterpret_cast<LPVOID *>(&_iVirtualDesktopManagerInternal));
}

quintptr VirtualDesktopManagerInternal::count() const
{
  UINT count = 0;
  _iVirtualDesktopManagerInternal->GetCount(&count);

  return count;
}