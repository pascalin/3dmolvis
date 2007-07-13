// File : CommandProcess.h


//	Copyright (C) 2007 David Suarez Pascal
//
//	This file is part of VMDGui
//
//	VMDGui is free software; you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation; either version 2 of the License, or
//	(at your option) any later version.
//
//	NCL is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with NCL; if not, write to the Free Software Foundation, Inc., 
//	59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//


#ifndef COMMANDPROCESS_H
#define COMMANDPROCESS_H

#include <QProcess>
#include <QString>

class CommandProcess;
class CommandInquirer;

class CommandInquirer : public QObject
{
  Q_OBJECT
private:
  CommandProcess *process;

public:
  CommandInquirer(CommandProcess*);
  enum ReturnType {Integer_Type, Float_Type, Vector_Type, String};
  void *getReturnValue(QString&, ReturnType);
};

class CommandProcess : public QProcess
{
  Q_OBJECT
private:
  QString program_name;
  QString begin_command;
  QString end_command;
  QString command_sep;
  QStringList param;

public:
  CommandProcess(QString, QString, QString,  QStringList);
public slots:
  void startProcess();
  void endProcess();
  void sendCommand(QString);
  void processOutput();
signals:
  void commandSended(QString);
  void commandFailed();
  void outputProduced(QString);
};

#endif
