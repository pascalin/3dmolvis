/*
 *  WidgetSelect.cpp
 *  wizard
 *
 *  Created by Alejandro Mata Sánchez on 21/12/07.
 *  Copyright 2007 All rights reserved.
 *  Modified by David Suarez Pascal on 02/08/2009
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
#include "WidgetSelect.h"

/*This class defines a QWizardPage which allow users to edit the list
  of selected widgets it employs two instances of MRoleStringListModel
  to keep track of both the library of available widgets and user
  selected widgets. The user can add new items to the list of selected
  widgets, change order and delete selected items.
*/
WidgetSelect::WidgetSelect(QWidget *parent) : QWizardPage(parent)
{
	setupUi( this );
	QStringList widget_list;
	QStringList::const_iterator widget_i;

	widget_model = new MRoleStringListModel();
	selected_widget_model = new MRoleStringListModel();

	finalList->setModel(selected_widget_model);

	setTitle(tr("Select Widgets for your lesson"));
	setSubTitle(tr("Select from our widget library"));

	/**TODO:**
	 *) La lista de widgets deberia generarse dinamicamente a partir de los
	 widgets registrados en el WidgetManager (WidgetManager::getWidgetList())
	 hay que revisar los detalles del disenho. Si WidgetManager no ha sido
	 definido como una clase estatica y global, eso deberia hacerse primero.
	*/ 

        wid = new WidgetManager();
	widget_list = wid->getWidgetList();

	for ( widget_i=widget_list.begin(); widget_i!=widget_list.end(); ++widget_i ) {
	  int row = widget_model->rowCount();
	  if ( widget_model->insertRows(row, 1) == true ) {
	    QModelIndex index = widget_model->index(row);
	    widget_model->setData(index, *widget_i, Qt::EditRole);
 	    widget_model->setData(index, wid->getTitleByName(*widget_i), Qt::DisplayRole);
 	    widget_model->setData(index, wid->getDescriptionByName(*widget_i), Qt::ToolTipRole);
 	    widget_model->setData(index, wid->getDescriptionByName(*widget_i), Qt::WhatsThisRole);
	  }
	}

	widgetList->setModel(widget_model);

        delete wid;

	connect(selected_widget_model, SIGNAL(rowsInserted(const QModelIndex & , int , int)), this, SIGNAL(completeChanged()));
	connect(selected_widget_model, SIGNAL(rowsRemoved(const QModelIndex & , int , int)), this, SIGNAL(completeChanged()));
	connect(widgetList, SIGNAL(currentIndexChanged(int)), this, SLOT(changeWidgetDescription(int)));
	connect(delWidget, SIGNAL(clicked()), this, SLOT(removeSelectedItem()));
	connect(addWidget, SIGNAL(clicked()), this, SLOT(addSelectedItem()));
	connect(upButton, SIGNAL(clicked()), this, SLOT(moveUpSelectedItem()));
	connect(downButton, SIGNAL(clicked()), this, SLOT(moveDownSelectedItem()));
}

//Copy selected item on widgetList QComboBox from widget_model to
//selected_widget_model
void WidgetSelect::addSelectedItem(){
  //Get row to insert new item
  int row = selected_widget_model->rowCount();
  //Set origin and destination indexes
  QModelIndex origin_index = widget_model->index(widgetList->currentIndex()),
    dest_index = widget_model->index(row);

  //Insert new row at the end of selected_widget_model and copy data
  selected_widget_model->insertRows(row, 1);
  selected_widget_model->setData(dest_index, widget_model->data(origin_index, Qt::EditRole), Qt::EditRole);
  selected_widget_model->setData(dest_index, widget_model->data(origin_index, Qt::DisplayRole), Qt::DisplayRole);
  selected_widget_model->setData(dest_index, widget_model->data(origin_index, Qt::ToolTipRole), Qt::ToolTipRole);
  selected_widget_model->setData(dest_index, widget_model->data(origin_index, Qt::WhatsThisRole), Qt::WhatsThisRole);
}

//Remove selected item from list of selected items
void WidgetSelect::removeSelectedItem(){
  selected_widget_model->removeRows(finalList->currentIndex().row(), 1);
}

/* Move the selected item one position up or down according to
   boolean move_up flag. Insert a new row on the desired
   position, copy data, remove the old row and set the new
   position as currentIndex at finalList QListView.
*/
void WidgetSelect::moveSelectedItem(bool move_up){
  QModelIndex origin_index;//, dest_index;
  int row = finalList->currentIndex().row();

  if (selected_widget_model->moveRow(row, move_up))
    {
      //Erase old row and set currentIndex to new row
      if (move_up)
	{
	  finalList->setCurrentIndex(selected_widget_model->index(row-1));
	}
      else
	{
	  finalList->setCurrentIndex(selected_widget_model->index(row+1));
	}
    }
}

//Move selected item upside
void WidgetSelect::moveUpSelectedItem(){
  moveSelectedItem(true);
}

//Move selected item downside
void WidgetSelect::moveDownSelectedItem(){
  moveSelectedItem(false);
}

//Display description of selected widget on label widgetDescLabel
void WidgetSelect::changeWidgetDescription(int row) {
  QModelIndex index = widget_model->index(row);
  widgetDescLabel->setText(widget_model->data(index, Qt::WhatsThisRole).toString());
}

//Check if finalList has items and return true, else return false. It
//is checked by QWizard to enable Next button
bool WidgetSelect::isComplete() const {
  if (selected_widget_model->rowCount()>0)
    return true;
  return false;
}
