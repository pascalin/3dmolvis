/*
 *  SaveLesson.h
 *  wizard
 *
 *  Created by Alejandro Mata Sánchez on 31/12/07.
 *  Copyright 2007  All rights reserved.
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
#ifndef SAVELESSON_H
#define SAVELESSON_H


#include <QWizardPage>
#include <QtGui>
#include <QFileDialog>
#include <QDir>
#include "ui_SaveLesson.h"


class  SaveLesson : public QWizardPage, public Ui::SaveLesson
{
    Q_OBJECT
public:
	SaveLesson(QWidget *parent = 0);
public slots:
	QString destinationDir();
private:
	QString destDir;
};
#endif
