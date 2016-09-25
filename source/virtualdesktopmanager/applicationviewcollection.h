#ifndef APPLICATIONVIEWCOLLECTION_H
#define APPLICATIONVIEWCOLLECTION_H

#include "virtualdesktopmanagerinternal/iapplicationviewcollection.h"

class ApplicationViewCollection
{
  public:
    ApplicationViewCollection();

    IApplicationViewPtr forHwnd(HWND window) const;

  private:
    IApplicationViewCollectionPtr _iApplicationViewCollection;
};

#endif