#include "options.h"

const QString Options::DesktopCount = "options/general/desktopCount";

MLazySingleton<Options> gOptions;

Options::Options()
{
  addProperty(DesktopCount, 1);
}

Options::~Options()
{
}