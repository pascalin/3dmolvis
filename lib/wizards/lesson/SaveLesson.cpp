/*
 *  SaveLesson.cpp
 *  wizard
 *
 *  Created by Alejandro Mata Sánchez on 31/12/07.
 *  Copyright 2007. All rights reserved.
 *
 */

#include "SaveLesson.h"

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

SaveLesson::SaveLesson(QWidget *parent) : QWizardPage(parent)
{
	setupUi( this );
	setTitle(tr("Select Destination Folder for your lesson"));
     	setSubTitle(tr("Select Destination Folder"));
	registerField("dir*", lineEdit);
	connect(pushButton,SIGNAL(clicked()),this,SLOT(destinationDir()));

}
// esta funcion sirve, para abrir un dialogo de seleccion de directorio donde se salvara la leccion
//recibe: nada devuelve: nada
QString SaveLesson::destinationDir()
{
	destDir = QFileDialog::getExistingDirectory(this,"Select Destination Directory for your Lesson",QDir::homePath(),QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	lineEdit->setText("");
	lineEdit->insert( destDir );
	return destDir;

}
