// File : AnimateWidget.cpp


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


#include "AnimateWidget.h"

AnimateWidget::AnimateWidget(QWidget *parent)
{
  title = tr("Animation");
  description = tr("Allows users controlling of animations (play, pause, stop, repeat, etc.)");
  init_code = "";
  if (parent)
    setParent(parent);
  setupUi(this);
  fw_dir = true;
  connect(start_button, SIGNAL(clicked()), this, SLOT(gotoStart()));
  connect(end_button, SIGNAL(clicked()), this, SLOT(gotoEnd()));
  connect(pause_button, SIGNAL(clicked(bool)), this, SLOT(setPause(bool)));
  connect(repeat_button, SIGNAL(clicked(bool)), this, SLOT(setRepeat(bool)));
  connect(reverse_button, SIGNAL(clicked()), this, SLOT(reverse()));
  connect(forward_button, SIGNAL(clicked()), this, SLOT(forward()));
  connect(speed_box, SIGNAL(valueChanged(int)), this, SLOT(setSpeed(int)));
}

void AnimateWidget::gotoStart()
{
  pause_button->setChecked(true);
  emit commandRaised("animate pause;animate goto start");
}


void AnimateWidget::gotoEnd()
{
  pause_button->setChecked(true);
  emit commandRaised("animate pause;animate goto end");
}


void AnimateWidget::setPause(bool pause)
{
  if (pause)
    emit commandRaised("animate pause");
  else
    {
      if (fw_dir)
	forward();
      else
	reverse();
    }
}


void AnimateWidget::setRepeat(bool repeat)
{
  if (repeat)
    emit commandRaised("animate style loop");
  else
    emit commandRaised("animate style once");
}


void AnimateWidget::reverse()
{
  fw_dir = false;
  pause_button->setChecked(false);
  emit commandRaised("animate reverse");
}


void AnimateWidget::forward()
{
  fw_dir = true;
  pause_button->setChecked(false);
  emit commandRaised("animate forward");
}


void AnimateWidget::setSpeed(int speed)
{
  emit commandRaised(QString("animate skip %1").arg(speed));
}
