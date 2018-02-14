#ifndef VDMHOOK_H
#define VDMHOOK_H

#include <QtCore/QSharedMemory>
#include <MkCore/MWindowsHook>
#include <MkCore/MSystemEvent>

class VdmHookWorker;

class VdmHookClient
{
  public:
     VdmHookClient();
    ~VdmHookClient();

    void setRulesEnabled(bool enabled);

  private:
    MSystemEvent   _helperStopEvent;
    MWindowsHook   _shellProcHook;
    QSharedMemory  _sharedMemory;
    VdmHookWorker *_vdmHookWorker;
};

#endif