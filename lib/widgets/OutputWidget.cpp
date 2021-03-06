// File : OutputWidget.cpp


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
#include "OutputWidget.h"

OutputWidget::OutputWidget(QWidget *parent)
{
  title = tr("Log");
  description = tr("This controls enables displaying of VMD messages. Useful for debugging of new lessons or controls.");
  init_code = "";
  if (parent)
    setParent(parent);
  setupUi(this);
}

void OutputWidget::processOutput(QString output)
{
  textEdit->append(output);
}
