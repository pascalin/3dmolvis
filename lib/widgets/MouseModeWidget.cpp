// File : MouseModeWidget.cpp


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


#include "MouseModeWidget.h"

MouseModeWidget::MouseModeWidget(QWidget *parent)
{
  title = tr("Mouse Mode");
  description = tr("With this control users can switch between several mouse interaction modes.");
  init_code = "";
  if (parent)
    setParent(parent);
  setupUi(this);
  connect(radio_rotate, SIGNAL(clicked()), this, SLOT(enableRotateMode()));
  connect(radio_scale, SIGNAL(clicked()), this, SLOT(enableScaleMode()));
  connect(radio_translate, SIGNAL(clicked()), this, SLOT(enableTranslateMode()));
}

void MouseModeWidget::enableRotateMode()
{
  emit commandRaised("mouse mode rotate");
}

void MouseModeWidget::enableScaleMode()
{
  emit commandRaised("mouse mode scale");
}

void MouseModeWidget::enableTranslateMode()
{
  emit commandRaised("mouse mode translate");
}
