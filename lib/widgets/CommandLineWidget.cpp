// File : CommandLineWidget.cpp


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


#include <QtGui>
#include "CommandLineWidget.h"

CommandLineWidget::CommandLineWidget(QWidget *parent)
{
  title = tr("Command Line");
  description = tr("This controls allows users to send text commands directly to VMD. Useful for testing.");
  init_code = "";
  if (parent)
    setParent(parent);
  setupUi(this);
  connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(inputReceived()));
  connect(pushButton, SIGNAL(clicked()), this, SLOT(inputReceived()));
}

void CommandLineWidget::inputReceived()
{
  emit commandRaised(lineEdit->text());
  lineEdit->clear();
}
