// File : MouseModeWidget.h


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


#ifndef MOUSEMODEWIDGET_H
#define MOUSEMODEWIDGET_H

#include "GenericWidget.h"
#include "ui_MouseModeWidget.h"

class MouseModeWidget : public GenericWidget, public Ui::MouseModeWidget
{
    Q_OBJECT
public:
    MouseModeWidget(QWidget *parent = 0);
private slots:
  void enableRotateMode();
  void enableScaleMode();
  void enableTranslateMode();
public slots:
  void processOutput(QString) {}
  void sendInitCode() { emit initCodeRequested(""); }
signals:
  void commandRaised(QString comm);
  void initCodeRequested(QString code);
};
#endif
