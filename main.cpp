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
//	VMDGui is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with VMDGui; if not, write to the Free Software Foundation, Inc., //	59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//


#include <QApplication>
#include <QStringList>
#include <QStatusBar>
#include <QTextEdit>
#include <QLabel>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QPalette>
#include "widgets/widgets.h"
#include "lib/CommandProcess.h"

QWidget *CreateWidgetByName(QString name)
{
  QStringList widgetlist;
  widgetlist << "CommandLine";
  widgetlist <<  "Output";

  int index = widgetlist.indexOf(name);
  QWidget* widget=NULL;
  switch (index)
    {
    case 0:
      widget = new CommandLineWidget();
      break;
    case 1:
      widget = new OutputWidget();
      break;
    case -1:
      break;
    }
  return widget;
}


int main(int argc, char* argv[])
{
  int exit_code=0;
  QApplication vmdguiapp(argc,argv);
  QWidget *window = new QWidget;

  QWidget *input = CreateWidgetByName("CommandLine");
  QWidget *log = CreateWidgetByName("Output");
  QPushButton *start_button = new QPushButton("Iniciar VMD");
  QPushButton *end_button = new QPushButton("Terminar VMD");
  QPushButton *quit_button = new QPushButton("Salir");
  QStatusBar *status_bar = new QStatusBar();

  QStringList param;
  CommandProcess *vmdprocess = new CommandProcess("./bin/vmd", "", "exit", param);

  QObject::connect(input, SIGNAL(commitCommand(QString)),
		   vmdprocess, SLOT(sendCommand(QString)));
  QObject::connect(vmdprocess, SIGNAL(outputProduced(QString)),
		   input, SLOT(processOutput(QString)));
  QObject::connect(log, SIGNAL(commitCommand(QString)),
		   vmdprocess, SLOT(sendCommand(QString)));
  QObject::connect(vmdprocess, SIGNAL(outputProduced(QString)),
		   log, SLOT(processOutput(QString)));
  QObject::connect(start_button, SIGNAL(clicked()),
		   vmdprocess, SLOT(startProcess()));
  QObject::connect(end_button, SIGNAL(clicked()),
		   vmdprocess, SLOT(endProcess()));
  QObject::connect(quit_button, SIGNAL(clicked()),
		   &vmdguiapp, SLOT(quit()));

  QVBoxLayout *layout = new QVBoxLayout;

  layout->addWidget(start_button);
  layout->addWidget(end_button);
  layout->addWidget(quit_button);
  layout->addWidget(input);
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
