/**
 * File name: Dialog.cpp
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor <http://iuriepage.wordpress.com>
 *
 * This file is part of Redkite.
 *
 * Redkite is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "RkMain.h"
#include "RkWidget.h"
#include "RkLog.h"

#include <vector>

int main(int arc, char **argv)
{
        RkMain app(arc, argv);

        // Create main window.
        auto mainWindow = new RkWidget(&app);
        mainWindow->setTitle("Main Window");
	mainWindow->setPosition(180, 180);
        mainWindow->setSize(400, 500);

        auto child = new RkWidget(mainWindow);
        child->setTitle("Child");
        child->setBackgroundColor(80, 255, 80);
        child->setPosition(10, 10);
        child->setSize(50, 50);
        child->show();

        auto modal = new RkWidget(mainWindow, Rk::WindowFlags::Dialog);
        modal->setTitle("Dialog");
        modal->setBackgroundColor(80, 80, 80);
        modal->setSize(170, 110);

        child = new RkWidget(modal);
        child->setTitle("Child on Modal");
        child->setBackgroundColor(80, 80, 255);
        child->setPosition(10, 10);
        child->setSize(50, 50);
        child->show();

        mainWindow->show();
        modal->show();

        int res = app.exec();
        return res;
}


