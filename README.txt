3DMolVis
Interface for the management of visualization sessions with VMD.

DESCRIPTION
3DMolVis is a program that makes easy design of visualization sessions
with VMD by means of an interface targetted on providing only the
essential interactive controls delivering easy and fast interaction to
the users.
3DMolVis is specially targeted on CAI audiences.

INSTALL
3DMolVis is programmed almost fully with Qt libraries, and it requires
to compile Qt 4.3 or greater on your system. Also, for running,
3DMolVis requires a recent version of VMD installed on your system.
To build 3DMolVis all you need to do is to run the qmake command
inside the top folder containing the source code of 3DMolVis:

$ qmake

This will create a Makefile which contains instructions for building
3DMolVis. After running qmake you will need to run make in the same
folder as qmake:

$ make

After building 3DMolVis, you will need to run the following script in
order to set a link to VMD and to compile translations of 3DMolVis:

$ ./bin/setvmdgui.sh

Once this last command finish successfully, you will find the vmdgui
program in the same folder. To run 3DMolVis just run:

$ ./vmdgui

ABOUT 3DMolVis

3DMolVis project is developed on the Universidad Nacional Autonoma de
Mexico, and is sponsored by the Program for Teaching Enpowerment of
Ixtli visualization laboratory.

Project page: http://tdmolvis.sourceforge.net
