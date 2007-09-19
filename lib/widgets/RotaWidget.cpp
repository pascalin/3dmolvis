// File : RotaWidget.cpp


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


#include <QtGui>
#include "RotaWidget.h"

RotaWidget::RotaWidget(QWidget *parent) : QWidget(parent)
{
  setupUi(this);
  connect(pushButton_on, SIGNAL(clicked()), this, SLOT(rotaon()));
  connect(pushButton_off, SIGNAL(clicked()), this, SLOT(rotaoff()));
  connect(pushButton_res, SIGNAL(clicked()), this, SLOT(reset()));
}

void RotaWidget::reset()
{
  std::ostringstream command;
  command << "display resetview";
  emit commandRaised(QString(command.str().c_str()));
}

void RotaWidget::rotaon()
{
  std::ostringstream command;
  command << "rock Y by 0.02 20000";
  emit commandRaised(QString(command.str().c_str()));
}

void RotaWidget::rotaoff()
{
  std::ostringstream command;
  command << "rock off";
  emit commandRaised(QString(command.str().c_str()));
}

