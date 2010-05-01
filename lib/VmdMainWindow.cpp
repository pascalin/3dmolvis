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

/* VmdMainWindow contructor */
VmdMainWindow::VmdMainWindow()
{
  setupUi(this);

  obox = new OptionBox();
  splitter_4->addWidget(obox);

  obox->setHidden(true);

  tree->setHeaderLabel("Contenido");
  tree->setHidden(true);

  connect(tree, SIGNAL(itemActivated(QTreeWidgetItem *, int)),
		   this, SLOT(requestAction(QTreeWidgetItem *, int)));

  dir_model = new QDirModel;
  explorer_view->setModel(dir_model);
  explorer_view->setRootIndex(dir_model->index(QDir::currentPath()));
  explorer_view->setHidden(true);
  error_widget->setHidden(true);

  connect(actionOpen, SIGNAL(triggered()), this, SLOT(openLesson()));
  connect(actionClose, SIGNAL(triggered()), this, SLOT(closeLesson()));

  connect(actionLessonWizard, SIGNAL(triggered()), this, SLOT(startLessonWizard()));

  connect(actionAbout, SIGNAL(triggered()), this, SLOT(about()));
  connect(actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

  vmd_path = QApplication::applicationDirPath()+"/bin/vmd";
  vmd_process = NULL;
  temp_file = NULL;
  tcl_out = NULL;

  wiz = NULL;

  newVmdProcess();
//   createActions();
//   createMenus();
//   createToolBars();
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
  appendToTclCommands("puts \"VMD Ready\"");
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

  if (main_widget->layout()->indexOf(logo_label) != -1)
    {
      main_widget->layout()->removeWidget(logo_label);
      logo_label->setHidden(true);
    }

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
  /* Deshabilita los tres elementos de control */
  main_widget->setEnabled(false);
  tree->setEnabled(false);
  obox->setEnabled(false);
}

void VmdMainWindow::appendToTclCommands(QString code)
{
  (*tcl_out) << code << ";";
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

void VmdMainWindow::openLesson()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Abrir archivo de aplicacion", QDir::currentPath(), "Archivos vmd (*.vmd *.xml)");
    if (fileName.isEmpty() or !QFile::exists(fileName))
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
        QMessageBox::warning(this, "3DMolvis",
                             tr("Unable to read file %1:\n%2.")
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

    setWindowTitle(handler.getProperty("title"));

    if (tree->topLevelItemCount() > 0)
      tree->setHidden(false);
    else
      tree->setHidden(true);

    if (obox->count() > 0)
      obox->setHidden(false);
    else
      obox->setHidden(true);

    main_widget->setEnabled(false);
    tree->setEnabled(false);
    obox->setEnabled(false);

    main_widget->resize(1,1);

    /* Cambia el directorio de trabajo al directorio que contiene al archivo de aplicacion e inicia VMD */
    QDir::setCurrent(QDir::current().absoluteFilePath(fileName.left(fileName.lastIndexOf(QRegExp("[/\\\\]")))));
    vmd_process->startProcess();

    actionClose->setEnabled(true);
}

void VmdMainWindow::closeLesson()
{
  QList<QWidget*>::const_iterator w;

  for (w=widgets.begin();w!=widgets.end();w++)
    {
      main_widget->layout()->removeWidget(*w);
      delete *w;
    }
  widgets.clear();

  tree->clear();
  obox->clear();

  obox->setHidden(true);
  tree->setHidden(true);
  explorer_view->setHidden(true);
  error_widget->setHidden(true);

  if (vmd_process && vmd_process->state() != QProcess::NotRunning)
    {
      vmd_process->endProcess();
    }
  if (temp_file && temp_file->isOpen())
    temp_file->close();

  main_widget->layout()->addWidget(logo_label);
  logo_label->setHidden(false);

  actionClose->setEnabled(false);

  setWindowTitle(tr("3DMolvis"));
}

void VmdMainWindow::about()
{
  QMessageBox::about(this, tr("About 3DMolvis"),
                     tr("<b>3DMolvis (version %1)</b><br/>A project designed for teaching and learning biochemistry<br/><a href='http://tdmolvis.sourceforge.net'>Home Page</a>").arg(tdmolvis::version));
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
  vmd_process = new CommandProcess(vmd_path, "", "exit", param);
  QObject::connect(vmd_process, SIGNAL(outputProduced(QString)),
		   this, SLOT(enableWidgets(QString)));

}

void VmdMainWindow::createStatusBar()
{
  statusBar()->showMessage(tr("Ready"));
}

void VmdMainWindow::enableWidgets(QString output)
{
  if (output.contains("VMD Ready"))
    {
      /* Habilita los tres elementos de control */
      main_widget->setEnabled(true);
      tree->setEnabled(true);
      obox->setEnabled(true);
      /* Le da el foco a la ventana principal */
      activateWindow();
      raise();
    }
}

void VmdMainWindow :: startLessonWizard()
{
  wiz = new LessonWizard();
  wiz->setWindowModality(Qt::ApplicationModal);
  wiz->show();
  QObject::connect(wiz, SIGNAL(finished(int)),
                   this, SLOT(endLessonWizard(int)));
  //wiz->setAttribute(Qt::WA_DeleteOnClose);
  return ;
}

void VmdMainWindow :: endLessonWizard(int result)
{
	if(result==QDialog::Accepted){
		LessonWizard* less_wiz = dynamic_cast<LessonWizard*> (wiz);
		less_wiz->writeLesson();
		statusBar()->showMessage(tr("Lesson was successfully saved"), 3000);
	}
}
