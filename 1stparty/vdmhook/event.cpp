#include "event.h"

Event::Event() : _event(nullptr)
{
}

Event::~Event()
{
  CloseHandle(_event);
}

void Event::open(LPCWSTR name)
{
  _event = OpenEvent(EVENT_MODIFY_STATE, FALSE, name);
}

void Event::set() const
{
  SetEvent(_event);
}