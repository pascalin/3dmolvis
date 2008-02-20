VMDGui
Una interfaz para el manejo de sesiones de visualizacion con VMD.

DESCRIPCION
VMDGui es una aplicacion que facilita la creacion de sesiones de
visualizacion con VMD mediante una interfaz destinada a proveer
unicamente los controles mas apropiados para permitir una interaccion
agil e intuitiva de los usuarios.
VMDGui es especialmente apropiada para su uso en aplicaciones de
docencia.

INSTALACION
VMDGui emplea las bibliotecas de Qt para la mayor parte de sus
funciones, por lo que su compilacion requiere la instalacion de Qt 4.3
o superior.
Para compilar VMDGui es necesario emplear el comando qmake de la
siguiente manera:

$ qmake

La ejecucion de estos dos comandos creara un Makefile con las
instrucciones apropiadas para la construccion de VMDGui. Una vez
creado este Makefile, bastara con invocar el comando:

$ make

Una vez compilado exitosamente, bastara con ejecutar el siguiente
comando desde el directorio donde se compilo VMDGui:

$ ./vmdgui

ACERCA DE VMDGui

El desarrollo de VMDGui forma parte del proyecto Programa de fortalecimiento de
la docencia a traves del observatorio de visualizacion de la UNAM,
Ixtli.