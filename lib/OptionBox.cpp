// File : OptionBox.cpp


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


#include "OptionBox.h"

OptionButton::OptionButton(QString text, QString command, QWidget *parent) : QCheckBox(text, parent), command(command)
{
  connect(this, SIGNAL(toggled(bool)), this, SLOT(sendCommand(bool)));
}

void OptionButton::sendCommand(bool checked)
{
  if (checked)
    emit commandRaised(command+" 1");
  else
    emit commandRaised(command+" 0");
}

OptionBox::OptionBox(QWidget *parent) : QToolBox(parent)
{
  
}

// void OptionBox::addOption(QString name, QString command, int group)
// {
//   QVBoxLayout *layout;
//   OptionButton *button = new OptionButton(name, command);

//   if (!group_widgets.contains(group))
//     {
//       group_widgets.insert(group, new QWidget());
//       group_layouts.insert(group, new QVBoxLayout());
//       group_titles.insert(group, "");
//     }
//   layout = group_layouts[group];
//   layout->addWidget(button);

//   connect(button, SIGNAL(commandRaised(QString)), this, SLOT(sendCommand(QString)));
// }

// void OptionBox::setGroupTitle(int group, QString title)
// {
//   if (group_widgets.contains(group))
//     group_titles[group] = title;
// }

void OptionBox::sendCommand(QString comm)
{
  emit commandRaised(comm);
}

// void OptionBox::update()
// {
//   QList<int> keys = group_widgets.keys();
//   QList<int>::const_iterator i;

//   for (i=keys.begin();i!=keys.end();i++)
//     {
//       group_widgets[*i]->setLayout(group_layouts[*i]);
//       this->addItem(group_widgets[*i], group_titles[*i]);
//     }
// }

void OptionBox::clear()
{
  QWidget *wp;
  int i=currentIndex();

  while (i>=0)
    {
      wp = widget(i);
      removeItem(i);
      delete wp;
      i=currentIndex();
    }
}
