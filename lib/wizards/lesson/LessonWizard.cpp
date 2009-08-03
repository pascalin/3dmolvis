/*
 *  LessonWizard.cpp
 *  wizard
 *
 *  Created by Alejandro Mata Sánchez on 02/01/08.
 *  Copyright 2008  All rights reserved.
 *
 */

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
#include <QtGui>
#include <iostream>

#include "LessonWizard.h"
using namespace std;
/*
QListWidget * SelectRepPage::representation=0;
QComboBox * SelectRepPage::mols=0;
*/
//SelRep * SelectRepPage::sr=0;
LessonWizard::LessonWizard(QWidget *parent) : QWizard(parent)
{
        sr = new SelRep;
        ws = new WidgetSelect;
        wid= new WidgetManager();
	setPage(IntroPage,new Introduction);
	setPage(GeneralPage,new GeneralData);
        setPage(WidgetPage,ws);
	setPage(OriginPage,new OriginData);
        setPage(SelRepPage,sr);
	setPage(SavePage,new SaveLesson);
	
	setWindowTitle("Lesson Wizard");
	
}

/* Método Provisto para poder Generar una Selección de representaciones para cada uno de nuestros archivos pdb seleccionados
mediante un comboB
recibe: nada
devuelve: nada
Notas:
Implementado únicamente para SelRepPage, porque es la única que queremos modificar en base a la pagina anterior
*/
// void SelectRepPage::initializePage()
// {

// 	QString files=field("files").toString();
// 	QStringList origin_files =files.split(" ");
// 	QListIterator<QString> i(origin_files);
// 	int pos=0;
// 	//La Expresion Regular filtra solo los nombres de archivo, para que peudan ser insertados en el comboBox 
// 	QRegExp rx("((\\w+\\.pdb\\b)+)");
// 	rx.setCaseSensitivity(Qt::CaseInsensitive);
// 	sr->fileSel->clear();
// 	while(i.hasNext())
// 	{
// 		i. next();
// 		pos=rx.indexIn(files,pos);
// 		//Añadimos solo los pdb's al comboBox para usarlo en esta pagina
// 		if ( rx.exactMatch( rx.cap(0) ) )
// 			sr->fileSel->addItem(QString::number(sr->counter++)+ ":" + rx.cap(0) );
		
// 		pos += rx.matchedLength();
// 	}
// 	sr->counter=0;	

// }

