#pragma once

#include "vdmhook.h"

void shellWindowCreated(HWND window);

VDMHOOK_EXPORT LRESULT CALLBACK shellProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam);