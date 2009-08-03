/*
 *  OriginData.cpp
 *  wizard
 *
 *  Created by Alejandro Mata Sánchez on 31/12/07.
 *  Copyright 2007 All rights reserved.
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
#include "OriginData.h"



OriginData::OriginData(QWidget *parent) : QWizardPage(parent)
{
	setupUi( this );
	setTitle(tr("Select Molecules for your lesson"));
	setSubTitle(tr("Select the molecule file"));
	registerField("files*", lineEdit);
	connect(pushButton,SIGNAL(clicked()),this,SLOT(FileDialog()));
}
// FUncion Obten nombres de archivos, para copiarlos posteriormente al directorio seleccionado y generar la leccion
//Recibe: nada	Devuleve: Lista de Archivos (QStringList)
QStringList OriginData::FileDialog()
{
	File = QFileDialog::getOpenFileNames(this,"Select VMD molecules Files",QDir::homePath(),"VMD Files(*.pdb *.psf)");
	lineEdit->setText("");
	
//	QListIterator<QString> i(File);
//	while(i.hasNext()){
//		QFile arch(i.next());
//		if(!arch.exists())
//			return QStringList("");
//		else
//		{
//			lineEdit->insert(File.join(" "));
//			return File;
//		}
//	}
	lineEdit->insert(File.join(" "));
	return File;
}
