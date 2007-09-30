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

/*
 * AppHandler es una subclase de QXmlDefaultHandler que implementa el
 * manejo de las llamadas startElement y endElement en el estilo de
 * SAX, extrayendo la informacion requerida de los archivos de
 * aplicacion XML que contiene los widgets que se requieren, un
 * storyboard y una seccion de opciones que pueden ser o no requeridos
 * por una aplicacion. Esta clase tambien extrae el codigo de
 * inicializacion Tcl incluido con la aplicacion.
 */

#ifndef APPHANDLER_H
#define APPHANDLER_H

#include <QtGui>
#include <QXmlDefaultHandler>
#include <QTreeWidget>
#include <QIcon>
#include "OptionBox.h"

class AppHandler : public QXmlDefaultHandler
{
public:
    AppHandler(QTreeWidget *tree, OptionBox *obox);
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
    bool hasOptions();
    QString getOptions();
    QString getProperty(QString);

private:
    QStringList controls;
    QString tcl_code;
    QString current_text;
    QString error_str;
    QMap<QString,QString> properties;
    QTreeWidget *tree_widget;
    OptionBox *obox_widget;
    QTreeWidgetItem *story_group, *story_item;
    QVBoxLayout *opt_layout;
    QString optgr_title;
    QIcon folder_icon, action_icon;
};

#endif
