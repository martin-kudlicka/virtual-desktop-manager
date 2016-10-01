#include "client.h"

#include "defs.h"

Client::Client() : _mapping(nullptr), _sharedMemory(nullptr)
{
  _mapping      = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, VdmHookDefs::SharedMemoryName);
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