#include "shellhook.h"

#include "client.h"

Client gClient;

VDMHOOK_EXPORT LRESULT CALLBACK ShellProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
  if (gClient.rulesEnabled())
  {
    switch (nCode)
    {
      case HSHELL_WINDOWCREATED:
        ShellWindowCreated(reinterpret_cast<HWND>(wParam));
    }
  }

  return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

void ShellWindowCreated(HWND window)
{
  WCHAR text[4096] = { 0 };

  auto chars = GetWindowText(window, text, _countof(text));
  if (chars == 0)
  {
    return;
  }

  chars = GetClassName(window, text, _countof(text));
  if (chars > 0)
  {
    // TODO
  }

  // TODO
}