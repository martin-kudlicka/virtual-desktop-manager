#ifndef OPTIONS_H
#define OPTIONS_H

#include "settings.h"
#include <MkCore/MLazySingleton>

class Options : public Settings
{
  public:
             Options();
    virtual ~Options();

    static const QString DesktopCount;
};

extern MLazySingleton<Options> gOptions;

#endif