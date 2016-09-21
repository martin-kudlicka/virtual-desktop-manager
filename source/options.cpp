#include "options.h"

#include "virtualdesktopmanager.h"

const QString Options::DesktopCount = "options/general/desktopCount";

MLazySingleton<Options> gOptions;

Options::Options()
{
  addProperty(DesktopCount, gVirtualDesktopManager->count());
}

Options::~Options()
{
}