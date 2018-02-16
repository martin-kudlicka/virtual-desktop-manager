#pragma once

#include "stdafx.h"

class Event
{
  public:
     Event();
    ~Event();

    void open(DWORD desiredAccess, LPCWSTR name);
    void set() const;

    const HANDLE *operator &() const;

  private:
    HANDLE _event;
};