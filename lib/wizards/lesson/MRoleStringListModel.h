// File : MRoleStringListModel.h


//	Copyright (C) 2009 David Suarez Pascal
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
#ifndef MROLESTRINGLISTMODEL_H
#define MROLESTRINGLISTMODEL_H

#include <QtGui>


typedef QMap<int, QVariant *> LItem;
typedef QList<LItem>::const_iterator LItemIterator;

class MRoleStringListModel : public QAbstractListModel {
    Q_OBJECT
public:
  MRoleStringListModel(QObject *parent = 0);

  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  
  QVariant data(const QModelIndex &index, int role) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
  
  //  Qt::ItemFlags flags(const QModelIndex &index) const;
  
  bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
  bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

  bool moveRow(int row, bool move_up);

  //void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);

  QStringList stringList() const;
  void setStringList(const QStringList &list);

  //Qt::DropActions supportedDropActions() const;
private:
  QList<LItem> lst;
};

#endif
