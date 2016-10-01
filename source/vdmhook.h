#ifndef VDMHOOK_H
#define VDMHOOK_H

#include <QtCore/QSharedMemory>
#include <MkCore/MWindowsHook>

class VdmHook
{
  public:
    VdmHook();

    void setRulesEnabled(bool enabled);

  private:
    MWindowsHook  _shellProcHook;
    QSharedMemory _sharedMemory;
};

#endif