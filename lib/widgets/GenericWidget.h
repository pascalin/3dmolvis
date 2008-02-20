// File : GenericWidget.h


//	Copyright (C) 2008 David Suarez Pascal
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

/* GenericWidget is intended to be the parent class of all widgets. It
   has three static methods employed by class WidgetManager to get a
   static info about the widget class.
*/

#ifndef GENERICWIDGET_H
#define GENERICWIDGET_H

#include <QWidget>

class GenericWidget : public QWidget
{
    Q_OBJECT
protected:
  QString init_code;
  QString title;
  QString description;
public:
  QString getInitCode();
  QString getTitle();
  QString getDescription();
public slots:
  void processOutput(QString output);
signals:
  void commandRaised(QString command);
};
#endif
