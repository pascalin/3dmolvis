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
#include "MRoleStringListModel.h"


MRoleStringListModel::MRoleStringListModel(QObject *parent):QAbstractListModel(parent) {
}

int MRoleStringListModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;

    return lst.size();
}

QVariant MRoleStringListModel::data(const QModelIndex &index, int role) const {
  if (index.row() < 0 || index.row() >= lst.size())
        return QVariant();

  if (lst.at(index.row()).contains(role))
    return *(lst.at(index.row()).value(role));

  return QVariant();
}

bool MRoleStringListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  QVariant *val = new QVariant(value);
  LItem *tmp;

  if (index.row() >= 0 && index.row() < lst.size()) {
    tmp = new LItem(lst.at(index.row()));
    tmp->insert(role, val);
    lst.replace(index.row(), *tmp);
    emit dataChanged(index, index);
    return true;
  }
  return false;
}

bool MRoleStringListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if (count < 1 || row < 0 || row > rowCount(parent))
        return false;

    LItem *item = new LItem();
    item->insert(static_cast<int> (Qt::EditRole), new QVariant());

    beginInsertRows(QModelIndex(), row, row + count - 1);

    for (int r = 0; r < count; ++r)
      lst.insert(row, *item);

    endInsertRows();

    return true;
}

bool MRoleStringListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if (count <= 0 || row < 0 || (row + count) > rowCount(parent))
        return false;

    beginRemoveRows(QModelIndex(), row, row + count - 1);

    for (int r = 0; r < count; ++r)
        lst.removeAt(row);

    endRemoveRows();

    return true;
}

/* Move the selected row one position up or down according to
   boolean move_up flag.
*/
bool MRoleStringListModel::moveRow(int row, bool move_up)
{
  LItem temp;
  int orig_pos, dest_pos;

  //Check if row to be moved is inside the range 
  if (row < 0 || row >= lst.size())
        return false;

  //Check if move-up flag is activated, set origin and destination
  //positions according to the flag
  orig_pos = row;
  if (move_up) {
    if (row<=0)
      return false;
    dest_pos = row-1;
  }
  else {
    if (row>=(lst.size()-1))
      return false;
    dest_pos = row+1;
  }

  layoutAboutToBeChanged();

  //Copy destination item to temporary variable
  temp = lst.at(dest_pos);

  //Swap values
  lst.replace(dest_pos, lst.at(orig_pos));
  lst.replace(orig_pos, temp);

  layoutChanged();
  //Inform views about the change
  reset();

  return true;
}

QStringList MRoleStringListModel::stringList() const
{
  QStringList *list = new QStringList();

  for (LItemIterator i=lst.begin(); i!=lst.end(); ++i) {
    list->append(i->value(Qt::EditRole)->toString());
  }

  return *list;
}

void MRoleStringListModel::setStringList(const QStringList &strings)
{
  QList<LItem> *list = new QList<LItem>();
  LItem * value;

  for (QStringList::const_iterator i=strings.begin(); i!=strings.end(); ++i) {
    value = new LItem();
    value->insert(static_cast<int> (Qt::EditRole), new QVariant(*i));
    list->append(*value);
    delete value;
  }
  lst = *list;
  reset();
}
