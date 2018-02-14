#pragma once

#ifdef VDMHOOK_EXPORTS
# define VDMHOOK_EXPORT extern "C" __declspec(dllexport)
#else
# define VDMHOOK_EXPORT extern "C" __declspec(dllimport)
#endif

namespace VdmHook
{
  static LPCWSTR   SharedMemoryName = L"VdmHook_SharedMemory";
         const int SharedMemorySize = 4096;

  const int SharedMemoryOffsetEnabledFlag  = 0;
  const int SharedMemoryOffsetWindowHandle = 1;
  const int SharedMemoryOffsetStringData   = 5;

  static LPCWSTR SharedMemoryWriteSemaphoreName = L"VdmHook_SharedMemory_Write_Semaphore";
  static LPCWSTR SharedMemoryDataReadyEventName = L"VdmHook_SharedMemory_DataReady_Event";

  static LPCWSTR VdmHookDllFileName = L"vdmhook.dll";

  static LPCSTR ShellProcName = "_shellProc@12";
}

/*
Shared memory
0 - rules enabled flag
1 - top-level window handle
5 - process file path /0
  - window title /0
  - window class /0
*/