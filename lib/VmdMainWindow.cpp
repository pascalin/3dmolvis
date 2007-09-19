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
  QSplitter *splitter1, *splitter2;

  splitter1 = new QSplitter(Qt::Vertical);
  splitter2 = new QSplitter(Qt::Horizontal);

  tree = new QTreeWidget();
  obox = new OptionBox();
  main_widget = new QWidget();

  splitter2->addWidget(tree);
  splitter2->addWidget(main_widget);

  splitter1->addWidget(splitter2);
  splitter1->addWidget(obox);

  setCentralWidget(splitter1);
  
  obox->setHidden(true);

  tree->setHeaderLabel("Contenido");
  tree->setHidden(true);
  QObject::connect(tree, SIGNAL(itemActivated(QTreeWidgetItem *, int)),
		   this, SLOT(requestAction(QTreeWidgetItem *, int)));

  vmd_process = NULL;
  temp_file = NULL;
  tcl_out = NULL;
  
  newVmdProcess();
  createActions();
  createMenus();
  createToolBars();
  createStatusBar();
}

void VmdMainWindow::closeEvent(QCloseEvent *event)
{
  /* Termina el proceso de VMD */
  if (vmd_process && vmd_process->state() != QProcess::NotRunning)
    {
      vmd_process->endProcess();
      if ( !vmd_process->waitForFinished() )
	{
	  vmd_process->terminate();
	  if ( !vmd_process->waitForFinished() )
	    vmd_process->kill();
	}
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
  QList<QWidget*>::const_iterator w;
  
  /* Borra los widgets existentes */
  for (w=widgets.begin();w!=widgets.end();w++)
    {
      main_widget->layout()->removeWidget(*w);
      delete *w;
    }
  widgets.clear();
  delete main_widget->layout();

  /* Crea y conecta los widgets contenidos en widget_list */
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
	  widgets.append(wp);
	}
    }
  main_widget->setLayout(layout);
}

void VmdMainWindow::appendToTclCommands(QString code)
{
  (*tcl_out) << code;
  tcl_out->flush();
}

void VmdMainWindow::setTclCode(QString code)
{
  (*tcl_out) << code;
  tcl_out->flush();
}

void VmdMainWindow::setTclCode(QTextStream &stream)
{
  (*tcl_out) << stream.readAll();
  tcl_out->flush();
}

void VmdMainWindow::requestAction(QTreeWidgetItem *item, int)
{
  if (item && item->data(0, Qt::UserRole).toString()=="action")
    vmd_process->sendCommand(item->data(0, Qt::UserRole+1).toString());
}

void VmdMainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Abrir archivo de aplicacion", QDir::currentPath(), "Archivos vmd (*.vmd *.xml)");
    if (fileName.isEmpty())
        return;

    tree->clear();
    obox->clear();
    newVmdProcess();

    QObject::connect(obox, SIGNAL(commandRaised(QString)),
		     vmd_process, SLOT(sendCommand(QString)));

    AppHandler handler(tree, obox);
    QXmlSimpleReader reader;
    reader.setContentHandler(&handler);
    reader.setErrorHandler(&handler);

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "VMDGui",
                             tr("Imposible leer archivo %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QXmlInputSource xmlInputSource(&file);
    if (reader.parse(xmlInputSource))
        statusBar()->showMessage("Archivo cargado", 2000);

    if (handler.hasTclCode())
      setTclCode(handler.getTclCode());

    if (handler.hasControls())
      setWidgets(handler.getControlList());

    vmd_process->startProcess();

    if (tree->topLevelItemCount() > 0)
      tree->setHidden(false);
    else
      tree->setHidden(true);

    if (obox->count() > 0)
      obox->setHidden(false);
    else
      obox->setHidden(true);
}

void VmdMainWindow::about()
{
  QMessageBox::about(this, "Acerca de VMDGui",
		     "<b>VMDGui</b> es una interfaz para el uso del sistema de visualizacion molecular VMD");
}

