#include "semaphore.h"

#include "defs.h"

Semaphore::Semaphore()
{
  _semaphore = CreateSemaphore(nullptr, 1, 1, VdmHookDefs::SharedMemorySemaphoreName);
}

Semaphore::~Semaphore()
{
  CloseHandle(_semaphore);
}

void Semaphore::lock()
{
  WaitForSingleObject(_semaphore, INFINITE);
}

void Semaphore::unlock()
{
  ReleaseSemaphore(_semaphore, 1, nullptr);
}