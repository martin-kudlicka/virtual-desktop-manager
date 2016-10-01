#ifndef DEFS_H
#define DEFS_H

namespace VdmHookDefs
{
  const wchar_t *SharedMemoryName = L"VDMHOOK_SHAREDMEMORY_NAME";
  const int      SharedMemorySize = 4096;

  const wchar_t *VdmHookDllFileName = L"vdmhook.dll";

  const char *ShellProcName = "_ShellProc@12";
}

/*
Shared memory
0 - rules enabled flag
*/

#endif