/*
 *  SelRep.cpp
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

#include "SelRep.h"
#include <iostream>
using namespace std;
SelRep::SelRep(QWidget *parent) : QWizardPage(parent)
{
	setupUi( this );
	setTitle(tr("Select Representations for your lesson"));
	setSubTitle(tr("Select Representation of your molecules"));
	registerField("rep_list*", listWidget);
	registerField("selection", lineEdit);
	counter=0;
	connect(add,SIGNAL(clicked()),this,SLOT(addRep()));
	connect(del,SIGNAL(clicked()),this,SLOT(delRep()));
}

/* Método Provisto para poder Generar una Selección de representaciones para cada uno de nuestros archivos pdb seleccionados
mediante un comboB
recibe: nada
devuelve: nada
Notas:
Implementado únicamente para SelRepPage, porque es la única que queremos modificar en base a la pagina anterior
*/
void SelRep::initializePage()
{

	QString files=field("files").toString();
        QStringList origin_files =files.split(";");
	QListIterator<QString> i(origin_files);
	int pos=0;
	//La Expresion Regular filtra solo los nombres de archivo, para que peudan ser insertados en el comboBox 
	QRegExp rx("((\\w+\\.pdb\\b)+)");
	rx.setCaseSensitivity(Qt::CaseInsensitive);
	fileSel->clear();
	while(i.hasNext())
	{
		i. next();
		pos=rx.indexIn(files,pos);
		//Añadimos solo los pdb's al comboBox para usarlo en esta pagina
		if ( rx.exactMatch( rx.cap(0) ) )
			fileSel->addItem(QString::number(counter++)+ ":" + rx.cap(0) );
		
		pos += rx.matchedLength();
	}
	counter=0;

}

//Funcion addRep , sirve para añadir una representacion del combo Box de la izquierda a la lista de items de la derecha
// recibe: nada devuelve: nada
void SelRep::addRep()
{ 
	
	if(listWidget->count()==0  )
	{
		listWidget->addItem(selected=QString::number(fileSel->currentIndex())+":"+reps->currentText()+"-"+colors->currentText()+"-"+lineEdit->text());
		listWidget->setCurrentRow(0);
	}
	else
	{
		selected=QString::number(fileSel->currentIndex())+":"+reps->currentText()+"-"+colors->currentText()+"-"+lineEdit->text();

		for(int i =0;i<listWidget->count();i++)
		{
			if( selected != listWidget->item(i)->text() || selected != listWidget->currentItem()->text() )
			{
				listWidget->addItem(selected=QString::number(fileSel->currentIndex())+":"+reps->currentText()+"-"+colors->currentText()+"-"+lineEdit->text());
				listWidget->setCurrentRow(0);
				break;
			}
		}
		return;
	}
}



//Funcion delRep , borra una representacion de la lista de items de la derecha, obteniendo la seleccion actual y borrandola
// recibe: nada devuelve:nada
void SelRep::delRep()
{
	listWidget->removeItemWidget(listWidget->takeItem(listWidget->currentRow()));	
}

// void SelRep::setSr(SelRep * selrep)
// {
//   SelRep::sr=selrep;
// }

// SelRep  * SelRep::getSr()
// {
//   return SelRep::sr;
// }
