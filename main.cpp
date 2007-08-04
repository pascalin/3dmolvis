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
#include <QVBoxLayout>
#include <QMainWindow>
#include "widgets/widgets.h"
#include "lib/CommandProcess.h"

/* This function returns a widget of the specified type */
QWidget *CreateWidgetByName(QString name)
{
  QStringList widgetlist;/* This list contains names of all widget classes */
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
  QMainWindow *window = new QMainWindow();
  QWidget *main_widget = new QWidget();/* This will contain all widgets requested */
  QVBoxLayout *layout = new QVBoxLayout;

  QWidget *wp;
  QStatusBar *status_bar;

  QStringList param, widget_list;
  CommandProcess *vmdprocess = new CommandProcess("./bin/vmd", "", "exit", param);

  /* Sets 3 buttons for controlling of VMD process */
  QPushButton *start_button = new QPushButton("Iniciar VMD");
  QPushButton *end_button = new QPushButton("Terminar VMD");
  QPushButton *quit_button = new QPushButton("Salir");

  QObject::connect(start_button, SIGNAL(clicked()),
		   vmdprocess, SLOT(startProcess()));
  QObject::connect(end_button, SIGNAL(clicked()),
		   vmdprocess, SLOT(endProcess()));
  QObject::connect(quit_button, SIGNAL(clicked()),
		   &vmdguiapp, SLOT(quit()));

  layout->addWidget(start_button);
  layout->addWidget(end_button);
  layout->addWidget(quit_button);

  /* Command line options processing */
  for (int i=0;i<argc;i++)
    {
      if (strcmp(argv[i],"-widgets")==0 && i+1<argc)
	{
	  widget_list = QString(argv[i+1]).split(",");
	  break;
	}
    }

  /* Creates all widgets requested */
  if (!widget_list.isEmpty())
    {
      QStringList::const_iterator i;
      for (i=widget_list.begin();i!=widget_list.end();i++)
	{
	  wp = CreateWidgetByName(*i);
	  if (wp!=NULL)
	    {
	      QObject::connect(wp, SIGNAL(commitCommand(QString)),
			       vmdprocess, SLOT(sendCommand(QString)));
	      QObject::connect(vmdprocess, SIGNAL(outputProduced(QString)),
			       wp, SLOT(processOutput(QString)));
	      layout->addWidget(wp);
	    }
	}
    }

  /* Finish main window setup */
  main_widget->setLayout(layout);
  window->setCentralWidget(main_widget);
  status_bar = window->statusBar();
  window->show();

  /* Start the app */
  exit_code = vmdguiapp.exec();

  /* Shutdown VMD process */
  vmdprocess->endProcess();
  if ( !vmdprocess->waitForFinished() )
    {
      vmdprocess->terminate();
      if ( !vmdprocess->waitForFinished() )
	vmdprocess->kill();
    }
  
  return exit_code;
}
