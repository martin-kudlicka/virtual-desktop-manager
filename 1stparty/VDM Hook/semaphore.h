#pragma once

#include "stdafx.h"

class Semaphore
{
  public:
     Semaphore();
    ~Semaphore();

    void lock() const;
    void open(LPCWSTR name);

  private:
    HANDLE _semaphore;
};