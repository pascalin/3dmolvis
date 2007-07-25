// File : CommandProcess.cpp


//	Copyright (C) 2007 David Suarez Pascal
//
//	This file is part of VMDGui
//
//	VMDGui is free software; you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation; either version 2 of the License, or
//	(at your option) any later version.
//
//	VMDGui is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with VMDGui; if not, write to the Free Software Foundation, Inc.,
//	59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//


#include "CommandProcess.h"

CommandInquirer::CommandInquirer(CommandProcess *process) : QObject(), process(process)
{
}

void * CommandInquirer::getReturnValue(QString &command, CommandInquirer::ReturnType type)
{
  process->sendCommand(command);
  return NULL;
}

CommandProcess::CommandProcess(QString progname, QString begin_command, QString end_command, QStringList param): QProcess(), program_name(progname),begin_command(begin_command),end_command(end_command),param(param)
{
  command_sep = "\n";
  connect(this, SIGNAL(readyReadStandardOutput()), this, SLOT(processOutput()));
}

void CommandProcess::startProcess()
{
  start(program_name, param, QIODevice::ReadWrite|QIODevice::Unbuffered);
  if ( !waitForStarted() )
    emit commandFailed();
  write(begin_command.toAscii());
  write(command_sep.toAscii());
}

void CommandProcess::endProcess()
{
  write(end_command.toAscii());
  write(command_sep.toAscii());
}

void CommandProcess::sendCommand(QString command)
{
  write(command.toAscii());
  write(command_sep.toAscii());
  emit commandSended(command);
}

void CommandProcess::processOutput()
{
  QString output = readAllStandardOutput().data();
  if (output.startsWith("wrong") || output.startsWith("can't") || output.startsWith("bad"))
    {
      emit commandFailed();
      return;
    }
  emit outputProduced(output);
}
