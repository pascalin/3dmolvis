/***************************************************************************
 *            SimWIdget.h
 *
 *  Fri Aug 31 01:49:00 2007
 *  Copyright  2007  User
 *  Email axyalms@gmail.com 
 ****************************************************************************/
//	Copyright (C) 2007 Alejandro Mata Sánchez
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
#ifndef SIMWIDGET_H
#define SIMWIDGET_H
#include "GenericWidget.h"
#include <QTimer>
#include <QTime>
#include "ui_SimWidget.h"

class SimWidget;
class SimWidget : public GenericWidget, public Ui::SimWidget
{ 
	Q_OBJECT
public:		
	
	SimWidget(QWidget * parent= 0 );
	
public slots:
	
	//void vmdArranca();// Este slot sirve apra arrancar el vmd cuando arranca el widget
	//void autoimd();// Este slot inicio el script de autoimd, que genera los parámetros de la simulación y lo deja esperando al visualizador
	void startSim();// Conecta el visualizador con la simulación
	void pauseSim();// pausa la visualización de la simulación
	void stopSim();//detiene el visualizdor y guarda los cambios
	void discardSim();// descarta los cambios que ocurrieron por la visualización
	void setVmd();// inicia a Vmd, para poder hacerlo standalone(deprecated)
	void setNamd();// prepara todo antes del uso del namd2
	void connectSim();// conecta con la simulación ya ke esta esta lista
	// Esta slot recibe la salida producida por VMD
	void processOutput(QString) {}
  	// Esta slot envia el codigo de inicializacion de Tcl
  	void sendInitCode() { emit initCodeRequested("AutoIMD::startup;wm withdraw .autoimd");}
	
	
signals:
	//señal errorComando obsoleta
	//void errorComando();// se genera cuando hay un error en el comando enviado
  	/* Esta signal envia los comando directamente al proceso de VMD  */
  	void commandRaised(QString comm);
  	/* Esta signal solamente se requiere para uso interno */
  	void initCodeRequested(QString code);
private:
	QStringList param;
	bool pressed,paused;
	QTime tiempo;
	int t;
};




#endif /* SIMWIDGET_H */
