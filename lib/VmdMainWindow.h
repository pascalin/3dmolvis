// File : VmdMainWindow.h


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

/*
 * VmdMainWindow implementa una subclase de QMainWindow que integra
 * todos los componentes de VMDGui de manera que puedan ser accedidos
 * desde una misma ventana. La ventana cuenta con un menu y una barra
 * de herramientas, asi como con una barra de estado. Y en la parte
 * central se crean de acuerdo a cada aplicacion un arbol de contenido
 * (tree) en el lado izquierdo y una seccion con opciones (obox) en la
 * parte inferior. En el lado derecho, y siempre presente esta la
 * seccion de widgets (main_widget).
 */

#ifndef VMDMAINWINDOW_H
#define VMDMAINWINDOW_H

/* Componentes de Qt */
#include <QMainWindow>
#include <QTemporaryFile>
#include <QTextStream>
#include <QCloseEvent>
#include <iostream>

/* Componentes de VMDGui */
#include "Widgets.h"
#include "OptionBox.h"
#include "CommandProcess.h"
#include "AppHandler.h"

/* La clase VmdMainWindow */
class VmdMainWindow : public QMainWindow
{
  Q_OBJECT
public:
  VmdMainWindow();
  void setWidgets(QStringList wl); // Establece los widgets requeridos
  /* Agregan codigo al archivo de inicializacion */
  void setTclCode(QString code);
  void setTclCode(QTextStream &stream);
protected:
  void closeEvent(QCloseEvent *event); // Procesa el evento de cierre
private slots:
  /* Permite que cada widget agregue su propio codigo de inicio */
  void appendToTclCommands(QString code);
  /* Maneja la activacion de elementos del arbol de contenido */ 
  void requestAction(QTreeWidgetItem *item, int column);
  void about(); // Muestra la ventana acerca de VMDGui
  void open(); // Maneja la apertura de un archivo de aplicacion
//   void newFile();
//   bool save();
//   bool saveAs();
//   void openRecentFile();
//   void updateStatusBar();
signals:
  void startupFinished(); // Indica el termino de la creacion de widgets
private:
  /* Componentes principales que maneja la aplicacion */
  QWidget *main_widget;
  QTreeWidget *tree;
  OptionBox *obox;
  CommandProcess *vmd_process;

  /* Manejo de widgets */
  WidgetManager wm;
  QList<QWidget*> widgets;
  QStringList widget_list;

  /* Auxiliares en el manejo del proceso de vmd */
  QStringList param; // Lista de parametros
  QTemporaryFile *temp_file; // Archivo de inicializacion
  QTextStream *tcl_out; // Stream de inicializacion

  QStringList recentFiles; // Lista de archivos recientes

  void newVmdProcess(); // Crea un nuevo proceso de VMD
  void createWidgets(); // Crea los widgets indicados mediante setWidgets
  void createActions(); // Crea las acciones de menu
  void createMenus(); // Crea el menu
  //  void createContextMenu();
  void createToolBars(); // Crea la barra de herramientas
  void createStatusBar(); // Crea la barra de estado
//   void readSettings();
//   void writeSettings();
  bool loadFile(const QString &file_name); // Carga un archivo
//   bool saveFile(const QString &fileName);
//   void setCurrentFile(const QString &fileName);
//   void updateRecentFileActions();
//   QString strippedName(const QString &fullFileName);

  /* Menus y acciones */
//   QAction *recentFileActions[MaxRecentFiles];
//   QAction *separatorAction;

  QMenu *fileMenu;
//   QMenu *editMenu;
  QMenu *helpMenu;

  QToolBar *fileToolBar;
//   QToolBar *editToolBar;

//   QAction *newAction;
  QAction *openAction;
//   QAction *saveAction;
//   QAction *saveAsAction;
  QAction *exitAction;
//   QAction *cutAction;
//   QAction *copyAction;
//   QAction *pasteAction;
  QAction *aboutAction;
  QAction *aboutQtAction;

};

#endif
