#include "virtualdesktopmanagerinternal.h"

#include "virtualdesktopmanagerinternal/immersiveshell.h"
#include "virtualdesktopmanagerinternal/virtualdesktopapiunknown.h"

VirtualDesktopManagerInternal::VirtualDesktopManagerInternal()
{
  _COM_SMARTPTR_TYPEDEF(IServiceProvider, IID_IServiceProvider);
  IServiceProviderPtr serviceProvider = Q_NULLPTR;
  CoCreateInstance(CLSID_ImmersiveShell, Q_NULLPTR, CLSCTX_LOCAL_SERVER, IID_IServiceProvider, reinterpret_cast<LPVOID *>(&serviceProvider));

  serviceProvider->QueryService(CLSID_VirtualDesktopAPI_Unknown, &_iVirtualDesktopManagerInternal);
}

quintptr VirtualDesktopManagerInternal::count() const
{
  UINT count;
  _iVirtualDesktopManagerInternal->GetCount(&count);

  return count;
}

VirtualDesktopManagerInternal::IVirtualDesktopList VirtualDesktopManagerInternal::desktops() const
{
  _COM_SMARTPTR_TYPEDEF(IObjectArray, IID_IObjectArray);
  IObjectArrayPtr desktopObjects;
  _iVirtualDesktopManagerInternal->GetDesktops(&desktopObjects);

  IVirtualDesktopList virtualDesktops;

  UINT desktopCount;
  desktopObjects->GetCount(&desktopCount);
  for (UINT desktopIndex = 0; desktopIndex < desktopCount; ++desktopIndex)
  {
    IVirtualDesktopPtr virtualDesktop;
    desktopObjects->GetAt(desktopIndex, IID_IVirtualDesktop, reinterpret_cast<LPVOID *>(&virtualDesktop));

    virtualDesktops.append(qMove(virtualDesktop));
  }

  return virtualDesktops;
}

IVirtualDesktopPtr VirtualDesktopManagerInternal::find(GUID id) const
{
  IVirtualDesktopPtr virtualDesktop;
  _iVirtualDesktopManagerInternal->FindDesktop(&id, &virtualDesktop);

  return virtualDesktop;
}

void VirtualDesktopManagerInternal::moveViewTo(IApplicationViewPtr view, quintptr index) const
{
  _iVirtualDesktopManagerInternal->MoveViewToDesktop(view, desktops().at(index));
}

void VirtualDesktopManagerInternal::switchTo(quintptr index) const
{
  quintptr index2 = 0;
  for (const auto &desktop : desktops())
  {
    if (index2 == index)
    {
      _iVirtualDesktopManagerInternal->SwitchDesktop(desktop);
      return;
    }

    ++index2;
  }

  Q_UNREACHABLE();
  return;
}