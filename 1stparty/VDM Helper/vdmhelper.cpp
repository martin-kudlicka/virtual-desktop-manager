#include "stdafx.h"
#include "vdmhelper.h"

#include "../common/event.h"
#include "../VDM Hook/vdmhook.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
  UNREFERENCED_PARAMETER(hInstance);
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);
  UNREFERENCED_PARAMETER(nCmdShow);

  Event stopEvent;
  stopEvent.open(SYNCHRONIZE, VdmHelper::StopEventName);

  auto vdmHook = LoadLibrary(VdmHook::FileName);

  auto hookProc = GetProcAddress(vdmHook, "shellProc");
  auto hook     = SetWindowsHookEx(WH_SHELL, reinterpret_cast<HOOKPROC>(hookProc), vdmHook, 0);

  for (;;)
  {
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
      DispatchMessage(&msg);
    }

    auto wait = MsgWaitForMultipleObjects(1, &stopEvent, FALSE, INFINITE, QS_ALLINPUT);
    if (wait == WAIT_OBJECT_0 + 1)
    {
      continue;
    }

    break;
  }

  UnhookWindowsHookEx(hook);

  FreeLibrary(vdmHook);

  return ERROR_SUCCESS;
}