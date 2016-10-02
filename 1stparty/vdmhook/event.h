#pragma once

#include <Windows.h>

class Event
{
  public:
     Event();
    ~Event();

    void open(LPCWSTR name);
    void set() const;

  private:
    HANDLE _mutex;
};