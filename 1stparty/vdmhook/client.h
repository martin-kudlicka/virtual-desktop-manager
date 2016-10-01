#pragma once

#include <Windows.h>

class Client
{
  public:
     Client();
    ~Client();

    bool rulesEnabled() const;

  private:
    HANDLE _mapping;
    LPVOID _sharedMemory;
};