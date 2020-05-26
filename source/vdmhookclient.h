#ifndef VDMHOOK_H
#define VDMHOOK_H

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