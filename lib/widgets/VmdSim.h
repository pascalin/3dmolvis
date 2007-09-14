/***************************************************************************
 *            vmdsim.h
 *
 *  Fri Aug 31 01:49:00 2007
 *  Copyright  2007  User
 *  Email axyalms@gmail.com 
 ****************************************************************************/

#ifndef VMDSIM_H
#define VMDSIM_H
#include "ui_VmdSim.h"
//#include "CommandProcess.h"
#ifdef __cplusplus
extern "C"
{
#endif
class VmdSim;
class VmdSim : public QWidget, public Ui::vmdsim
{ 
	Q_OBJECT
public:		
	VmdSim(QWidget *parent);
	
	VmdSim();
	//~VmdSim();
	//QFile *tcl_file = NULL; impelementado para que corriera scripts de tcl al inicio

public slots:
	
	//void vmdArranca();// Este slot sirve apra arrancar el vmd cuando arranca el widget
	//void autoimd();// Este slot inicio el script de autoimd, que genera los parámetros de la simulación y lo deja esperando al visualizador
	void arranc();// Conecta el visualizador con la simulación
	void paus();// pausa la visualización de la simulación
	void deten();//detiene el visualizdor y guarda los cambios
	void descarta();// descarta los cambios que ocurrieron por la visualización
	void preparaVmd();// inicia a Vmd, para poder
	void preparaNamd();// prepara todo antes del uso del namd2
	// Esta slot recibe la salida producida por VMD
	void processOutput(QString) {}
  	// Esta slot envia el codigo de inicializacion de Tcl
  	void sendInitCode() { emit initCodeRequested("");}
	
	
signals:
	//señal errorComando obsoleta
	//void errorComando();// se genera cuando hay un error en el comando enviado
  	/* Esta signal envia los comando directamente al proceso de VMD  */
  	void commandRaised(QString comm);
  	/* Esta signal solamente se requiere para uso interno */
  	void initCodeRequested(QString code);
private:
	QStringList param;
};


#ifdef __cplusplus
}
#endif

#endif /* _VMDSIM_H */
