#include "vdmhook.h"

//#include <QtCore/qt_windows.h>
#include "../1stparty/vdmhook/defs.h"

VdmHook::VdmHook() : _shellProcHook(WH_SHELL)
{
  _sharedMemory.setNativeKey(QString::fromWCharArray(VdmHookDefs::SharedMemoryName));
  _sharedMemory.create(VdmHookDefs::SharedMemorySize);
  memset(_sharedMemory.data(), 0, _sharedMemory.size());

  _shellProcHook.set(VdmHookDefs::ShellProcName, VdmHookDefs::VdmHookDllFileName);
}

void VdmHook::setRulesEnabled(bool enabled)
{
  _sharedMemory.lock();

  *static_cast<bool *>(_sharedMemory.data()) = enabled;

  _sharedMemory.unlock();
}