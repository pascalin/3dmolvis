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


#ifndef VMDMAINWINDOW_H
#define VMDMAINWINDOW_H

#include <QMainWindow>
#include <QTemporaryFile>
#include <QTextStream>
#include <QCloseEvent>
#include <iostream>
#include "Widgets.h"
#include "CommandProcess.h"

class VmdMainWindow : public QMainWindow
{
  Q_OBJECT
public:
  VmdMainWindow();
  void setWidgets(QStringList wl);
  void setTclCode(QString code);
  void setTclCode(QTextStream &stream);
protected:
   void closeEvent(QCloseEvent *event);
private slots:
  void appendToTclCommands(QString code);
//   void about();
//   void newFile();
//   void open();
//   bool save();
//   bool saveAs();
//   void openRecentFile();
//   void updateStatusBar();
signals:
void startupFinished();
private:
  QWidget *main_widget;
  QStringList param, widget_list;
  CommandProcess *vmd_process;
  QStringList recentFiles;
  WidgetManager wm;
  QTemporaryFile *temp_file;
  QTextStream *tcl_out;
  void createWidgets();
//   void createActions();
//   void createMenus();
//   void createContextMenu();
//   void createToolBars();
//   void createStatusBar();
//   void readSettings();
//   void writeSettings();
  bool loadFile(const QString &file_name);
//   bool saveFile(const QString &fileName);
//   void setCurrentFile(const QString &fileName);
//   void updateRecentFileActions();
//   QString strippedName(const QString &fullFileName);

//   QLabel *locationLabel;
//   QLabel *formulaLabel;

//   QAction *recentFileActions[MaxRecentFiles];
//   QAction *separatorAction;

//   QMenu *fileMenu;
//   QMenu *editMenu;
//   QMenu *helpMenu;

//   QToolBar *fileToolBar;
//   QToolBar *editToolBar;

//   QAction *newAction;
//   QAction *openAction;
//   QAction *saveAction;
//   QAction *saveAsAction;
//   QAction *exitAction;
//   QAction *cutAction;
//   QAction *copyAction;
//   QAction *pasteAction;
//   QAction *aboutAction;
//   QAction *aboutQtAction;

};

#endif
