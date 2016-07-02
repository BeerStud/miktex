/* Recipe.h:                                            -*- C++ -*-

   Copyright (C) 2016 Christian Schenk

   This file is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 2, or (at your
   option) any later version.
   
   This file is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this file; if not, write to the Free Software
   Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
   USA.  */

#pragma once

#include "TDS.h"

class Recipe :
  public MiKTeX::Core::HasNamedValues
{
public:
  Recipe(const std::string & package, const MiKTeX::Core::PathName & sourceDir, const MiKTeX::Core::PathName & destDir) :
    package(package),
    sourceDir(sourceDir),
    destDir(destDir),
    tds(package)
  {
  }

public:
  void Read(const MiKTeX::Core::PathName & path)
  {
    recipe->Read(path);
  }

public:
  void SetFormat(const std::string & format)
  {
    this->format = format;
    tds.SetFormat(format);
  }

public:
  void Execute(bool printOnly);

private:
  bool PrintOnly(const std::string & message);

private:
#if defined(CreateDirectory)
#undef CreateDirectory
#endif
  void CreateDirectory(const MiKTeX::Core::PathName & path);

private:
  void SetupWorkingDirectory();

private:
  void InstallTeXFiles();

private:
  void Install(const std::vector<std::string> & patterns, const MiKTeX::Core::PathName & tdsDir);

private:
  bool MIKTEXTHISCALL TryGetValue(const std::string & valueName, std::string & value) override
  {
    if (valueName == "package")
    {
      value = package;
      return true;
    }
    else if (valueName == "format")
    {
      value = format;
      return true;
    }
    return false;
  }

private:
  std::string MIKTEXTHISCALL GetValue(const std::string & valueName) override
  {
    MIKTEX_UNEXPECTED();
  }

private:
  std::unique_ptr<MiKTeX::Core::Cfg> recipe = MiKTeX::Core::Cfg::Create();

private:
  std::string package;

private:
  MiKTeX::Core::PathName sourceDir;

private:
  MiKTeX::Core::PathName destDir;

private:
  TDS tds;

private:
  std::string format;

private:
  bool printOnly;

private:
  std::unique_ptr<MiKTeX::Core::TemporaryDirectory> scratchDir;

private:
  MiKTeX::Core::PathName workDir;

private:
  std::shared_ptr<MiKTeX::Core::Session> session = MiKTeX::Core::Session::Get();

private:
  const std::string standardFormat = "latex";

private:
  const std::vector<std::string> standardTexFiles = { "*.cls", "*.sty" };
};
