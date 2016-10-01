#pragma once

#include <Windows.h>

class Semaphore
{
  public:
     Semaphore();
    ~Semaphore();

    void lock  ();
    void unlock();

  private:
    HANDLE _semaphore;
};