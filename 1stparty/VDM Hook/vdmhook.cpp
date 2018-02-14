#include <Windows.h>
#include "event.h"
#include "semaphore.h"
#include "vdmhook.h"

extern Event     gDataSync;
extern Semaphore gWriteSync;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	  case DLL_PROCESS_ATTACH:
      gDataSync.open(VdmHook::SharedMemoryDataReadyEventName);
      gWriteSync.open(VdmHook::SharedMemoryWriteSemaphoreName);
      break;
	  case DLL_THREAD_ATTACH:
	  case DLL_THREAD_DETACH:
	  case DLL_PROCESS_DETACH:
		  break;
	}

	return TRUE;
}