// File : RotationWidget.cpp


//	Copyright (C) 2007 David Suarez Pascal
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
#include "RotationWidget.h"

/* El constructor de la clase principal */
RotationWidget::RotationWidget(QWidget *parent)
{
  if (parent)
    setParent(parent);
  setupUi(this); // Llama la funcion Ui::RotationWidget::setupUi que agrega todas las propiedades definidas en el designer
  /* Conecta el control QDial para rotacion sobre X,Y y Z con el slot rotateX , rotateY y rotateZ, segun corresponda*/
  connect(x_dial, SIGNAL(valueChanged(int)), this, SLOT(rotateX(int)));
  connect(y_dial, SIGNAL(valueChanged(int)), this, SLOT(rotateY(int)));
  connect(z_dial, SIGNAL(valueChanged(int)), this, SLOT(rotateZ(int)));
}

/* Implementa las funciones de rotacion sobre el eje X */
void RotationWidget::rotateX(int degrees)
{
  std::ostringstream command; // Crea una cadena temporal con la clase std::ostringstream de la biblioteca estandar de C++
  command << "rotate X by " << degrees-x_angle; // Agrega a la cadena temporal el comando Tcl para VMD que indica cuantos grados hay que rotar
  emit commandRaised(QString(command.str().c_str())); // Envia el comando contenido en la cadena temporal a VMD
  x_angle = degrees; // Actualiza el valor de la variable privada x_angle
}

/* Implementa las funciones de rotacion sobre el eje Y */
void RotationWidget::rotateY(int degrees)
{
  std::ostringstream command;
  command << "rotate Y by " << degrees-y_angle;
  emit commandRaised(QString(command.str().c_str()));
  y_angle = degrees;
}

/* Implementa las funciones de rotacion sobre el eje Z */
void RotationWidget::rotateZ(int degrees)
{
  std::ostringstream command;
  command << "rotate Z by " << degrees-z_angle;
  emit commandRaised(QString(command.str().c_str()));
  z_angle = degrees;
}
