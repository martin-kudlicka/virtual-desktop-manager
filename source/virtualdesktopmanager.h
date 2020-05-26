#ifndef VIRTUALDESKTOPMANAGER_H
#define VIRTUALDESKTOPMANAGER_H

#include "virtualdesktopmanager/virtualdesktopmanagerinternal.h"
#include "virtualdesktopmanager/ivirtualdesktopmanager.h"

class VirtualDesktopManager : public VirtualDesktopManagerInternal
{
  public:
    static const quintptr InvalidDesktop = std::numeric_limits<quintptr>::max();

             VirtualDesktopManager();
    virtual ~VirtualDesktopManager() Q_DECL_EQ_DEFAULT;

    quintptr index       (HWND window)                 const;
    void     moveWindowTo(HWND window, quintptr index) const;

  private:
    IVirtualDesktopManagerPtr _iVirtualDesktopManager;
};

extern MLazySingleton<VirtualDesktopManager> gVirtualDesktopManager;

#endif