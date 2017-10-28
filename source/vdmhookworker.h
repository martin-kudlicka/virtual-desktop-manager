#ifndef VDMHOOKWORKER_H
#define VDMHOOKWORKER_H

#include <QtCore/QRunnable>
#include <MkCore/MSystemSemaphore>
#include <MkCore/MSystemEvent>
#include "appinfo.h"

class QSharedMemory;

class VdmHookWorker : public QRunnable
{
  public:
             VdmHookWorker(QSharedMemory *sharedMemory);
    virtual ~VdmHookWorker() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    void stop();

  private:
    bool             _stop;
    MSystemEvent     _dataSync;
    MSystemSemaphore _writeSync;
    QSharedMemory   *_sharedMemory;

    void    processData()                    const;
    AppInfo readData   ()                    const;
    QString readString (wchar_t **sharedPos) const;

    virtual void run();
};

#endif