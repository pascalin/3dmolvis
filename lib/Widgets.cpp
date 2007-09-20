// File : Widgets.cpp


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


#include "Widgets.h"

WidgetManager::WidgetManager()
{
  widget_list << "CommandLine";
  widget_list <<  "Output";
  widget_list <<  "Rotation";
  widget_list <<  "Scale";
  widget_list <<  "Rota";
  widget_list <<  "MouseMode";
  widget_list <<  "Animate";
  widget_list <<  "Stereo";
}


QWidget *WidgetManager::createWidgetByName(QString name)
{
  int index = widget_list.indexOf(name);
  QWidget* widget=NULL;
  switch (index)
    {
    case 0:
      widget = new CommandLineWidget();
      break;
    case 1:
      widget = new OutputWidget();
      break;
    case 2:
      widget = new RotationWidget();
      break;
    case 3:
      widget = new ScaleWidget();
      break;
    case 4:
      widget = new RotaWidget();
      break;
    case 5:
      widget = new MouseModeWidget();
      break;
    case 6:
      widget = new AnimateWidget();
      break;
    case 7:
      widget = new StereoWidget();
      break;
    }
  return widget;
}
