#include "event.h"

Event::Event() : _event(nullptr)
{
}

Event::~Event()
{
  CloseHandle(_event);
}

void Event::open(DWORD desiredAccess, LPCWSTR name)
{
  _event = OpenEvent(desiredAccess, FALSE, name);
}

void Event::set() const
{
  SetEvent(_event);
}

const HANDLE *Event::operator &() const
{
  return &_event;
}