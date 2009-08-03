/*
 *  SelRep.h
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
#ifndef SELREP_H
#define SELREP_H


#include <QWizardPage>
#include <QtGui>
#include <QListWidget>
#include "ui_SelRep.h"


class  SelRep : public QWizardPage, public Ui::SelRep
{
    Q_OBJECT
public:
	SelRep(QWidget *parent = 0);
	virtual void initializePage();
/* 	static void setSr(SelRep * const); */
/* 	static SelRep  *getSr(); */
	int counter;
public slots:
	void addRep();
	void delRep();
private:
	QString selected;
/* 	static SelRep *sr; */
	 
};
#endif
