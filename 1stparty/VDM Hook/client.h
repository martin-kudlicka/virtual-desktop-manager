#pragma once

#include "stdafx.h"

class Client
{
  public:
     Client();
    ~Client();

    bool rulesEnabled() const;
    void writeAppInfo(HWND window, LPCWSTR filePath, LPCWSTR windowTitle, LPCWSTR windowClass) const;

  private:
    HANDLE _mapping;
    LPVOID _sharedMemory;

    void writeString(LPBYTE *sharedPos, LPCWSTR text) const;
};