#pragma once

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