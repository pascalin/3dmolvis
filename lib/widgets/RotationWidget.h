// File : RotationWidget.h


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

/*
 * Este widget contiene tres elementos de control de la clase QDial,
 * con los nombre x_dial, y_dial y z_dial. Cada vez que uno de estos
 * widgets emite la se#al valueChanged se activa el slot
 * correspondiente (rotateX, rotateY o rotateZ), que a su vez emite la
 * se#al commandRaised, enviando el comando "rotate X by" indicando el
 * angulo de rotacion. Para calcular que tantos grados hay que rotar
 * se calcula la diferencia entre el valor enviado por valueChanged y
 * el valor anterior.
*/


#ifndef ROTATIONWIDGET_H
#define ROTATIONWIDGET_H

#include <QWidget>
#include <sstream>
#include "ui_RotationWidget.h"

/* Clase que implementa las funciones del widget de rotacion  */
class RotationWidget : public QWidget, public Ui::RotationWidget // Utiliza herencia multiple de QWidget y Ui::RotationWidget
{
  Q_OBJECT // Macro que introduce los miembros requeridos por todo objeto de Qt
private:
  int x_angle, y_angle, z_angle; // Variables privadas para almacenar la ultima rotacion sobre cada eje
public:
  RotationWidget(QWidget *parent = 0); //Constructor de la clase. Recibe como argumento opcional el widget padre
public slots:
/* Slots que son llamadas cada vez que se activa el widget correspondiente a la rotacion sobre X, Y o Z */
  void rotateX(int);
  void rotateY(int);
  void rotateZ(int);
  /* Esta slot recibe la salida producida por VMD, pero este widget no la utiliza */
  void processOutput(QString) {}
  /* Esta slot envia el codigo de inicializacion de Tcl, pero este widget no lo requiere*/
  void sendInitCode() { emit initCodeRequested(""); }
signals:
  /* Esta signal envia los comando directamente al proceso de VMD  */
  void commandRaised(QString comm);
  /* Esta signal solamente se requiere para uso interno */
  void initCodeRequested(QString code);
};
#endif
