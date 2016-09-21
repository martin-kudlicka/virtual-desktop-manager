#include "virtualdesktopmanagerinternal.h"

#include <ActiveQt/QAxObject>
#include <QtCore/QUuid>
#include "virtualdesktopmanagerinternal/virtualdesktopapiunknown.h"

VirtualDesktopManagerInternal::VirtualDesktopManagerInternal()
{
  QAxObject immersiveShell("c2f03a33-21f5-47fa-b4bb-156362a2f239");

  _COM_SMARTPTR_TYPEDEF(IServiceProvider, IID_IServiceProvider);
  IServiceProvider *serviceProvider = nullptr;
  immersiveShell.queryInterface("6d5140c1-7436-11ce-8034-00aa006009fa", reinterpret_cast<LPVOID *>(&serviceProvider));

  serviceProvider->QueryService(CLSID_VirtualDesktopAPI_Unknown, IID_IVirtualDesktopManagerInternal, reinterpret_cast<LPVOID *>(&_iVirtualDesktopManagerInternal));
}

quintptr VirtualDesktopManagerInternal::count() const
{
  UINT count = 0;
  _iVirtualDesktopManagerInternal->GetCount(&count);

  return count;
}