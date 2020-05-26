#pragma once

#ifdef VDMHOOK_EXPORTS
# define VDMHOOK_EXPORT extern "C" __declspec(dllexport)
#else
# define VDMHOOK_EXPORT extern "C" __declspec(dllimport)
#endif

namespace VdmHook
{
  __declspec(selectany) LPCWSTR   SharedMemoryName = L"VdmHook_SharedMemory";
                        const int SharedMemorySize = 4096;

  const int SharedMemoryOffsetEnabledFlag  = 0;
  const int SharedMemoryOffsetWindowHandle = 1;
  const int SharedMemoryOffsetStringData   = 5;

  __declspec(selectany) LPCWSTR SharedMemoryWriteSemaphoreName = L"VdmHook_SharedMemory_Write_Semaphore";
  __declspec(selectany) LPCWSTR SharedMemoryDataReadyEventName = L"VdmHook_SharedMemory_DataReady_Event";

  __declspec(selectany) LPCWSTR FileName = L"VDMHook.dll";
}

/*
Shared memory
0 - rules enabled flag
1 - top-level window handle
5 - process file path /0
  - window title /0
  - window class /0
*/