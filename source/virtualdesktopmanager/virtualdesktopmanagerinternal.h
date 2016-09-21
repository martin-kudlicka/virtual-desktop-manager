#ifndef VIRTUALDESKTOPMANAGERINTERNAL_H
#define VIRTUALDESKTOPMANAGERINTERNAL_H

#include <QtCore/QtGlobal>
#include <comdef.h>
#include "virtualdesktopmanagerinternal/ivirtualdesktopmanagerinternal.h"

class VirtualDesktopManagerInternal
{
  public:
    quintptr count() const;

  protected:
    VirtualDesktopManagerInternal();

  private:
    _COM_SMARTPTR_TYPEDEF(IVirtualDesktopManagerInternal, IID_IVirtualDesktopManagerInternal);

    IVirtualDesktopManagerInternalPtr _iVirtualDesktopManagerInternal;
};

#endif