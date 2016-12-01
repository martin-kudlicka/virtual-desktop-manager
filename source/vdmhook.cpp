#include "vdmhook.h"

//#include <QtCore/qt_windows.h>
#include "../1stparty/VDM Hook/defs.h"
#include "vdmhookworker.h"
#include <QtCore/QThreadPool>

VdmHook::VdmHook() : _shellProcHook(WH_SHELL)
{
  _sharedMemory.setNativeKey(QString::fromWCharArray(VdmHookDefs::SharedMemoryName));
  _sharedMemory.create(VdmHookDefs::SharedMemorySize);
  setRulesEnabled(false);

  _vdmHookWorker = new VdmHookWorker(&_sharedMemory);
  QThreadPool::globalInstance()->start(_vdmHookWorker);

  _shellProcHook.set(VdmHookDefs::ShellProcName, VdmHookDefs::VdmHookDllFileName);
}

VdmHook::~VdmHook()
{
  _vdmHookWorker->stop();
  QThreadPool::globalInstance()->waitForDone();
}

void VdmHook::setRulesEnabled(bool enabled)
{
  _sharedMemory.lock();

  *reinterpret_cast<bool *>(static_cast<char *>(_sharedMemory.data()) + VdmHookDefs::SharedMemoryOffsetEnabledFlag) = enabled;

  _sharedMemory.unlock();
}