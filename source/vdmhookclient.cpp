#include "vdmhookclient.h"

#include "../1stparty/VDM Hook/vdmhook.h"
#include "vdmhookworker.h"
#include <QtCore/QThreadPool>
#include <MkCore/MOperatingSystemVersion>
#include "../1stparty/VDM Helper/vdmhelper.h"
#include <QtCore/QProcess>

VdmHookClient::VdmHookClient() : _helperStopEvent(VdmHelper::StopEventName), _shellProcHook(WH_SHELL)
{
  _sharedMemory.setNativeKey(QString::fromWCharArray(VdmHook::SharedMemoryName));
  _sharedMemory.create(VdmHook::SharedMemorySize);
  setRulesEnabled(false);

  _vdmHookWorker = new VdmHookWorker(&_sharedMemory);
  QThreadPool::globalInstance()->start(_vdmHookWorker);

  _shellProcHook.set(VdmHook::ShellProcName, VdmHook::VdmHookDllFileName);

  if (MOperatingSystemVersion::platform() == MOperatingSystemVersion::Platform::X64)
  {
    QProcess::startDetached("VDMHelper.exe");
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