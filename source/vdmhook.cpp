#include "vdmhook.h"

#include "../1stparty/VDM Hook/defs.h"
#include "vdmhookworker.h"
#include <QtCore/QThreadPool>
#include <MkCore/MOperatingSystemVersion>
#include "../1stparty/VDM Helper/defs.h"
#include <QtCore/QProcess>

VdmHook::VdmHook() : _helperStopEvent(VdmHelperDefs::StopEventName), _shellProcHook(WH_SHELL)
{
  _sharedMemory.setNativeKey(QString::fromWCharArray(VdmHookDefs::SharedMemoryName));
  _sharedMemory.create(VdmHookDefs::SharedMemorySize);
  setRulesEnabled(false);

  _vdmHookWorker = new VdmHookWorker(&_sharedMemory);
  QThreadPool::globalInstance()->start(_vdmHookWorker);

  _shellProcHook.set(VdmHookDefs::ShellProcName, VdmHookDefs::VdmHookDllFileName);

  if (MOperatingSystemVersion::platform() == MOperatingSystemVersion::Platform::X64)
  {
    QProcess::startDetached("VDMHelper.exe");
  }
}

VdmHook::~VdmHook()
{
  if (MOperatingSystemVersion::platform() == MOperatingSystemVersion::Platform::X64)
  {
    _helperStopEvent.set();
  }

  _vdmHookWorker->stop();
  QThreadPool::globalInstance()->waitForDone();
}

void VdmHook::setRulesEnabled(bool enabled)
{
  _sharedMemory.lock();

  *reinterpret_cast<bool *>(static_cast<char *>(_sharedMemory.data()) + VdmHookDefs::SharedMemoryOffsetEnabledFlag) = enabled;

  _sharedMemory.unlock();
}