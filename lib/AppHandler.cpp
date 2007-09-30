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

AppHandler::AppHandler(QTreeWidget *tree, OptionBox *obox) : tree_widget(tree), obox_widget(obox)
{
  QStyle *style = tree_widget->style();
  
  folder_icon.addPixmap(style->standardPixmap(QStyle::SP_DirClosedIcon),
		       QIcon::Normal, QIcon::Off);
  folder_icon.addPixmap(style->standardPixmap(QStyle::SP_DirOpenIcon),
		       QIcon::Normal, QIcon::On);
  action_icon.addPixmap(style->standardPixmap(QStyle::SP_FileIcon));
  story_group = NULL;
}

bool AppHandler::startElement(const QString &namespaceURI,
                               const QString &localName,
                               const QString &qName,
                               const QXmlAttributes &attributes)
{
  OptionButton *ob;

  if (namespaceURI == "http://purl.org/dc/elements/1.1/")
    {
      current_text = "";
    }
  else if (namespaceURI == "http://vmdgui.sourceforge.net")
    {
      if (localName == "storyboard")
	{
	  
	}
      else if (localName == "group")
	{
	  if (story_group == NULL)
	    story_group = new QTreeWidgetItem(tree_widget);
	  else
	    story_group = new QTreeWidgetItem(story_group);
	  story_group->setIcon(0, folder_icon);
	  story_group->setData(0, Qt::DisplayRole, attributes.value("name"));
	  story_group->setData(0, Qt::UserRole, "group");
	}
      else if (localName == "action")
	{
	  story_item = new QTreeWidgetItem(story_group);
	  story_item->setIcon(0, action_icon);
	  story_item->setData(0, Qt::DisplayRole, attributes.value("title"));
	  story_item->setData(0, Qt::UserRole, "action");
	  story_item->setData(0, Qt::UserRole+1, attributes.value("command"));
	}
      else if (localName == "controls")
	{
	  
	}
      else if (localName == "control")
	{
	  controls << attributes.value("name");
	}
      else if (localName == "options")
	{
	  
	}
      else if (localName == "optgroup")
	{
	  opt_layout = new QVBoxLayout();
	  optgr_title = attributes.value("title");
	}
      else if (localName == "option")
	{
	  ob = new OptionButton(attributes.value("name"), attributes.value("command"));
	  QObject::connect(ob, SIGNAL(commandRaised(QString)), obox_widget, SLOT(sendCommand(QString)));
	  opt_layout->addWidget(ob);
	}
      else if (localName == "tclcode")
	{
	  current_text = "";
	}
    }

  return true;
}

bool AppHandler::endElement(const QString & namespaceURI,
                             const QString & localName,
                             const QString &qName)
{
  QWidget *wp;

  if (namespaceURI == "http://purl.org/dc/elements/1.1/")
    {
      if (localName == "title")
	{
	  properties["title"] = current_text;
	}      
      else if (localName == "publisher")
	{
	  properties["publisher"] = current_text;	  
	}      
    }
  else if (namespaceURI == "http://vmdgui.sourceforge.net")
    {
      if (localName == "storyboard")
	{
	  
	}
      else if (localName == "group")
	{
	  story_group = story_group->parent();
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
      else if (localName == "options")
	{
	  
	}
      else if (localName == "optgroup")
	{
	  wp = new QWidget();
	  wp->setLayout(opt_layout);
	  obox_widget->addItem(wp, optgr_title);
	}
      else if (localName == "option")
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

bool AppHandler::hasOptions()
{
  return false;
}

QString AppHandler::getOptions()
{
  return "";
}

QString AppHandler::getProperty(QString name)
{
  return properties[name];
}

bool AppHandler::hasControls()
{
  return !controls.isEmpty();
}

QStringList AppHandler::getControlList()
{
  return controls;
}
