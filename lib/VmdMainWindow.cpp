// File : VmdMainWindow.cpp


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


#include "VmdMainWindow.h"

VmdMainWindow::VmdMainWindow()
{
  main_widget = new QWidget();
  setCentralWidget(main_widget);
  temp_file = new QTemporaryFile();
  temp_file->open();
  tcl_out = new QTextStream(temp_file);
  param << "-e";
  param << temp_file->fileName();
  std::cout << "employing temporary file: " << temp_file->fileName().toStdString() << std::endl;
  vmd_process = new CommandProcess("./bin/vmd", "", "exit", param);
}

void VmdMainWindow::closeEvent(QCloseEvent *event)
{
  /* Shutdown VMD process */
  vmd_process->endProcess();
  if ( !vmd_process->waitForFinished() )
    {
      vmd_process->terminate();
      if ( !vmd_process->waitForFinished() )
	vmd_process->kill();
    }
  event->accept();
}

void VmdMainWindow::setWidgets(QStringList wl)
{
  if (!wl.isEmpty())
    {
      widget_list = wl;
    }
  createWidgets();
  emit startupFinished();
}

void VmdMainWindow::createWidgets()
{
  QVBoxLayout *layout = new QVBoxLayout;
  QWidget *wp;

  /* Sets 3 buttons for controlling of VMD process */
  QPushButton *start_button = new QPushButton("Iniciar VMD");
  QPushButton *end_button = new QPushButton("Terminar VMD");
  QPushButton *quit_button = new QPushButton("Salir");

  QObject::connect(start_button, SIGNAL(clicked()),
		   vmd_process, SLOT(startProcess()));
  QObject::connect(end_button, SIGNAL(clicked()),
		   vmd_process, SLOT(endProcess()));
  QObject::connect(quit_button, SIGNAL(clicked()),
		   this, SLOT(close()));

  layout->addWidget(start_button);
  layout->addWidget(end_button);
  layout->addWidget(quit_button);

  QStringList::const_iterator i;
  for (i=widget_list.begin();i!=widget_list.end();i++)
    {
      wp = wm.createWidgetByName(*i);
      if (wp!=NULL)
	{
	  QObject::connect(wp, SIGNAL(commandRaised(QString)),
			   vmd_process, SLOT(sendCommand(QString)));
	  QObject::connect(vmd_process, SIGNAL(outputProduced(QString)),
			   wp, SLOT(processOutput(QString)));
	  QObject::connect(wp, SIGNAL(initCodeRequested(QString)),
			   this, SLOT(appendToTclCommands(QString)));
	  QObject::connect(this, SIGNAL(startupFinished()),
			   wp, SLOT(sendInitCode()));
	  layout->addWidget(wp);
	}
    }
  main_widget->setLayout(layout);
}

void VmdMainWindow::appendToTclCommands(QString code)
{
  (*tcl_out) << code;
}

void VmdMainWindow::setTclCode(QString code)
{
//   std::ostringstream tempsstream;
//   tempsstream << std::endl;
//   command_sep = tempsstream.str().c_str();
  (*tcl_out) << code;
  tcl_out->flush();
}

void VmdMainWindow::setTclCode(QTextStream &stream)
{
  (*tcl_out) << stream.readAll();
  tcl_out->flush();
}
