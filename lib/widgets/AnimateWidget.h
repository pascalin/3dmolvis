// File : AnimateWidget.h


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


#ifndef ANIMATEWIDGET_H
#define ANIMATEWIDGET_H

#include <QWidget>
#include "ui_AnimateWidget.h"

class AnimateWidget : public QWidget, public Ui::AnimateWidget
{
    Q_OBJECT
public:
    AnimateWidget(QWidget *parent = 0);
private:
    bool fw_dir; // Indica si la direccion de reproduccion es hacia delante
private slots:
  void gotoStart();
  void gotoEnd();
  void setPause(bool);
  void setRepeat(bool);
  void reverse();
  void forward();
  void setSpeed(int);
public slots:
  void processOutput(QString) {}
  void sendInitCode() { emit initCodeRequested("animate style once;animate goto start"); }
signals:
  void commandRaised(QString comm);
  void initCodeRequested(QString code);
};
#endif
