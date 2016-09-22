#ifndef VIRTUALDESKTOPMANAGER_H
#define VIRTUALDESKTOPMANAGER_H

#include "virtualdesktopmanager/virtualdesktopmanagerinternal.h"
#include "virtualdesktopmanager/ivirtualdesktopmanager.h"
#include <MkCore/MLazySingleton>

class VirtualDesktopManager : public VirtualDesktopManagerInternal
{
  public:
             VirtualDesktopManager();
    virtual ~VirtualDesktopManager();

    quintptr index(HWND window) const;

  private:
    _COM_SMARTPTR_TYPEDEF(IVirtualDesktopManager, IID_IVirtualDesktopManager);

    IVirtualDesktopManagerPtr _iVirtualDesktopManager;
};

extern MLazySingleton<VirtualDesktopManager> gVirtualDesktopManager;

#endif