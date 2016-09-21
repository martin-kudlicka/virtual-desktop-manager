#ifndef IVIRTUALDESKTOPMANAGER_H
#define IVIRTUALDESKTOPMANAGER_H

#include "virtualdesktopmanager/virtualdesktopmanagerinternal.h"
#include <ActiveQt/QAxObject>
#include <MkCore/MLazySingleton>

class VirtualDesktopManager : public VirtualDesktopManagerInternal
{
  public:
    VirtualDesktopManager();

  private:
    QAxObject _iVirtualDesktopManager;
};

extern MLazySingleton<VirtualDesktopManager> gVirtualDesktopManager;

#endif