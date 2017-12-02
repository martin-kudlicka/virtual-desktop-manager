#ifndef VIRTUALDESKTOPMANAGERINTERNAL_H
#define VIRTUALDESKTOPMANAGERINTERNAL_H

#include <QtCore/QList>
#include "virtualdesktopmanagerinternal/ivirtualdesktopmanagerinternal.h"

class VirtualDesktopManagerInternal
{
  public:
    using IVirtualDesktopList = QList<IVirtualDesktopPtr>;

    quintptr            count     ()                                         const;
    IVirtualDesktopList desktops  ()                                         const;
    IVirtualDesktopPtr  find      (GUID id)                                  const;
    void                moveViewTo(IApplicationViewPtr view, quintptr index) const;
    void                switchTo  (quintptr index)                           const;

  protected:
    VirtualDesktopManagerInternal();

  private:
    IVirtualDesktopManagerInternalPtr _iVirtualDesktopManagerInternal;
};

#endif