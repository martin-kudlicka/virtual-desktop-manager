#include "pch.h"
#include "appinfo.h"

#include "virtualdesktopmanager.h"
#include "rules.h"

RuleOptions AppInfo::bestRule() const
{
  auto ruleIds = gRules->ids();
  return bestRule(ruleIds);
}

RuleOptions AppInfo::bestRule(const MUuidPtrList &rulesIds) const
{
  auto rulesOptions = suitableRules(rulesIds);
  return bestRule(rulesOptions);
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

RuleOptions AppInfo::bestRule(const RuleOptionsList &rulesOptions) const
{
  if (rulesOptions.isEmpty())
  {
    return RuleOptions();
  }

  const RuleOptions *bestOptions = Q_NULLPTR;
  auto bestFilledFields          = 0;
  auto bestFieldChars            = 0;

  for (const auto &ruleOptions : rulesOptions)
  {
    auto ruleFilledFields = 0;
    auto ruleFieldChars   = 0;
    if (!ruleOptions.process().isEmpty())
    {
      ++ruleFilledFields;
      ruleFieldChars += ruleOptions.process().size();
    }
    if (!ruleOptions.title().isEmpty())
    {
      ++ruleFilledFields;
      ruleFieldChars += ruleOptions.title().size();
    }
    if (!ruleOptions.className().isEmpty())
    {
      ++ruleFilledFields;
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

RuleOptionsList AppInfo::suitableRules(const MUuidPtrList &ruleIds) const
{
  RuleOptionsList rulesOptions;

  for (const auto &ruleId : ruleIds)
  {
    RuleOptions ruleOptions(ruleId);

    if (!ruleOptions.enabled())
    {
      continue;
    }

    if (!ruleOptions.process().isEmpty())
    {
      auto filePath = ruleOptions.process();
      if (!filePath.contains(QDir::separator()))
      {
        filePath.prepend('*' + QDir::separator());
      }

      QRegExp regExp(QDir::fromNativeSeparators(filePath), Qt::CaseInsensitive, QRegExp::Wildcard);
      auto ok = regExp.exactMatch(QDir::fromNativeSeparators(_process.fileInfo.filePath()));
      if (!ok)
      {
        continue;
      }
    }

    if (!ruleOptions.title().isEmpty())
    {
      QRegExp regExp(ruleOptions.title(), Qt::CaseInsensitive, QRegExp::Wildcard);
      auto ok = regExp.exactMatch(_window.title);
      if (!ok)
      {
        continue;
      }
    }

    if (!ruleOptions.className().isEmpty())
    {
      QRegExp regExp(ruleOptions.className(), Qt::CaseInsensitive, QRegExp::Wildcard);
      auto ok = regExp.exactMatch(_window.className);
      if (!ok)
      {
        continue;
      }
    }

    rulesOptions.append(ruleOptions);
  }

  return rulesOptions;
}

AppInfo::WindowInfo::WindowInfo() : handle(Q_NULLPTR), desktopIndex(VirtualDesktopManager::InvalidDesktop)
{
}