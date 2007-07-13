// File : main.cpp


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


#include <QApplication>
#include <QStringList>
#include <QStatusBar>
#include <QTextEdit>
#include <QLabel>
#include <QCheckBox>
#include <QVBoxLayout>
#include "widgets/widgets.h"
#include "lib/CommandProcess.h"

int main(int argc, char* argv[])
{
  int exit_code=0;
  QApplication vmdguiapp(argc,argv);
  QWidget *window = new QWidget;
  QString command;
  QStringList param;

  CommandLineWidget *input = new CommandLineWidget();
  QTextEdit *log = new QTextEdit();
  log->setDisabled(true);
  QPushButton *start_button = new QPushButton("Iniciar VMD");
  QPushButton *end_button = new QPushButton("Terminar VMD");
  QPushButton *quit_button = new QPushButton("Salir");
  QStatusBar *status_bar = new QStatusBar();

  CommandProcess *vmdprocess = new CommandProcess("../vmd", "", "exit", param);

  QObject::connect(input, SIGNAL(commitCommand(QString)),
		   vmdprocess, SLOT(sendCommand(QString)));
  QObject::connect(vmdprocess, SIGNAL(outputProduced(QString)),
		   log, SLOT(append(QString)));
  QObject::connect(start_button, SIGNAL(clicked()),
		   vmdprocess, SLOT(startProcess()));
  QObject::connect(end_button, SIGNAL(clicked()),
		   vmdprocess, SLOT(endProcess()));
  QObject::connect(vmdprocess, SIGNAL(commandFailed()),
		   status_bar, SLOT(show()));
  QObject::connect(quit_button, SIGNAL(clicked()),
		   &vmdguiapp, SLOT(quit()));

  QVBoxLayout *layout = new QVBoxLayout;

  layout->addWidget(start_button);
  layout->addWidget(end_button);
  layout->addWidget(input);
  layout->addWidget(quit_button);
  layout->addWidget(log);
  layout->addWidget(status_bar);

  window->setLayout(layout);
  window->setWindowTitle("VMD");
  window->show();

  exit_code = vmdguiapp.exec();

  vmdprocess->endProcess();

  if ( !vmdprocess->waitForFinished() )
    {
      vmdprocess->terminate();
      if ( !vmdprocess->waitForFinished() )
	vmdprocess->kill();
    }
  
  return exit_code;
}
