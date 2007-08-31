// File : RotationWidget.h


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


#ifndef ROTATIONWIDGET_H
#define ROTATIONWIDGET_H

#include <QWidget>
#include <sstream>
#include "ui_RotationWidget.h"

class RotationWidget : public QWidget, public Ui::RotationWidget
{
    Q_OBJECT
private:
    int x_angle, y_angle, z_angle;
public:
    RotationWidget(QWidget *parent = 0);
public slots:
  void rotateX(int);
  void rotateY(int);
  void rotateZ(int);
  void processOutput(QString) {}
  void sendInitCode() { emit initCodeRequested(""); }
signals:
  void commandRaised(QString comm);
  void initCodeRequested(QString code);
};
#endif
