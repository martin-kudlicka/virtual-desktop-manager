#pragma once

#include <Windows.h>
#include "vdmhook.h"

VDMHOOK_EXPORT LRESULT CALLBACK ShellProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam);
void ShellWindowCreated(HWND window);