#include "shellhook.h"

#include "client.h"
#include "semaphore.h"
#include "event.h"

Client    gClient;
Event     gDataSync;
Semaphore gWriteSync;

VDMHOOK_EXPORT LRESULT CALLBACK shellProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
  if (gClient.rulesEnabled())
  {
    switch (nCode)
    {
      case HSHELL_WINDOWCREATED:
        shellWindowCreated(reinterpret_cast<HWND>(wParam));
    }
  }

  return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

void shellWindowCreated(HWND window)
{
  WCHAR windowTitle[4096] = { 0 };
  auto chars = GetWindowText(window, windowTitle, _countof(windowTitle));
  if (chars == 0)
  {
    return;
  }

  WCHAR filePath[4096] = { 0 };
  chars = GetModuleFileName(nullptr, filePath, _countof(filePath));
  if (chars == 0)
  {
    return;
  }

  WCHAR windowClass[4096] = { 0 };
  GetClassName(window, windowClass, _countof(windowClass));

  gWriteSync.lock();

  gClient.setAppInfo(filePath, windowTitle, windowClass);

  gDataSync.set();
}