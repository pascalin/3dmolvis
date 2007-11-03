
/***************************************************************************
 *            SimWidget.cpp
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

#include "SimWidget.h"
#include "../CommandProcess.h"
#include <iostream>
using namespace std;
//Define si algunos botones estan disponibles.

SimWidget::SimWidget(QWidget *)
{
 	setupUi(this);
	t=2500;
	//CommandProcess *namd2process = new CommandProcess("./bin/namd2", "", "exit", param);
	//VmdMainWindow ventana_vmd; esta parte se dejo de utilizar
	//QObject::connect(vmdbutton, SIGNAL(clicked()),vmdprocess, SLOT(startProcess())); 
	//El boton de VMD y namd2 se dejo de emplear debido a que en la vnetan principal ya existia
	//una ventana de VMD y el namd2 porque se ejecuta ucando se llama el proc de autoimd
	//QObject::connect(namd2, SIGNAL(clicked()),namd2process, SLOT(startProcess()));
	//----> La idea de esta parte es para inicializar los vlaores de los botones para poder usarlso adecuadamente
	connect(start, SIGNAL(clicked()),this, SLOT(startSim()));
	connect(stop, SIGNAL(clicked()),this, SLOT(stopSim()));
	connect(discard, SIGNAL(clicked()),this, SLOT(discardSim()));
	connect(pause, SIGNAL(clicked()),this, SLOT(pauseSim()));
	QTimer::singleShot(t,this,SLOT(setNamd() ));	
}

/*
La idea inicial para este constructor, es que el gui puede trabajr integrado con le proyecto,
asi como stand-alone
*/

/*
SimWidget::SimWidget()
{
 	setupUi(this);
	
	
	//VmdMainWindow ventana_vmd; esta parte se dejo de utilizar
	//QObject::connect(vmdbutton, SIGNAL(clicked()),vmdprocess, SLOT(startProcess())); 
	// El boton de VMD y namd2 se dejo de emplear debido a que en la vnetan principal ya existia
	//una ventana de VMD y el namd2 porque se ejecuta ucando se llama el proc de autoimd
	//QObject::connect(namd2, SIGNAL(clicked()),namd2process, SLOT(startProcess()));
	//----> La idea de esta parte es para inicializar los vlaores de los botones para poder usarlso adecuadamente
	//Estos botones desaparecieron, para integrarlo al a version 1.0 vmdgui
	//QObject::connect(vmdbutton, SIGNAL(clicked()),this, SLOT(setVmd()));
	//QObject::connect(namd2, SIGNAL(clicked()),this, SLOT(setNamd()));
	QObject::connect(start, SIGNAL(clicked()),this, SLOT(startSim()));
	QObject::connect(stop, SIGNAL(clicked()),this, SLOT(stopSim()));
	QObject::connect(discard, SIGNAL(clicked()),this, SLOT(discardSim()));
	QObject::connect(pause, SIGNAL(clicked()),this, SLOT(pauseSim()));
	
};
*/
/*
-----> este slot implementó la llamada conexion despues de un tiempo
para dalre tiempo suficiente al autoimd para prepara sus archivos
recibe: nada	devuelve: nada
*/
void SimWidget::connectSim()
{
	emit commandRaised( QString("AutoIMD::autoconnect") );	
}
/*
-----> este slot implementó la llamada al simulador autoimd
recibe: nada	devuelve: nada
*/
void SimWidget::startSim()
{

	//emit commandRaised( QString("AutoIMD::submit all") ); en un principio desde aqui se 
	//preparaba y arrancaba, pero en la pràctica se vio que teniamos que prepara antes y luego
	// arrancar con el autoconnect
				
	emit commandRaised( QString("AutoIMD::submit \"all\" ") );
		//debug msgs
	//cout << "Inicio los parametros de simulacion\n";
	//cout << "\tel tiempo que lleva corriendo es:" << tiempo.elapsed() << "\n";
	// Habilitamos de nuevo los botones necesarios y otros los desactivamos
	pressed=true;
	pause->setEnabled(pressed);
	discard->setEnabled(pressed);
	stop->setEnabled(pressed);
	pressed=false;
	start->setEnabled(pressed);

	//Lanzamos un contador de tiempo para conectar.. en lo que se inician los parametros..
	t=1500; // es para darle tiempo a ke prepare la simulacion (ms)
	QTimer::singleShot(t,this,SLOT(connectSim() ));
	emit commandRaised( QString("wm withdraw .autoimd") );
}
/*
-----> el slot autoimd se volvio obsoleto
recibe: nada	devuelve: nada
*/
/*
SimWidget::autoimd()
{
	emit commandRaised();
}
*/
/*
-----> este slot implementó para detener al simulación, pero dejandola en el estado
en el que se quedo la simulación
recibe: nada	devuelve: nada
*/
void SimWidget::stopSim()
{
	
	emit commandRaised( QString("AutoIMD::finish") );
	// Habilitamos de nuevo los botones necesarios y otros los desactivamos
	pause->setEnabled(pressed);
	discard->setEnabled(pressed);
	stop->setEnabled(pressed);
	pressed=true;
	start->setEnabled(pressed);
}
/*
-----> se usa para pausar la simulación, pero dejandola en el estado
en el que se quedo la simulación
recibe: nada	devuelve: nada
*/
void SimWidget::pauseSim()
{
	
	emit commandRaised( QString("imd pause toggle") );
}
/*
-----> se usa para detener la simulación, pero restaurandola al estado original
recibe: nada	devuelve: nada
*/
void SimWidget::discardSim()
{
	
	emit commandRaised( QString("AutoIMD::finish -nosave") );
	// Habilitamos de nuevo los botones necesarios y otros los desactivamos
	pause->setEnabled(pressed);
	discard->setEnabled(pressed);
	stop->setEnabled(pressed);
	pressed=true;
	start->setEnabled(pressed);	
}
/*
-----> Prepara la simulación para que se peuda iniciar
recibe: nada	devuelve: nada
*/
void SimWidget::setNamd()
{
	emit commandRaised( QString("AutoIMD::startup") );
	//debug msgs
	cout << "Inicio ventana autoimd\n"; 
	cout << "\tel tiempo que lleva corriendo es:" << tiempo.elapsed() << "\n";
	
	//se verifica si ya paso cierto tiempo, para minimizar la ventana
	if(tiempo.elapsed()>t)
	{			
		emit commandRaised( QString("wm withdraw .autoimd") );
			//debug msgs
		//cout << "minimiza la ventana\n\n";		
	}
}
/*
-----> Prepara a Vmd
recibe: nada	devuelve: nada
*/
void SimWidget::setVmd()
{
// aqui se pretende arrancar vmd con el botton de arrancar vmd, pero antes se debe crear uan instancia del commando
	// y hacer la conecion de la salida del comando con lo ke le enviemos aki
	CommandProcess *vmdprocess = new CommandProcess("./bin/vmd", "", "exit", param);
	QObject::connect(this, SIGNAL(commandRaised(QString)),vmdprocess, SLOT(sendCommand(QString)));	
	vmdprocess->startProcess();
}