void LessonWizard::writeLesson()
{

        QDomDocument lesson("application");
        QDomElement root,element,another_element;
        QDomComment comment;

        QString dest_file,files=field("files").toString();
        QStringList origin_files =files.split(" ");

        int pos=0;

        QFile xml( field("dir").toString() + "/" + field("title").toString() + ".xml" );
        QTextStream file(&xml);
//	QFile xml(field("dir").toString().append("test.xml") );


//	if(xml.isWritable() )
                xml.open(QIODevice::ReadWrite  | QIODevice::Truncate);
//		QTextStream file(&xml);


        //  Aqui empezamos la creación del árbol DOM
        root=lesson.createElementNS(NAMESPACE,"application");
        root.setAttribute("version",VERSION);

        comment = lesson.createComment("This is an automatic lesson file, dont modify unless you know what you are doing");
        root.appendChild(comment);

        // Aniadimos la parte de información de la lección (creador, descripcion, etc)
	QDomElement rdfns = lesson.createElementNS(RDF,"rdf:Description");
	QDomElement dcns = lesson.createElementNS(DC,"dc:title");
		dcns.appendChild(lesson.createTextNode( field("title").toString() ));
		rdfns.appendChild(dcns);
	dcns = lesson.createElementNS(DC,"dc:publisher");
		dcns.appendChild(lesson.createTextNode( field("author").toString() ));
		rdfns.appendChild(dcns);
	dcns = lesson.createElementNS(DC,"dc:creator");
		dcns.appendChild(lesson.createTextNode( field("author").toString() ));
		rdfns.appendChild(dcns);
	dcns = lesson.createElementNS(DC,"dc:description");
		dcns.appendChild(lesson.createTextNode( field("description").toString() ));
		rdfns.appendChild(dcns);
	dcns = lesson.createElementNS(DC,"dc:date");
		dcns.appendChild(lesson.createTextNode( QDateTime::currentDateTime().toString(Qt::ISODate) ));
	rdfns.appendChild(dcns);
	root.appendChild(rdfns);
	
	// Empezamos con el diseño de la lección, empezando por los controles a usar
	
	element = lesson.createElementNS(NAMESPACE,"controls");
	
        QStringList widgets = ws->selected_widget_model->stringList();
	QStringList::const_iterator widget_i;

	for ( widget_i=widgets.begin(); widget_i!=widgets.end(); ++widget_i )
        {
	  another_element=lesson.createElementNS(NAMESPACE,"control");
	  another_element.setAttribute("name", *widget_i);
	  element.appendChild(another_element);
        }
	root.appendChild(element);
	
	//Agregamos el elemento tclcode, que será el que introduzca código tcl
	element=lesson.createElementNS(NAMESPACE,"tclcode");
		QDomText text_element=lesson.createTextNode("\n\t\tmenu main off \n \
		display eyesep       0.065000 \n \
		display focallength  2.000000 \n \
		display height       6.000000 \n \
		display distance     -2.000000 \n \
		display projection   Orthographic \n \
		display nearclip set 0.0000010 \n \
		display farclip  set 10.000000 \n \
		display depthcue   off \n \
		display cuestart   0.500000 \n \
		display cueend     10.000000 \n \
		display cuedensity 0.400000 \n \
		display cuemode    Exp2 \n \
		axes location off \n \
		color scale method RGB \n ");
		//cd "+field("dir").toString());
		element.appendChild(text_element);
	root.appendChild(element);
		
		//element=lesson.createElementNS(NAMESPACE,"tclcode");
		QRegExp rx("((\\w+\\.pdb\\b)+)|((\\w+\\.psf\\b)+)");
		rx.setCaseSensitivity(Qt::CaseInsensitive);
		QListIterator<QString> i=QListIterator<QString>(origin_files);
		while(i.hasNext())
		{
			QString temp=i.next();
			pos=rx.indexIn(temp,pos);
			if( rx.exactMatch( dest_file=rx.cap(1) ) )
			{
				text_element=lesson.createTextNode("\nmol new "+dest_file +" type pdb \n");
				element.appendChild(text_element);
				pos =0;
				continue;
			}
			pos =0;
			pos=rx.indexIn(temp,pos);
			if( rx.exactMatch( dest_file=rx.cap(3) ) )
			{
				text_element=lesson.createTextNode("\nmol addfile "+dest_file +" type psf \n");
				element.appendChild(text_element);
				pos =0;
				continue;

			}
			
		}
		text_element=lesson.createTextNode("\nmol delrep 0 top \n");
		element.appendChild(text_element);
		
		//Esta parte crea las representaciones, en base a lso escogido por el usuario a lo largo del wizard
		comment = lesson.createComment("This is an automatic lesson file, dont modify unless you know what you are doing");
		root.appendChild(comment);
		
		//QListWidget *list=SelectRepPage::getRepresentation();
		QListWidget *list=sr->listWidget;
		QComboBox *molFiles=sr->fileSel;

		QRegExp expr("((\\b\\d+)\\:(\\w+)\\-(\\w+)\\-(\\w+\\b))"),expr1("((\\b\\d+)\\:(\\w+\\.\\w+\\b))");
		int numberRepresentations=0,numberFiles=0;
		list->setCurrentRow(0);
		molFiles->setCurrentIndex(0);
		QString tmp=list->takeItem(0)->text();
		expr.indexIn(tmp);
		while(list->count()!=0 && molFiles->count()!=0)
		{
			expr1.indexIn(molFiles->currentText());
			while( expr.cap(2)==expr1.cap(2) )
			{

                                //cout  << expr.cap(2).toStdString() << endl << expr1.cap(2).toStdString() << endl;
				if(expr.exactMatch(expr.cap(0)))
				{
					text_element=lesson.createTextNode("\n\t\tmol representation "+ expr.cap(3) +"\n \
		mol color "+ expr.cap(4) + "\n \
		mol selection { " + expr.cap(5) + " } \n \
		mol material Opaque	\n \
		mol addrep "+ QString::number(numberFiles) +"\n\
		mol showrep " + QString::number(numberFiles) +" "+  QString::number(numberRepresentations++) + " off\n\n" );
					element.appendChild(text_element);
				}
				if(list->count()!=0)
				{
					tmp=list->takeItem(0)->text();
					expr.indexIn(tmp);
				}
				else
					break;
				list->setCurrentRow(0);
			}
			numberFiles++;
			numberRepresentations=0;
			molFiles->removeItem(0);
			molFiles->setCurrentIndex(0);
		}
		
		//element.appendChild(text_element);
	root.appendChild(element);
	
	
	lesson.appendChild(root);
	lesson.save(file, 1);
	xml.flush();
	xml.close();
	/* Aqui es donde Copiamos los archivos de origen, a la carpeta donde deben de estar */

	//La Expresion Regular filtra solo los nombres de archivo, para que peudan ser copiados a la carpeta destino adecuadamente
	//QRegExp rx1("((\\w+\\.pdb\\b)+)|((\\w+\\.psf\\b)+)");
	//rx1.setCaseSensitivity(Qt::CaseInsensitive);
	pos=0;
	 i=QListIterator<QString>(origin_files);
	while(i.hasNext())
	{
		QString or_file=i. next();
		pos=rx.indexIn(files,pos);
		dest_file=rx.cap(0);
		
		QFile input( or_file );
		QFile output( field("dir").toString() + "/" +dest_file );
		//cout << field("dir").toString().toStdString() + "/" + dest_file.toStdString() << "\n";
		pos += rx.matchedLength();
		
		
			
		if (input.open(QIODevice::ReadOnly) && output.open(QIODevice::WriteOnly))
		{
			QTextStream inputstream(&input);
			QTextStream outputstream(&output);
			outputstream << inputstream.readAll();
			output.close();
			input.close();			
		}
	}
	return;
}

