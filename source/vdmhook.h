#ifndef VDMHOOK_H
#define VDMHOOK_H

#include <QtCore/QSharedMemory>
#include <MkCore/MWindowsHook>

class VdmHookWorker;

class VdmHook
{
  public:
     VdmHook();
    ~VdmHook();

    void setRulesEnabled(bool enabled);

  private:
    MWindowsHook   _shellProcHook;
    VdmHookWorker *_vdmHookWorker;
    QSharedMemory  _sharedMemory;
};

#endif