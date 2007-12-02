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
//	along with VMDGui; if not, write to the Free Software Foundation, Inc.,
//	59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//


#include <QApplication>
#include <QStringList>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QFile>
#include <iostream>
#include "lib/VmdMainWindow.h"


int main(int argc, char* argv[])
{
  int exit_code=0;
  QFile *tcl_file = NULL;
  QApplication vmdguiapp(argc,argv);
  VmdMainWindow *window = new VmdMainWindow();

  
  QTranslator qtTranslator;
  QTranslator appTranslator;

  /* Obtiene el locale de pais usado por el usuario */
  QString lang = QLocale::system().name();
  lang.truncate(2);

  /* Agrega las traducciones de Qt */
  qtTranslator.load("i18n/" + lang + "qt_" + lang);
  vmdguiapp.installTranslator(&qtTranslator);

  /* Agrega las traducciones de VMDGui */
  appTranslator.load("i18n/" + lang + "/vmdgui_" + lang);
  vmdguiapp.installTranslator(&appTranslator);

//   QWidget *main_widget = new QWidget();/* This will contain all widgets requested */
//   QVBoxLayout *layout = new QVBoxLayout;

//   WidgetManager wm;
//   QWidget *wp;
//   QStatusBar *status_bar;

  QStringList param, widget_list;
//   QString tcl_init;
//   CommandProcess *vmdprocess = new CommandProcess("./bin/vmd", "", "exit", param);

  /* Sets 3 buttons for controlling of VMD process */
//   QPushButton *start_button = new QPushButton("Iniciar VMD");
//   QPushButton *end_button = new QPushButton("Terminar VMD");
//   QPushButton *quit_button = new QPushButton("Salir");

//   QObject::connect(start_button, SIGNAL(clicked()),
// 		   vmdprocess, SLOT(startProcess()));
//   QObject::connect(end_button, SIGNAL(clicked()),
// 		   vmdprocess, SLOT(endProcess()));
//   QObject::connect(quit_button, SIGNAL(clicked()),
// 		   &vmdguiapp, SLOT(quit()));

//   layout->addWidget(start_button);
//   layout->addWidget(end_button);
//   layout->addWidget(quit_button);

  /* Command line options processing */
  for (int i=1;i<argc;i++)
    {
      if (strcmp(argv[i],"-widgets")==0 && i+1<argc)
	{
	  widget_list = QString(argv[i+1]).split(",");
	  i++;
	}
      else if (strcmp(argv[i],"-tcl")==0 && i+1<argc)
	{
	  tcl_file = new QFile(argv[i+1]);
	  if (!tcl_file->open(QIODevice::ReadOnly | QIODevice::Text))
	    {
	      std::cerr << argv[i+1] << " is not a valid file name" << std::endl;
	      tcl_file = NULL;
	    }
	  i++;
	}
      else
	{
	  std::cerr << argv[i] << " is not a valid command-line option" << std::endl;
	}
    }

  /* Creates all widgets requested */
//   if (!widget_list.isEmpty())
//     {
//       QStringList::const_iterator i;
//       for (i=widget_list.begin();i!=widget_list.end();i++)
// 	{
// 	  wp = wm.createWidgetByName(*i);
// 	  if (wp!=NULL)
// 	    {
// 	      QObject::connect(wp, SIGNAL(commandRaised(QString)),
// 			       vmdprocess, SLOT(sendCommand(QString)));
// 	      QObject::connect(vmdprocess, SIGNAL(outputProduced(QString)),
// 			       wp, SLOT(processOutput(QString)));
// 	      layout->addWidget(wp);
// 	    }
// 	}
//     }

  /* Finish main window setup */
//   main_widget->setLayout(layout);
//   window->setCentralWidget(main_widget);
//   status_bar = window->statusBar();
  if (tcl_file != NULL)
    {
      QTextStream tcl(tcl_file);
      window->setTclCode(tcl);
    }
  if (!widget_list.isEmpty())
    window->setWidgets(widget_list);
  window->show();

  /* Start the app */
  exit_code = vmdguiapp.exec();

  /* Shutdown VMD process */
//   vmdprocess->endProcess();
//   if ( !vmdprocess->waitForFinished() )
//     {
//       vmdprocess->terminate();
//       if ( !vmdprocess->waitForFinished() )
// 	vmdprocess->kill();
//     }
  
  return exit_code;
}
