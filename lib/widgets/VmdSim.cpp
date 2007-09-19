
/***************************************************************************
 *            vmdsim.h
 *
 *  Fri Aug 31 01:49:00 2007
 *  Copyright  2007  User
 *  Email axyalms@gmail.com 
 ****************************************************************************/
#include <QtGui>
#include "VmdSim.h"
#include "../CommandProcess.h"

VmdSim::VmdSim(QWidget *parent)
{
 	setupUi(this);
	
	//CommandProcess *namd2process = new CommandProcess("./bin/namd2", "", "exit", param);
	//VmdMainWindow ventana_vmd; esta parte se dejo de utilizar
	//QObject::connect(vmdbutton, SIGNAL(clicked()),vmdprocess, SLOT(startProcess())); 
	/* El boton de VMD y namd2 se dejo de emplear debido a que en la vnetan principal ya existia
	una ventana de VMD y el namd2 porque se ejecuta ucando se llama el proc de autoimd
	QObject::connect(namd2, SIGNAL(clicked()),namd2process, SLOT(startProcess()));
	----> La idea de esta parte es para inicializar los vlaores de los botones para poder usarlso adecuadamente*/
	QObject::connect(arranca, SIGNAL(clicked()),this, SLOT(arranc()));
	QObject::connect(detiene, SIGNAL(clicked()),this, SLOT(deten()));
	QObject::connect(descartar, SIGNAL(clicked()),this, SLOT(descarta()));
	QObject::connect(pausa, SIGNAL(clicked()),this, SLOT(paus()));
};
/*
La idea inicial para este constructor, es que el gui puede trabajr integrado con le proyecto,
asi como stand-alone
*/
VmdSim::VmdSim()
{
 	setupUi(this);
	
	
	//VmdMainWindow ventana_vmd; esta parte se dejo de utilizar
	//QObject::connect(vmdbutton, SIGNAL(clicked()),vmdprocess, SLOT(startProcess())); 
	/* El boton de VMD y namd2 se dejo de emplear debido a que en la vnetan principal ya existia
	una ventana de VMD y el namd2 porque se ejecuta ucando se llama el proc de autoimd
	QObject::connect(namd2, SIGNAL(clicked()),namd2process, SLOT(startProcess()));
	----> La idea de esta parte es para inicializar los vlaores de los botones para poder usarlso adecuadamente*/
	QObject::connect(vmdbutton, SIGNAL(clicked()),this, SLOT(preparaVmd()));
	QObject::connect(namd2, SIGNAL(clicked()),this, SLOT(preparaNamd()));
	QObject::connect(arranca, SIGNAL(clicked()),this, SLOT(arranc()));
	QObject::connect(detiene, SIGNAL(clicked()),this, SLOT(deten()));
	QObject::connect(descartar, SIGNAL(clicked()),this, SLOT(descarta()));
	QObject::connect(pausa, SIGNAL(clicked()),this, SLOT(paus()));
	
	
};
/*
----> VmdArranca se volvio obsoleta
VmdSim::VmdArranca()
{
	
}
*/
/*
-----> este slot implementó la llamada al simulador autoimd
recibe: nada	devuelve: nada
*/
void VmdSim::arranc()
{
	//emit commandRaised( QString("AutoIMD::submit all") ); en un principio desde aqui se 
	//preparaba y arrancaba, pero en la pràctica se vio que teniamos que prepara antes y luego
	// arrancar con el autoconnect
	emit commandRaised( QString("AutoIMD::autoconnect") );
}
/*
-----> el slot autoimd se volvio obsoleto
recibe: nada	devuelve: nada
*/
/*
VmdSim::autoimd()
{
	emit commandRaised();
}
*/
/*
-----> este slot implementó para detener al simulación, pero dejandola en el estado
en el que se quedo la simulación
recibe: nada	devuelve: nada
*/
void VmdSim::deten()
{
	emit commandRaised( QString("AutoIMD::finish") );
}
/*
-----> se usa para pausar la simulación, pero dejandola en el estado
en el que se quedo la simulación
recibe: nada	devuelve: nada
*/
void VmdSim::paus()
{
	emit commandRaised( QString("imd pause toggle") );
}
/*
-----> se usa para detener la simulación, pero restaurandola al estado original
recibe: nada	devuelve: nada
*/
void VmdSim::descarta()
{
	emit commandRaised( QString("AutoIMD::finish -nosave") );
}
/*
-----> Prepara la simulación para que se peuda iniciar
recibe: nada	devuelve: nada
*/
void VmdSim::preparaNamd()
{
	emit commandRaised( QString("AutoIMD::submit all") );
}
/*
-----> Prepara a Vmd
recibe: nada	devuelve: nada
*/
void VmdSim::preparaVmd()
{
// aqui se pretende arrancar vmd con el botton de arrancar vmd, pero antes se debe crear uan instancia del commando
	// y hacer la conecion de la salida del comando con lo ke le enviemos aki
	CommandProcess *vmdprocess = new CommandProcess("./bin/vmd", "", "exit", param);
	QObject::connect(this, SIGNAL(commandRaised(QString)),vmdprocess, SLOT(sendCommand(QString)));	
	vmdprocess->startProcess();
}
