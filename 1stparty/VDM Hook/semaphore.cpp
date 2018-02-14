#include "semaphore.h"

#include "vdmhook.h"

Semaphore::Semaphore() : _semaphore(nullptr)
{
}

Semaphore::~Semaphore()
{
  CloseHandle(_semaphore);
}

void Semaphore::lock() const
{
  WaitForSingleObject(_semaphore, INFINITE);
}

void Semaphore::open(LPCWSTR name)
{
  _semaphore = OpenSemaphore(SYNCHRONIZE, FALSE, name);
}