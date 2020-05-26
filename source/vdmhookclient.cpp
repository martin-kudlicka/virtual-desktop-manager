#include "pch.h"
#include "vdmhookclient.h"

#include "../1stparty/VDM Hook/vdmhook.h"
#include "vdmhookworker.h"
#include "../1stparty/VDM Helper/vdmhelper.h"

VdmHookClient::VdmHookClient() : _helperStopEvent(VdmHelper::StopEventName), _shellProcHook(WH_SHELL)
{
  _sharedMemory.setNativeKey(QString::fromWCharArray(VdmHook::SharedMemoryName));
  if (!_sharedMemory.create(VdmHook::SharedMemorySize))
  {
    _sharedMemory.attach();
  }
  setRulesEnabled(false);

  _vdmHookWorker = new VdmHookWorker(&_sharedMemory);
  QThreadPool::globalInstance()->start(_vdmHookWorker);

  _shellProcHook.set("_shellProc@12", VdmHook::FileName);

  if (MOperatingSystemVersion::platform() == MOperatingSystemVersion::Platform::X64)
  {
    QProcess::startDetached("x64\\VDMHelper.exe");
  }
}

VdmHookClient::~VdmHookClient()
{
  if (MOperatingSystemVersion::platform() == MOperatingSystemVersion::Platform::X64)
  {
    _helperStopEvent.set();
  }

  _vdmHookWorker->stop();
  QThreadPool::globalInstance()->waitForDone();
}

void VdmHookClient::setRulesEnabled(bool enabled)
{
  _sharedMemory.lock();

  *reinterpret_cast<bool *>(static_cast<char *>(_sharedMemory.data()) + VdmHook::SharedMemoryOffsetEnabledFlag) = enabled;

  _sharedMemory.unlock();
}