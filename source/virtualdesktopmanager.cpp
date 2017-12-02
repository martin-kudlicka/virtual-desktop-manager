#include "virtualdesktopmanager.h"

#include "virtualdesktopmanager/virtualdesktopmanagerinternal/immersiveshell.h"
#include "virtualdesktopmanager/applicationviewcollection.h"

MLazySingleton<VirtualDesktopManager> gVirtualDesktopManager;

VirtualDesktopManager::VirtualDesktopManager()
{
  _COM_SMARTPTR_TYPEDEF(IServiceProvider, IID_IServiceProvider);
  IServiceProviderPtr serviceProvider = Q_NULLPTR;
  CoCreateInstance(CLSID_ImmersiveShell, Q_NULLPTR, CLSCTX_LOCAL_SERVER, IID_IServiceProvider, reinterpret_cast<LPVOID *>(&serviceProvider));

  serviceProvider->QueryService(IID_IVirtualDesktopManager, &_iVirtualDesktopManager);
}

quintptr VirtualDesktopManager::index(HWND window) const
{
  GUID id;
  _iVirtualDesktopManager->GetWindowDesktopId(window, &id);

  quintptr index2 = 0;
  for (const auto &desktop : desktops())
  {
    GUID id2;
    desktop->GetID(&id2);
    if (id == id2)
    {
      return index2;
    }

    ++index2;
  }

  return InvalidDesktop;
}

void VirtualDesktopManager::moveWindowTo(HWND window, quintptr index) const
{
  DWORD processId;
  GetWindowThreadProcessId(window, &processId);

  if (processId == GetCurrentProcessId())
  {
    auto desktop = desktops().at(index);

    GUID id;
    desktop->GetID(&id);

    _iVirtualDesktopManager->MoveWindowToDesktop(window, id);
  }
  else
  {
    auto applicationView = ApplicationViewCollection().forHwnd(window);
    moveViewTo(applicationView, index);
  }
}