#include "vdmhookworker.h"

#include "../1stparty/VDM Hook/defs.h"
#include <QtCore/QSharedMemory>
#include "virtualdesktopmanager.h"
#include <MkCore/MCoInitialize>

VdmHookWorker::VdmHookWorker(QSharedMemory *sharedMemory) : _sharedMemory(sharedMemory), _stop(false), _dataSync(VdmHookDefs::SharedMemoryDataReadyEventName), _writeSync(VdmHookDefs::SharedMemoryWriteSemaphoreName)
{
}

void VdmHookWorker::stop()
{
  _stop = true;
  _dataSync.set();
}

void VdmHookWorker::processData() const
{
  auto appInfo = readData();

  auto ruleOptions = appInfo.bestRule();
  if (!ruleOptions.valid())
  {
    return;
  }

  switch (ruleOptions.action())
  {
    case RuleOptions::ActionType::MoveToDesktop:
      gVirtualDesktopManager->moveWindowTo(appInfo.window().handle, ruleOptions.desktopIndex() - 1);
      break;
    case RuleOptions::ActionType::KeepOnDesktop:
      // TODO
      break;
    case RuleOptions::ActionType::AutoClose:
      PostMessage(appInfo.window().handle, WM_CLOSE, 0, 0);
      break;
    default:
      Q_UNREACHABLE();
  }
}

AppInfo VdmHookWorker::readData() const
{
  _sharedMemory->lock();

  AppInfo appInfo;

  appInfo.window().handle = *reinterpret_cast<HWND *>(static_cast<char *>(_sharedMemory->data()) + VdmHookDefs::SharedMemoryOffsetWindowHandle);

  auto sharedPos = static_cast<char *>(_sharedMemory->data()) + VdmHookDefs::SharedMemoryOffsetStringData;
  appInfo.process().fileInfo.setFile(readString(reinterpret_cast<wchar_t **>(&sharedPos)));
  appInfo.window().title     = readString(reinterpret_cast<wchar_t **>(&sharedPos));
  appInfo.window().className = readString(reinterpret_cast<wchar_t **>(&sharedPos));

  _sharedMemory->unlock();

  return appInfo;
}

QString VdmHookWorker::readString(wchar_t **sharedPos) const
{
  QString text;

  while (**sharedPos)
  {
    text.append(**sharedPos);

    ++(*sharedPos);
  }

  ++(*sharedPos);

  return text;
}

void VdmHookWorker::run()
{
  MCoInitialize coInitialize;

  forever
  {
    _dataSync.wait();

    if (_stop)
    {
      break;
    }

    processData();

    _writeSync.release();
  }
}