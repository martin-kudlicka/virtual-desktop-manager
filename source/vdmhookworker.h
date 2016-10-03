#ifndef VDMHOOKWORKER_H
#define VDMHOOKWORKER_H

#include <QtCore/QRunnable>
#include <MkCore/MSystemSemaphore>
#include <MkCore/MSystemEvent>

class QSharedMemory;

class VdmHookWorker : public QRunnable
{
  public:
             VdmHookWorker(QSharedMemory *sharedMemory);
    virtual ~VdmHookWorker();

    void stop();

  private:
    bool             _stop;
    MSystemEvent     _dataSync;
    MSystemSemaphore _writeSync;
    QSharedMemory   *_sharedMemory;

    virtual void run();
};

#endif