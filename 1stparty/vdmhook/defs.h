#ifndef DEFS_H
#define DEFS_H

namespace VdmHookDefs
{
  static const wchar_t *SharedMemoryName = L"VDMHOOK_SHAREDMEMORY_NAME";
         const int      SharedMemorySize = 4096;

  static const wchar_t *SharedMemoryWriteSemaphoreName = L"VDMHOOK_SHAREDMEMORY_WRITE_SEMAPHORE";
  static const wchar_t *SharedMemoryDataReadyEventName = L"VDMHOOK_SHAREDMEMORY_DATAREADY_EVENT";

  static const wchar_t *VdmHookDllFileName = L"vdmhook.dll";

  static const char *ShellProcName = "_shellProc@12";
}

/*
Shared memory
0 - rules enabled flag
1 - process file path /0
  - window title /0
  - window class /0
*/

#endif