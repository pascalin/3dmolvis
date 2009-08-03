/*
 *  WidgetSelect.h
 *  wizard
 *
 *  Created by Alejandro Mata Sánchez on 21/12/07.
 *  Copyright 2007  All rights reserved.
 *  Modified by David Suarez Pascal on 02/08/2009
 *
 */
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
#ifndef WIDGETSELECT_H
#define WIDGETSELECT_H


#include <QWizardPage>
#include <QtGui>
#include "ui_WidgetSelect.h"
#include "../../Widgets.h"
#include "MRoleStringListModel.h"


class  WidgetSelect : public QWizardPage, public Ui::WidgetSelect
{
    Q_OBJECT
public:
	WidgetSelect(QWidget *parent = 0);
	WidgetManager * wid;
	MRoleStringListModel *widget_model, *selected_widget_model;
	bool isComplete() const;
public slots:
	void changeWidgetDescription(int row);
	void removeSelectedItem();
	void addSelectedItem();
	void moveUpSelectedItem();
	void moveDownSelectedItem();
	void moveSelectedItem(bool move_up);
};
#endif
