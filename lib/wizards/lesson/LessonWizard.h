/*
 *  LessonWizard.h
 *  wizard
 *
 *  Created by Alejandro Mata Sánchez on 02/01/08.
 *  Copyright 2008  All rights reserved.
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
#ifndef LESSONWIZARD_H
#define LESSONWIZARD_H

#include <QWizard>
#include <QXmlStreamWriter>
#include <QDomDocument>
#include <QFile>
#include "Introduction.h"
#include "GeneralData.h"
#include "WidgetSelect.h"
#include "OriginData.h"
#include "SelRep.h"
#include "SaveLesson.h"
#include "../../Widgets.h"

#define VERSION (QString)"1.0"
#define DC (QString)"http://purl.org/dc/elements/1.1/"
#define RDF (QString)"http://www.w3.org/1999/02/22-rdf-syntax-ns#"
#define NAMESPACE (QString)"http://tdmolvis.sourceforge.net/application/1.0/"


class LessonWizard : public QWizard
{
	Q_OBJECT
public:
	enum { IntroPage, GeneralPage, WidgetPage, OriginPage , SelRepPage , SavePage};
	LessonWizard(QWidget *parent=0);
	void writeLesson();
private:
        SelRep * sr;
        WidgetSelect * ws;
        WidgetManager * wid;
};


// class GeneralDataPage : public QWizardPage
// {
// 	Q_OBJECT
// public:
// 	GeneralDataPage(QWidget *parent=0);
// private:
// 	GeneralData *gendata;
// };


// class IntroductionPage : public QWizardPage
// {
// 	Q_OBJECT
// public:
// 	IntroductionPage(QWidget *parent=0);
// private:
// 	Introduction *intr;
// };


// class OriginDataPage : public QWizardPage
// {
// 	Q_OBJECT
// public:
// 	OriginDataPage(QWidget *parent=0);
// private:
// 	OriginData *od;

// };


// class SaveLessonPage : public QWizardPage
// {
// 	Q_OBJECT
// public:
// 	SaveLessonPage(QWidget *parent=0);
	
// private:
// 	SaveLesson *sl;
	
// };


// class SelectRepPage : public QWizardPage
// {
// 	Q_OBJECT
// public:
// 	SelectRepPage(QWidget *parent=0);
// 	static void setSr(SelRep * const);
// 	static SelRep  * getSr();

// 	virtual void initializePage () ;

// private:
// 	static SelRep *sr;
	
// };


// class WidgetSelectPage : public QWizardPage
// {
// 	Q_OBJECT
// public:
// 	WidgetSelectPage(QWidget *parent=0);
// private:
// 	WidgetSelect *ws;
// };

#endif
