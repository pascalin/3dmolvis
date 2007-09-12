// File : OptionBox.h


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
 *  OptionButton y OptionBox son especializaciones de QCheckBox y de
 *  QToolBox respectivamente. Esencialmente, lo que cada una de estas
 *  clases hace es implementar el envio de comandos con un parametro
 *  booleano a VMD. Cada OptionButton representa una opcion que
 *  incluye un nombre y un comando. Al modificar una opcion el
 *  OptionButton emitira la se~al commandRaised con el nombre del
 *  comando y un valor de 0 si la opcion fue desactivada o 1 en caso
 *  contrario.
 */


#ifndef OPTIONBOX_H
#define OPTIONBOX_H

#include <QToolBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QMap>


class OptionButton : public QCheckBox
{
  Q_OBJECT
private:
  QString command;
public:
  OptionButton(QString text, QString command, QWidget *parent=0);
public slots:
  void sendCommand(bool checked);
signals:
 void commandRaised(QString); 
};


class OptionBox : public QToolBox
{
  Q_OBJECT
/* private: */
/*   QMap<int, QWidget*> group_widgets; */
/*   QMap<int, QVBoxLayout*> group_layouts; */
/*   QMap<int, QString> group_titles; */
public:
  OptionBox(QWidget *parent=0);
/*   void addOption(QString name, QString command, int group); */
/*   void setGroupTitle(int group, QString title); */
/*   void update(); */
  void clear();
public slots:
  void sendCommand(QString comm);
signals:
  void commandRaised(QString);
};

#endif
