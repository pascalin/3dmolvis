// File : ScaleWidget.cpp


//	Copyright (C) 2007 Natalia Pérez Escutia
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


#include <QtGui>
#include "ScaleWidget.h"
#include <iostream>
using namespace std;

ScaleWidget::ScaleWidget(QWidget *parent) : QWidget(parent)
{
  setupUi(this);
  connect(Slider, SIGNAL(valueChanged(int)), this, SLOT(slider(int)));
}

void ScaleWidget::slider(int size)
{
 
  std::ostringstream command; 
  //auxiliar=size;

  //cout << "valor de size " << size << "\n";
  //cout << "valor de value " << value << "\n";
  //cout << "valor de final " << final << "\n";
  //cout << "valor de aux " << auxiliar << "\n";
  
  	//if(auxiliar>size) //|| size==0)
		//{
			//final=size*0.1;
			//final=(auxiliar*0.01)-0.01;
			//cout << "valor de final disminuyendo" << final << "\n";
		//}
  	//else
		//{
			//final=size*0.01;
			//cout << "valor de final aumentando " << final << "\n";
		//}

float valor=size*0.01;  
command << "scale to " << valor;
  	//command << "scale by " << auxiliar;
  	//auxiliar=size;
  	//cout << "valor de command " << command.str().c_str() << "\n";
  emit commandRaised(QString(command.str().c_str()));
}

