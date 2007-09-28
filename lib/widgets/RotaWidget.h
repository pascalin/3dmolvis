// File : RotaWidget.h


//	Copyright (C) 2007 Natalia Pérez Escutia
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


#ifndef ROTAWIDGET_H
#define ROTAWIDGET_H

#include <QWidget>
#include <sstream>
#include "ui_RotaWidget.h"

class RotaWidget : public QWidget, public Ui::RotaWidget
{
    Q_OBJECT
private:
    
public:
    RotaWidget(QWidget *parent = 0);
public slots:
  //void reset();
  void rota();
  //void rotaoff();
  void processOutput(QString) {}
  void sendInitCode() { emit initCodeRequested(""); }
signals:
  void commandRaised(QString comm);
  void initCodeRequested(QString code);
};
#endif
