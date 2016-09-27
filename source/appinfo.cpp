#include "appinfo.h"

#include "virtualdesktopmanager.h"
#include "rules.h"
#include <QtCore/QDir>
#include "wildcard.h"

RuleOptions AppInfo::bestRule() const
{
  auto rulesOptions = suitableRules();
  if (rulesOptions.empty())
  {
    return RuleOptions();
  }

  const RuleOptions *bestOptions = Q_NULLPTR;
  auto bestFilledFields          = 0;
  auto bestFieldChars            = 0;

  for (const auto &ruleOptions : rulesOptions)
  {
    if (!ruleOptions.enabled())
    {
      continue;
    }

    auto ruleFilledFields = 0;
    auto ruleFieldChars   = 0;
    if (!ruleOptions.process().isEmpty())
    {
      ruleFilledFields++;
      ruleFieldChars += ruleOptions.process().size();
    }
    if (!ruleOptions.title().isEmpty())
    {
      ruleFilledFields++;
      ruleFieldChars += ruleOptions.title().size();
    }
    if (!ruleOptions.className().isEmpty())
    {
      ruleFilledFields++;
      ruleFieldChars += ruleOptions.className().size();
    }

    if (bestOptions)
    {
      if (ruleFilledFields < bestFilledFields)
      {
        continue;
      }
      if (ruleFieldChars <= bestFieldChars)
      {
        continue;
      }
    }

    bestOptions      = &ruleOptions;
    bestFilledFields = ruleFilledFields;
    bestFieldChars   = ruleFieldChars;
  }

  return *bestOptions;
}

AppInfo::ProcessInfo &AppInfo::process()
{
  return _process;
}

const AppInfo::ProcessInfo &AppInfo::process() const
{
  return _process;
}

AppInfo::WindowInfo &AppInfo::window()
{
  return _window;
}

const AppInfo::WindowInfo &AppInfo::window() const
{
  return _window;
}

RuleOptionsList AppInfo::suitableRules() const
{
  RuleOptionsList rulesOptions;

  auto ruleIds = gRules->ids();
  for (auto &&ruleId : ruleIds)
  {
    RuleOptions ruleOptions(qMove(ruleId));

    if (!ruleOptions.process().isEmpty())
    {
      auto filePath = ruleOptions.process();
      if (!filePath.contains(QDir::separator()))
      {
        filePath.prepend('*' + QDir::separator());
      }

      Wildcard wildcard(qMove(filePath));
      auto ok = wildcard.matches(QDir::toNativeSeparators(_process.fileInfo.filePath()));
      if (!ok)
      {
        continue;
      }
    }

    if (!ruleOptions.title().isEmpty())
    {
      Wildcard wildcard(ruleOptions.title());
      auto ok = wildcard.matches(QDir::toNativeSeparators(_window.title));
      if (!ok)
      {
        continue;
      }
    }

    if (!ruleOptions.className().isEmpty())
    {
      Wildcard wildcard(ruleOptions.className());
      auto ok = wildcard.matches(QDir::toNativeSeparators(_window.className));
      if (!ok)
      {
        continue;
      }
    }

    rulesOptions.append(qMove(ruleOptions));
  }

  return rulesOptions;
}

AppInfo::WindowInfo::WindowInfo() : handle(Q_NULLPTR), desktopIndex(VirtualDesktopManager::InvalidDesktop)
{
}