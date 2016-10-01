#pragma once

#include <Windows.h>

class Client
{
  public:
     Client();
    ~Client();

    bool rulesEnabled() const;
    void setAppInfo(LPCWSTR filePath, LPCWSTR windowTitle, LPCWSTR windowClass) const;

  private:
    HANDLE _mapping;
    LPVOID _sharedMemory;

    void writeString(LPBYTE *sharedPos, LPCWSTR text) const;
};