#ifndef VIRTUALDESKTOPMANAGERINTERNAL_H
#define VIRTUALDESKTOPMANAGERINTERNAL_H

#include <QtCore/QList>
#include <comdef.h>
#include "virtualdesktopmanagerinternal/ivirtualdesktopmanagerinternal.h"

class VirtualDesktopManagerInternal
{
  public:
    _COM_SMARTPTR_TYPEDEF(IVirtualDesktop, IID_IVirtualDesktop);
    using IVirtualDesktopList = QList<IVirtualDesktopPtr>;

    quintptr            count   ()               const;
    IVirtualDesktopList desktops()               const;
    void                switchTo(quintptr index) const;

  protected:
    VirtualDesktopManagerInternal();

  private:
    _COM_SMARTPTR_TYPEDEF(IVirtualDesktopManagerInternal, IID_IVirtualDesktopManagerInternal);

    IVirtualDesktopManagerInternalPtr _iVirtualDesktopManagerInternal;
};

#endif