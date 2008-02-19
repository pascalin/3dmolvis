// File : OutputWidget.h


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


#ifndef OUTPUTWIDGET_H
#define OUTPUTWIDGET_H

#include "GenericWidget.h"
#include "ui_OutputWidget.h"

class OutputWidget : public GenericWidget, public Ui::OutputWidget
{
    Q_OBJECT
public:
    OutputWidget(QWidget *parent = 0);
    QString getInitCode() { return ""; }
public slots:
  void processOutput(QString output);
  void sendInitCode() { emit initCodeRequested(""); }
signals:
  void commandRaised(QString command);
  void initCodeRequested(QString code);
};
#endif
