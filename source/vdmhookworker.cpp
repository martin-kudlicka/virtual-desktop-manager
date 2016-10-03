#include "vdmhookworker.h"

#include "../1stparty/vdmhook/defs.h"

VdmHookWorker::VdmHookWorker(QSharedMemory *sharedMemory) : _sharedMemory(sharedMemory), _stop(false), _dataSync(VdmHookDefs::SharedMemoryDataReadyEventName), _writeSync(VdmHookDefs::SharedMemoryWriteSemaphoreName)
{
}

VdmHookWorker::~VdmHookWorker()
{
}

void VdmHookWorker::stop()
{
  _stop = true;
  _dataSync.set();
}

void VdmHookWorker::run()
{
  forever
  {
    _dataSync.wait();

    if (_stop)
    {
      break;
    }

    // TODO

    _writeSync.release();
  }
}