// GeneralDataPage::GeneralDataPage(QWidget *parent) : QWizardPage(parent)
// {
// 	gendata=new GeneralData();
// 	QHBoxLayout *layout=new QHBoxLayout;
// 	layout->addWidget(gendata);
// 	setLayout(layout);
// 	setTitle("Obtainig general data for the Lesson");
// 	registerField("title*",gendata->lineEdit);
// 	registerField("description*",gendata->lineEdit_3);
// 	registerField("author*",gendata->lineEdit_2);
// }


// IntroductionPage::IntroductionPage(QWidget *parent) : QWizardPage(parent)
// {
// 	intr=new Introduction();
// 	QHBoxLayout *layout=new QHBoxLayout;
// 	layout->addWidget(intr);
// 	setLayout(layout);
// 	setTitle("Introduction");
// 	setSubTitle("Information");
// }


// OriginDataPage::OriginDataPage(QWidget *parent) : QWizardPage(parent)
// {
// 	od=new OriginData();
// 	QHBoxLayout *layout=new QHBoxLayout;
// 	layout->addWidget(od);
// 	setLayout(layout);
// 	setSubTitle("Select the molecule file(s)");
// 	setTitle("Select Molecules for your lesson");
// 	registerField("files*",od->lineEdit);
	
// }


// SaveLessonPage::SaveLessonPage(QWidget *parent) : QWizardPage(parent)
// {
// 	sl=new SaveLesson();
// 	QHBoxLayout *layout=new QHBoxLayout;
// 	layout->addWidget(sl);
// 	setLayout(layout);
// 	setSubTitle("Select Destination Folder");
// 	setTitle("Select Destination Folder for your lesson");
// 	registerField("dir*",sl->lineEdit);
// }

// SelectRepPage::SelectRepPage(QWidget *parent) : QWizardPage(parent) 
// {
// 	sr=new SelRep();
// 	sr->counter=0;
// 	QHBoxLayout *layout=new QHBoxLayout;
// 	layout->addWidget(sr);
// 	setLayout(layout);
// 	setSubTitle("Select Representation of your molecules");
// 	setTitle("Select Representations for your lesson");
// 	registerField("rep_list*",sr->listWidget);
// 	registerField("selection",sr->lineEdit);
// 	//setRepresentation(sr->listWidget);
// 	//setMols(sr->fileSel);
// }
// void SelectRepPage::setSr(SelRep * selrep)
// {
// 	sr=selrep;
// }
// SelRep  * SelectRepPage::getSr()
// {
// 	return sr;
// }
/*
void SelectRepPage::setRepresentation(QListWidget * const lw )
{
	SelectRepPage::representation=lw;
}

 QListWidget * SelectRepPage::getRepresentation() 
{
	return SelectRepPage::representation;
}
void SelectRepPage::setMols(QComboBox * const cb )
{
	SelectRepPage::mols=cb;
}

QComboBox * SelectRepPage::getMols() 
{
	return SelectRepPage::mols;
}
*/
// WidgetSelectPage::WidgetSelectPage(QWidget *parent) : QWizardPage(parent)
// {
// 	ws=new WidgetSelect();
// 	QHBoxLayout *layout=new QHBoxLayout;
// 	layout->addWidget(ws);
// 	setLayout(layout);
// 	setSubTitle("Select from our wigdet library");
// 	setTitle("Select Widgets for your lesson");
// 	registerField("Animate",ws->animate);
// 	registerField("GLShading",ws->glshading);
// 	registerField("MouseMode",ws->mousemode);
// 	registerField("Output",ws->output);
// 	registerField("Planes",ws->planes);
// 	registerField("Reset",ws->reset);
// 	registerField("Rotation",ws->rotation);
// 	registerField("Rota",ws->rota);
// 	registerField("CommandLine",ws->commandline);
// 	registerField("Sim",ws->sim);
// 	registerField("Stereo",ws->stereo);
// 	registerField("Scale",ws->scale);
// }
