// File : GLShadingWidget.cpp


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


#include "GLShadingWidget.h"

GLShadingWidget::GLShadingWidget(QWidget *parent)
{
  title = tr("Programmable Shading");
  description = tr("This control allows users to enable/disable OpenGL Programmable Shading if it is available.");
  init_code = "";
  if (parent)
    setParent(parent);
  setupUi(this);
  connect(push_button, SIGNAL(clicked(bool)), this, SLOT(checkState(bool)));
}

void GLShadingWidget::checkState(bool state)
{
  if (state)
    emit commandRaised("display rendermode GLSL");
  else
    emit commandRaised("display rendermode Normal");
}

void GLShadingWidget::processOutput(QString output)
{
  if (output.contains("OpenGL Programmable Shading not available"))
    setEnabled(false);
}
