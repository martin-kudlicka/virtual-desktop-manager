#ifndef DEFS_H
#define DEFS_H

namespace VdmHookDefs
{
  static const wchar_t *SharedMemoryName = L"VdmHook_SharedMemory_Name";
         const int      SharedMemorySize = 4096;

  const int SharedMemoryOffsetEnabledFlag  = 0;
  const int SharedMemoryOffsetWindowHandle = 1;
  const int SharedMemoryOffsetStringData   = 5;

  static const wchar_t *SharedMemoryWriteSemaphoreName = L"VdmHook_SharedMemory_Write_Semaphore";
  static const wchar_t *SharedMemoryDataReadyEventName = L"VdmHook_SharedMemory_DataReady_Event";

  static const wchar_t *VdmHookDllFileName = L"vdmhook.dll";

  static const char *ShellProcName = "_shellProc@12";
}

/*
Shared memory
0 - rules enabled flag
1 - top-level window handle
5 - process file path /0
  - window title /0
  - window class /0
*/

#endif