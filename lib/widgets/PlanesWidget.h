// File : PlanesWidget.h


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


#ifndef PLANESWIDGET_H
#define PLANESWIDGET_H

#include <QWidget>
#include <sstream>
#include "ui_PlanesWidget.h"

class PlanesWidget : public QWidget, public Ui::PlanesWidget
{
    Q_OBJECT
private:
    int size;
public:
    PlanesWidget(QWidget *parent = 0);
public slots:
  void cut(int);
  void processOutput(QString) {}
  void sendInitCode() { emit initCodeRequested(" set todo [atomselect top all];set minmaxvec [measure minmax $todo];set minz [lindex $minmaxvec 0 2];set maxz [lindex $minmaxvec 1 2];set minzz [expr [lindex $minmaxvec 0 2] - 2];set maxzz [expr [lindex $minmaxvec 1 2] + 2];proc cortaplano { valor } { global todo;global minmaxvec;global minz; global maxz; global minzz;global maxzz;set cutz [expr $minzz+($maxzz-$minzz)*($valor/100.0)];set centro {0.0 0.0};lappend centro $cutz;mol clipplane center 0 0 0 $centro;mol clipplane normal 0 0 0 {0.0 0.0 1.0};mol clipplane status 0 0 0 1;} "); }
signals:
  void commandRaised(QString comm);
  void initCodeRequested(QString code);
};
#endif