void VmdMainWindow::newVmdProcess()
{
  if (vmd_process && vmd_process->state() != QProcess::NotRunning)
    {
      vmd_process->endProcess();
    }
  if (temp_file && temp_file->isOpen())
      temp_file->close();

  temp_file = new QTemporaryFile();
  temp_file->open();
  tcl_out = new QTextStream(temp_file);
  param << "-e";
  param << temp_file->fileName();
  vmd_process = new CommandProcess("./bin/vmd", "", "exit", param);
}

void VmdMainWindow::createActions()
{
//   newAct = new QAction(QIcon(":/icons/default/icons/new.png"), "&Nuevo", this);
//   newAct->setShortcut(tr("Ctrl+N"));
//   newAct->setStatusTip(tr("Create a new file"));
//   connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

  openAction = new QAction(QIcon(":/icons/default/icons/folder.png"), "&Abrir...", this);
  openAction->setShortcut(tr("Ctrl+O"));
  openAction->setStatusTip("Abre un archivo existente");
  connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

//   saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
//   saveAct->setShortcut(tr("Ctrl+S"));
//   saveAct->setStatusTip(tr("Save the document to disk"));
//   connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

//   saveAsAct = new QAction(tr("Save &As..."), this);
//   saveAsAct->setStatusTip(tr("Save the document under a new name"));
//   connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

  exitAction = new QAction("Sa&lir", this);
  exitAction->setShortcut(tr("Ctrl+Q"));
  exitAction->setStatusTip("Sale de VMDGui");
  connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

//   cutAct = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
//   cutAct->setShortcut(tr("Ctrl+X"));
//   cutAct->setStatusTip(tr("Cut the current selection's contents to the "
// 			  "clipboard"));
//   connect(cutAct, SIGNAL(triggered()), textEdit, SLOT(cut()));

//   copyAct = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
//   copyAct->setShortcut(tr("Ctrl+C"));
//   copyAct->setStatusTip(tr("Copy the current selection's contents to the "
// 			   "clipboard"));
//   connect(copyAct, SIGNAL(triggered()), textEdit, SLOT(copy()));

//   pasteAct = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
//   pasteAct->setShortcut(tr("Ctrl+V"));
//   pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
// 			    "selection"));
//   connect(pasteAct, SIGNAL(triggered()), textEdit, SLOT(paste()));

  aboutAction = new QAction("&Acerca de...", this);
  aboutAction->setStatusTip("Muestra informacion sobre VMDGui");
  connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

  aboutQtAction = new QAction("Acerca de &Qt", this);
  aboutQtAction->setStatusTip("Muestra la informacion sobre la biblioteca Qt");
  connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

//   cutAct->setEnabled(false);
//   copyAct->setEnabled(false);
//   connect(textEdit, SIGNAL(copyAvailable(bool)),
// 	  cutAct, SLOT(setEnabled(bool)));
//   connect(textEdit, SIGNAL(copyAvailable(bool)),
// 	  copyAct, SLOT(setEnabled(bool)));
}

void VmdMainWindow::createMenus()
{
  fileMenu = menuBar()->addMenu("&Archivo");
//   fileMenu->addAction(newAct);
  fileMenu->addAction(openAction);
//   fileMenu->addAction(saveAct);
//   fileMenu->addAction(saveAsAct);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAction);

//   editMenu = menuBar()->addMenu(tr("&Edit"));
//   editMenu->addAction(cutAct);
//   editMenu->addAction(copyAct);
//   editMenu->addAction(pasteAct);

  menuBar()->addSeparator();

  helpMenu = menuBar()->addMenu("A&yuda");
  helpMenu->addAction(aboutAction);
  helpMenu->addAction(aboutQtAction);
}

void VmdMainWindow::createToolBars()
{
  fileToolBar = addToolBar(tr("File"));
//   fileToolBar->addAction(newAct);
  fileToolBar->addAction(openAction);
//   fileToolBar->addAction(saveAct);

//   editToolBar = addToolBar(tr("Edit"));
//   editToolBar->addAction(cutAct);
//   editToolBar->addAction(copyAct);
//   editToolBar->addAction(pasteAct);
}

void VmdMainWindow::createStatusBar()
{
  statusBar()->showMessage("Listo");
}
