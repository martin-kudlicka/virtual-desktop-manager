#include "client.h"

#include "vdmhook.h"

Client::Client() : _mapping(nullptr), _sharedMemory(nullptr)
{
  _mapping      = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, VdmHook::SharedMemoryName);
  _sharedMemory = MapViewOfFile(_mapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
}

Client::~Client()
{
  UnmapViewOfFile(_sharedMemory);
  CloseHandle(_mapping);
}

bool Client::rulesEnabled() const
{
  return *static_cast<bool *>(_sharedMemory);
}

void Client::writeAppInfo(HWND window, LPCWSTR filePath, LPCWSTR windowTitle, LPCWSTR windowClass) const
{
  auto sharedPos = static_cast<LPBYTE>(_sharedMemory) + VdmHook::SharedMemoryOffsetWindowHandle;
  *reinterpret_cast<HWND *>(sharedPos) = window;

  sharedPos = static_cast<LPBYTE>(_sharedMemory) + VdmHook::SharedMemoryOffsetStringData;
  writeString(&sharedPos, filePath);
  writeString(&sharedPos, windowTitle);
  writeString(&sharedPos, windowClass);
}

void Client::writeString(LPBYTE *sharedPos, LPCWSTR text) const
{
  auto sharedOccupied = *sharedPos - static_cast<LPCBYTE>(_sharedMemory);
  auto sharedFree     = VdmHook::SharedMemorySize - sharedOccupied;
  auto textSize       = (wcslen(text) + 1) * sizeof(WCHAR);
  auto writeSize      = min(sharedFree, textSize);

  memcpy(*sharedPos, text, writeSize);
  *sharedPos += writeSize;
}