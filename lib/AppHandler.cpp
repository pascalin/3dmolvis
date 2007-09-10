// File : AppHandler.cpp


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


#include "AppHandler.h"

AppHandler::AppHandler(QTreeWidget *tree) : tree_widget(tree)
{
  QStyle *style = tree_widget->style();
  
  folder_icon.addPixmap(style->standardPixmap(QStyle::SP_DirClosedIcon),
		       QIcon::Normal, QIcon::Off);
  folder_icon.addPixmap(style->standardPixmap(QStyle::SP_DirOpenIcon),
		       QIcon::Normal, QIcon::On);
  action_icon.addPixmap(style->standardPixmap(QStyle::SP_FileIcon));
  cur_group = NULL;
}

bool AppHandler::startElement(const QString &namespaceURI,
                               const QString &localName,
                               const QString &qName,
                               const QXmlAttributes &attributes)
{
  if (namespaceURI == "http://vmdgui.sourceforge.net")
    {
      if (localName == "storyboard")
	{
	  
	}
      else if (localName == "group")
	{
	  if (cur_group == NULL)
	    cur_group = new QTreeWidgetItem(tree_widget);
	  else
	    cur_group = new QTreeWidgetItem(cur_group);
	  cur_group->setIcon(0, folder_icon);
	  cur_group->setData(0, Qt::DisplayRole, attributes.value("name"));
	  cur_group->setData(0, Qt::UserRole, "group");
	  tree_level++;
	}
      else if (localName == "action")
	{
	  cur_item = new QTreeWidgetItem(cur_group);
	  cur_item->setIcon(0, action_icon);
	  cur_item->setData(0, Qt::DisplayRole, attributes.value("title"));
	  cur_item->setData(0, Qt::UserRole, "action");
	  cur_item->setData(0, Qt::UserRole+1, attributes.value("command"));
	}
      else if (localName == "controls")
	{
	  
	}
      else if (localName == "control")
	{
	  controls << attributes.value("name");
	}
      else if (localName == "tclcode")
	{
	  
	}
    }

  return true;
}

bool AppHandler::endElement(const QString & namespaceURI,
                             const QString & localName,
                             const QString &qName)
{
  if (namespaceURI == "http://vmdgui.sourceforge.net")
    {
      if (localName == "storyboard")
	{
	  
	}
      else if (localName == "group")
	{
	  //if (tree_level > 0)
	  cur_group = cur_group->parent();
	  //else
	  //  cur_group = NULL;
	  tree_level--;
	}
      else if (localName == "action")
	{
	  
	}
      else if (localName == "controls")
	{
	  
	}
      else if (localName == "control")
	{
	  
	}
      else if (localName == "tclcode")
	{
	  tcl_code = current_text;
	}
    }

  return true;
}

bool AppHandler::characters(const QString &str)
{
  current_text += str;
  return true;
}

bool AppHandler::fatalError(const QXmlParseException &exception)
{
  QMessageBox::information(tree_widget->window(), QObject::tr("VMDGui Application"),
			   QObject::tr("Parse error at line %1, column %2:\n"
				       "%3")
			   .arg(exception.lineNumber())
			   .arg(exception.columnNumber())
			   .arg(exception.message()));
  return false;
}

QString AppHandler::errorString() const
{
  return error_str;
}

// QTreeWidgetItem *AppHandler::createChildItem(const QString &tagName)
// {
//     QTreeWidgetItem *childItem;
//     if (item) {
//         childItem = new QTreeWidgetItem(item);
//     } else {
//         childItem = new QTreeWidgetItem(treeWidget);
//     }
//     childItem->setData(0, Qt::UserRole, tagName);
//     return childItem;
// }

bool AppHandler::hasTclCode()
{
  return !tcl_code.isEmpty();
}

QString AppHandler::getTclCode()
{
  return tcl_code;
}

bool AppHandler::hasStoryboard()
{
  return false;
}

QString AppHandler::getStoryboard()
{
  return "";
}

bool AppHandler::hasControls()
{
  return !controls.isEmpty();
}

QStringList AppHandler::getControlList()
{
  return controls;
}
