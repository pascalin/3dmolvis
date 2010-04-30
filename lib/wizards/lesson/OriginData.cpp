/*
 *  OriginData.cpp
 *  wizard
 *
 *  Created by Alejandro Mata Sánchez on 31/12/07.
 *  Copyright 2007 All rights reserved.
 *
 */

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
#include "OriginData.h"



OriginData::OriginData(QWidget *parent) : QWizardPage(parent)
{
	setupUi( this );
	setTitle(tr("Select Molecules for your lesson"));
	setSubTitle(tr("Select the molecule file"));
	registerField("files*", lineEdit);
        lineEdit->hide();

	data_model = new MRoleStringListModel();
	dataList->setModel(data_model);

        connect(data_model, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(updateFileList()));
        connect(data_model, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(updateFileList()));
        connect(data_model, SIGNAL(layoutChanged()), this, SLOT(updateFileList()));
        connect(pushButton,SIGNAL(clicked()),this,SLOT(addNewItem()));
        connect(delData, SIGNAL(clicked()), this, SLOT(removeSelectedItem()));
        connect(upButton, SIGNAL(clicked()), this, SLOT(moveUpSelectedItem()));
        connect(downButton, SIGNAL(clicked()), this, SLOT(moveDownSelectedItem()));
}

// FUncion Obten nombres de archivos, para copiarlos posteriormente al directorio seleccionado y generar la leccion
//Recibe: nada	Devuleve: Lista de Archivos (QStringList)
void OriginData::addNewItem()
{
  QStringList file_list = QFileDialog::getOpenFileNames(this,tr("Select VMD molecules Files"),QDir::homePath(),tr("VMD Files(*.pdb *.psf)"));
  QStringList::const_iterator file_i;
  int row;
  //lineEdit->setText("");
  
  for (file_i=file_list.begin();file_i!=file_list.end();file_i++) {
    QFile arch(*file_i);
    if(arch.exists())
      {
	//Insert new row at the end of data_model and copy data
        row = data_model->rowCount();
        if ( data_model->insertRows(row, 1) == true ) {
            QModelIndex index = data_model->index(row);
            data_model->setData(index, *file_i, Qt::EditRole);
            data_model->setData(index, *file_i, Qt::DisplayRole);
            data_model->setData(index, *file_i, Qt::ToolTipRole);
            data_model->setData(index, *file_i, Qt::WhatsThisRole);

            //Set selection to the row just inserted
            dataList->setCurrentIndex(index);
        }
      }
  }
}

//Remove selected item from list of selected items
void OriginData::removeSelectedItem(){
  data_model->removeRows(dataList->currentIndex().row(), 1);
}

/* Move the selected item one position up or down according to
   boolean move_up flag. Insert a new row on the desired
   position, copy data, remove the old row and set the new
   position as currentIndex at finalList QListView.
*/
void OriginData::moveSelectedItem(bool move_up){
  QModelIndex origin_index;
  int row = dataList->currentIndex().row();

  if (data_model->moveRow(row, move_up))
    {
      //Erase old row and set currentIndex to new row
      if (move_up)
	{
	  dataList->setCurrentIndex(data_model->index(row-1));
	}
      else
	{
	  dataList->setCurrentIndex(data_model->index(row+1));
	}
    }
}

//Move selected item upside
void OriginData::moveUpSelectedItem(){
  moveSelectedItem(true);
}

//Move selected item downside
void OriginData::moveDownSelectedItem(){
  moveSelectedItem(false);
}

void OriginData::updateFileList() {
  QString files;
  QModelIndex index;
  int rows = data_model->rowCount();
  for (int i=0;i<rows;i++)
    {
      if (i>0)
	files.append(";");
      index = data_model->index(i);
      files.append(data_model->data(index, Qt::EditRole).toString());
    }
  lineEdit->setText(files);
}
