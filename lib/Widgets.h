// File : Widgets.h


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
#ifndef WIDGETS_H
#define WIDGETS_H

#include <QStringList>
#include "widgets/GenericWidget.h"
#include "widgets/CommandLineWidget.h"
#include "widgets/OutputWidget.h"
#include "widgets/RotationWidget.h"
#include "widgets/ScaleWidget.h"
#include "widgets/RotaWidget.h"
#include "widgets/MouseModeWidget.h"
#include "widgets/AnimateWidget.h"
#include "widgets/StereoWidget.h"
#include "widgets/ResetWidget.h"
#include "widgets/PlanesWidget.h"
#include "widgets/GLShadingWidget.h"
#include "widgets/SimWidget.h"



class WidgetManager
{
  // Contains names of all widget classes
  QStringList widget_list;
public:
  WidgetManager();
  // Returns a widget of the specified type
  GenericWidget *createWidgetByName(QString);
  // Returns a QStringList containing the names of all registered widgets
  QStringList getWidgetList();
  // Returns title of specified widget
  QString getTitleByName(QString);
  // Returns decription of specified widget
  QString getDescriptionByName(QString);
};
#endif
