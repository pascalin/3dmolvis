// File : AppHandler.h


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


#ifndef APPHANDLER_H
#define APPHANDLER_H

#include <QtGui>
#include <QXmlDefaultHandler>
#include <QTreeWidget>
#include <QIcon>

class AppHandler : public QXmlDefaultHandler
{
public:
    AppHandler(QTreeWidget *tree);
    bool startElement(const QString &namespaceURI, const QString &localName,
                      const QString &qName, const QXmlAttributes &attributes);
    bool endElement(const QString &namespaceURI, const QString &localName,
                    const QString &qName);
    bool characters(const QString &str);
    bool fatalError(const QXmlParseException &exception);
    QString errorString() const;
    bool hasTclCode();
    QString getTclCode();
    bool hasStoryboard();
    QString getStoryboard();
    bool hasControls();
    QStringList getControlList();

private:
    QStringList controls;
    QString tcl_code;
    QString current_text;
    QString error_str;
    QTreeWidget *tree_widget;
    QTreeWidgetItem *cur_group, *cur_item;
    int tree_level;
    QIcon folder_icon, action_icon;
};

#endif
