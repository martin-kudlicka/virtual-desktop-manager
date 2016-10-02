#include "event.h"

Event::Event() : _mutex(nullptr)
{
}

Event::~Event()
{
  CloseHandle(_mutex);
}

void Event::open(LPCWSTR name)
{
  _mutex = OpenEvent(SYNCHRONIZE, FALSE, name);
}

void Event::set() const
{
  SetEvent(_mutex);
}